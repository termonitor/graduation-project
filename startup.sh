#!/bin/bash
if [ ! -d /sys/class/gpio/gpio76 ]; then
	echo 76 > /sys/class/gpio/export
fi
sw_value = cat /sys/class/gpio/gpio76/value;
while [$sw_value -eq 0]
do
	#wait 
done
if [sw_value -eq 1]; then
	#执行程序
	/mnt/SD/main
fi