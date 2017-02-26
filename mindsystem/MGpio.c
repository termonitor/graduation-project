#include "MGpio.h"

extern int fd_export;
extern int fd_led[8];
extern int fd_led_value[8];
extern int fd_sw[8];
char ld_number[8][3] = {"61", "62", "63", "64", "65", "66", "67", "68"};
char sw_number[8][3] = {"69", "70", "71", "72", "73", "74", "75", "76"};
extern char sw_status[8];
extern int function_status;
extern pthread_mutex_t mut;

void initGpio()
{
	int i;
	//获取export的句柄，并初始化61-76的gpio口
	fd_export  = open(M_GPIO_EXPORT, O_WRONLY);
	for(i=0; i<8; i++)
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
	for(i=0; i<8; i++)
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
	//初始化sw的状态值和LD的值
	for(i=0; i<8; i++)
	{
		sw_status[i] = '0';
		write(fd_led_value[i], GPIO_FALSE, sizeof(GPIO_FALSE));
	}
	//程序启动，说明SW7是开状态的
	sw_status[7] = '1';
	function_status = 0;
}

void closeGpio()
{
	int i;
	for(i=0; i<8; i++)
	{
		write(fd_led_value[i], GPIO_FALSE, sizeof(GPIO_FALSE));
	}
	for(i=0; i<8; i++)
	{
		close(fd_sw[i]);
		close(fd_led_value[i]);
		close(fd_led[i]);
	}
	close(fd_export);
	fd_export  = open(M_GPIO_UNEXPORT, O_WRONLY);
	//此处不用关闭gpio76，因为gpio76用于启动脚本，所以不必关闭
	for(i=0; i<8; i++)
	{
		write(fd_export, ld_number[i], sizeof(ld_number[i]));
		if(i != 7)
			write(fd_export, sw_number[i], sizeof(ld_number[i]));
	}
	close(fd_export);
}

void clearLed()
{
	int i;
	for(i=0; i<8; i++)
	{
		write(fd_led_value[i], GPIO_FALSE, sizeof(GPIO_FALSE));
	}
}

void rGetSWFD()
{
	int i;
	for(i=0; i<8; i++)
	{
		close(fd_sw[i]);
	}
	fd_sw[0] = open(M_GPIO_VALUE(69), O_RDONLY);
	fd_sw[1] = open(M_GPIO_VALUE(70), O_RDONLY);
	fd_sw[2] = open(M_GPIO_VALUE(71), O_RDONLY);
	fd_sw[3] = open(M_GPIO_VALUE(72), O_RDONLY);
	fd_sw[4] = open(M_GPIO_VALUE(73), O_RDONLY);
	fd_sw[5] = open(M_GPIO_VALUE(74), O_RDONLY);
	fd_sw[6] = open(M_GPIO_VALUE(75), O_RDONLY);
	fd_sw[7] = open(M_GPIO_VALUE(76), O_RDONLY);
}

void updateLed()
{
	int i;
	//SW7专门用于启动脚本startup.sh，所以这里对于SW7不响应
	char sw_value;
	//重新获取SW的句柄，因为每次读取设备文件后，读取位置会变，因此这里要关闭原有句柄，重新打开新句柄
	rGetSWFD();
	for(i=0; i<7; i++)
	{
		sw_value = '0';
		read(fd_sw[i], &sw_value, sizeof(sw_value));
		sw_status[i] = sw_value;
	}
	//根据sw_status更新function_status
	function_status = 0;
	for(i=0; i<7; i++)
	{
		if(sw_status[i] == '1')
			function_status += 1<<i;
	}
	if(function_status == 1)
		return;
	//将灯光点亮的工作后移。
	for(i=0; i<7; i++)
	{
		if(sw_status[i] == '1')
		{
			write(fd_led_value[i], GPIO_TRUE, sizeof(GPIO_TRUE));
		}
		else
		{
			write(fd_led_value[i], GPIO_FALSE, sizeof(GPIO_FALSE));
		}
	}
}

void* swThread()
{
	while(1)
	{
		pthread_mutex_lock(&mut);
		updateLed();
		pthread_mutex_unlock(&mut);
		sleep(3);
	}
}

void setLedValue(int number, int status)
{
	if(status)
	{
		write(fd_led_value[number], GPIO_TRUE, sizeof(GPIO_TRUE));
		return;
	}
	write(fd_led_value[number], GPIO_FALSE, sizeof(GPIO_FALSE));
}