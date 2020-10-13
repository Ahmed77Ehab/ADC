#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"
#include"ADC_Priv.h"
#include"ADC_Config.h"
#include"../Global Interrupt/GIE_Config.h"
/**GLOBAL POINTER TO FUNCTION**/
static void (*Gpfunc)(void)=NULL;

/********CALL BACK FUNCTION*****/
void ADC_VidSetCallBack(void (*Lpfunc)(void))
{
	Gpfunc=Lpfunc;
}

/*************ISR FOR ADC**********/
ISR(__vector_16)
{
	if(Gpfunc != NULL)
	{
		Gpfunc();
	}
}

void ADC_VidInit(void)
{
	/****************ADC VOLTAGE REF***************/
	#if      ADC_Vref==AREF_Internal_Vref_turned_off
	CLR_BIT(ADMUX,REF0);
	CLR_BIT(ADMUX,REF1);
	#elif    ADC_Vref==AVCC
	SET_BIT(ADMUX,REF0);
	CLR_BIT(ADMUX,REF1);
	#elif    ADC_Vref==Reserved
	CLR_BIT(ADMUX,REF0);
	SET_BIT(ADMUX,REF1);
	#elif    ADC_Vref==Internal_2.56V
	CLR_BIT(ADMUX,REF0);
	SET_BIT(ADMUX,REF1);
	#endif
	
	/**********************ADC PRESCALER**************/
	#if      Prescaler_Mood==PRESCALER_ADC_2
	CLR_BIT(ADCSRA,ADPS0);
    CLR_BIT(ADCSRA,ADPS1);
    CLR_BIT(ADCSRA,ADPS2);
    #elif    Prescaler_Mood==PRESCALER_ADC_4
    CLR_BIT(ADCSRA,ADPS0);
    SET_BIT(ADCSRA,ADPS1);
	CLR_BIT(ADCSRA,ADPS2);
    #elif    Prescaler_Mood==PRESCALER_ADC_8
    SET_BIT(ADCSRA,ADPS0);
    SET_BIT(ADCSRA,ADPS1);
	CLR_BIT(ADCSRA,ADPS2);
	#elif    Prescaler_Mood==PRESCALER_ADC_16
    CLR_BIT(ADCSRA,ADPS0);
    CLR_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
	#elif    Prescaler_Mood==PRESCALER_ADC_32
	SET_BIT(ADCSRA,ADPS0);
	CLR_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
	#elif    Prescaler_Mood==PRESCALER_ADC_64
	CLR_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
	#elif    Prescaler_Mood==PRESCALER_ADC_128
	SET_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
	#endif
	
	/********************ADC ENABLE************/
	SET_BIT(ADCSRA,ADEN);
	/**********MOODS OF STORAGE*************/
	#if    ADC_Mood_Storage==Right
	CLR_BIT(ADMUX,ADLAR);
	#elif  ADC_Mood_Storage==Left
    SET_BIT(ADMUX,ADLAR);
	#endif
}

void ADC_VidMood(void)
{
	#if    ADC_Mood==Single_Conversion_Mood
	CLR_BIT(ADCSRA,ADATE);
	#elif  ADC_Mood==Free_Running_Mood
	SET_BIT(ADCSRA,ADATE);//AUTO TRIGGER ENABLE
	/*FREE RUNNING MODE*/
	CLR_BIT(SFIOR,ADTS0);
	CLR_BIT(SFIOR,ADTS1);
	CLR_BIT(SFIOR,ADTS2);
	#endif
}

void ADC_VidChannel(u8 LOC_u8Channel)
{
	ADMUX=ADMUX&11100000;      //CLEAR ADMUX 
	ADMUX=ADMUX|LOC_u8Channel; //ASSIGN VALUE OF CHANNEL AT ADMUX
}

void ADC_VidStartConversion(void)
{
	SET_BIT(ADCSRA,ADSC);
}

void ADC_VidInterruptEnable(void)
{
	SET_BIT(ADCSRA,ADIE);
}

void ADC_VidPolling(void)
{
	while ( (GET_BIT(ADCSRA,ADIF)) != 1){} //WAITING FOR FLAG
	SET_BIT(ADCSRA,ADIF);                //CLEAR FLAG
}

void ADC_VidGetRes(u8*p)
{
	*p= ADC_REG;
}


    