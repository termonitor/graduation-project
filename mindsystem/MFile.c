#include "MFile.h"

extern FILE* fp_small;
extern FILE* fp_big;

void initFile()
{
	//判断是否存在数据存储文件夹
	if(access(DATA_DIR, F_OK) != 0)
	{
		mkdir(DATA_DIR, 0755);
	}
	//如果存在文件夹不存在配置文件，则创建配置文件,并初始化
	if(access(DATA_NUM_LOG, F_OK) != 0)
	{
		FILE* fp_config = fopen(DATA_NUM_LOG, "at");
		fwrite("num=0", 1, strlen("num=0"), fp_config);
		fclose(fp_config);
	}
	//判断是否存在上次未存储的文件，根据配置更改文件名。
	FILE* fp_config = fopen(DATA_NUM_LOG, "rt+");
	char buffer[1024];
	int filesize = -1;
	fseek(fp_config, 0, SEEK_END);
	filesize = ftell(fp_config);
	fseek(fp_config, 0, SEEK_SET);
	//取出配置文件中的信息，存在buffer中
	fread(buffer, 1, filesize, fp_config);
	//计算当前编号，存在num
	int num = 0;
	int i;
	for(i=0; i<filesize; i++)
	{
		if(buffer[i]>='0' && buffer[i]<='9')
		{
			num *= 10;
			num += buffer[i] - '0';
		}
	}
	int flag = 0;
	if(access(DATA_SMALL, F_OK) == 0)
	{
		memset(buffer, '\0', sizeof(buffer));
//		snprintf(buffer, 1024, "/mnt/SD/old/test/DataStorge/small_%d", num);
		snprintf(buffer, 1024, "/root/mindsystem/DataStorge/small_%d", num);
		rename(DATA_SMALL, buffer);
		flag = 1;
	}
	if(access(DATA_BIG, F_OK) == 0)
	{
		memset(buffer, '\0', sizeof(buffer));
//		snprintf(buffer, 1024, "/mnt/SD/old/test/DataStorge/big_%d", num);
		snprintf(buffer, 1024, "/root/mindsystem/DataStorge/big_%d", num);
		rename(DATA_BIG, buffer);
		flag = 1;
	}
	if(flag == 1)
	{
		fseek(fp_config, 0, SEEK_SET);
		memset(buffer, '\0', sizeof(buffer));
		num++;
		snprintf(buffer, 1024, "num=%d", num);
		fwrite(buffer, 1, strlen(buffer), fp_config);
	}
	//关闭配置文件句柄
	fclose(fp_config);
	//新建文件small和big并获取句柄。
	fp_small = fopen(DATA_SMALL, "wt+");
	fp_big = fopen(DATA_BIG, "wt+");
	memset(buffer, '\0', sizeof(buffer));
	snprintf(buffer, 1024, "Raw\n");
	fwrite(buffer, 1, strlen(buffer), fp_small);
	memset(buffer, '\0', sizeof(buffer));
	snprintf(buffer, 1024, "Attention	Meditation	PoorSignal	Delta	Theta	LowAlpha	HighAlpha	LowBeta	HighBeta	LowGamma	MiddleGamma\n");
	fwrite(buffer, 1, strlen(buffer), fp_big);
}

void closeFile()
{
	fclose(fp_small);
	fclose(fp_big);
}