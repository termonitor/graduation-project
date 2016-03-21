#ifndef __M_PARSER_H__
#define __M_PARSER_H__

#include <stdio.h>
#include <stdlib.h>
#include "MConstant.h"
#include "MOled.h"
//body
int parserStatus;
int payloadLength;
int payloadBytesReceived;
int payloadSum;
int checkSum;
int payload[256];
void initParser();
int getRawWaveValue(char highOrderByte, char lowOrderByte);
int getEEGValue(char highOrderByte, char middleOrderByte, char lowOrderByte);
int parseByte(char buffer);
void parsePacketPayload();

#endif