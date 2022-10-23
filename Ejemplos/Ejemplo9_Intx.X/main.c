/* 
 * File:   main.c
 * Author: HP
 *
 * Created on 15 de octubre de 2022, 04:07 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Config.h"
#include <libpic30.h>
#include <stdbool.h>
#include <stdint.h>
#include "Interrupt_external.h"
#include <xc.h>
/*
 * 
 */
//uint8_t i=0;
volatile bool a=false,b=false,c=false;
int main(int argc, char** argv) {

    INT0_Config();
    TRISC = 0X0000;
    
   for(;;){
   
//       
//       if(a){
//            for(i=0;i<=5;i++){
//                LATC = 0xF0;
//                 __delay_ms(300);   
//                 LATC = 0x0F;
//                 __delay_ms(300); 
//            }
//            LATC = 0x00;
//            a = false;
//       }
//        if(b){
//            for(i=0;i<=5;i++){
//                LATC = 0xFF;
//                 __delay_ms(300);   
//                 LATC = 0x00;
//                 __delay_ms(300); 
//            }
//            LATC = 0x00;
//            b = false;
//       }
//       if(c){
//            for(i=0;i<=5;i++){
//                LATC = 0b10101010;
//                 __delay_ms(300);   
//                 LATC = 0b01010101;
//                 __delay_ms(300); 
//            }
//            LATC = 0x00;
//            c = false;
//       }
//   
   
   }
    
    
    return (EXIT_SUCCESS);
}

