This is a logic analyzer based on the Raspberry Pi Pico
microcontroller.

It is based on code by Mark Komus, which in turn extended the logic
analyzer example by the Raspberry Pi Foundation.

My version extends the commands and adds support for storing the
samples on an SD card attached to the Pico using a commonly available
SD card adaptor.

The samples are written to a file OUTPUT.csv on the SD card. These can
be loaded into applications on a desktop computer for analysis. For
example, it can be loaded into PulseView using a command like
"pulseview -i OUTPUT.csv -I csv:samplerate=2000000"

## Hardware Setup

| SD Adaptor | Pi Pico  | Pin |
| ---------- | -------  | --- |
| MISO       | GP16/RX  | 21  |
| CS         | GP17/CSn | 22  |
| GND        | GND      | 23  |
| SCK        | GP18/SCK | 24  |
| MOSI       | GP19/TX  | 25  |
| 3V3        | 3V3OUT   | 36  |

Note that the Pico input pins uses 3.3V logic and cannot accept other
levels such as 5V without level converters.

Note that you can't use GPIO pins 16 through 19 for logic analyzer
input since they are allocated to the SD card.

Building:

Set the environment variable PICO_SDK_PATH to the location of the
installed Pico SDK and build in the usual manner, e.g.

```
mkdir build
cd build
cmake ..
make
```

Put the Pico in boot mode and copy rp2040-logic-analyzer.uf2 to the
mounted folder.

References:

* https://www.hackster.io/markkomus/using-a-raspberry-pi-pico-as-a-logic-analyzer-with-pulseview-e12543
* https://github.com/gamblor21/rp2040-logic-analyzer/
* https://github.com/raspberrypi/pico-examples/tree/master/pio/logic_analyser
* https://github.com/carlk3/no-OS-FatFS-SD-SPI-RPi-Pico
* http://elm-chan.org/fsw/ff/00index_e.html
* https://sigrok.org/wiki/File_format:Csv

The original README.md file (with some changes) is below:

# rp2040-logic-analyzer

This project modified the PIO logic analyzer example that that was part of the 
Raspberry Pi Pico examples. The example now allows interactive configuration 
of the capture to perform and outputs the capture in CSV format suitable for
importing into sigrock / Pulseview for further analysis.

To use the analyzer install it on a Pico and connect to the COM port at 115200
baud. Once connected press h to get help of the commands. The capture is
only limited by the abilities of the Pico.

The commands are:
  * p#   - Set the first pin to receive capture data
  * n#   - Set how many pins to receive capture data
  * f#   - Set the frequency to capture data in Hz
  * t1|0 - Set the trigger to high or low (triggers on first pin)
  * s#   - Set how many samples to capture
  * g    - Go!
  * ?    - show current parameters
  * h    - Show command usage

Once "go" is selected the trigger will arm and wait for the specified signal.
The output is a CSV file, each line contains every pin being sampled.
