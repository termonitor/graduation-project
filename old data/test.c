#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<bluetooth/bluetooth.h>
#include<bluetooth/hci.h>
#include<bluetooth/hci_lib.h>
int main(int argc, char** argv)
{
	inquiry_info *ii = NULL;
	int max_rsp, num_rsp;
	int dev_id, sock, len, flags;
	int i;
	char addr[19] = {0};
	char name[2048] = {0};
	printf("hci_get_route\n");
	dev_id = hci_get_route(NULL);
	printf("hci_open_dev\n");
	sock = hci_open_dev(dev_id);
	
	if(dev_id<0 || sock<0) {
		printf("opening socket\n");
		perror("opening socket");
		exit(1);
	}
	len = 8;
	max_rsp = 255;
	flags = IREQ_CACHE_FLUSH;
	ii = (inquiry_info*)malloc(max_rsp*sizeof(inquiry_info));
	printf("hci_inquiry\n");
	num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
	if(num_rsp < 0) {
		printf("hci_inquiry\n");
		perror("hci_inquiry");
	}
	printf("num_rsp: %d\n", num_rsp);
	for(i=0;i<num_rsp;i++) {
		ba2str(&(ii+i)->bdaddr, addr);
		memset(name, 0, sizeof(name));
		printf("hci_read_remote_name\n");
		if(hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name), name, 0) < 0)
			strcpy(name, "[unknown]");
		printf("%s %s\n", addr, name);
	}
	printf("over\n");
	free(ii);
	close(sock);
	return 0;
}
