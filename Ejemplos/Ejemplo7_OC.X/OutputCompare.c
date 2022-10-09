#include "OutputCompare.h"
#include <xc.h>


void OC1_Pin_Config(void){

/*RB7 como salida*/
    TRISB &= ~(1<<7);
    
/*remapeamos*/
  RPOR3bits.RP7R = 0b10010;
}

void Timer2_Init(void){
/*Iniciamos con el Timer Apagado*/
T2CONbits.TON = 0;

/*Seleccionamos la Fuente de Reloj*/
T2CONbits.TCS = 0;

/*Preescalador 1*/
T2CONbits.TCKPS = 1; // cuenta 0.2us

/* Modo de 16 bits*/
T2CONbits.T32 = 0;

/* FCY = 5MHZ 
   TCY = 0.2uS
 */
    
}
void OC1_Active_Low_One_Shot(void){
/*Desabilitamos el Modulo OC1*/
    OC1CONbits.OCM = 0B000;
    
/*Seleccionamos el Timer*/    
    OC1CONbits.OCTSEL =0;//timer2
    
/*ISR*/

IEC0bits.OC1IE = 1;
IFS0bits.OC1IF = 0;
IPC0bits.OC1IP = 7;
 
/*ACTIVAMOS EL MODO ONE SHOT*/
  OC1CONbits.OCM = 0B001;

  OC1R = 200;
/*Disparamos el Timer*/
T2CONbits.TON = 1;   
}
void OC1_Active_High_One_Shot(void){
/*Desabilitamos el Modulo OC1*/
    OC1CONbits.OCM = 0B000;
    
/*Seleccionamos el Timer*/    
    OC1CONbits.OCTSEL =0;//timer2
    
/*ISR*/

IEC0bits.OC1IE = 1;
IFS0bits.OC1IF = 0;
IPC0bits.OC1IP = 7;
 
/*ACTIVAMOS EL MODO ONE SHOT*/
  OC1CONbits.OCM = 0B010;

  OC1R = 1000;
/*Disparamos el Timer*/
// TMR2 =0;
T2CONbits.TON = 1;   
}
void OC1_Toggle_mode(void){
/*Desabilitamos el Modulo OC1*/
    OC1CONbits.OCM = 0B000;
    
/*Seleccionamos el Timer*/    
    OC1CONbits.OCTSEL =0;//timer2
    
/*ISR*/

IEC0bits.OC1IE = 1;
IFS0bits.OC1IF = 0;
IPC0bits.OC1IP = 7;
 
/*ACTIVAMOS EL MODO Togle*/
  OC1CONbits.OCM = 0B011;

  OC1R = 1000;
/*Disparamos el Timer*/
// TMR2 =0;
T2CONbits.TON = 1;   
}
void OC1_Delayed_One_Shot(void){

}
void OC1_Continuous_Pulse(void){

}
void OC1_PWM(void){

}



void __attribute__ ((interrupt,no_auto_psv)) _OC1Interrupt(void){


   TMR2 =0;
IFS0bits.OC1IF = 0;
}