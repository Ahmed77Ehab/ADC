#ifndef   _ADC_PRIV_H
#define   _ADC_PRIV_H



#define  ADMUX       *((volatile u8*)  0x27)
#define  ADCSRA      *((volatile u8*)  0x26)
#define  ADCH        *((volatile u8*)  0x25)
#define  ADCL        *((volatile u8*)  0x24)
#define  SFIOR       *((volatile u8*)  0x50)

#define  ADC_REG     *((volatile u16*)  0x24)



#endif