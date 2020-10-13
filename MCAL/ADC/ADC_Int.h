#ifndef   _ADC_INT_H
#define   _ADC_INT_H


void ADC_VidInit(void);
void ADC_VidStartConversion(void);
void ADC_VidChannel(u8 LOC_u8Channel);
void ADC_VidMood(void);
void ADC_VidInterruptEnable(void);
void ADC_VidPolling(void);
void ADC_VidGetRes(u8*p);
void ADC_VidSetCallBack(void (*Lpfunc)(void));








#endif