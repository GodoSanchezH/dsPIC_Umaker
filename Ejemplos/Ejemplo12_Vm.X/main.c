/* 
 * File:   main.c
 * Author: HP
 *
 * Created on 23 de octubre de 2022, 03:29 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Config.h"
#include <libpic30.h>
#include "LCD_dsPIC.h"
#include <xc.h>
#include <string.h>

uint16_t PULSOS=0;
float rpm,FrecAngular;
char buffer[20];
void __attribute__ ((interrupt,no_auto_psv)) _OC1Interrupt(void){


   //TMR2 =0;
IFS0bits.OC1IF = 0;
}
void __attribute__ ((interrupt,no_auto_psv)) _T1Interrupt(void){

    PULSOS = TMR3;
    TMR3 =0;
    /**calculo los rpm*/
    rpm =PULSOS*60/(0.01*24);
  //  memset(buffer,0,20);
    FrecAngular= rpm*(2*3.141592)/60;
    LATC ^= (1<<0);
    
 IFS0bits.T1IF = 0;
}
void OC1_PWM(void);
void OC1_Pin_Config(void);
void Timer2_Init(void);
void Timer3_Init(void);
void Timer1_Init(void);
int main(int argc, char** argv) {

    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    LATBbits.LATB2 =1;
    LATBbits.LATB3 = 0;
    TRISCbits.TRISC0 = 0; 
    OC1_Pin_Config();
    Timer2_Init();
    Timer1_Init();
    Timer3_Init();
    OC1_PWM();
  
    LCD_dsPIC_Init();
    LCD_dsPIC_SetCursor(0,Fila1);
    LCD_dsPIC_Print_String("Vel. Motor");
   
    OC1RS = 100;
    
    for (;;) {
        
  sprintf(buffer,"RPM:%0.2f",FrecAngular);
  
    LCD_dsPIC_SetCursor(0,Fila2);
    LCD_dsPIC_Print_String(buffer);
    __delay_ms(200);
    }

    
    
    return (EXIT_SUCCESS);
}
void OC1_PWM(void){
/*Desabilitamos el Modulo OC1*/
    OC1CONbits.OCM = 0B000;
    
/*Seleccionamos el Timer*/    
    OC1CONbits.OCTSEL =0;//timer2
    
/*ISR*/

IEC0bits.OC1IE = 1;
IFS0bits.OC1IF = 0;
IPC0bits.OC1IP = 7;
 
/*ACTIVAMOS EL MODO continuous pulse*/
  OC1CONbits.OCM = 0B110;

  TMR2 = 0x0000;  
  PR2  = 249;
  //OC1RS = 5000;
  
/*Disparamos el Timer*/
// TMR2 =0;
T2CONbits.TON = 1;  
    
    
}
void OC1_Pin_Config(void){

/*RB7 como salida*/
    TRISB &= ~(1<<7);
    
/*remapeamos*/
  RPOR3bits.RP7R = 0b10010;
}
void Timer3_Init(void){
    T3CONbits.TON = 0;
    T3CONbits.TCS = 1;//CLOCK EXTERNO
    T3CONbits.TCKPS = 0b0;//1
    
    PR3 = 0XFFFF;
    TMR3 = 0;
    T3CONbits.TON = 1;
    RPINR3bits.T3CKR = 0X9;//RB9
    /*DEFINIMOS SU PIN DE ENTRADA*/
}
void Timer2_Init(void){
/*Iniciamos con el Timer Apagado*/
T2CONbits.TON = 0;

/*Seleccionamos la Fuente de Reloj*/
T2CONbits.TCS = 0;

/*Preescalador 8*/
T2CONbits.TCKPS = 1; // 

/* Modo de 16 bits*/
T2CONbits.T32 = 0;

/* FCY = 5MHZ 
   TCY = 0.2uS
 */
    
}
void Timer1_Init(void){
    T1CONbits.TON = 0;
    T1CONbits.TCS = 0;//fcy
    T1CONbits.TCKPS = 0b1;//8
    //10ms
    // pr1 ->   fcy*t/pre -1 
    //pr1 976
    PR1 = 2499;
    TMR1 = 0;
    
    /*habilito la interrupcion*/
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;
    IPC0bits.T1IP = 7;
    
    T1CONbits.TON = 1;

}
