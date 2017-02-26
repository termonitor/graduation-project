#include "MPeripheral.h"

extern int fd_knn;
extern int rd32_buf[REG_NUM];

void initPeripheral()
{
	fd_knn = open("/dev/my_knn_dev", 0);
}

void closePeripheral()
{
	close(fd_knn);
}

void setPeripheralReg(int loc, int num)
{
	ioctl(fd_knn, loc, num);
}

void getPeripheralReg()
{
	int i;
	char rd8_buf[REG_NUM*4];
	read(fd_knn, rd8_buf, sizeof(rd8_buf));
	for(i=0; i<REG_NUM; i++)
	{
		rd32_buf[i] = (int)rd8_buf[i*4] + ((int)rd8_buf[i*4+1]<<8) 
									+ ((int)rd8_buf[i*4+2]<<16) + ((int)rd8_buf[i*4+3]<<24);
	}
}

int getPeripheralResult()
{
	char rd8_buf[REG_NUM*4];
	read(fd_knn, rd8_buf, sizeof(rd8_buf));
	int result;
	result = (int)rd8_buf[40] + ((int)rd8_buf[41]<<8) + ((int)rd8_buf[42]<<16)+ ((int)rd8_buf[43]<<24);
	return result;
}

int setPeripheralData(int a, int b, int c, int d, int e)
{
	setPeripheralReg(0, a);
	setPeripheralReg(1, b);
	setPeripheralReg(3, c);
	setPeripheralReg(4, d);
	setPeripheralReg(5, e);
}