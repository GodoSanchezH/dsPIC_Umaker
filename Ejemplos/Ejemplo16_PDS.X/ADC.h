/* 
 * File:   ADC.h
 * Author: HP
 *
 * Created on 8 de octubre de 2022, 03:24 PM
 */

#ifndef ADC_H
#define	ADC_H

#include <stdint.h>

typedef enum{
    AN0=0,
            AN1,
            AN2,
            AN3,
            AN4,
            AN5
}ChannelAnalog;


void ADC_Init(void);
uint16_t AnalogRead(ChannelAnalog ANx);


#endif	/* ADC_H */

