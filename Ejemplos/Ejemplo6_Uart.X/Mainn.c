/* 
 * File:   main.c
 * Author: HP
 *
 * Created on 8 de octubre de 2022, 03:23 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Config.h"
#include "ADC.h"
#include "Uart.h"
#include <xc.h>
#include <libpic30.h>

uint16_t dato1,dato2,dato3,dato4,dato5,dato6;
char str_dato1[10],str_dato2[10],str_dato3[10],str_dato4[10],str_dato5[10],str_dato6[10];

void __attribute__ ((interrupt,no_auto_psv)) _U1RXInterrupt(void){

 IFS0bits.U1RXIF = 0;//CLEAN
}



int main(int argc, char** argv) {
    

    ADC_Init();
    Uart_Init(115200);
    for(;;){
       dato1 =  AnalogRead(AN0);
       dato2 =  AnalogRead(AN1);
       dato3 =  AnalogRead(AN2);
       dato4 =  AnalogRead(AN3);
       dato5 =  AnalogRead(AN4);
       dato6 =  AnalogRead(AN5);
       
       printf("\r\r***LECTURAS ANALOGICAS****\n\rADC0:%u \n\rADC1:%u \n\rADC2:%u \n\rADC3:%u \n\rADC4:%u \n\rADC5:%u \n\n\n",dato1,dato2,dato3,dato4,dato5,dato6);
       

        //printf("Hola Mundo dsPIC33\n\r");
       
       __delay_ms(200);
    
    }
    
    
    return (EXIT_SUCCESS);
}

