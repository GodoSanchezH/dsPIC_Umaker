#include "Timer_dsPIC.h"
#include <xc.h>

void __attribute__ ((interrupt,no_auto_psv)) _T1Interrupt(void){

    LATC ^= (1<<0);

 IFS0bits.T1IF = 0;
}
void __attribute__ ((interrupt,no_auto_psv)) _T2Interrupt(void){

    LATC ^= (1<<1);

 IFS0bits.T2IF = 0;
}
void __attribute__ ((interrupt,no_auto_psv)) _T3Interrupt(void){

    LATC ^= (1<<2);

 IFS0bits.T3IF = 0;
}

void Timer1_Init(void){

    T1CONbits.TON = 0;
    T1CONbits.TCS = 0;//fcy
    T1CONbits.TCKPS = 0b10;//64
    
    //50ms
    // pr1 ->   fcy*t/pre -1 
    //pr1 976
    PR1 = 2877;
    TMR1 = 0;
    
    /*habilito la interrupcion*/
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;
    IPC0bits.T1IP = 7;
    
    T1CONbits.TON = 1;
}
void Timer2_Init(void){
    T2CONbits.TON = 0;
    T2CONbits.TCS = 0;//fcy
    T2CONbits.TCKPS = 0b10;//64
    
    //50ms
    // pr1 ->   fcy*t/pre -1 
    //pr1 976
    PR2 = 2877;
    TMR2 = 0;
    
    /*habilito la interrupcion*/
    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0;
    IPC1bits.T2IP = 6;
    
    T2CONbits.TON = 1;
}
void Timer3_Init(void){
    T3CONbits.TON = 0;
    T3CONbits.TCS = 0;//fcy
    T3CONbits.TCKPS = 0b10;//64
    
    //50ms
    // pr1 ->   fcy*t/pre -1 
    //pr1 976
    PR3 = 2877;
    TMR3 = 0;
    
    /*habilito la interrupcion*/
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;
    IPC2bits.T3IP = 5;
    
    T3CONbits.TON = 1;
}
