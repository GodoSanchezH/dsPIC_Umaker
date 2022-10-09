/* 
 * File:   mainn.c
 * Author: HP
 *
 * Created on 9 de octubre de 2022, 05:04 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
 * 
 */

char var1 __attribute__ ((space(ymemory)))= 'a';
uint8_t var2 __attribute__ ((space(ymemory))) = 250;
float var3 __attribute__ ((space(ymemory)))= 33.896;
char var4[]__attribute__ ((space(ymemory))) = "hola Mundo\r\n";


/*__attribute__((space))*/
/*->DMA*/
/*->DATOS*/
/*->PROGRAMA*/
/*->XMEMORY*/
/*->YMEMORY*/
/*->EEPROM*/
/*->PSV*/


int x_memory_buffer[5] __attribute__ ((space(xmemory))) = {0,1,2,3,4};
int y_memory_buffer[5] __attribute__ ((space(ymemory))) = {5,6,7,8,9};


void EjemploPrintf(void);
uint8_t i;
int main(int argc, char** argv) {

    asm("nop");
    asm("nop");
    printf("Simulacion XC16\n\r");
    
    asm("nop");
    printf("\n\r\n\r****MEMORIA X****\n\r");
    
    for (i = 0; i <=4; i++) {
        printf("\n\rLa direccion %u de la memoria X  es igual a %X, y sus valor es %u\n\r",i,&(x_memory_buffer[i]),x_memory_buffer[i]);

    }
    asm("MOV #0X16,W1");
    asm("MOV W1,0XC0E");

      asm("nop");
    printf("\n\r\n\r****MEMORIA y****\n\r");
    
    for (i = 0; i <=4; i++) {
        printf("\n\rLa direccion %u de la memoria Y  es igual a %X, y sus valor es %u\n\r",i,&(y_memory_buffer[i]),y_memory_buffer[i]);

    }
    
    for(;;){
    
    
    }
    
    
    return (EXIT_SUCCESS);
}
void EjemploPrintf(void){
  asm("nop");
    printf("dsPIC33\n\r"); 
    printf("\n\rVar1=%c",var1); 
    printf("\n\rVar2=%u",var2); 
    printf("\n\rVar3=%0.3f",var3);
    printf("\n\rVar4=%s",var4); 

}
