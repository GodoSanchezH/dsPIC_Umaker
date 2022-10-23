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

void ConfigGpio(void);
void TimerInit(void);
uint16_t Distancia_Ultrasonido(void);
uint16_t distancia;
char str_distancia[50];
int main(int argc, char** argv) {

    ConfigGpio();
    LCD_dsPIC_Init();
    TimerInit();
    
    LCD_dsPIC_SetCursor(0,Fila1);
    LCD_dsPIC_Print_String("Sensor Ultrasonido");
   
   
    for (;;) {
        
        distancia = Distancia_Ultrasonido()+1;
        
        sprintf(str_distancia,"dist:%03ucm",distancia);
        
    LCD_dsPIC_SetCursor(0,Fila2);
    LCD_dsPIC_Print_String(str_distancia);
    
    }

    
    
    return (EXIT_SUCCESS);
}

void ConfigGpio(void){
   
    //Triguer
    TRISC &= ~(1<<5);
    //Echo
    TRISC |= (1<<4);

}
void TimerInit(void){
    T1CONbits.TON = 0;
    T1CONbits.TCS = 0;//fcy
    T1CONbits.TCKPS = 0b00;//64
    
    PR1 = 0xFFFF;
    TMR1 = 0;
   
    
}
uint16_t Distancia_Ultrasonido(void){

    uint16_t Time;
    float Dist;
    
    LATC |= (1<<5);///triguer a 1
    __delay_us(10);
    LATC &= ~(1<<5);
    TMR1 = 0;
    while(PORTCbits.RC4 ==0);
    T1CONbits.TON = 1;//habilito timer
    while(PORTCbits.RC4 ==1);
    T1CONbits.TON = 0;
    Time = TMR1;
    
    Dist = TMR1/117;
    
    return (uint16_t) Dist;
}



