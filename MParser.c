#include "MParser.h"

extern int parserStatus;
extern int payloadLength;
extern int payloadBytesReceived;
extern int payloadSum;
extern int checkSum;
extern int payload[256];
extern char oledImage[512];

void initParser()
{
	parserStatus = PARSER_STATE_SYNC;
	payloadLength = 0;
	payloadBytesReceived = 0;
	payloadSum = 0;
	checkSum = 0;
	memset(payload, 0, sizeof(payload));
	clearImage();
	printImage();
}

int getRawValue(char highOrderByte, char lowOrderByte)
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
	int poorSignal = 0; 
	int heartrate = 0;
    int raw = 0;
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
	int signal[12];
	//此信号用于表示是小包，还是大包，0为小包，1为大包
	int config;
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
			config = 0;
			if(valueBytesLength == RAW_DATA_BYTE_LENGTH)
			{
				char highOrderByte = payload[i];
				char lowOrderByte = payload[i+1];
				raw = getRawValue(highOrderByte, lowOrderByte);
				if (raw > 32768) 
					raw -= 65536;
				//输出Raw的值
//				fprintf(fp1, "Raw:%d\n", raw);
			}
			i += valueBytesLength;
		}
		else
		{
			config = 1;
			switch(code)
			{
				case PARSER_CODE_POOR_SIGNAL:
					poorSignal = payload[i] & 0xFF;
					i += valueBytesLength;
					//输出PoorSignal的值
//					fprintf(fp1, "PoorSignal:%d\n", poorSignal);
					break;
				case PARSER_CODE_EEG_POWER:
//					fprintf(fp1, "hello\n");
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
						i = i+3;/*
						fprintf(fp1, "delta:%d\n", delta);
						fprintf(fp1, "theta:%d\n", theta);
						fprintf(fp1, "lowAlpha:%d\n", lowAlpha);
						fprintf(fp1, "highAlpha:%d\n", highAlpha);
						fprintf(fp1, "lowBeta:%d\n", lowBeta);
						fprintf(fp1, "highBeta:%d\n", highBeta);
						fprintf(fp1, "lowGamma:%d\n", lowGamma);
						fprintf(fp1, "middleGamma:%d\n", middleGamma);*/
						//在这里将结果输出？
					}
					else
						i += valueBytesLength;
					break;
				case PARSER_CODE_ATTENTION:
					attention = (int)payload[i];
					i += valueBytesLength;
//					fprintf(fp1, "attention:%d\n", attention);
/*					clearImage();
					handleNumber(attention);
					printImage(); */
					break;
				case PARSER_CODE_MEDITATION:
					meditation = (int)payload[i];
					i += valueBytesLength;
//					fprintf(fp1, "meditation:%d\n", meditation);
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
	//在执行完循环后，执行功能函数
	signal[0] = poorSignal, signal[1] = raw, signal[2] = delta;
	signal[3] = theta, signal[4] = lowAlpha, signal[5] = highAlpha;
	signal[6] = lowBeta, signal[7] = highBeta, signal[8] = lowGamma;
	signal[9] = middleGamma, signal[10] = attention, signal[11] = meditation;
	action(signal, config);
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
			if((buffer & 0XFF) != 4 && (buffer & 0XFF) != 32)
			{
				parserStatus = PARSER_STATE_SYNC;
				break;
			}
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
//				fprintf(fp1, "无效数据\n");
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