/* 
 * File:   main.c
 * Author: HP
 *
 * Created on 23 de octubre de 2022, 05:31 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Config.h"
#include <libpic30.h>
#include "I2C.h"
#include "RTC.h"
#include "Uart.h"
#include <xc.h>

char rx;
void __attribute__ ((interrupt,no_auto_psv)) _U1RXInterrupt(void){
    
    if (U1STAbits.OERR ==1) {
       U1STAbits.OERR = 0;
    }
    else if((U1STAbits.PERR==0) && (U1STAbits.FERR==0)){
    
        rx = (char)U1RXREG;

    }

    
 IFS0bits.U1RXIF = 0;//CLEAN
}
   int i;
uint8_t Display_7SegA[10]={0xC0,0xf9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
uint8_t Horas,Segundos,Minutos;
uint8_t Dia_S , Dia , Mes , A;
int main(int argc, char** argv) {

    Uart_Init(9600);
    I2C_Init(100);
    DS1307_Init();
    DS1307_Write_Hours_24(16,34,30);
    DS1307_Write_Date(29,10,22,6);
    
    for(;;){
    
     
        DS1307_Read_H_24(&Horas,&Minutos,&Segundos);
        DS1307_Read_Date(&Dia,&Mes,&A,&Dia_S);
        
        printf("\n\r***Calendario RTC***\n\r");
        printf("Hora:%u - Minutos:%u - Segundo:%u\n\r",Horas,Minutos,Segundos);
        printf("Dia:%u - Mes:%u - Year:%u \n\r",Dia,Mes,A);
        printf("Estamos en el dia %u de la semana\n\r",Dia_S);
    __delay_ms(500);
        
    }
    
    
    return (EXIT_SUCCESS);
}

