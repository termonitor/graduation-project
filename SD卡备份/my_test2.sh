#!/bin/bash
for i in {61..68}                                                               
do                                                                              
        echo 0 > /sys/class/gpio/gpio$i/value                                   
        sleep 1                                                                 
done 
