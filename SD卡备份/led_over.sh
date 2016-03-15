#!/bin/bash
for i in {61..68}
do
	if [ -d /sys/class/gpio/gpio$i ]; then
		echo 0 > /sys/class/gpio/gpio$i/value
		echo $i > /sys/class/gpio/unexport
	fi
done
