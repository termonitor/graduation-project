#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<bluetooth/bluetooth.h>
#include<bluetooth/rfcomm.h>

#define PARSER_STATE_SYNC 1
#define PARSER_STATE_SYNC_CHECK 2
#define PARSER_STATE_PAYLOAD_LENGTH 3
#define PARSER_STATE_PAYLOAD 4
#define PARSER_STATE_CHKSUM 5
#define PARSER_SYNC_BYTE 170 //AA
#define PARSER_EXCODE_BYTE 85 //55
#define MULTI_BYTE_CODE_THRESHOLD 127
#define PARSER_CODE_RAW 128 //80
#define RAW_DATA_BYTE_LENGTH 2
#define PARSER_CODE_POOR_SIGNAL 2
#define PARSER_CODE_EEG_POWER 131 //83
#define PARSER_CODE_ATTENTION 4
#define PARSER_CODE_MEDITATION 5
#define PARSER_CODE_HEARTRATE 3
#define PARSER_CODE_DEBUG_ONE 132
#define EEG_DEBUG_ONE_BYTE_LENGTH 5
#define PARSER_CODE_DEBUG_TWO 133
#define EEG_DEBUG_TWO_BYTE_LENGTH 3
#define EEG_POWER_BYTE 24
#define MINN 10
#define MAXN 100000000

int parserStatus;
int payloadLength;
int payloadBytesReceived;
int payloadSum;
int checkSum;
char payload[256];
char buf[256];
FILE *fp1;

int getRawWaveValue(char highOrderByte, char lowOrderByte)
{
	int hi = ((int)highOrderByte) & 0xFF;
	int lo = ((int)lowOrderByte) & 0xFF;
	int value = (hi << 8) | lo;
	return value;
}

int getEEGValue(char highOrderByte, char middleOrderByte, char lowOrderByte)
{
	int hi = ((int)highOrderByte) & 0xFF;
	int mi = ((int)middleOrderByte) & 0xFF;
	int lo = ((int)lowOrderByte) & 0xFF;
	int value = (((hi<<8) | mi)<<8 | lo);
	return value;
}

void parsePacketPayload()
{
	int i = 0;
	int extendedCodeLevel = 0;
    int code = 0;
    int valueBytesLength = 0;
	int signal = 0; 
	int config = 0; 
	int heartrate = 0;
    int rawWaveData = 0;
	int delta = 0;
	int theta = 0;
	int lowAlpha = 0;
	int highAlpha = 0;
	int lowBeta = 0;
	int highBeta = 0;
	int lowGamma = 0;
	int middleGamma = 0;
	int attention = 0;
	int meditation = 0;
	while(i < payloadLength)
	{
		extendedCodeLevel++;
		while (payload[i] == PARSER_EXCODE_BYTE)
			i++;
		code = payload[i++] & 0xFF;
		if(code > MULTI_BYTE_CODE_THRESHOLD)
		{
			valueBytesLength = payload[i++] & 0xFF;
		}
		else
			valueBytesLength = 1;
		if(code == PARSER_CODE_RAW)
		{
			if(valueBytesLength == RAW_DATA_BYTE_LENGTH)
			{
				char highOrderByte = payload[i];
				char lowOrderByte = payload[i+1];
				rawWaveData = getRawWaveValue(highOrderByte, lowOrderByte);
				if (rawWaveData > 32768) 
					rawWaveData -= 65536;
				//输出Raw的值
				fprintf(fp1, "Raw:%d\n", rawWaveData);
			}
			i += valueBytesLength;
		}
		else
		{
			switch(code)
			{
				case PARSER_CODE_POOR_SIGNAL:
					signal = payload[i] & 0xFF;
					i += valueBytesLength;
					//输出PoorSignal的值
					fprintf(fp1, "PoorSignal:%d\n", signal);
					break;
				case PARSER_CODE_EEG_POWER:
					fprintf(fp1, "hello\n");
					//fprintf(fp1, "hhh:%02hhx\n", (unsigned char)payload[i]);
					if(valueBytesLength == EEG_POWER_BYTE)
					{
						delta = getEEGValue(payload[i], payload[i+1], payload[i+2]);
						i = i+3;
						theta = getEEGValue(payload[i], payload[i+1], payload[i+2]);
						i = i+3;
						lowAlpha = getEEGValue(payload[i], payload[i+1], payload[i+2]);
						i = i+3;
						highAlpha = getEEGValue(payload[i], payload[i+1], payload[i+2]);
						i = i+3;
						lowBeta = getEEGValue(payload[i], payload[i+1], payload[i+2]);
						i = i+3;
						highBeta = getEEGValue(payload[i], payload[i+1], payload[i+2]);
						i = i+3;
						lowGamma = getEEGValue(payload[i], payload[i+1], payload[i+2]);
						i = i+3;
						middleGamma = getEEGValue(payload[i], payload[i+1], payload[i+2]);
						i = i+3;
						fprintf(fp1, "delta:%d\n", delta);
						fprintf(fp1, "theta:%d\n", theta);
						fprintf(fp1, "lowAlpha:%d\n", lowAlpha);
						fprintf(fp1, "highAlpha:%d\n", highAlpha);
						fprintf(fp1, "lowBeta:%d\n", lowBeta);
						fprintf(fp1, "highBeta:%d\n", highBeta);
						fprintf(fp1, "lowGamma:%d\n", lowGamma);
						fprintf(fp1, "middleGamma:%d\n", middleGamma);
					}
					else
						i += valueBytesLength;
					break;
				case PARSER_CODE_ATTENTION:
					attention = (int)payload[i];
					i += valueBytesLength;
					fprintf(fp1, "attention:%d\n", attention);
					break;
				case PARSER_CODE_MEDITATION:
					meditation = (int)payload[i];
					i += valueBytesLength;
					fprintf(fp1, "meditation:%d\n", meditation);
					break;
/*				case PARSER_CODE_HEARTRATE:
					heartrate = payload[i] & 0xFF;
					fprintf(fp1, "HeartRate:%d\n", heartrate);
					i += valueBytesLength;
					break;
				case PARSER_CODE_DEBUG_ONE:
					if (valueBytesLength == EEG_DEBUG_ONE_BYTE_LENGTH)
					{
						i += valueBytesLength;
					}
					break;
				case PARSER_CODE_DEBUG_TWO:
					if (valueBytesLength == EEG_DEBUG_TWO_BYTE_LENGTH)
					{
						i += valueBytesLength;
					}
					break;*/
			}
		}
	}
	parserStatus = PARSER_STATE_SYNC;
}

int parseByte(char buffer)
{
	int returnValue = 0;
	switch(parserStatus)
	{
		case 1:
			if((buffer & 0xFF) != PARSER_SYNC_BYTE)
				break;
			parserStatus = PARSER_STATE_SYNC_CHECK;
			break;
		case 2:
			if((buffer & 0xFF) == PARSER_SYNC_BYTE)
				parserStatus = PARSER_STATE_PAYLOAD_LENGTH;
			else
				parserStatus = PARSER_STATE_SYNC;
			break;
		case 3:
			payloadLength = (buffer & 0xFF);
			payloadBytesReceived = 0;
			payloadSum = 0;
			parserStatus = PARSER_STATE_PAYLOAD;
			break;
		case 4:
			payload[payloadBytesReceived++] = buffer;
			payloadSum += (buffer & 0xFF);
			if(payloadBytesReceived < payloadLength)
				break;
			parserStatus = PARSER_STATE_CHKSUM;
			break;
		case 5:
			checkSum = (buffer & 0xFF);
			parserStatus = PARSER_STATE_SYNC;
			if(checkSum != ((payloadSum ^ 0xFFFFFFFF) & 0xFF))
			{
				returnValue = -2;
				//输出Error
				fprintf(fp1, "无效数据\n");
			}
			else
			{	
				returnValue = 1;
				parsePacketPayload();
			}
			break;
	}
	return returnValue;
}

int main(int argc, char** argv)
{
	struct sockaddr_rc addr = {0};
	int s, status, len = 0;
	char dest[18] = "9C:B7:0D:90:EC:52";
	parserStatus = PARSER_STATE_SYNC;
	printf("create socket\n");
	//获取socket
	s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
	//设置sockaddr_rc
	addr.rc_family = AF_BLUETOOTH;
	addr.rc_channel = (uint8_t)1;
	printf("str2ba\n");	
	str2ba(dest, &addr.rc_bdaddr);
	printf("connect\n");
	//通过socket s 尝试对目标mac地址进行连接，返回状态status
	status = connect(s, (struct sockaddr*)&addr, sizeof(addr));
	if(status) {
		printf("status: %d\n", status);		
		printf("failed to connect the device!\n");
		return -1;
	}
/*	int time = 0;
	while(status)
	{
		if(time <= MINN)
		{
			printf("status: %d\n", status);
			printf("failed to connect the device!\n");
		}
		if(time > MAXN)
		{
			printf("failed to connect the device!\n");
			return -1;
		}
		status = connect(s, (struct sockaddr*)&addr, sizeof(addr));
		time++;
	}*/
	printf("reading.....\n");
	memset(buf, 0, sizeof(buf));
	fp1 = fopen("1.txt", "w");
	do {
		//通过socket读取字符，保存在buf缓冲区中
		len = read(s, buf, sizeof(buf));
		if(len > 0) {
			buf[len] = 0;
			int j;
			for(j=0;j<len;j++) {
				//printf("%02x ", buf[j]);
				//fprintf(fp1, "%02hhx\n", (unsigned char)buf[j]);
				parseByte(buf[j]);
			}
			//printf("\n");
			//fprintf(fp1, "\n");
			//printf("%02x\n", buf);
		}
	} while(len>0);
	close(s);
	return 0;
}
