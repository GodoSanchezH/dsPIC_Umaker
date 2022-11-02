
#include "Uart.h"
#include "Config.h"
#include <stdio.h>
#include <xc.h>

void Uart_Init(uint32_t Baudios){

    /*Configuracion de los Pines*/
    /*RX-RB9*/
    TRISB |=(1<<11);
    RPINR18bits.U1RXR = 11 ;
    /*TX-RB8*/
    TRISB &= ~(1<<10);
    RPOR5bits.RP10R =0b00011;
    
    /*Iniciamos la configuracion*/
    
    /*apagamos la UART*/
    U1MODEbits.UARTEN = 0;//off

    /*Stop bit*/
    U1MODEbits.STSEL = 0;//1 bit de stop
    
    /*Paridad & Data*/
    U1MODEbits.PDSEL = 0b00;//8bit - sin paridad
    
    /*Selector de Baudios*/
    U1MODEbits.BRGH = 0;//16/FCY
    
    /*Calcular los Baudios*/
    U1BRG = (uint16_t) ((FCY/16/Baudios)-1);
    
    /*Habilitamos la TX*/
    U1STAbits.UTXEN = 1;//TX on
    
    /*Habilitamos la RX*/
    U1STAbits.URXISEL = 0b00;
    
    /*Habilitamos la Interrupcion de la UART*/
    IEC0bits.U1RXIE =1;//ON 
    IFS0bits.U1RXIF = 0;//CLEAN
    IPC2bits.U1RXIP = 0B111;//ALTA PRIORIDAD        
            
    /*Encendemos la UART*/
    U1MODEbits.UARTEN = 1;//on   
}
void Uart_TX_Char(char c){
    while(U1STAbits.UTXBF==1);
    U1TXREG = c;
}

void Uart_TX_String(char *str){
    char *ptr;
    ptr = str;
    while(*ptr)
        Uart_TX_Char(*ptr++);
    
}

int write(int handle, void *buffer, unsigned int len){

    int i;
    switch(handle)
    {
        case 0:
        case 1:
        case 2:
        default:
            for(i=0;i<len;i++)                
                Uart_TX_Char(*(char*)buffer++);
       
    }
    
    return(len);
}
