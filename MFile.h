#ifndef __M_FILE_H__
#define __M_FILE_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DATA_DIR "/mnt/SD/old/test/DataStorge"
#define DATA_NUM_LOG "/mnt/SD/old/test/DataStorge/.config"
#define DATA_SMALL "/mnt/SD/old/test/DataStorge/small"
#define DATA_BIG "/mnt/SD/old/test/DataStorge/big"

FILE* fp_small;
FILE* fp_big;

void initFile();
void closeFile();

#endif