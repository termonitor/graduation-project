#!/bin/bash
for i in {61..68}
do
	if [ ! -d /sys/class/gpio/gpio$i ]; then
		echo $i > /sys/class/gpio/export
	fi
done

for i in {61..68}
do
	echo out > /sys/class/gpio/gpio$i/direction
	echo 1 > /sys/class/gpio/gpio$i/value
	sleep 1
done

for i in {61..68}
do
	echo 0 > /sys/class/gpio/gpio$i/value
	sleep 1
done
