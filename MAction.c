#include "MAction.h"

extern int function_status;
extern pthread_mutex_t mut;
extern FILE* fp_small;
extern FILE* fp_big;
extern int gameLdStatus;

void initAction()
{
	gameLdStatus = -1;
	initPeripheral();
}

void oledOutput(int num, int status)
{
	clearImage();
	switch(status)
	{
		case -1:
			break;
		case 0:
			addAttentionFlag();
			break;
		case 2:
			addMeditationFlag();
			break;
		case 3:
			addPoorSignalFlag();
			break;
		case 4:
			addDeltaFlag();
			break;
		case 5:
			addThetaFlag();
			break;
		case 6:
			addLowAlphaFlag();
			break;
		case 7:
			addHighAlphaFlag();
			break;
		case 8:
			addLowBetaFlag();
			break;
		case 9:
			addHighBetaFlag();
			break;
		case 10:
			addLowGammaFlag();
			break;
		case 11:
			addMiddleGammaFlag();
			break;
	}
	handleNumber(num);
	printImage();
}

void game1(int attention)
{
//	setLedValue(int number, int status)
	int oldStatus = gameLdStatus;
	if(attention>50 && gameLdStatus>=-1 && gameLdStatus<6)
	{
		gameLdStatus++;
	}
	else if(attention<50 && gameLdStatus>-1 && gameLdStatus<=6)
	{
		gameLdStatus--;
	}
	if(oldStatus == gameLdStatus)
	{
		//do nothing
	} 
	else if(oldStatus < gameLdStatus)
	{
		//点亮一盏新灯
		setLedValue(gameLdStatus, 1);
	}
	else if(oldStatus > gameLdStatus)
	{
		setLedValue(oldStatus, 0);
	}
}

/**
	signal[0] = poorSignal, signal[1] = raw, signal[2] = delta;
	signal[3] = theta, signal[4] = lowAlpha, signal[5] = highAlpha;
	signal[6] = lowBeta, signal[7] = highBeta, signal[8] = lowGamma;
	signal[9] = middleGamma, signal[10] = attention, signal[11] = meditation;
	
	config 表示大小包，0为小包，1为大包
 **/
void action(int *signal, int config)
{
	pthread_mutex_lock(&mut);
	char buffer[1024];
	memset(buffer, '\0', sizeof(buffer));
/*
	if(config == 0 && function_status == 1)
	{
		//数据量太大，oled来不及显示，所以对于raw不做显示
	//	oledOutput(signal[1]);	//raw
	//	oledOutput(0, -1);
		pthread_mutex_unlock(&mut);
		return;
	}
*/
	if(config == 0)
	{
		snprintf(buffer, 1024, "%d\n", signal[1]);
		fwrite(buffer, 1, strlen(buffer), fp_small);
		pthread_mutex_unlock(&mut);
		return;
	}
	if(function_status != 1)
	{
		initAction();
	}
	switch(function_status)
	{
		case 0:
			oledOutput(signal[10], 0);	//attention
			break;
		case 1:
			//oledOutput(0, -1);
			oledOutput(signal[10], 0);
			game1(signal[10]);
			break;
		case 2:
			oledOutput(signal[11], 2); //meditation
			break;
		case 3:
			oledOutput(signal[0], 3);	//poorSignal
			break;
		case 4:
			oledOutput(signal[2], 4);	//delta
			break;
		case 5:
			oledOutput(signal[3], 5);	//theta
			break;
		case 6:
			oledOutput(signal[4], 6);	//lowAlpha
			break;
		case 7:
			oledOutput(signal[5], 7);	//highAlpha
			break;
		case 8:
			oledOutput(signal[6], 8);	//lowBeta
			break;
		case 9:
			oledOutput(signal[7], 9);	//highBeta
			break;
		case 10:
			oledOutput(signal[8], 10);	//lowGamma
			break;
		case 11:
			oledOutput(signal[9], 11); //middleGamma
			break;
		case 12:
			setPeripheralData(signal[6], signal[7], signal[8], signal[10], signal[11]);
		//	oledOutput(getPeripheralResult(), -1);
			int result = getPeripheralResult();
			addEmotionFlag(result);
			printImage();
			break;
		default:
			clearImage();
			printImage();
			break;
	}
	snprintf(buffer, 1024, "%d	%d	%d	%d	%d	%d	%d	%d	%d	%d	%d\n", 
				signal[10], signal[11], signal[0], signal[2], signal[3], signal[4], 
				signal[5], signal[6], signal[7], signal[8], signal[9]);
	fwrite(buffer, 1, strlen(buffer), fp_big);
	pthread_mutex_unlock(&mut);
}