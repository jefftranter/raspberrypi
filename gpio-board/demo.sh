#!/bin/sh

# GPIO pin assignments
led1=2
led2=3
led3=4
sw1=18

# Make LED pins outputs
gpio -g mode $led1 out
gpio -g mode $led2 out
gpio -g mode $led3 out

# Make switch pin input
gpio -g mode $sw1 in

while true
do
    gpio -g write $led1 0
    gpio -g write $led2 0
    gpio -g write $led3 0
    sleep 1
    gpio -g write $led1 0
    gpio -g write $led2 0
    gpio -g write $led3 1
    sleep 1
    gpio -g write $led1 0
    gpio -g write $led2 1
    gpio -g write $led3 0
    sleep 1
    gpio -g write $led1 0
    gpio -g write $led2 1
    gpio -g write $led3 1
    sleep 1
    gpio -g write $led1 1
    gpio -g write $led2 0
    gpio -g write $led3 0
    sleep 1
    gpio -g write $led1 1
    gpio -g write $led2 0
    gpio -g write $led3 1
    sleep 1
    gpio -g write $led1 1
    gpio -g write $led2 1
    gpio -g write $led3 0
    sleep 1
    gpio -g write $led1 1
    gpio -g write $led2 1
    gpio -g write $led3 1
    sleep 1

    # Read switch
    echo -n "Switch = "
    gpio -g read $sw1
done
