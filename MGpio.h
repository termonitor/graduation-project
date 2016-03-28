#ifndef __M_GPIO_H__
#define __M_GPIO_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define M_GPIO_EXPORT "/sys/class/gpio/export"
#define M_GPIO_DIRECTION(n) "/sys/class/gpio/gpio"#n"/direction"
#define M_GPIO_VALUE(n) "/sys/class/gpio/gpio"#n"/value"
#define GPIO_TRUE "1"
#define GPIO_FALSE "0"

int fd_export;
int fd_led[8];
int fd_led_value[8];
int fd_sw[8];
char ld_number[8][3] = {"61", "62", "63", "64", "65", "66", "67", "68"};
char sw_number[8][3] = {"69", "70", "71", "72", "73", "74", "75", "76"};
void initGpio();
void updateLed();
void clearLed();
void setLedValue(int number, int status);

#endif