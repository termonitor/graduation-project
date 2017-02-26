#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DATA_DIR "/mnt/SD/old/test/DataStorge"
#define DATA_NUM_LOG "/mnt/SD/old/test/DataStorge/.config"

int main()
{
	rename("/mnt/SD/old/test/test.txt", "/mnt/SD/old/test/test1.txt");
	if(access(DATA_DIR, F_OK) != 0)
	{
		mkdir(DATA_DIR, 0755);
	}
	if(access(DATA_NUM_LOG, F_OK) != 0)
	{
		FILE* fp_config = fopen(DATA_NUM_LOG, "at");
		fwrite("num=0", 1, strlen("num=0"), fp_config);
		fclose(fp_config);
	}
	FILE* fp_config = fopen(DATA_NUM_LOG, "rt+");
	char buffer[1024];
	int filesize = -1;
	fseek(fp_config, 0, SEEK_END);
	filesize = ftell(fp_config);
	fseek(fp_config, 0, SEEK_SET);
	fread(buffer, 1, filesize, fp_config);
	printf("%s\n", buffer);
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
	printf("%d\n", num);
	fseek(fp_config, 0, SEEK_SET);
	memset(buffer, '\0', sizeof(buffer));
	num++;
	snprintf(buffer, 1024,"num=%d", num);
	fwrite(buffer, 1, strlen(buffer), fp_config);
	fclose(fp_config);
	return 0;
}