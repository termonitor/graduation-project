#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define M_GPIO_EXPORT "/sys/class/gpio/export"
#define M_GPIO_DIRECTION(n) "/sys/class/gpio/gpio"#n"/direction"
#define M_GPIO_VALUE(n) "/sys/class/gpio/gpio"#n"/value"
#define M_FD_LED_DIRECTION(n) fd_led_#n

int main()
{
	int fd_export  = open(M_GPIO_EXPORT, O_WRONLY);
	/*
	int i;
	for(i=61; i<69; i++)
		write(fd_export, ""+i, sizeof(""+i));
	for(i=69; i<77; i++)
		write(fd_export, ""+i, sizeof(""+i));
	*/
	write(fd_export, "61", sizeof("61"));
	write(fd_export, "62", sizeof("62"));
	write(fd_export, "63", sizeof("63"));
	write(fd_export, "64", sizeof("64"));
	write(fd_export, "65", sizeof("65"));
	write(fd_export, "66", sizeof("66"));
	write(fd_export, "67", sizeof("67"));
	write(fd_export, "68", sizeof("68"));
	write(fd_export, "69", sizeof("69"));
	write(fd_export, "70", sizeof("70"));
	write(fd_export, "71", sizeof("71"));
	write(fd_export, "72", sizeof("72"));
	write(fd_export, "73", sizeof("73"));
	write(fd_export, "74", sizeof("74"));
	write(fd_export, "75", sizeof("75"));
	write(fd_export, "76", sizeof("76"));
	
	int fd_led_0 = open(M_GPIO_DIRECTION(61), O_RDWR);
	int fd_led_1 = open(M_GPIO_DIRECTION(62), O_RDWR);
	int fd_led_2 = open(M_GPIO_DIRECTION(63), O_RDWR);
	int fd_led_3 = open(M_GPIO_DIRECTION(64), O_RDWR);
	int fd_led_4 = open(M_GPIO_DIRECTION(65), O_RDWR);
	int fd_led_5 = open(M_GPIO_DIRECTION(66), O_RDWR);
	int fd_led_6 = open(M_GPIO_DIRECTION(67), O_RDWR);
	int fd_led_7 = open(M_GPIO_DIRECTION(68), O_RDWR);

	write(fd_led_0, "out", sizeof("out"));
	write(fd_led_1, "out", sizeof("out"));
	write(fd_led_2, "out", sizeof("out"));
	write(fd_led_3, "out", sizeof("out"));
	write(fd_led_4, "out", sizeof("out"));
	write(fd_led_5, "out", sizeof("out"));
	write(fd_led_6, "out", sizeof("out"));
	write(fd_led_7, "out", sizeof("out"));
	
	int fd_led_value_0 = open(M_GPIO_VALUE(61), O_RDWR);
	int fd_led_value_1 = open(M_GPIO_VALUE(62), O_RDWR);
	int fd_led_value_2 = open(M_GPIO_VALUE(63), O_RDWR);
	int fd_led_value_3 = open(M_GPIO_VALUE(64), O_RDWR);
	int fd_led_value_4 = open(M_GPIO_VALUE(65), O_RDWR);
	int fd_led_value_5 = open(M_GPIO_VALUE(66), O_RDWR);
	int fd_led_value_6 = open(M_GPIO_VALUE(67), O_RDWR);
	int fd_led_value_7 = open(M_GPIO_VALUE(68), O_RDWR);

	write(fd_led_value_0, "0", sizeof("0"));
	write(fd_led_value_1, "0", sizeof("0"));
	write(fd_led_value_2, "0", sizeof("0"));
	write(fd_led_value_3, "0", sizeof("0"));
	write(fd_led_value_4, "0", sizeof("0"));
	write(fd_led_value_5, "0", sizeof("0"));
	write(fd_led_value_6, "0", sizeof("0"));
	write(fd_led_value_7, "0", sizeof("0"));
	
	int fd_sw_0 = open(M_GPIO_VALUE(69), O_RDONLY);
	int fd_sw_1 = open(M_GPIO_VALUE(70), O_RDONLY);
	int fd_sw_2 = open(M_GPIO_VALUE(71), O_RDONLY);
	int fd_sw_3 = open(M_GPIO_VALUE(72), O_RDONLY);
	int fd_sw_4 = open(M_GPIO_VALUE(73), O_RDONLY);
	int fd_sw_5 = open(M_GPIO_VALUE(74), O_RDONLY);
	int fd_sw_6 = open(M_GPIO_VALUE(75), O_RDONLY);
	int fd_sw_7 = open(M_GPIO_VALUE(76), O_RDONLY);
	
	char n;
	n = '0';
	read(fd_sw_0, &n, sizeof(n));
	if(n == '1')
		write(fd_led_value_0, "1", sizeof("1"));
	n = '0';
	read(fd_sw_1, &n, sizeof(n));
	if(n == '1')
		write(fd_led_value_1, "1", sizeof("1"));
	n = '0';
	read(fd_sw_2, &n, sizeof(n));
	if(n == '1')
		write(fd_led_value_2, "1", sizeof("1"));
	n = '0';
	read(fd_sw_3, &n, sizeof(n));
	if(n == '1')
		write(fd_led_value_3, "1", sizeof("1"));
	n = '0';
	read(fd_sw_4, &n, sizeof(n));
	if(n == '1')
		write(fd_led_value_4, "1", sizeof("1"));
	n = '0';
	read(fd_sw_5, &n, sizeof(n));
	if(n == '1')
		write(fd_led_value_5, "1", sizeof("1"));
	n = '0';
	read(fd_sw_6, &n, sizeof(n));
	if(n == '1')
		write(fd_led_value_6, "1", sizeof("1"));
	n = '7';
	read(fd_sw_7, &n, sizeof(n));
	if(n == '1')
		write(fd_led_value_7, "1", sizeof("1"));
	return 0;
}