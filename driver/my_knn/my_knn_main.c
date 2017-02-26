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

int main()
{
	int rd32_buf[REG_NUM], num;
	char rd8_buf[REG_NUM*4];
	int my_knn_fd = 0;
	my_knn_fd = open("/dev/my_knn_dev", 0);
	if(my_knn_fd < 0)
	{
		printf("Can't open device.\n");
		return 0;
	}
	int i;
	num = 12345;
	for(i=0; i<6; i++)
	{
		ioctl(my_knn_fd, i, num);
	}
	read(my_knn_fd, rd8_buf, sizeof(rd8_buf));
	for(i=0; i<REG_NUM; i++)
	{
		rd32_buf[i] = (int)rd8_buf[i*4] + ((int)rd8_buf[i*4+1]<<8) 
									+ ((int)rd8_buf[i*4+2]<<16) + ((int)rd8_buf[i*4+3]<<24);
		printf("%d : %d\n", i, rd32_buf[i]);
	}
	close(my_knn_fd);
	return 0;
}