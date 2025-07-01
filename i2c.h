/*
 * i2c.h
 *
 *  Created on: 21 May 2025
 *      Author: JonathanStorey
 */

#ifndef I2C_H_
#define I2C_H_
#include <stdbool.h>

void enableI2cSlaveInterrupts(void);
void disableI2cInterrupts(void);
void performI2CTransfer(void);
void receiveI2CData(void);
void I2C0_IRQHandler(void);

bool i2cReadRegister(uint8_t, uint8_t*);
void initI2C(void);

void i2cStartReadByte(void);
bool i2cIsTransferDone(void);
uint8_t i2cGetLastByte(void);


#endif /* I2C_H_ */
