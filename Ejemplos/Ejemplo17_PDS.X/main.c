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
#include "Configuracion.h"
#include <libpic30.h>
#include "ADC_dspic.h"
#include "Uart_dspic.h"
#include "Timer_dsPIC.h"
#include "I2C_dspic.h"
#include <xc.h>

#define N_Max_Coef 15

#define PasaBajo 1

#ifdef PasaBajo
/*coeficientes*/
#define a0 0.1116 
#define a1 0.1116 
#define b0 0.7767
#elif  PasaAlto
#define a0 0.9876
#define a1 0.9876
#define b0 0.9752

#elif FIR
#define c0  0.00357339134833414														
#define c1 	0.00664771989932296
#define c2 	0.0153299607846751
#define c3 0.0294048295549019
#define c4 	0.0466563167060366
#define c5 0.0633940391432615
#define c6 0.0755543491619574
#define c7 0.0800000000000000 
#define c8 0.0755543491619574
 #define c9 0.0633940391432615
#define c10 0.0466563167060366
#define c11 0.0294048295549019
#define c12 0.0153299607846751
#define c13 0.00664771989932296
#define c14 0.00357339134833414


#endif
volatile bool flag;
            
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
    Timer_Temporizador(Timer3,0,0.002,64);
    I2C_Init(100);
    
    //Uart_Init(115200);
    /*Inicilisamos las variables*/
    for (i = 0; i < N_Max_Coef; i++) {
        X.n[i] = 0;
    }
    for (i = 0; i < N_Max_Coef; i++) {
        Y.n[i] = 0;
    }
    
/*pasa bajao funcion discretizada*/ 
//      0.1116 z + 0.1116
//  -----------------
//     z - 0.7767
// 
    
  /*pasa alto funcion discretizada*/
//Fd =
// 
//  0.8884 z - 0.8884
//  -----------------
//     z - 0.7767
// 
//Sample time: 0.02 seconds

    for(;;){
        
        if (flag) {
         
        X.n[14] = X.n[13];
        X.n[13] = X.n[12];
        X.n[12] = X.n[11];
        X.n[11] = X.n[10];
        X.n[10] = X.n[9];
        X.n[9] = X.n[8];
        X.n[8] = X.n[7];
        X.n[7] = X.n[6];
        X.n[6] = X.n[5];
        X.n[5] = X.n[4];
        X.n[4] = X.n[3];      
        X.n[3] = X.n[2];
        X.n[2] = X.n[1];
        X.n[1] = X.n[0];
        X.n[0] = X.adc;
        Y.n[1] = Y.n[0];
        
#ifdef PasaBajo       
        Y.n[0] = X.n[0]*a0 + X.n[1]*a1- Y.n[1]*b0;
#elif PasaAlto
        Y.n[0] = +X.n[0]*a0 - X.n[1]*a1- Y.n[1]*b0;
#elif FIR

       Y.n[0]  = c0*X.n[0]+c1*X.n[1]+c2*X.n[2]+c3*X.n[3]+c4*X.n[4]+c5*X.n[5]+c6*X.n[6]+c7*X.n[7]+c8*X.n[8]+c9*X.n[9]+c10*X.n[10]+c11*X.n[11]+c12*X.n[12]+c13*X.n[13]+c14*X.n[14];

#endif
        temp = (uint16_t) Y.n[0];
          //0000 0000 0000 0000 
        I2C_Start();
        I2C_Write_Data_Slave(0xC0);
        I2C_Write_Data_Slave(temp>>8);
        I2C_Write_Data_Slave(temp);
        I2C_Stop();
          //__delay_ms(1);

            flag = false;
        }

        

    }
    
    
    return (EXIT_SUCCESS);
}

