#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include "MConstant.h"
#include "MOled.h"
#include "MSocket.h"
#include "MParser.h"

pthread_t thread_socket;
char buf[256];
extern int s;
extern int socket_status;

int main()
{
	int result = pthread_create(&thread_socket, NULL, threadSocket, NULL);
	if(result != 0)
	{
		printf("create socket error!\n");
		return 0;
	}
	pthread_join(thread_socket, NULL);
	printf("successful!\n");
	//此处应该点亮LD灯，作为连接上的象征。
	memset(buf, 0, sizeof(buf));
	getOledFD();
	int len = 0;
	while(socket_status)
	{
		initParser();
		do {
			len = read(s, buf, sizeof(buf));
			//正常数据长度为80
			if(len != 80)
				break;
			if(len > 0) {
				buf[len] = 0;
				int j;
				for(j=0;j<len;j++) {
					parseByte(buf[j]);
				}
			}
		} while(len > 0);
		if(len <= 0 || len != 80)
		{
			//熄灭LD灯，表示断开连接	
			printf("socket close, try connect again!\n");
			//关闭当前连接
			close(s);
			result = pthread_create(&thread_socket, NULL, threadSocket, NULL);
			if(result != 0)
			{
				printf("create socket error!\n");
				return 0;
			}
			pthread_join(thread_socket, NULL);
			memset(buf, 0, sizeof(buf));
		}
	}
	return 0;
}
