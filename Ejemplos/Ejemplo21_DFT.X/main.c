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
#include <xc.h>
#include <math.h>
#include <dsp.h>

/*Numero de Muestras*/
#define N 32 

/*Estructura Compleja*/

struct Complex{

    float Real;
    float Imaginario;
};

/*Prototipamos las Funciones*/
    void DFT(float *x,struct Complex *X,uint16_t N_data);
    void ABS(struct Complex *X,float *Xm,uint16_t N_data);
    
 /*Variables*/
 /*DFT*/
    struct Complex X[N];
 /*Magnitud*/
    float Xm[N];
 /*Vector de Entrada*/
    float xn[N];
    uint16_t k=0,n=0;
    uint16_t adc=0;
    float signal =0;
    bool flag = false;

/*Ts*/
void __attribute__ ((interrupt,no_auto_psv)) _T3Interrupt(void){
   
   // adc = AnalogRead(AN0);
    //flag=true;
    IFS0bits.T3IF = 0;
}




main(int argc, char** argv) {

    TRISBbits.TRISB15 = 0;
    Analog_Init(Modo_12bits);
    UART_dsPIC_Init(9600,one_bit_Stop,Ocho_D_SP,1);
    Timer_Temporizador(Timer3,0,0.002,64);

    for(;;){
        
       
    for (n = 0; n <=N-1 ; n++) {
        
        adc=AnalogRead(AN0);
        
        signal = (float) (5.0*adc/4096.0)-2.5;
        
        xn[n]=signal;
        
    }
    //HACEMOS EL CALCULO
    DFT(xn,X,N);
    ///DETERMINAMOS EL MODULO
    ABS(&X[0],Xm,N);
    
    //muestreamos:
        for (k = 0; k <= N/2-1; k++) {
          
            printf("%.3f\n\r",Xm[k]);

        }

    
    

        

    }
    
    
    return (EXIT_SUCCESS);
}

/*Desarrollo las Funciones*/
    void DFT(float *x,struct Complex *X,uint16_t N_data){
        uint16_t n=0,k=0;
        float Img,Real;
        /*for por cada muestra de frecuencia*/
        for (k = 0; k <= N_data-1; k++) {
            
             for (n = 0; n <= N_data-1; n++) {
            
                 //parte real
                 Real = Real + xn[n]*cos(2*PI*k*n/N_data);
                 
                 //parte imaginaria
                 Img = Img + xn[n]*sin(-2*PI*k*n/N_data);
                }

             X[k].Real = Real;
             X[k].Imaginario = Img;
            
         }

    
    }
    void ABS(struct Complex *X,float *Xm,uint16_t N_data){
    
        uint16_t k;
    for ( k= 0;  k< N_data-1; k++) {

    *(Xm+k)=(float) sqrt(pow((X+k)->Imaginario,2)+pow((X+k)->Real,2));

    }

    
    }