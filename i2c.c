/*
 * i2c.c
 *
 *  Created on: 21 May 2025
 *      Author: JonathanStorey
 */

#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_chip.h"
#include "em_timer.h"
#include "em_i2c.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "EFM32GG11B420F2048GQ100.h"
#include "sw_delay.h"
#include "hw_timer.h"
#include "usart.h"
#include "buzzer.h"
#include "defines.h"
#include "i2c.h"



#define I2C_ADDRESS                     0xE2    // Defines
#define I2C_ADDRESS_MASK                0xFE    // Must match exact I2C_ADDRESS
#define I2C_RXBUFFER_SIZE                 10

uint8_t i2c_txBuffer[] = "Gecko";                 // Buffers++
uint8_t i2c_txBufferSize = sizeof(i2c_txBuffer);
uint8_t i2c_rxBuffer[I2C_RXBUFFER_SIZE];
uint8_t i2c_rxBufferIndex;

volatile bool i2c_rxInProgress;                   // Transmission flags
volatile bool i2c_startTx;


void initI2C(void)
{

  I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;  // Using default settings
  i2cInit.freq = I2C_FREQ_FAST_MAX;   // Use ~400khz SCK
  i2cInit.clhr = i2cClockHLRAsymetric;   // Use 6:3 low high SCK ratio

  // Initializing the I2C
  I2C_Init(I2C0, &i2cInit);
  I2C0->ROUTELOC0 = ~_I2C_ROUTELOC0_SDALOC_MASK | I2C_ROUTELOC0_SDALOC_LOC1;
  I2C0->ROUTELOC0 = ~_I2C_ROUTELOC0_SCLLOC_MASK | I2C_ROUTELOC0_SCLLOC_LOC1;
  I2C0->ROUTEPEN |= I2C_ROUTEPEN_SDAPEN | I2C_ROUTEPEN_SCLPEN;

  //I2C0->ROUTELOC0 = (I2C0->ROUTELOC0 & (~_I2C_ROUTELOC0_SDALOC_MASK)) | I2C_ROUTELOC0_SDALOC_LOC1;
  //I2C0->ROUTELOC0 = (I2C0->ROUTELOC0 & (~_I2C_ROUTELOC0_SCLLOC_MASK)) | I2C_ROUTELOC0_SCLLOC_LOC1;
  //I2C0->ROUTEPEN = I2C_ROUTEPEN_SDAPEN | I2C_ROUTEPEN_SCLPEN; original



  i2c_rxInProgress = false;           // Setting the status flags and index
  i2c_startTx = false;
  i2c_rxBufferIndex = 0;


  I2C0->SADDR = I2C_ADDRESS;            // Setting up to enable slave mode
  I2C0->SADDRMASK = I2C_ADDRESS_MASK;
  I2C0->CTRL |= I2C_CTRL_SLAVE | I2C_CTRL_AUTOACK | I2C_CTRL_AUTOSN;
  enableI2cSlaveInterrupts();
}


void enableI2cSlaveInterrupts(void)
{
  I2C_IntClear(I2C0, I2C_IFC_ADDR | I2C_IF_RXDATAV | I2C_IFC_SSTOP);
  I2C_IntEnable(I2C0, I2C_IEN_ADDR | I2C_IEN_RXDATAV | I2C_IEN_SSTOP);
  NVIC_EnableIRQ(I2C0_IRQn);
}



void disableI2cInterrupts(void)
{
  NVIC_DisableIRQ(I2C0_IRQn);
  I2C_IntDisable(I2C0, I2C_IEN_ADDR | I2C_IEN_RXDATAV | I2C_IEN_SSTOP);
  I2C_IntClear(I2C0, I2C_IFC_ADDR | I2C_IF_RXDATAV | I2C_IFC_SSTOP);
}


/**************************************************************************//**
 * @brief  Transmitting I2C data. Will busy-wait until the transfer is complete.
 *****************************************************************************/
void performI2CTransfer(void)
{
  I2C_TransferSeq_TypeDef i2cTransfer;            // Transfer structure
  I2C_TransferReturn_TypeDef result;

  i2cTransfer.addr          = I2C_ADDRESS;        // Initializing I2C transfer
  i2cTransfer.flags         = I2C_FLAG_WRITE;
  i2cTransfer.buf[0].data   = i2c_txBuffer;
  i2cTransfer.buf[0].len    = i2c_txBufferSize;
  i2cTransfer.buf[1].data   = i2c_rxBuffer;
  i2cTransfer.buf[1].len    = I2C_RXBUFFER_SIZE;
  result = I2C_TransferInit(I2C0, &i2cTransfer);

  while (result == i2cTransferInProgress)         // Sending data
  {
    result = I2C_Transfer(I2C0);
  }

  enableI2cSlaveInterrupts();
}


/**************************************************************************//**
 * @brief  Receiving I2C data. Along with the I2C interrupt, it will keep the
  EFM32 in EM1 while the data is received.
 *****************************************************************************/
void receiveI2CData(void)
{
  while(i2c_rxInProgress)
  {
    EMU_EnterEM1();
  }
}


/**************************************************************************//**
 * @brief I2C Interrupt Handler.
 *        The interrupt table is in assembly startup file startup_efm32.s
 *****************************************************************************/
void I2C0_IRQHandler(void)
{
  int status;

  status = I2C0->IF;                // read interrupt flag register

  if (status & I2C_IF_ADDR)         // Address Match, Indicating that reception is started
  {
    i2c_rxInProgress = true;        // ste flag to indicate in recieve mode
    I2C0->RXDATA;                   //
    i2c_rxBufferIndex = 0;          //
    I2C_IntClear(I2C0, I2C_IFC_ADDR);

  }
  else if (status & I2C_IF_RXDATAV)
  {
    i2c_rxBuffer[i2c_rxBufferIndex] = I2C0->RXDATA;     // Data received
    i2c_rxBufferIndex++;
  }

  if(status & I2C_IEN_SSTOP)      // Stop received, reception is ended
  {
    I2C_IntClear(I2C0, I2C_IFC_SSTOP);
    i2c_rxInProgress = false;
    i2c_rxBufferIndex = 0;
  }


}

/***************************************************************************//**
 * @brief GPIO Interrupt handler
 ******************************************************************************/
//void GPIO_EVEN_IRQHandler(void)
//{
  // Clear pending
//  uint32_t interruptMask = GPIO_IntGet();
//  GPIO_IntClear(interruptMask);

  // If RX is not in progress, a new transfer is started
//  if (!i2c_rxInProgress)
//  {
//    disableI2cInterrupts();
//      i2c_startTx = true;
//  }
//}
