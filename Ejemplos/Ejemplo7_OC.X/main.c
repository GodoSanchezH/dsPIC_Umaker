/* 
 * File:   main.c
 * Author: HP
 *
 * Created on 9 de octubre de 2022, 03:27 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Config.h"
#include "OutputCompare.h"
#include <libpic30.h>
#include <p33FJ32MC202.h>
/*
 * 
 */
int main(int argc, char** argv) {

    OC1_Pin_Config();
    Timer2_Init();
    OC1_PWM();
    
    for(;;){
    
        int i;
        for (i = 0; i <=999; i++) {
            OC1RS= i;
            __delay_ms(5);
        }

    
    }
    
    
    return (EXIT_SUCCESS);
}

