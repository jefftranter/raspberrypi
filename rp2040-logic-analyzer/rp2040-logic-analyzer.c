/**
 * Modifed by Jeff Tranter <tranter@pobox.com>
 * Added ? and h commands.
 * Added support for saving captured data to a CSV file on an SD card.
 * Added more error checking of parameters.
 *
 * Modified by Mark Komus 2021
 * Now repeatedly captures data and outputs to a CSV format
 * Intended to be imported by sigrok / PulseView
 *
 */

/**
 *
 * Original code (found in the pico examples project):
 *
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hardware/clocks.h"

#include "sd_card.h"
#include "ff.h"
#include "f_util.h"

#ifndef LED_PIN
const uint LED_PIN = 25;
#endif

// Defaults - just what I tested with any legal value is fine
uint CAPTURE_PIN_BASE = 0;
uint CAPTURE_PIN_COUNT = 4;
uint CAPTURE_N_SAMPLES = 10000;
char FILENAME[16] = "OUTPUT.csv";
float FREQ_DIV = 125.0f; // Divide 125Mhz by this to get your freq
uint FREQUENCY = 1000000;
bool TRIGGER = false; // true = high : false = low


uint offset;
struct pio_program *capture_prog_2;

void logic_analyser_init(PIO pio, uint sm, uint pin_base, uint pin_count, float div) {
    // Load a program to capture n pins. This is just a single `in pins, n`
    // instruction with a wrap.
    uint16_t capture_prog_instr = pio_encode_in(pio_pins, pin_count);
    struct pio_program capture_prog = {
        .instructions = &capture_prog_instr,
        .length = 1,
        .origin = -1
    };
    capture_prog_2 = &capture_prog;

    offset = pio_add_program(pio, &capture_prog);

    // Configure state machine to loop over this `in` instruction forever,
    // with autopush enabled.
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_in_pins(&c, pin_base);
    sm_config_set_wrap(&c, offset, offset);
    sm_config_set_clkdiv(&c, div);
    sm_config_set_in_shift(&c, true, true, 32);
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_RX);
    pio_sm_init(pio, sm, offset, &c);
}

void logic_analyser_arm(PIO pio, uint sm, uint dma_chan, uint32_t *capture_buf, size_t capture_size_words,
                        uint trigger_pin, bool trigger_level) {
    pio_sm_set_enabled(pio, sm, false);
    pio_sm_clear_fifos(pio, sm);

    dma_channel_config c = dma_channel_get_default_config(dma_chan);
    channel_config_set_read_increment(&c, false);
    channel_config_set_write_increment(&c, true);
    channel_config_set_dreq(&c, pio_get_dreq(pio, sm, false));

    dma_channel_configure(dma_chan, &c,
        capture_buf,        // Destinatinon pointer
        &pio->rxf[sm],      // Source pointer
        capture_size_words, // Number of transfers
        true                // Start immediately
    );

    pio_sm_exec(pio, sm, pio_encode_wait_gpio(trigger_level, trigger_pin));
    pio_sm_set_enabled(pio, sm, true);
}

void print_capture_buf_csv(const uint32_t *buf, uint pin_base, uint pin_count, uint32_t n_samples) {
    FATFS *p_fs = malloc(sizeof(FATFS));

    FRESULT res = f_mount(p_fs, "", 0);
    if (res != FR_OK) {
        printf("SD card mount error: %s (%d)\n", FRESULT_str(res), res);
        return;
    }

    FIL fil;
    res = f_open(&fil, FILENAME, FA_WRITE|FA_CREATE_ALWAYS);
    if (res != FR_OK) {
        printf("file open error: %s (%d)\n", FRESULT_str(res), res);
        return;
    }

    for (int sample = 0; sample < n_samples; ++sample) {
        for (int pin = 0; pin < pin_count; ++pin) {
            uint bit_index = pin + sample * pin_count;
            bool level = !!(buf[bit_index / 32] & 1u << (bit_index % 32));
            f_printf(&fil, level ? "1" : "0");
            if (pin != pin_count-1) {
                f_printf(&fil, ",");
            }
        }
        f_printf(&fil, "\n");
    }

    res = f_close(&fil);
    if (res != FR_OK) {
        printf("file close error: %s (%d)\n", FRESULT_str(res), res);
        return;
    }

    res = f_unmount("");
    if (res != FR_OK) {
        printf("SD card unmount error: %s (%d)\n", FRESULT_str(res), res);
        return;
    }

    free(p_fs);
}

void read_user_input() {
    const int BUFFER_MAX = 16;
    char buffer[BUFFER_MAX+1];

    while (true) {
        memset(buffer, 0, BUFFER_MAX+1);
        int bufpos = 0;
        int c = 0;

        printf("%% ");
        stdio_flush();

        while (c != '\r') {
            c = getchar_timeout_us(30000000);
            if (c == -1) continue; // timeout ran out
            if (c == '\r' || c == '\n') break;

            buffer[bufpos++] = (char)c;
            printf("%c", c);
            if (bufpos >= BUFFER_MAX)
                break;
        }
        printf("\n");

        if (buffer[0] == 'p') {
            int pin = -1;
            if (isdigit(buffer[1]) != 0) {
                pin = strtol(buffer+1, NULL, 10);
                if (pin > 28)
                    pin = -1;
            }

            if (pin == -1)
                printf("Pin number is not valid\n");
            else {
                CAPTURE_PIN_BASE = pin;
            }
        }
        else if (buffer[0] == 'n') {
            int number = -1;
            if (isdigit(buffer[1]) != 0) {
                number = strtol(buffer+1, NULL, 10);
                if ((number == 0) || (number > 28))
                    number = -1;
            }

            if (number == -1)
                printf("Number of pins is not valid\n");
            else {
                CAPTURE_PIN_COUNT = number;
            }
        }
        else if (buffer[0] == 'f') {
            uint freq = 0;
            if (isdigit(buffer[1]) != 0) {
                freq = strtol(buffer+1, NULL, 10);
                if (freq > clock_get_hz(clk_sys))
                    freq = 0;
            }

            if (freq <= 0)
                printf("Frequency is not valid\n");
            else {
                FREQUENCY = freq;
                FREQ_DIV = clock_get_hz(clk_sys) / (float)FREQUENCY;
            }
        }
        else if (buffer[0] == 't') {
            int t = -1;
            if (buffer[1] == 't' || buffer[1] == '1')
                t = 1;
            else if (buffer[1] == 'f' || buffer[1] == '0')
                t = 0;

            if (t < 0)
                printf("Trigger value is not valid\n");
            else {
                TRIGGER = t;
            }
        }
        else if (buffer[0] == 's') {
            int number = -1;
            if (isdigit(buffer[1]) != 0) {
                number = strtol(buffer+1, NULL, 10);
                if (number < 0 || number > 500000)
                    number = -1;
            }

            if (number == -1)
                printf("Sample number is not valid\n");
            else {
                CAPTURE_N_SAMPLES = number;
            }
        }
        else if (buffer[0] == 'g') {
            break;
        }
        else if ((buffer[0] == 'c') && (strlen(buffer) > 2)) {
            strcpy(FILENAME, &buffer[1]);
        }
        else if (buffer[0] == '?') {
            printf("Current settings:\n");
            printf("First pin:      %d\n", CAPTURE_PIN_BASE);
            printf("Number of pins: %d\n", CAPTURE_PIN_COUNT);

            if (FREQUENCY >= 1e6) {
                printf("Frequency:      %f MHz\n", FREQUENCY / 1000000.0 );
            } else if (FREQUENCY >= 1e3) {
                printf("Frequency:      %f kHz\n", FREQUENCY / 1000.0 );
            } else {
                printf("Frequency:      %d Hz\n", FREQUENCY);
            }
            printf("Trigger level:  %d\n", TRIGGER);
            printf("Samples:        %d\n", CAPTURE_N_SAMPLES);
            printf("Filename:       %s\n", FILENAME);
        }
        else if (buffer[0] == 'h') {
            printf("p#        - Set the first pin to receive capture data\n");
            printf("n#        - Set how many pins to receive capture data\n");
            printf("f#        - Set the frequency to capture data in Hz\n");
            printf("t1|0      - Set the trigger to high or low (triggers on first pin)\n");
            printf("s#        - Set how many samples to capture\n");
            printf("cfilename - Set filename to save (default OUTPUT.csv)\n");
            printf("g         - Go!\n");
            printf("?         - show current parameters\n");
            printf("h         - Show command usage\n");
        }
        else {
            printf("Unknown command, type h for help\n");
        }
    }
}

int main() {
    stdio_init_all();
    sd_init_driver();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    uint32_t *capture_buf = 0;

    PIO pio = pio0;
    uint sm = 0;
    uint dma_chan = 0;

    sleep_ms(2000); // Allow time for serial connection to come up.
    printf("Raspberry Pi Pico Logic Analyzer ver 0.2\n");
    printf("Type h for help.\n");

    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(1000);
        gpio_put(LED_PIN, 0);

        read_user_input();

        uint32_t capture_buf_memory_size = (CAPTURE_PIN_COUNT * CAPTURE_N_SAMPLES + 31) / 32 * sizeof(uint32_t);
        capture_buf = malloc(capture_buf_memory_size);
        if (capture_buf == NULL) {
            printf("Error allocating capture buffer size %d\n", capture_buf_memory_size);
        }

        logic_analyser_init(pio, sm, CAPTURE_PIN_BASE, CAPTURE_PIN_COUNT, FREQ_DIV);

        uint32_t hz = clock_get_hz(clk_sys);
        float caphz = (float)hz / FREQ_DIV;

        printf("Arming trigger\n");
        gpio_put(LED_PIN, 1);

        logic_analyser_arm(pio, sm, dma_chan, capture_buf,
            (CAPTURE_PIN_COUNT * CAPTURE_N_SAMPLES + 31) / 32,
            CAPTURE_PIN_BASE, TRIGGER);

        dma_channel_wait_for_finish_blocking(dma_chan);

        gpio_put(LED_PIN, 0);
        printf("Data acquired\n");

        printf("Writing data to SD card...\n");
        print_capture_buf_csv(capture_buf, CAPTURE_PIN_BASE, CAPTURE_PIN_COUNT, CAPTURE_N_SAMPLES);
        printf("Data written to %s\n", FILENAME);

        pio_remove_program(pio, capture_prog_2, offset);

        free(capture_buf);
    }
}
