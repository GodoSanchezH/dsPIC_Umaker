#include "Config.h"
#include "I2C.h"
#include <xc.h>
float delay,baud;

void I2C_Init(uint16_t F_scl){
/*120ns*/
     delay=120*0.000000001;
     baud = (((FCY/F_scl)/1000)-FCY*delay) -2;
I2C1BRG = (uint16_t)baud;   
I2C1CONbits.IPMIEN = 0;
I2C1CONbits.I2CEN = 1;//habilitamos el i2c
}

void I2C_Start(void){
I2C1CONbits.SEN = 1;
while (I2C1CONbits.SEN == 1) ;
}

void I2C_Stop(void){
I2C1CONbits.PEN = 1;
while (I2C1CONbits.PEN == 1) ;

}

void I2C_Restart(void){
I2C1CONbits.RSEN = 1;
while (I2C1CONbits.RSEN == 1) ;
}

void I2C_Write_Addres_Data_Slave(uint8_t Address,uint8_t data_dir){

    I2C1TRN = (Address & 0B11111110) | (data_dir & 0B00000001);
    while(I2C1STATbits.TRSTAT );
}
void I2C_Write_Data_Slave(uint8_t data){
    I2C1TRN = data;
    while(I2C1STATbits.TRSTAT);
}
void I2C_Read_Data(uint8_t *ptr_Dato,uint8_t var_Ack_nAck){

}
