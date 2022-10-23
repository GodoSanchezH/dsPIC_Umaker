/* 
 * File:   main.c
 * Author: HP
 *
 * Created on October 15, 2022, 5:22 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Config.h"
#include "Timer_dsPIC.h"
#include <libpic30.h>
#include <p33FJ32MC204.h>

/*
 * 
 */
int main(int argc, char** argv) {

    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    
    Timer1_Init();
    Timer2_Init();
    Timer3_Init();
    
    for (;;) {
        

    }

    
    
    return (EXIT_SUCCESS);
}

