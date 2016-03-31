#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>

#define REG_NUM     2

int main()
{
	int my_test_fd = 0;
	int i, ret, buf[REG_NUM], rd32_buf[REG_NUM];
	char rd8_buf[REG_NUM*4];
	my_test_fd = open("/dev/my_test_dev", 0);
	if(my_test_fd<0)
	{
		printf("[ERROR] Can't open device.");
		return;
	}	
	printf("Open device. Filedescription of my_test_dev is %d\n",my_test_fd);
	printf("Input Reg0:");
	scanf("%d", &buf[0]);
	ioctl(my_test_fd, 0, buf[0]);
	ret = read(my_test_fd, rd8_buf, sizeof(rd8_buf));
	if(ret != sizeof(rd8_buf))
	{
		printf("[ERROR] Need %d bytes. Read %d bytes.", sizeof(rd8_buf), ret);
	}
	for(i=0; i<REG_NUM; i++)
	{
		rd32_buf[i] = (int)rd8_buf[i*4] + ((int)rd8_buf[i*4+1]<<8) 
									+ ((int)rd8_buf[i*4+2]<<16) + ((int)rd8_buf[i*4+3]<<24);
		
		printf("Read reg%d:0x%x\n", i, rd32_buf[i]);
	}
	close(my_test_fd);
	return 0;
}