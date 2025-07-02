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
#include "EFM32GG11B420F2048GQ100.h"
//#include "sw_delay.h"
#include "hw_timer.h"
#include "usart.h"
#include "buzzer.h"
#include "defines.h"
#include "i2c.h"
#include <stdbool.h>



#define I2C             I2C0
#define I2C_SCL_PORT    gpioPortD
#define I2C_SCL_PIN     7
#define I2C_SDA_PORT    gpioPortD
#define I2C_SDA_PIN     6
#define I2C_LOCATION    1
//#define I2C_SLAVE_ADDR  0x76
#define I2C_SLAVE_ADDR  0x19      //compass address

#define I2C_REG_ADDR    0x00


static volatile I2C_State_t i2cState = I2C_STATE_IDLE;
static volatile bool i2cTransferComplete = false;
static volatile uint8_t i2cRxData = 0;




void initI2C(void)
{

     CMU_ClockEnable(cmuClock_GPIO, true);      // Enable clocks
     CMU_ClockEnable(cmuClock_I2C0, true);

     GPIO_PinModeSet(I2C_SCL_PORT, I2C_SCL_PIN, gpioModeWiredAndPullUpFilter, 1); // Configure SDA/SCL as open-drain with pull-up
     GPIO_PinModeSet(I2C_SDA_PORT, I2C_SDA_PIN, gpioModeWiredAndPullUpFilter, 1);

     I2C0->ROUTELOC0 = I2C_ROUTELOC0_SCLLOC_LOC1 | I2C_ROUTELOC0_SDALOC_LOC1;   // Route pins
     I2C0->ROUTEPEN = I2C_ROUTEPEN_SCLPEN | I2C_ROUTEPEN_SDAPEN;

     I2C_Init_TypeDef init = I2C_INIT_DEFAULT;                                  // Init I2C
     init.enable = false;
     I2C_Init(I2C0, &init);

     while (I2C0->STATUS & I2C_STATE_BUSY);                                      // Clear bus

     I2C_Enable(I2C0, true);
     I2C0->IFC = _I2C_IFC_MASK;                                                  // Clear and enable interrupts
     I2C0->IEN = I2C_IEN_ACK | I2C_IEN_RXDATAV | I2C_IEN_NACK | I2C_IEN_MSTOP;

     NVIC_ClearPendingIRQ(I2C0_IRQn);
     NVIC_EnableIRQ(I2C0_IRQn);
}





void i2cStartReadByte(void)
{
    if (i2cState != I2C_STATE_IDLE) return;
    i2cTransferComplete = false;            //set flag to false so that transmission loops until complete
    i2cState = I2C_STATE_SEND_ADDR;         // initilise state to send the address
    I2C0->CMD = I2C_CMD_ABORT;
    I2C0->IFC = _I2C_IFC_MASK;                  // Clear flags
    I2C0->CMD = I2C_CMD_START;                  // send a start bit
    I2C0->TXDATA = (I2C_SLAVE_ADDR << 1) | 0;  // Write slave address shifted right
}




bool i2cIsTransferDone(void)
{
    return i2cTransferComplete;
}


uint8_t i2cGetLastByte(void)
{
    return i2cRxData;
}


void I2C0_IRQHandler(void)
{
    uint32_t flags = I2C0->IF;              //read all the I2C flags

    if (flags & I2C_IF_NACK)              // if we have seen a NACK, then send stop and complete TX
    {
        print_string("NAK\n\r" , Node);
        i2cState = I2C_STATE_ERROR;
        I2C0->CMD = I2C_CMD_STOP;
        I2C0->IFC = I2C_IF_NACK;
        i2cTransferComplete = true;
        return;
    }

    switch (i2cState)
    {
        case I2C_STATE_SEND_ADDR:
          put_char('1', Node);
          if (flags & I2C_IF_ACK)
          {
              I2C0->TXDATA = I2C_REG_ADDR;
              i2cState = I2C_STATE_SEND_REG;
              I2C0->IFC = I2C_IF_ACK;           // Clear ack flag all handled flags
          }
            break;

        case I2C_STATE_SEND_REG:
            if (flags & I2C_IF_TXBL)
            {
                I2C0->CMD = I2C_CMD_START;                  // repeated start
                I2C0->TXDATA = (I2C_SLAVE_ADDR << 1) | 1;   // read
                i2cState = I2C_STATE_READ;
                I2C0->IFC = I2C_IF_TXBL;                  // Clear ack flag all handled flags
            }
            break;


        case I2C_STATE_READ:

            if (flags & I2C_IF_RXDATAV)
            {
                i2cRxData = I2C0->RXDATA;
                I2C0->CMD = I2C_CMD_NACK | I2C_CMD_STOP;
                i2cState = I2C_STATE_WAITSTOP;
                I2C0->IFC = I2C_IF_RXDATAV;           // Clear ack flag all handled flags
            }
            break;

        case I2C_STATE_WAITSTOP:
            if (flags & I2C_IF_MSTOP)
            {
                i2cTransferComplete = true;
                i2cState = I2C_STATE_IDLE;
                I2C0->IFC = I2C_IF_MSTOP;
            }
            break;

        default:
          I2C0->IFC = flags;        //The idle state will cause this default to happen clear all flags
            break;
    }
}






 /*   // Enable clocks
    CMU_ClockEnable(cmuClock_HFPER, true);
    CMU_ClockEnable(cmuClock_GPIO, true);
    CMU_ClockEnable(cmuClock_I2C0, true);

    // Configure SDA/SCL pins
    GPIO_PinModeSet(I2C_PORT, SDA_PIN, gpioModeWiredAndPullUpFilter, 1);
    GPIO_PinModeSet(I2C_PORT, SCL_PIN, gpioModeWiredAndPullUpFilter, 1);

    // Route I2C0 to location 1
    I2C->ROUTELOC0 = (I2C_ROUTELOC0_SDALOC_LOC1 | I2C_ROUTELOC0_SCLLOC_LOC1);
    I2C->ROUTEPEN = I2C_ROUTEPEN_SDAPEN | I2C_ROUTEPEN_SCLPEN;

    // Reset and init
    I2C_Reset(I2C);

    I2C_Init_TypeDef init = I2C_INIT_DEFAULT;
    init.enable = false;  // Don't enable yet
    I2C_Init(I2C, &init);

    // Enable interface now
    I2C_Enable(I2C, true);

    // Wait for bus idle
    while (I2C0->STATUS & I2C_STATE_BUSY);

    */




/*
uint8_t readRegister(uint8_t reg)
{
    // Send start + slave address (write)
    I2C_TransferSeq_TypeDef seq;
    uint8_t writeData[1];
    uint8_t readData[1];

    seq.addr = I2C_SLAVE_ADDR << 1;
    seq.flags = I2C_FLAG_WRITE_READ;

    writeData[0] = reg;
    seq.buf[0].data = writeData;
    seq.buf[0].len = 1;

    seq.buf[1].data = readData;
    seq.buf[1].len = 1;

    I2C_TransferReturn_TypeDef ret = I2C_TransferInit(I2C, &seq);

    while (ret == i2cTransferInProgress)
    {
        ret = I2C_Transfer(I2C);
    }

    if (ret != i2cTransferDone)
    {
        // Error handling
        return 0xFF;
    }

    return readData[0];
}
*/
