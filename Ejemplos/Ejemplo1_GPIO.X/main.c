/* 
 * File:   main.c
 * Author: HP
 *
 * Created on October 1, 2022, 5:57 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p33FJ32MC202.h>
#include "Config.h"
#include <libpic30.h>

/*
 * 
 */

void  Ejemplo1(void);

int main(int argc, char** argv) {

    //Pines de salida  RB0 , RB1 ,RB2 , RB3
    //Definimos como pines digitales
    AD1PCFGL |= (1<<2) | (1<<3) | (1<<4) | (1<<5);
    
    //Definimos las salidas  (TRISX) 0-> Salida 1-> entrada
    TRISB &= ~(1<<0) & ~(1<<1) & ~(1<<2) & ~(1<<3);
    
   // Definimoslas entradas:
    TRISB |= (1<<14) | (1<<15);
    
    for(;;){
    
        
    
    }
    
    
    return (EXIT_SUCCESS);
}

void  Ejemplo1(void){

LATB ^= (1<<0) | (1<<1) | (1<<2) | (1<<3) ;
        __delay_ms(500);
}


