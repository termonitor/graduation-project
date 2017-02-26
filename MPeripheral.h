#ifndef __M_PERIPHERAL_H__
#define __M_PERIPHERAL_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>

#define REG_NUM     11

int fd_knn;
int rd32_buf[REG_NUM];

void initPeripheral();
void closePeripheral();
void setPeripheralReg(int loc, int num);
void getPeripheralReg();
int getPeripheralResult();
int setPeripheralData(int a, int b, int c, int d, int e);

#endif