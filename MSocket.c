#include "MSocket.h"

extern struct sockaddr_rc addr;
extern int s;
extern char dest[18];

int initSocket()
{
	//初始化变量
	memset((char*)&addr, 0, sizeof(addr));
	strcpy(dest, "9C:B7:0D:90:EC:52");
	s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
	printf("%s\n", dest);
	//设置sockaddr_rc
	addr.rc_family = AF_BLUETOOTH;
	addr.rc_channel = (uint8_t)1;
	str2ba(dest, &addr.rc_bdaddr);
}

int tryConnect()
{
	int status = connect(s, (struct sockaddr*)&addr, sizeof(addr));
	if(status)
	{
		return -1;
	}
	return 0;
}

void* threadSocket()
{
	initSocket();
	int result = tryConnect();
	while(result == -1)
	{
		close(s);
		sleep(5);
		initSocket();
		result = tryConnect();
		sleep(5);
	}
	pthread_exit(NULL);
}

