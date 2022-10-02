/* 
 * File:   main.c
 * Author: HP
 *
 * Created on October 2, 2022, 4:14 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Config.h"
#include <libpic30.h>
#include "LCD_dsPIC.h"


/*
 * 
 */
int main(int argc, char** argv) {
    
    LCD_dsPIC_Init();
    LCD_dsPIC_New_Char(1,0x0A,0x1F,0x1F,0x1F,0x0E,0x04,0x00,0x00);
    LCD_dsPIC_New_Char(2,0x0E,0x1B,0x1F,0x18,0x1F,0x0E,0x00,0x00);
    LCD_dsPIC_New_Char(3,0x04,0x0E,0x0E,0x0E,0x0E,0x1F,0x04,0x00);
    LCD_dsPIC_SetCursor(0,0);
    LCD_dsPIC_Print_String("Bienvidos al Curso");
    LCD_dsPIC_SetCursor(0,1);
    LCD_dsPIC_Print_String("de Procesamiento");
    LCD_dsPIC_Write_New_Char(1);
    LCD_dsPIC_SetCursor(0,2);
    LCD_dsPIC_Print_String("Digital de Signal");
    LCD_dsPIC_Write_New_Char(2);
    LCD_dsPIC_SetCursor(0,3);
    LCD_dsPIC_Print_String("con dsPIC");
    LCD_dsPIC_Write_New_Char(3);
    for (;;) {
        
    }

    
    return (EXIT_SUCCESS);
}

