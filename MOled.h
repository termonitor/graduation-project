#ifndef __M_OLED__
#define __M_OLED__

//body
int fd;					//用于存放/dev/zed_oled"的句柄
char oledImage[512];	//存放要输出的数组信息

void getOledFD();		//获取设备句柄
void printImage();		//输出函数
void setNum(int loc, int num);	//设置每个位置的数组信息
void handleNumber(int num);		//根据数字生成数组

#endif