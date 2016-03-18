#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include "MConstant.h"
//#include "MOled.h"
#include "MSocket.h"

pthread_t thread_socket;

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
	return 0;
}
