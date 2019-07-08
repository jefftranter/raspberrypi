#!/usr/bin/python3
#
# Read temperature and humidity from a DHT11 or DHT22
# temperature/humidity sensor.
# Calculate the Heat Index.
# Indicate the Heat Level range using the three LEDs.
#
# Heat Levels
#
# Level            Range (F) LEDs
# ---------------  --------  ------------
# Safe             <80       Green
# Caution          80-90     Yellow
# Extreme Caution  90-105    Yellow flashing
# Danger           105-130   Red
# Extreme Danger   130+      Red flashing
#
# Jeff Tranter <tranter@pobox.com>

import Adafruit_DHT
from gpiozero import LED
from time import sleep

# Sensor type: DHT22 or DHT11
sensor = 11

# LED pins
red = LED(24)
green = LED(25)
yellow = LED(5)

# Sensor GPIO pin
pin = 26

# Constants for Heat Index calculation
c1 = -42.379
c2 = 2.04901523
c3 = 10.14333127
c4 = -0.22475541
c5 = -6.83783e-3
c6 = -5.481717e-2
c7 = 1.22874e-3
c8 = 8.5282e-4
c9 = -1.99e-6


# Convert temperature in C to F
def c_to_f(c):
    return c * 9.0/5.0 + 32.0


# Convert temperature in F to C
def f_to_c(f):
    return (f - 32.0) * 5.0/9.0


# Calculate heat index given temperature (F) and relative humidity.
# See https://en.wikipedia.org/wiki/Heat_index
def heat_index(t, r):
    return c1 + c2*t + c3*r + c4*t*r + c5*t*t + c6*r*r + c7*t*t*r + c8*t*r*r + c9*t*t*r*r


# Return the heat level range given the heat index in degrees F.
# Also turn the appropriate LEDs on.
def heat_level(t):
    if t < 80:
        green.on(); yellow.off(); red.off()
        return "Safe"
    elif t < 90:
        green.off(); yellow.on(); red.off()
        return "Caution"
    elif t < 105:
        green.off(); yellow.blink(); red.off()
        return "Extreme Caution"
    elif t < 130:
        green.off(); yellow.off(); red.on()
        return "Danger"
    else:
        green.off(); yellow.off(); red.blink()
        return "Extreme Danger"


while True:
    humidity, ctemp = Adafruit_DHT.read_retry(sensor, pin)
    if humidity is not None and ctemp is not None:
        ftemp = c_to_f(ctemp)
        print('Temperature: {0:0.1f}C/{1:0.1f}F Humidity: {2:0.1f}%'.format(ctemp, ftemp, humidity))
        hi = heat_index(ftemp, humidity)
        print('Heat index: {0:0.1f}C/{1:0.1f}F ({2})'.format(f_to_c(hi), hi, heat_level(hi)))
    else:
        print('Failed to get reading.')
    sleep(2)
