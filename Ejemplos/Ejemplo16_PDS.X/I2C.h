/* 
 * File:   I2C.h
 * Author: HP
 *
 * Created on 23 de octubre de 2022, 05:31 PM
 */

#ifndef I2C_H
#define	I2C_H

#include <stdint.h>

void I2C_Init(uint16_t F_scl);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Restart(void);
void I2C_Write_Addres_Data_Slave(uint8_t Address,uint8_t data_dir);
void I2C_Write_Data_Slave(uint8_t data);
void I2C_Read_Data(uint8_t *ptr_Dato,uint8_t var_Ack_nAck);

#endif	/* I2C_H */

