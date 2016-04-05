#ifndef __M_OLED_H__
#define __M_OLED_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

//body
int fd_oled;					//用于存放/dev/zed_oled"的句柄
char oledImage[512];	//存放要输出的数组信息

void clearImage();
void getOledFD();		//获取设备句柄
void closeOled();		//关闭设备句柄
void printImage();		//输出函数
void setNum(int loc, int num);	//设置每个位置的数组信息
void handleNumber(int num);		//根据数字生成数组

#endif