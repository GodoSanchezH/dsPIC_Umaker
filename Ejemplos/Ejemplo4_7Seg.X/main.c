/* 
 * File:   main.c
 * Author: HP
 *
 * Created on October 2, 2022, 5:03 PM
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Config.h"
#include <libpic30.h>
#include <p33FJ32MC204.h>

uint8_t Display_7SegA[10]={0xC0,0xf9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
uint8_t i = 0;
uint8_t unidades = 0,decenas = 0,cuenta = 0;

void GPIO_Init(void);
void Ejemplo1(void);
 
int main(int argc, char** argv) {

    GPIO_Init();
    LATB = Display_7SegA[0];
    
    for(;;){
        unidades = cuenta%10;
        decenas = cuenta/10;
        
        for (i = 0; i < 255; i++) {
            
             LATB = Display_7SegA[unidades];
             LATCbits.LATC1 = 0;
             __delay_ms(1);
             LATCbits.LATC1 = 1;
             
             
             LATB = Display_7SegA[decenas];
                LATCbits.LATC0 = 0;
                __delay_ms(1);
                LATCbits.LATC0 = 1;
             
        
        }
        cuenta++;
        
        if(cuenta==100) cuenta =0;
                

        
        

    }
    
    return (EXIT_SUCCESS);
}

void GPIO_Init(void){

    AD1PCFGL = 0xFF;
    TRISB = 0x00;
    TRISC = 0x00;
    
}

void Ejemplo1(void){

    for (i = 0; i < 10; i++) {
            LATB = Display_7SegA[i];
            LATC = Display_7SegA[i];
            __delay_ms(800);
        }

}
