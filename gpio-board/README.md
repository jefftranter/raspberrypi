                         GPIO LEARNING BOARD
                         ===================

INTRODUCTION

This is a simple board which connects to a Raspberry Pi (or
compatible) computer's GPIO connector and provides some simple
functions for experimenting with GPIO programming. The functions
provided are:

1. Red, Green, and Yellow LEDs which can be individually turned on or off.
2. A pushbutton whose status can be read.
3. A DHT11 or DHT22 temperature/humidity sensor
4. A connector for an FTDI USB to serial adaptor which provides access
   to the Raspberry Pi's serial port/console.

It is compatible with the Raspberry Pi 2 or 3. It is not compatible
with the Raspberry Pi version 1 which had a smaller GPIO connector.
It should work with the Raspberry Pi Zero.

TO DO

While the circuit has been tested on a breadboard, I have not yet
assembled or tested any PCBs.

The board should be compatible with the GPIO connector on a Toradex
i.MX series SOM mounted on a Colibri or Aster carrier board.
Programming is slightly different from a Raspberry Pi as the GPIO
devices names are numbered differently.

PARTS LIST

See the file bom.csv.

Make sure the tactile switch has the correct footprint for the PCB.

Either a DHT11 or DHT22 temperature/humidity sensor can be used (they
differ in price and accuracy). This can be omitted if desired. You can
solder a header if you don't want to permanently solder in the sensor.

Any suitable LEDs can be used. You may need to adjust the values of
R3, R4, and R5 slightly to make all LEDs similar brightness, depending
on the LEDs used.

The GPIO connector needs to be a suitable "female" connector to
connect to the Raspberry Pi.

The optional FTDI connector will work with most FTDI breakout boards
such as the AdaFruit FTDI Friend or DFRobot Basic Breakout. The power
pin is not used so it doesn't matter if it is set for 3.3V or 5V.

ASSEMBLY

All parts are through hole, not surface mount. Note that the GPIO
connector mounts on the bottom (non silk-screened) side of the board.

SOFTWARE

Function    P1 Pin  GPIO Name
----------  ------  ---------
Red LED        3    GPIO2
Green LED      5    GPIO3
Yellow LED     7    GPIO4
Switch        12    GPIO18
DHT           16    GPIO23

Sample programs (shell script and Python) are provided here. The DHT
example requires downloading a AdaFruit DHT Python module.

REFERENCES

https://learn.adafruit.com/dht/overview
http://www.circuitbasics.com/how-to-set-up-the-dht11-humidity-sensor-on-the-raspberry-pi/
https://www.adafruit.com/product/385
https://tutorials-raspberrypi.com/raspberry-pi-measure-humidity-temperature-dht11-dht22/
https://thepihut.com/blogs/raspberry-pi-tutorials/27968772-turning-on-an-led-with-your-raspberry-pis-gpio-pins
https://raspberrypihq.com/use-a-push-button-with-raspberry-pi-gpio/
https://www.raspberrypi.org/documentation/usage/gpio/python/README.md
https://gpiozero.readthedocs.io/en/stable/recipes.html
https://developer.toradex.com/knowledge-base/gpio-(linux)
https://developer.toradex.com/getting-started/module-3-hardware-peripherals/basic-gpio-usage-aster-carrier-board-colibri-imx6
