#ifndef __M_BASIC_H__
#define __M_BASIC_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/**
	基础库，放一些自己修改过的系统函数
**/

char* Mstrcpy(char* des, char*source, int len);

#endif