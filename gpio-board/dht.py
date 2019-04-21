#!/usr/bin/python

import sys
import Adafruit_DHT
from time import sleep

# Sensor type: dht22 or dht11
sensor = 22
# Sensor GPIO pin
pin = 26

humidity, ctemp = Adafruit_DHT.read_retry(sensor, pin)

while True:
  if humidity is not None and ctemp is not None:
    ftemp = ctemp * 9/5.0 + 32
    print('Temperature: {0:0.1f}C/{1:0.1f}F Humidity: {2:0.1f}%'.format(ctemp, ftemp, humidity))
  else:
    print('Failed to get reading.')
  sleep(2)
