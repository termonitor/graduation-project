#include "MAction.h"

extern int function_status;
extern pthread_mutex_t mut;

void oledOutput(int num)
{
	clearImage();
	handleNumber(num);
	printImage();
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
	if(config == 0 && function_status == 1)
	{
		oledOutput(signal[1]);	//raw
		pthread_mutex_unlock(&mut);
		return;
	}
	if(config == 0)
	{
		pthread_mutex_unlock(&mut);
		return;
	}
	switch(function_status)
	{
		case 0:
			oledOutput(signal[10]);	//attention
			break;
		case 2:
			oledOutput(signal[11]); //meditation
			break;
		case 3:
			oledOutput(signal[0]);	//poorSignal
			break;
		case 4:
			oledOutput(signal[2]);	//delta
			break;
		case 5:
			oledOutput(signal[3]);	//theta
			break;
		case 6:
			oledOutput(signal[4]);	//lowAlpha
			break;
		case 7:
			oledOutput(signal[5]);	//highAlpha
			break;
		case 8:
			oledOutput(signal[6]);	//lowBeta
			break;
		case 9:
			oledOutput(signal[7]);	//highBeta
			break;
		case 10:
			oledOutput(signal[8]);	//lowGamma
			break;
		case 11:
			oledOutput(signal[9]); //middleGamma
			break;
	}
	pthread_mutex_unlock(&mut);
}