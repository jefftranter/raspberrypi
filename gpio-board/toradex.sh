#!/bin/sh

# Demo for Toradex Colbri with Aster carrier board.
# Must be run as root, e.g under sudo.

# Pin assignments
led1=52
led2=53
led3=39
sw1=93

# Unexport pins to avoid errors if case they were already exported.
echo $led1 >/sys/class/gpio/unexport
echo $led2 >/sys/class/gpio/unexport
echo $led3 >/sys/class/gpio/unexport
echo $sw1 >/sys/class/gpio/unexport

# Export pins and set direction.
echo $led1 >/sys/class/gpio/export
echo out >/sys/class/gpio/gpio$led1/direction
echo $led2 >/sys/class/gpio/export
echo out >/sys/class/gpio/gpio$led2/direction
echo $led3 >/sys/class/gpio/export
echo out >/sys/class/gpio/gpio$led3/direction
echo $sw1 >/sys/class/gpio/export
echo in >/sys/class/gpio/gpio$sw1/direction

# Cycle LEDs and show switch level.
while true
do
  echo 0 >/sys/class/gpio/gpio$led1/value
  echo 0 >/sys/class/gpio/gpio$led2/value
  echo 0 >/sys/class/gpio/gpio$led3/value
  sleep 1
  echo 0 >/sys/class/gpio/gpio$led1/value
  echo 0 >/sys/class/gpio/gpio$led2/value
  echo 1 >/sys/class/gpio/gpio$led3/value
  sleep 1
  echo 0 >/sys/class/gpio/gpio$led1/value
  echo 1 >/sys/class/gpio/gpio$led2/value
  echo 0 >/sys/class/gpio/gpio$led3/value
  sleep 1
  echo 0 >/sys/class/gpio/gpio$led1/value
  echo 1 >/sys/class/gpio/gpio$led2/value
  echo 1 >/sys/class/gpio/gpio$led3/value
  sleep 1
  echo 1 >/sys/class/gpio/gpio$led1/value
  echo 0 >/sys/class/gpio/gpio$led2/value
  echo 0 >/sys/class/gpio/gpio$led3/value
  sleep 1
  echo 1 >/sys/class/gpio/gpio$led1/value
  echo 0 >/sys/class/gpio/gpio$led2/value
  echo 1 >/sys/class/gpio/gpio$led3/value
  sleep 1
  echo 1 >/sys/class/gpio/gpio$led1/value
  echo 1 >/sys/class/gpio/gpio$led2/value
  echo 0 >/sys/class/gpio/gpio$led3/value
  sleep 1
  echo 1 >/sys/class/gpio/gpio$led1/value
  echo 1 >/sys/class/gpio/gpio$led2/value
  echo 1 >/sys/class/gpio/gpio$led3/value
  sleep 1

  echo -n "switch = "
  cat /sys/class/gpio/gpio$sw1/value
done
