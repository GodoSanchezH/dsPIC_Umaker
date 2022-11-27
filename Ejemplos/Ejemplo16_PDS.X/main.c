/* 
 * File:   main.c
 * Author: HP
 *
 * Created on 26 de noviembre de 2022, 06:41 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "Config.h"
#include <libpic30.h>
#include "ADC.h"
//#include "Uart.h"
#include "I2C.h"
#include <xc.h>

#define N_Max_Coef 2

/*coeficientes*/
#define a0 0.1116 
#define a1 0.1116 
#define b0 0.7767

volatile bool flag;


#define c0 0.0287615832015545	
#define c1 0.143095989407480	
#define c2 0.328142427390966	
#define c3 0.328142427390966	
#define c4 0.143095989407480	
#define c5 0.0287615832015545
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

void Ts_Init(void);

uint16_t temp;
main(int argc, char** argv) {

    TRISBbits.TRISB15 = 0;
    Ts_Init();
    ADC_Init();
    I2C_Init(100);
    
    //Uart_Init(115200);
    /*Inicilisamos las variables*/
    for (i = 0; i < N_Max_Coef; i++) {
        X.n[i] = 0;
    }
    for (i = 0; i < N_Max_Coef; i++) {
        Y.n[i] = 0;
    }
//      0.1116 z + 0.1116
//  -----------------
//     z - 0.7767
// 
    
    for(;;){
        
//        if (flag) {
        
//        X.n[6] = X.n[5];
//        X.n[5] = X.n[4];
//        X.n[4] = X.n[3];
//        X.n[3] = X.n[2];
//        X.n[2] = X.n[1];
        X.n[1] = X.n[0];
        X.n[0] = X.adc;
        
        Y.n[1] = Y.n[0];
        
        Y.n[0] = X.n[0]*a0 + X.n[1]*a1- Y.n[1]*b0;
            
        temp = (uint16_t) Y.n[0];
          //0000 0000 0000 0000 
        I2C_Start();
        I2C_Write_Data_Slave(0xC0);
        I2C_Write_Data_Slave(temp>>8);
        I2C_Write_Data_Slave(temp);
        I2C_Stop();
           __delay_ms(1);
///**/
//            flag = false;
//        }

        

    }
    
    
    return (EXIT_SUCCESS);
}

void Ts_Init(void){
//timer 3
    T3CONbits.TON = 0;
    T3CONbits.TCS = 0;//fcy
    T3CONbits.TCKPS = 0b00;//64
    
    //50ms
    // pr1 ->   fcy*t/pre -1 
    //pr1 976
    PR3 = 4999;//1khz
    TMR3 = 0;
    
    /*habilito la interrupcion*/
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;
    IPC2bits.T3IP = 5;
    
    T3CONbits.TON = 1; 

}