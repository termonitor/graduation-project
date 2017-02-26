#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<bluetooth/bluetooth.h>
#include<bluetooth/rfcomm.h>

int main(int argc, char** argv)
{
	struct sockaddr_rc addr = {0};
	int s, status, len = 0;
	char dest[18] = "9C:B7:0D:90:EC:52";
	char buf[256];
	printf("create socket\n");
	s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
	addr.rc_family = AF_BLUETOOTH;
	addr.rc_channel = (uint8_t)1;
	printf("str2ba\n");	
	str2ba(dest, &addr.rc_bdaddr);
	printf("connect\n");
	status = connect(s, (struct sockaddr*)&addr, sizeof(addr));
	if(status) {
		printf("status: %d\n", status);		
		printf("failed to connect the device!\n");
		return -1;
	}
	printf("reading.....\n");
	do {
		len = read(s, buf, sizeof(buf));
		if(len > 0) {
			buf[len] = 0;
			int j;
			for(j=0;j<len;j++) {
				printf("%02x ", buf[j]);
			}
			printf("\n");
			//printf("%02x\n", buf);
		}
	} while(len>0);
	close(s);
	return 0;
}
