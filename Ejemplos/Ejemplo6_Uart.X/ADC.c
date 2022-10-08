
#include <p33FJ32MC202.h>
#include "Config.h"
#include <libpic30.h>
#include "ADC.h"

void ADC_Init(void){
    /*Definimos los pines ANx como Analogicos*/
    AD1PCFGL &= ~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5));
    
    //Puerto A
    TRISA |= (1<<0) | (1<<1);
    //Puerto B
    TRISB |= (1<<0) | (1<<1)| (1<<2)| (1<<3);
    
    
    /*Configuracion del ADC*/
    /*apagamos el ADC*/
    AD1CON1bits.ADON = 0;
    
    /*Modo de Trabajo */ 
    AD1CON1bits.AD12B = 1;//- 12 Bit
    
    /*Formato del dato*/
    AD1CON1bits.FORM = 0b00;//Integer
    
    /*Seleccion de Trigger*/
    AD1CON1bits.SSRC = 0b000;//Por Software
    
    /*Habilitador de Conversion*/
    AD1CON1bits.SAMP = 0;
    
    /*Seleccion de Voltaje de Referencia*/
    AD1CON2bits.VCFG = 0b000;//AVDD - AVSS
    
    /*Seleccion del Canal*/
    AD1CON2bits.CHPS = 0b00;
    
    AD1CHS0bits.CH0NA = 0;// Channel 0 negative input is VREF
    
    /*Tiempo de Muestreo*/
    AD1CON3bits.ADRC = 0; //FCY = 0.2uS
    AD1CON3bits.ADCS = 0b00000000;
    /*Encendemos el ADC*/
    AD1CON1bits.ADON = 1;
    //AD1CON1 |= (1<<ADON);
}


uint16_t AnalogRead(ChannelAnalog ANx){

    AD1CHS0bits.CH0SA = ANx;
    AD1CON1bits.SAMP = 1;
    __delay_ms(1);
    AD1CON1bits.SAMP = 0;
    while(!AD1CON1bits.DONE);//esperar q termine la conversion

 return ADC1BUF0;
}