/* 
 * File:   main.c
 * Author: HP
 *
 * Created on 2 de octubre de 2022, 03:23 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Config.h"
#include <libpic30.h>
#include <p33FJ32MC204.h>


/*Enumeracion*/
typedef enum{
    SemaforoINIT=0,
            Paso_Av_Universitaria,
            Paso_Av_Argentina,
            Precaucion

}State;


State State_Semaforo = SemaforoINIT;

/*Macros*/

#define Semaforo_Auto_Init  0b00001001
#define Pase_Autos_Av_Universitaria   0b00001100
#define Pase_Autos_Av_Argentina   0b00100001
#define Alerta  0b00010010
#define Semaforo_Peatones_Init 0b00000101
#define Pase_Peatones_Av_Universitaria 0b00001001
#define Pase_Peatones_Av_Argentina 0b00000110

/*FUNCIONES*/
void GPIO_Init(void);
void Semaforo_Init(void);
void Activar_Paso_Av_Argentina(void);
void Activar_Paso_Av_Universitaria(void);
void Activar_Precaucion(void);

/*variables*/

uint8_t est_precaucion=0;

int main(int argc, char** argv) {

    GPIO_Init();
    
    for (;;) {
       

        switch(State_Semaforo){
            
            case SemaforoINIT:
                
                Semaforo_Init();
                
                break;
        /*****************************/       
            case Paso_Av_Universitaria:
                Activar_Paso_Av_Universitaria();
                
                break;
        /*****************************/  
            case Paso_Av_Argentina:
                Activar_Paso_Av_Argentina();
                
                
                break;
        /*****************************/          
            case Precaucion:
                
                Activar_Precaucion();
                
                break;        
        }
        
        
    }

    
    
    
    return (EXIT_SUCCESS);
}

void GPIO_Init(void){

//Ponemos todos los fines a digital
    AD1PCFGL = 0xFF;
//Definimos como salidas al puerto A y al Puerto B
    TRISC &= ~(1<<0) & ~(1<<1) & ~(1<<2) & ~(1<<3);
    TRISB &= ~(1<<0) & ~(1<<1) & ~(1<<2) & ~(1<<3)& ~(1<<4)& ~(1<<5);

}

void Semaforo_Init(void){

    LATC = Semaforo_Peatones_Init;
    LATB = Semaforo_Auto_Init;
    __delay_ms(300);
    State_Semaforo = Paso_Av_Argentina;
}

void Activar_Paso_Av_Argentina(void){
    LATC = Pase_Peatones_Av_Universitaria;
    LATB = Pase_Autos_Av_Argentina ;
    __delay_ms(500);
    State_Semaforo = Precaucion;
    est_precaucion++;
}
void Activar_Paso_Av_Universitaria(void){
    LATC = Pase_Peatones_Av_Argentina;
    LATB = Pase_Autos_Av_Universitaria ;
    __delay_ms(500);
    State_Semaforo = Precaucion;
    est_precaucion++;

}
void Activar_Precaucion(void){

    LATB = Alerta ;
    __delay_ms(200);
    
    switch(est_precaucion){
        case 1:
        State_Semaforo = Paso_Av_Universitaria;    
        
            break; 
        case 2:
         State_Semaforo = Paso_Av_Argentina;  
         est_precaucion =0;
            break;
    }

}
