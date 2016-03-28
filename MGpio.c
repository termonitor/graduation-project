#include "MGpio.h"

extern int fd_export;
extern int fd_led[8];
extern int fd_led_value[8];
extern int fd_sw[8];
extern char ld_number[8][3];
extern char sw_number[8][3];

void initGpio()
{
	//获取export的句柄，并初始化61-76的gpio口
	fd_export  = open(M_GPIO_EXPORT, O_WRONLY);
	for(int i=0; i<8; i++)
	{
		write(fd_export, ld_number[i], sizeof(ld_number[i]));
		write(fd_export, sw_number[i], sizeof(ld_number[i]));
	}
	//获取led灯的方向句柄，并将输入方向设置为out
	fd_led[0] = open(M_GPIO_DIRECTION(61), O_RDWR);
	fd_led[1] = open(M_GPIO_DIRECTION(62), O_RDWR);
	fd_led[2] = open(M_GPIO_DIRECTION(63), O_RDWR);
	fd_led[3] = open(M_GPIO_DIRECTION(64), O_RDWR);
	fd_led[4] = open(M_GPIO_DIRECTION(65), O_RDWR);
	fd_led[5] = open(M_GPIO_DIRECTION(66), O_RDWR);
	fd_led[6] = open(M_GPIO_DIRECTION(67), O_RDWR);
	fd_led[7] = open(M_GPIO_DIRECTION(68), O_RDWR);
	for(int i=0; i<8; i++)
	{
		write(fd_led[i], "out", sizeof("out"));
	}
	//获取led灯的值句柄，并初始化为0
	fd_led_value[0] = open(M_GPIO_VALUE(61), O_RDWR);
	fd_led_value[1] = open(M_GPIO_VALUE(62), O_RDWR);
	fd_led_value[2] = open(M_GPIO_VALUE(63), O_RDWR);
	fd_led_value[3] = open(M_GPIO_VALUE(64), O_RDWR);
	fd_led_value[4] = open(M_GPIO_VALUE(65), O_RDWR);
	fd_led_value[5] = open(M_GPIO_VALUE(66), O_RDWR);
	fd_led_value[6] = open(M_GPIO_VALUE(67), O_RDWR);
	fd_led_value[7] = open(M_GPIO_VALUE(68), O_RDWR);
	clearLed();
	//以只读的方式获取sw的值句柄
	fd_sw[0] = open(M_GPIO_VALUE(69), O_RDONLY);
	fd_sw[1] = open(M_GPIO_VALUE(70), O_RDONLY);
	fd_sw[2] = open(M_GPIO_VALUE(71), O_RDONLY);
	fd_sw[3] = open(M_GPIO_VALUE(72), O_RDONLY);
	fd_sw[4] = open(M_GPIO_VALUE(73), O_RDONLY);
	fd_sw[5] = open(M_GPIO_VALUE(74), O_RDONLY);
	fd_sw[6] = open(M_GPIO_VALUE(75), O_RDONLY);
	fd_sw[7] = open(M_GPIO_VALUE(76), O_RDONLY);
}

void clearLed()
{
	for(int i=0; i<8; i++)
	{
		write(fd_led_value[i], GPIO_FALSE, sizeof(GPIO_FALSE));
	}
}

void updateLed()
{
	//SW7专门用于启动脚本startup.sh，所以这里对于SW7不响应
	char sw_value;
	for(int i=0; i<7; i++)
	{
		sw_value = '0';
		read(fd_sw[i], &sw_value, sizeof(sw_value));
		if(sw_value == GPIO_TRUE)
			write(fd_led_value[i], GPIO_TRUE, sizeof(GPIO_TRUE));
	}
}

void setLedValue(int number, int status)
{
	if(status)
		write(fd_led_value[number], GPIO_TRUE, sizeof(GPIO_TRUE));
	write(fd_led_value[number], GPIO_FALSE, sizeof(GPIO_FALSE));
}