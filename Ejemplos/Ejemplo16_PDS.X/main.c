/* 
 * File:   main.c
 * Author: HP
 *
 * Created on 26 de noviembre de 2022, 06:41 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>

#define N_Max_Coef 2

/*coeficientes*/
#define a0 0.1116 
#define a1 0.1116 
#define b0 0.7767



/*Ts*/
void __attribute__ ((interrupt,no_auto_psv)) _T1Interrupt(void){

    X.adc;
 IFS0bits.T1IF = 0;
}
#define c0 0.0287615832015545	
#define c1 0.143095989407480	
#define c2 0.328142427390966	
#define c3 0.328142427390966	
#define c4 0.143095989407480	
#define c5 0.0287615832015545
/*Entradas*/
typedef struct{
   float n[N_Max_Coef];
   uint16_t adc;
}Entradas;
/*Salidas*/
typedef struct{
    float n[N_Max_Coef];
}Salidas;

Entradas X;
Salidas Y;

uint8_t i;
main(int argc, char** argv) {

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
        
        X.n[1] = X.n[0];
        X.n[0] = X.adc;
        
        Y[1] = Y[0];
        
        Y[0] = X.n[0]*a0 + X.n[1]*a1- Y[1]*b0;
            
       /*muestrear dac*/ 
       /*dac_Send(Y[0])*/
        /**LatB = Y[0]*/
    }
    
    
    return (EXIT_SUCCESS);
}

