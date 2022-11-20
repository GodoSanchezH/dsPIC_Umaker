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
#include "dsp.h"
#include <xc.h>
/*
 * 
 */
fractcomplex Ia;
   int i;
uint8_t Display_7SegA[10]={0xC0,0xf9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
int main(int argc, char** argv) {

    I2C_Init(100);
    
    Ia.imag = 1.33;
    Ia.real = 2.32;
    
    asm("nop");
    for(;;){
    
     
        for (i = 0; i < 10; i++) {
            I2C_Start();
            I2C_Write_Addres_Data_Slave(0b01000000,0);
            //I2C_Write_Data_Slave(0x64);
            I2C_Write_Data_Slave(Display_7SegA[i]);
            I2C_Stop();
            __delay_ms(300);
        }

    
    
        
    }
    
    
    return (EXIT_SUCCESS);
}

