# GPIO LEARNING BOARD

## INTRODUCTION

This is a simple board which connects to a Raspberry Pi (or compatible) computer's GPIO connector and provides some simple functions for experimenting with GPIO programming. The functions provided are:

1. Red, Green, and Yellow LEDs which can be individually turned on or off.
2. A pushbutton whose status can be read.
3. A DHT11 or DHT22 temperature/humidity sensor
4. A connector for an FTDI USB to serial adaptor which provides access to the Raspberry Pi's serial port/console.

It is compatible with the Raspberry Pi 2 or 3. It is not compatible with the Raspberry Pi version 1 which had a smaller GPIO connector. It should work with the Raspberry Pi Zero if it has a GPIO header installed.

The board is compatible with the GPIO connector on a Toradex Colibri i.MX6 series mounted on an Aster carrier board. Programming is slightly different from a Raspberry Pi as the GPIO devices names are numbered differently (see below).

## PARTS LIST

See the file bom.csv.

Make sure the tactile switch has the correct footprint for the PCB.

Either a DHT11 or DHT22 temperature/humidity sensor can be used (they differ in price and accuracy). This can be omitted if desired. You can solder a header if you don't want to permanently solder in the sensor.

Any suitable LEDs can be used. You may need to adjust the values of R3, R4, and R5 slightly to make all LEDs similar brightness, depending on the LEDs used.

The GPIO connector needs to be a suitable "female" connector to connect to the Raspberry Pi. A suitable part is http://adafru.it/2222

The optional FTDI connector will work with most FTDI breakout boards such as the AdaFruit FTDI Friend or DFRobot Basic Breakout. The power pin is not used so it doesn't matter if it is set for 3.3V or 5V.

## ASSEMBLY

All parts are through hole, making them easy to assemble. Note that the GPIO connector mounts on the bottom (non silk-screened) side of the board.

The suggested order of installing and soldering is:
- resistors
- LEDs
- pushbutton
- 6 pin SIP connector
- GPIO connector
- 4 pin SIP or DHT11/DHT22 sensor

The LEDs must be oriented correctly. Most LEDs have a flat side on the cathode pin which should be lined up to match the symbol on the silkscreen. Alternatively,
the longer lead indicates the anode which should be on the left when looking at the top of the component side of the board with the GPIO connector at the top.

Make sure all component leads are cut flush to the bottom of the board after soldering so they don't short anything when the board is installed on a Raspberry Pi.

## SOFTWARE

Raspberry Pi 2/3:

| Function   | P1 Pin | GPIO Name |
| ---------- | ------ | --------- |
| Red LED    | 18     | GPIO24    |
| Green LED  | 22     | GPIO25    |
| Yellow LED | 29     | GPIO5     |
| Switch     | 31     | GPIO6     |
| DHT        | 37     | GPIO26    |

Toradex i.MX6 series Colibri SOM with Aster carrier board:

| Function   | P1 Pin | GPIO Name |
| ---------- | ------ | --------- |
| Red LED    |   18   | GPIO52    |
| Green LED  |   22   | GPIO53    |
| Yellow LED |   28   | GPIO39    |
| Switch     |   31   | GPIO93    |
| DHT        |   37   | GPIO51    |

Sample programs for the Raspberry Pi (shell script and Python) are provided here. The DHT example requires downloading an AdaFruit DHT Python module.

To use the serial port, on the Raspberry Pi you can run raspi-config to enable a serial console and you should then be able to log in on the serial port using settings of 115200 bps 8N1.

## REFERENCES

1. https://learn.adafruit.com/dht/overview
2. http://www.circuitbasics.com/how-to-set-up-the-dht11-humidity-sensor-on-the-raspberry-pi/
3. https://www.adafruit.com/product/385
4. https://tutorials-raspberrypi.com/raspberry-pi-measure-humidity-temperature-dht11-dht22/
5. https://thepihut.com/blogs/raspberry-pi-tutorials/27968772-turning-on-an-led-with-your-raspberry-pis-gpio-pins
6. https://github.com/adafruit/Adafruit_Python_DHT
7. https://raspberrypihq.com/use-a-push-button-with-raspberry-pi-gpio/
8. https://www.raspberrypi.org/documentation/usage/gpio/python/README.md
9. https://gpiozero.readthedocs.io/en/stable/recipes.html
10. https://developer.toradex.com/knowledge-base/gpio-(linux)
11. https://developer.toradex.com/getting-started/module-3-hardware-peripherals/basic-gpio-usage-aster-carrier-board-colibri-imx6
