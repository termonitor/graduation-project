#!/bin/bash
if [ ! -d /sys/class/gpio/gpio76 ]; then
	echo 76 > /sys/class/gpio/export
fi
#simple-agent的注册
./simple-agent &
#my_knn模块的插入
insmod my_knn.ko
while [ "1" = "1" ];
do
	sw_value=`cat /sys/class/gpio/gpio76/value`;
	while [ $sw_value -eq 0 ];
	do
		sw_value=`cat /sys/class/gpio/gpio76/value`;
		#wait
	done;
	if [ $sw_value -eq 1 ]; then
		#执行程序
		/mnt/SD/test/main
	fi
done;
