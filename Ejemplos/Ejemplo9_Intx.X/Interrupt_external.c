#include "Interrupt_external.h"
#include <xc.h>
#include "Config.h"
#include <libpic30.h>
#include <stdbool.h>

extern volatile bool a;
extern volatile bool b;
extern volatile bool c;

uint8_t i,j,k;

void __attribute__ ((interrupt,no_auto_psv)) _INT0Interrupt(void){

   // a=true;
    for(i=0;i<=5;i++){
                LATC = 0xF0;
                 __delay_ms(300);   
                 LATC = 0x0F;
                 __delay_ms(300); 
            }
            LATC = 0x00;
    IFS0bits.INT0IF = 0;
}


void __attribute__ ((interrupt,no_auto_psv)) _INT1Interrupt(void){

    b=true;
       for(j=0;j<=5;j++){
                LATC = 0xFF;
                 __delay_ms(300);   
                 LATC = 0x00;
                 __delay_ms(300); 
            }
            LATC = 0x00;
    IFS1bits.INT1IF = 0;
}

void __attribute__ ((interrupt,no_auto_psv)) _INT2Interrupt(void){

    c=true;
       for(k=0;k<=5;k++){
                LATC = 0b10101010;
                 __delay_ms(300);   
                 LATC = 0b01010101;
                 __delay_ms(300); 
            }
            LATC = 0x00;
    IFS1bits.INT2IF = 0;
}

void INT0_Config(void){
    
    //asignamos los pines
      /* rb7= int0
        rn15 =  inti
        rb14 = int2
       */
    
    
    //INT0
    
    TRISB |= (1<<7);
    IEC0bits.INT0IE = 1;
    IFS0bits.INT0IF = 0;
    IPC0bits.INT0IP = 0b111;
    INTCON2bits.INT0EP = 1 ;
   
    //Int1
     TRISB |= (1<<15);
     RPINR0bits.INT1R = 15;
    IEC1bits.INT1IE = 1;
    IFS1bits.INT1IF = 0;
    IPC5bits.INT1IP = 0b110;
    INTCON2bits.INT1EP = 1 ;
   
    
    
    //INT2
    TRISB |= (1<<14);
    RPINR1bits.INT2R = 14;
    IEC1bits.INT2IE = 1;
    IFS1bits.INT2IF = 0;
    IPC7bits.INT2IP = 0b1;
    INTCON2bits.INT2EP = 0 ;
   
}
