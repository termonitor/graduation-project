#include "MOled.h"

extern int fd_oled;
extern char oledImage[512];

void clearImage()
{
	memset(oledImage, 0X0, sizeof(oledImage));
}

void getOledFD()
{
	fd_oled = open("/dev/zed_oled",O_RDWR);
	if(fd_oled == -1) {
		printf("Can't open zed_oled device!\n");
	} 
	else {
		printf("/dev/zed_oled open success!\n");
	}
}

void closeOled()
{
	clearImage();
	printImage();
	close(fd_oled);
}

void printImage()
{
	write(fd_oled, oledImage, 128*4);
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
			part1 = (char*)malloc(10*sizeof(char));
//            part1 = new char[10];               
            part1[0]=0XC0, part1[1]=0XF0, part1[2]=0X38, part1[3]=0X18;
            part1[4]=0X18, part1[5]=0X18, part1[6]=0X30, part1[7]=0XE0;
            part1[8]=0XC0, part1[9]='\0';    
			part2 = (char*)malloc(10*sizeof(char));
//            part2 = new char[10];
            part2[0]=0XFF, part2[1]=0XE1, part2[2]=0X00, part2[3]=0X00;
            part2[4]=0X00, part2[5]=0X00, part2[6]=0X00, part2[7]=0XFF;
            part2[8]=0X7F, part2[9]='\0';
			part3 = (char*)malloc(8*sizeof(char));
//            part3 = new char[8];
            part3[0]=0X01, part3[1]=0X03, part3[2]=0X06, part3[3]=0X06;
            part3[4]=0X02, part3[5]=0X03, part3[6]=0X01, part3[7]='\0';
            offset1=135, offset2=263, offset3=392;
            break;   
        case 1:
			part1 = (char*)malloc(10*sizeof(char));
//            part1 = new char[6];
            part1[0]=0XF8, part1[1]=0XF8, part1[2]=0X60, part1[3]=0X40;
            part1[4]=0XC0, part1[5]='\0';
			part2 = (char*)malloc(3*sizeof(char));
//            part2 = new char[3];
            part2[0]=0XFF, part2[1]=0XFF, part2[2]='\0';
			part3 = (char*)malloc(3*sizeof(char));
//            part3 = new char[3];
            part3[0]=0X03, part3[1]=0X03, part3[2]='\0';
            offset1=138, offset2=266, offset3=394;
            break;
        case 2:
			part1 = (char*)malloc(10*sizeof(char));
//            part1 = new char[10];
            part1[0]=0XE0, part1[1]=0XF0, part1[2]=0X18, part1[3]=0X18;
            part1[4]=0X18, part1[5]=0X18, part1[6]=0X18, part1[7]=0X70;
            part1[8]=0X60, part1[9]='\0';
			part2 = (char*)malloc(8*sizeof(char));
//            part2 = new char[8];
            part2[0]=0X01, part2[1]=0X07, part2[2]=0X0E, part2[3]=0X18;
            part2[4]=0X70, part2[5]=0XE0, part2[6]=0X80, part2[7]='\0';
			part3 = (char*)malloc(10*sizeof(char));
//            part3 = new char[10];
            part3[0]=0X02, part3[1]=0X02, part3[2]=0X02, part3[3]=0X02;
            part3[4]=0X02, part3[5]=0X02, part3[6]=0X03, part3[7]=0X03;
            part3[8]=0X02, part3[9]='\0';
            offset1=135, offset2=263, offset3=391;
            break;
        case 3:
			part1 = (char*)malloc(10*sizeof(char));
//            part1 = new char[10];
            part1[0]=0XE0, part1[1]=0XF0, part1[2]=0X18, part1[3]=0X18;
            part1[4]=0X18, part1[5]=0X18, part1[6]=0X30, part1[7]=0X70;
            part1[8]=0X40, part1[9]='\0';
			part2 = (char*)malloc(10*sizeof(char));
//            part2 = new char[10];
            part2[0]=0XF0, part2[1]=0XFB, part2[2]=0X0E, part2[3]=0X06;
            part2[4]=0X04, part2[5]=0X00, part2[6]=0X00, part2[7]=0X80;
            part2[8]=0X80, part2[9]='\0';
			part3 = (char*)malloc(8*sizeof(char));
//            part3= new char[8];
            part3[0]=0X03, part3[1]=0X03, part3[2]=0X06, part3[3]=0X06;
            part3[4]=0X06, part3[5]=0X03, part3[6]=0X03, part3[7]='\0';
            offset1=135, offset2=263, offset3=392;
            break;
        case 4:
			part1 = (char*)malloc(5*sizeof(char));
//           part1 = new char[5];
            part1[0]=0XF8, part1[1]=0XF8, part1[2]=0X60, part1[3]=0XC0;
            part1[4]='\0';
			part2 = (char*)malloc(12*sizeof(char));
//            part2 = new char[12];
            part2[0]=0X40, part2[1]=0X40, part2[2]=0XFF, part2[3]=0XFF;
            part2[4]=0X40, part2[5]=0X41, part2[6]=0X43, part2[7]=0X4E;
            part2[8]=0X5C, part2[9]=0X70, part2[10]=0X60, part2[11]='\0';
			part3 = (char*)malloc(3*sizeof(char));
//            part3= new char[3];
            part3[0]=0X03, part3[1]=0X03, part3[2]='\0';
            offset1=136, offset2=262, offset3=392;
            break;
        case 5:
			part1 = (char*)malloc(9*sizeof(char));
//            part1 = new char[9];
            part1[0]=0X18, part1[1]=0X18, part1[2]=0X18, part1[3]=0X18;
            part1[4]=0X18, part1[5]=0X18, part1[6]=0X38, part1[7]=0XF0;
            part1[8]='\0';
			part2 = (char*)malloc(10*sizeof(char));
//            part2 = new char[10];
            part2[0]=0XF8, part2[1]=0XFE, part2[2]=0X06, part2[3]=0X03;
            part2[4]=0X03, part2[5]=0X03, part2[6]=0X03, part2[7]=0X07;
            part2[8]=0XC7, part2[9]='\0';
			part3 = (char*)malloc(9*sizeof(char));
//            part3= new char[9];
            part3[0]=0X01, part3[1]=0X03, part3[2]=0X06, part3[3]=0X06;
            part3[4]=0X06, part3[5]=0X02, part3[6]=0X03, part3[7]=0X01;
            part3[8]='\0';
            offset1=135, offset2=263, offset3=392;
            break;
        case 6:
			part1 = (char*)malloc(6*sizeof(char));
//            part1 = new char[6];
            part1[0]=0X08, part1[1]=0X38, part1[2]=0X70, part1[3]=0XC0;
            part1[4]=0X80, part1[5]='\0';
			part2 = (char*)malloc(11*sizeof(char));
//            part2 = new char[11];
            part2[0]=0XF8, part2[1]=0XFC, part2[2]=0X06, part2[3]=0X02;
            part2[4]=0X02, part2[5]=0X02, part2[6]=0X03, part2[7]=0X07;
            part2[8]=0XFE, part2[9]=0XF8, part2[10]='\0';
			part3 = (char*)malloc(9*sizeof(char));
//            part3= new char[9];
            part3[0]=0X01, part3[1]=0X03, part3[2]=0X06, part3[3]=0X06;
            part3[4]=0X06, part3[5]=0X06, part3[6]=0X03, part3[7]=0X03;
            part3[8]='\0';
            offset1=137, offset2=262, offset3=391;
            break;
        case 7:
			part1 = (char*)malloc(11*sizeof(char));
//            part1 = new char[11];
            part1[0]=0X18, part1[1]=0X78, part1[2]=0XF8, part1[3]=0X98;
            part1[4]=0X18, part1[5]=0X18, part1[6]=0X18, part1[7]=0X18;
            part1[8]=0X18, part1[9]=0X18, part1[10]='\0';
			part2 = (char*)malloc(5*sizeof(char));
//            part2 = new char[5];
            part2[0]=0X03, part2[1]=0X1E, part2[2]=0XF8, part2[3]=0XC0;
            part2[4]='\0';
			part3 = (char*)malloc(3*sizeof(char));
//            part3= new char[3];
            part3[0]=0X03, part3[1]=0X02, part3[2]='\0';
            offset1=134, offset2=265, offset3=396;
            break;
        case 8:
			part1 = (char*)malloc(10*sizeof(char));
//            part1 = new char[10];
            part1[0]=0XE0, part1[1]=0XF0, part1[2]=0X18, part1[3]=0X18;
            part1[4]=0X18, part1[5]=0X18, part1[6]=0X18, part1[7]=0XF0;
            part1[8]=0XE0, part1[9]='\0';
			part2 = (char*)malloc(10*sizeof(char));
//            part2 = new char[10];
            part2[0]=0XF0, part2[1]=0X9B, part2[2]=0X0E, part2[3]=0X06;
            part2[4]=0X06, part2[5]=0X06, part2[6]=0X0E, part2[7]=0X9B;
            part2[8]=0XF1, part2[9]='\0';
			part3 = (char*)malloc(10*sizeof(char));
//            part3= new char[10];
            part3[0]=0X01, part3[1]=0X03, part3[2]=0X03, part3[3]=0X06;
            part3[4]=0X06, part3[5]=0X06, part3[6]=0X02, part3[7]=0X03;
            part3[8]=0X01, part3[9]='\0';
            offset1=135, offset2=263, offset3=391;
            break;
        case 9:
			part1 = (char*)malloc(10*sizeof(char));
//            part1 = new char[10];
            part1[0]=0XE0, part1[1]=0XF0, part1[2]=0X38, part1[3]=0X18;
            part1[4]=0X18, part1[5]=0X18, part1[6]=0X18, part1[7]=0X70;
            part1[8]=0XE0, part1[9]='\0';
			part2 = (char*)malloc(10*sizeof(char));
//            part2 = new char[10];
            part2[0]=0X03, part2[1]=0X0F, part2[2]=0X3C, part2[3]=0XF8;
            part2[4]=0XD8, part2[5]=0X18, part2[6]=0X18, part2[7]=0X0E;
            part2[8]=0X07, part2[9]='\0';
			part3 = (char*)malloc(4*sizeof(char));
//            part3= new char[4];
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
    strcpy(oledImage+offset1, part1);
    strcpy(oledImage+offset2, part2);
    strcpy(oledImage+offset3, part3); 
    if(num == 0)
    {
        strcpy(oledImage+offset2+7, part2+7);
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