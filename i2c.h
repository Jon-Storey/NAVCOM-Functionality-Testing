/*
 * i2c.h
 *
 *  Created on: 21 May 2025
 *      Author: JonathanStorey
 */

#ifndef I2C_H_
#define I2C_H_

void initI2C(void);
void enableI2cSlaveInterrupts(void);
void disableI2cInterrupts(void);
void performI2CTransfer(void);
void receiveI2CData(void);
void I2C0_IRQHandler(void);

#endif /* I2C_H_ */
