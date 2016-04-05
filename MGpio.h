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
#define M_GPIO_UNEXPORT "/sys/class/gpio/unexport"
#define GPIO_TRUE "1"
#define GPIO_FALSE "0"

int fd_export;
int fd_led[8];
int fd_led_value[8];
int fd_sw[8];
extern char ld_number[8][3];
extern char sw_number[8][3];
char sw_status[8];
int function_status;
void initGpio();
void updateLed();
void* swThread();
void closeGpio();
void clearLed();
void setLedValue(int number, int status);

#endif