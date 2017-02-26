#ifndef __M_SOCKET_H__
#define __M_SOCKET_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <string.h>

//body
struct sockaddr_rc addr;
int s;
char dest[18];
int socket_status;
int initSocket();
int tryConnect();
void* threadSocket();

#endif
