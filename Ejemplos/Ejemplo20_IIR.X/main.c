/* 
 * File:   main.c
 * Author: HP
 *
 * Created on 2 de enero de 2023, 10:07 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "Configuracion.h"
#include <libpic30.h>
#include "ADC_dspic.h"
#include "Uart_dspic.h"
#include "Timer_dsPIC.h"
#include "I2C_dspic.h"
#include <dsp.h>
#include <xc.h>

extern IIRCanonicStruct Filter1;

#define Block 1
fractional FilterOut[Block];

volatile bool flag;
            

#define N_Max_Coef 10

/*Entradas*/
typedef struct{
   uint16_t n[N_Max_Coef];
   uint16_t adc;
}Entradas;
/*Salidas*/
typedef struct{
    float n[N_Max_Coef];
}Salidas;

Entradas X;
Salidas Y;

uint8_t i;

/*Ts*/
void __attribute__ ((interrupt,no_auto_psv)) _T3Interrupt(void){
   
    flag = true;
    
    LATB ^=(1<<15);
    X.adc = AnalogRead(AN0);
    IFS0bits.T3IF = 0;
}



uint16_t temp;


main(int argc, char** argv) {

    TRISBbits.TRISB15 = 0;
    Analog_Init(Modo_12bits);
    UART_dsPIC_Init(9600,one_bit_Stop,Ocho_D_SP,1);
    Timer_Temporizador(Timer3,0,0.02,1);
    I2C_Init(100);

    
    //inicializamos el filtro
    char *apuntador = NULL;
    uint8_t valor_h,valor_l;
    apuntador = &FilterOut;
    IIRCanonicInit(&Filter1);
   // FIRDelayInit(&lowpassexampleFilter);
    
    for (i = 0; i < N_Max_Coef; i++) {
        X.n[i] = 0;
    }
    for (i = 0; i < N_Max_Coef; i++) {
        Y.n[i] = 0;
    }
    

    for(;;){
        
        if (flag) {
         
            
            IIRCanonic(Block,&FilterOut,&X.adc,&Filter1);
            
            //FIR(Block,&FilterOut,&X.adc,&lowpassexampleFilter);
            valor_h = apuntador[1];
            valor_l = apuntador[0];;
            
          //0000 0000 0000 0000 
        I2C_Start();
        I2C_Write_Data_Slave(0xC0);
        I2C_Write_Data_Slave(valor_h & 0xF);
        I2C_Write_Data_Slave(valor_l);
        I2C_Stop();
          //__delay_ms(1);

            flag = false;
        }

        

    }
    
    
    return (EXIT_SUCCESS);
}

