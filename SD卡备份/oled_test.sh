#!/bin/bash
mknod /dev/zed_oled c 252 0
cat logo.bin > /dev/zed_oled
