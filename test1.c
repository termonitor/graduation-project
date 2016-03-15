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
int fd;
char Image[512];

void printImage()
{
	write(fd, Image, 128*4);
}

/**
    loc：位置
    num: 数字 
**/
void setNum(int loc, int num)
{
    char* part1;
    char* part2;
    char* part3;
    int offset1, offset2, offset3;
//    printf("%d %d\n", loc, num);
//    return;
    switch(num)
    {
        /*
            part1 = new char[];
            part1[0]=
            part2 = new char[];
            part2[0]=
            part3= new char[];
            part3[0]=
            offset1=, offset2=, offset3=;
            break;
        */
        case 0:
            part1 = new char[10];               
            part1[0]=0XC0, part1[1]=0XF0, part1[2]=0X38, part1[3]=0X18;
            part1[4]=0X18, part1[5]=0X18, part1[6]=0X30, part1[7]=0XE0;
            part1[8]=0XC0, part1[9]='\0';    
            part2 = new char[10];
            part2[0]=0XFF, part2[1]=0XE1, part2[2]=0X00, part2[3]=0X00;
            part2[4]=0X00, part2[5]=0X00, part2[6]=0X00, part2[7]=0XFF;
            part2[8]=0X7F, part2[9]='\0';
            part3 = new char[8];
            part3[0]=0X01, part3[1]=0X03, part3[2]=0X06, part3[3]=0X06;
            part3[4]=0X02, part3[5]=0X03, part3[6]=0X01, part3[7]='\0';
            offset1=135, offset2=263, offset3=392;
            break;   
        case 1:
            part1 = new char[6];
            part1[0]=0XF8, part1[1]=0XF8, part1[2]=0X60, part1[3]=0X40;
            part1[4]=0XC0, part1[5]='\0';
            part2 = new char[3];
            part2[0]=0XFF, part2[1]=0XFF, part2[2]='\0';
            part3 = new char[3];
            part3[0]=0X03, part3[1]=0X03, part3[2]='\0';
            offset1=138, offset2=266, offset3=394;
            break;
        case 2:
            part1 = new char[10];
            part1[0]=0XE0, part1[1]=0XF0, part1[2]=0X18, part1[3]=0X18;
            part1[4]=0X18, part1[5]=0X18, part1[6]=0X18, part1[7]=0X70;
            part1[8]=0X60, part1[9]='\0';
            part2 = new char[8];
            part2[0]=0X01, part2[1]=0X07, part2[2]=0X0E, part2[3]=0X18;
            part2[4]=0X70, part2[5]=0XE0, part2[6]=0X80, part2[7]='\0';
            part3 = new char[10];
            part3[0]=0X02, part3[1]=0X02, part3[2]=0X02, part3[3]=0X02;
            part3[4]=0X02, part3[5]=0X02, part3[6]=0X03, part3[7]=0X03;
            part3[8]=0X02, part3[9]='\0';
            offset1=135, offset2=263, offset3=391;
            break;
        case 3:
            part1 = new char[10];
            part1[0]=0XE0, part1[1]=0XF0, part1[2]=0X18, part1[3]=0X18;
            part1[4]=0X18, part1[5]=0X18, part1[6]=0X30, part1[7]=0X70;
            part1[8]=0X40, part1[9]='\0';
            part2 = new char[10];
            part2[0]=0XF0, part2[1]=0XFB, part2[2]=0X0E, part2[3]=0X06;
            part2[4]=0X04, part2[5]=0X00, part2[6]=0X00, part2[7]=0X80;
            part2[8]=0X80, part2[9]='\0';
            part3= new char[8];
            part3[0]=0X03, part3[1]=0X03, part3[2]=0X06, part3[3]=0X06;
            part3[4]=0X06, part3[5]=0X03, part3[6]=0X03, part3[7]='\0';
            offset1=135, offset2=263, offset3=392;
            break;
        case 4:
            part1 = new char[5];
            part1[0]=0XF8, part1[1]=0XF8, part1[2]=0X60, part1[3]=0XC0;
            part1[4]='\0';
            part2 = new char[12];
            part2[0]=0X40, part2[1]=0X40, part2[2]=0XFF, part2[3]=0XFF;
            part2[4]=0X40, part2[5]=0X41, part2[6]=0X43, part2[7]=0X4E;
            part2[8]=0X5C, part2[9]=0X70, part2[10]=0X60, part2[11]='\0';
            part3= new char[3];
            part3[0]=0X03, part3[1]=0X03, part3[2]='\0';
            offset1=136, offset2=262, offset3=392;
            break;
        case 5:
            part1 = new char[9];
            part1[0]=0X18, part1[1]=0X18, part1[2]=0X18, part1[3]=0X18;
            part1[4]=0X18, part1[5]=0X18, part1[6]=0X38, part1[7]=0XF0;
            part1[8]='\0';
            part2 = new char[10];
            part2[0]=0XF8, part2[1]=0XFE, part2[2]=0X06, part2[3]=0X03;
            part2[4]=0X03, part2[5]=0X03, part2[6]=0X03, part2[7]=0X07;
            part2[8]=0XC7, part2[9]='\0';
            part3= new char[9];
            part3[0]=0X01, part3[1]=0X03, part3[2]=0X06, part3[3]=0X06;
            part3[4]=0X06, part3[5]=0X02, part3[6]=0X03, part3[7]=0X01;
            part3[8]='\0';
            offset1=135, offset2=263, offset3=392;
            break;
        case 6:
            part1 = new char[6];
            part1[0]=0X08, part1[1]=0X38, part1[2]=0X70, part1[3]=0XC0;
            part1[4]=0X80, part1[5]='\0';
            part2 = new char[11];
            part2[0]=0XF8, part2[1]=0XFC, part2[2]=0X06, part2[3]=0X02;
            part2[4]=0X02, part2[5]=0X02, part2[6]=0X03, part2[7]=0X07;
            part2[8]=0XFE, part2[9]=0XF8, part2[10]='\0';
            part3= new char[9];
            part3[0]=0X01, part3[1]=0X03, part3[2]=0X06, part3[3]=0X06;
            part3[4]=0X06, part3[5]=0X06, part3[6]=0X03, part3[7]=0X03;
            part3[8]='\0';
            offset1=137, offset2=262, offset3=391;
            break;
        case 7:
            part1 = new char[11];
            part1[0]=0X18, part1[1]=0X78, part1[2]=0XF8, part1[3]=0X98;
            part1[4]=0X18, part1[5]=0X18, part1[6]=0X18, part1[7]=0X18;
            part1[8]=0X18, part1[9]=0X18, part1[10]='\0';
            part2 = new char[5];
            part2[0]=0X03, part2[1]=0X1E, part2[2]=0XF8, part2[3]=0XC0;
            part2[4]='\0';
            part3= new char[3];
            part3[0]=0X03, part3[1]=0X02, part3[2]='\0';
            offset1=134, offset2=265, offset3=396;
            break;
        case 8:
            part1 = new char[10];
            part1[0]=0XE0, part1[1]=0XF0, part1[2]=0X18, part1[3]=0X18;
            part1[4]=0X18, part1[5]=0X18, part1[6]=0X18, part1[7]=0XF0;
            part1[8]=0XE0, part1[9]='\0';
            part2 = new char[10];
            part2[0]=0XF0, part2[1]=0X9B, part2[2]=0X0E, part2[3]=0X06;
            part2[4]=0X06, part2[5]=0X06, part2[6]=0X0E, part2[7]=0X9B;
            part2[8]=0XF1, part2[9]='\0';
            part3= new char[10];
            part3[0]=0X01, part3[1]=0X03, part3[2]=0X03, part3[3]=0X06;
            part3[4]=0X06, part3[5]=0X06, part3[6]=0X02, part3[7]=0X03;
            part3[8]=0X01, part3[9]='\0';
            offset1=135, offset2=263, offset3=391;
            break;
        case 9:
            part1 = new char[10];
            part1[0]=0XE0, part1[1]=0XF0, part1[2]=0X38, part1[3]=0X18;
            part1[4]=0X18, part1[5]=0X18, part1[6]=0X18, part1[7]=0X70;
            part1[8]=0XE0, part1[9]='\0';
            part2 = new char[10];
            part2[0]=0X03, part2[1]=0X0F, part2[2]=0X3C, part2[3]=0XF8;
            part2[4]=0XD8, part2[5]=0X18, part2[6]=0X18, part2[7]=0X0E;
            part2[8]=0X07, part2[9]='\0';
            part3= new char[4];
            part3[0]=0X03, part3[1]=0X07, part3[2]=0X04, part3[3]='\0';
            offset1=135, offset2=263, offset3=395;
            break;
    } 
    if(loc == 2)
    {
        offset1 += 11;
        offset2 += 11;
        offset3 += 11; 
    } else if(loc != 1) {
        offset1 += (loc-2)*12+11;
        offset2 += (loc-2)*12+11;
        offset3 += (loc-2)*12+11;   
    }
    strcpy(Image+offset1, part1);
    strcpy(Image+offset2, part2);
    strcpy(Image+offset3, part3); 
    if(num == 0)
    {
        strcpy(Image+offset2+7, part2+7);
    }
}

void handleNumber(int num)
{
    if(num == 0)
    {
        setNum(1, 0);
        return;   
    }      
    int i=1; 
    while(num != 0)
    {
        int temp = num%10;
        setNum(i, temp);
        i++;
        num /= 10;
    }
}

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
						//在这里将结果输出？
					}
					else
						i += valueBytesLength;
					break;
				case PARSER_CODE_ATTENTION:
					attention = (int)payload[i];
					i += valueBytesLength;
					fprintf(fp1, "attention:%d\n", attention);
					memset(Image, 0X0, sizeof(Image));
					handleNumber(attention);
					printImage();
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
	fd = open("/dev/zed_oled",O_RDWR);
	fp1 = fopen("1.txt", "w");
	if(fd == -1){
	    printf("Can't open zed_oled device!\n");
	    return 0;
  	}
  	else{
	    printf("/dev/zed_oled open success!\n");
	}
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
