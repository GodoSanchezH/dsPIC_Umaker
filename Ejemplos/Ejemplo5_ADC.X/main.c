/* 
 * File:   main.c
 * Author: HP
 *
 * Created on 8 de octubre de 2022, 03:23 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Config.h"
#include "ADC.h"
#include "LCD_dsPIC.h"
#include <libpic30.h>

float dato1,dato2,dato3,dato4,dato5,dato6;
char str_dato1[10],str_dato2[10],str_dato3[10],str_dato4[10],str_dato5[10],str_dato6[10];
int main(int argc, char** argv) {
    
    LCD_dsPIC_Init();
    ADC_Init();
    
    for(;;){
       dato1 =  AnalogRead(AN0)*0.01221;
       dato2 =  AnalogRead(AN1)*0.01221;
       dato3 =  AnalogRead(AN2)*0.01221;
       dato4 =  AnalogRead(AN3)*0.01221;
       dato5 =  AnalogRead(AN4)*0.01221;
       dato6 =  AnalogRead(AN5)*0.01221;
       
       sprintf(str_dato1,"A0:%0.2f",dato1);
       sprintf(str_dato2,"A1:%0.2f",dato2);
       sprintf(str_dato3,"A2:%0.2f",dato3);
       sprintf(str_dato4,"A3:%0.2f",dato4);
       sprintf(str_dato5,"A4:%0.2f",dato5);
       sprintf(str_dato6,"A5:%0.2f",dato6);
       
       LCD_dsPIC_SetCursor(0,0);
       LCD_dsPIC_Print_String(str_dato1);
       LCD_dsPIC_SetCursor(0,1);
       LCD_dsPIC_Print_String(str_dato2);
       LCD_dsPIC_SetCursor(0,2);
       LCD_dsPIC_Print_String(str_dato3);
       LCD_dsPIC_SetCursor(0,3);
       LCD_dsPIC_Print_String(str_dato4);
       LCD_dsPIC_SetCursor(11,0);
       LCD_dsPIC_Print_String(str_dato5);
       LCD_dsPIC_SetCursor(11,1);
       LCD_dsPIC_Print_String(str_dato6);
       
       
       __delay_ms(200);
    
    }
    
    
    return (EXIT_SUCCESS);
}

