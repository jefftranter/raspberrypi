#!/usr/bin/python

from gpiozero import LED
from time import sleep
from gpiozero import Button

led1 = LED(2)
led2 = LED(3)
led3 = LED(4)
button = Button(18)

while True:
  # Make LEDs cycle in a binary count pattern.
  for i in range(8):
    if (i & 1):
      led3.on()
    else:
      led3.off()
    if (i & 2):
      led2.on()
    else:
      led2.off()
    if (i & 4):
      led1.on()
    else:
      led1.off()

    sleep(0.2)

    # Wait for button to be pressed (go low).
    while not button.is_pressed:
      pass
