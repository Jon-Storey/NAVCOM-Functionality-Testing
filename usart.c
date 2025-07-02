/*
 * usart.c
 *
 *  Created on: 20 May 2025
 *      Author: JonathanStorey
 */

#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_chip.h"
#include "EFM32GG11B420F2048GQ100.h"
//#include "sw_delay.h"
#include "em_timer.h"
#include "hw_timer.h"
#include "usart.h"
#include "defines.h"



#define MODE                                                                    \
  {                                                                                                \
    usartEnable,           /* Enable RX/TX when initialization is complete. */                     \
    0,                     /* Use current configured reference clock for configuring baud rate. */ \
    115200,                  /* 115200 bits/s. */                                                    \
    usartOVS16,            /* 16x oversampling. */                                                 \
    usartDatabits8,        /* 8 data bits. */                                                      \
    usartNoParity,         /* No parity. */                                                        \
    usartStopbits1,        /* 1 stop bit. */                                                       \
    false,                 /* Do not disable majority vote. */                                     \
    false,                 /* Not USART PRS input mode. */                                         \
    0,                     /* PRS channel 0. */                                                    \
    false,                 /* Auto CS functionality enable/disable switch */                       \
    false,                 /* No CS invert. */                                                     \
    0,                     /* Auto CS Hold cycles. */                                              \
    0,                     /* Auto CS Setup cycles. */                                             \
    usartHwFlowControlNone /* No HW flow control. */                                               \
  }


void usart_init(void)
{

  USART_InitAsync_TypeDef init = MODE;


  //Initialize USART/UART asynchronous mode and route pins
  USART_InitAsync(USART0, &init);
  USART0->ROUTELOC0 = USART_ROUTELOC0_RXLOC_LOC2 | USART_ROUTELOC0_TXLOC_LOC2;      //USART 0 - LOCATION 2 - IMU
  USART0->ROUTEPEN |= USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN;

  USART_InitAsync(USART1, &init);
  USART1->ROUTELOC0 = USART_ROUTELOC0_RXLOC_LOC1 | USART_ROUTELOC0_TXLOC_LOC1;      //USART 1 - LOCATION 1 - PDEM  - checked correct
  USART1->ROUTEPEN |= USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN;

  USART_InitAsync(USART2, &init);
  USART2->ROUTELOC0 = USART_ROUTELOC0_RXLOC_LOC5 | USART_ROUTELOC0_TXLOC_LOC5;      //USART 2 - LOCATION 5 - NODE - checked correct
  USART2->ROUTEPEN |= USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN;

  USART_InitAsync(USART3, &init);
  USART3->ROUTELOC0 = USART_ROUTELOC0_RXLOC_LOC1 | USART_ROUTELOC0_TXLOC_LOC1;      //USART 3 - LOCATION 1 - THRUSTERS
  USART3->ROUTEPEN |= USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN;

  USART_InitAsync(USART4, &init);
  USART4->ROUTELOC0 = USART_ROUTELOC0_RXLOC_LOC0 | USART_ROUTELOC0_TXLOC_LOC0;      //USART 4 - LOCATION 0 - 3 USART EXPANDER -> payload A, B,C,D, E, Antenna, Ext pressure
  USART4->ROUTEPEN |= USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN;                  //SPI

  USART_InitAsync(USART5, &init);
  USART5->ROUTELOC0 = USART_ROUTELOC0_RXLOC_LOC2 | USART_ROUTELOC0_TXLOC_LOC1;      //USART 5 - LOCATION 2/1 - SDAS - checked working
  USART5->ROUTEPEN |= USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN;

  USART_InitAsync(UART0, &init);
  UART0->ROUTELOC0 = (USART_ROUTELOC0_TXLOC_LOC1 | USART_ROUTELOC0_RXLOC_LOC1);       //UART 0 - LOCATION 1 - USBL
  UART0->ROUTEPEN = USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_TXPEN;

  USART_InitAsync(UART1, &init);
  UART1->ROUTELOC0 = (USART_ROUTELOC0_TXLOC_LOC3 | USART_ROUTELOC0_RXLOC_LOC3);       //UART 1 - LOCATION 3 - FCPU
  UART1->ROUTEPEN = USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_TXPEN;


  //Sensor caddy    I2C0 (Compass A, Internal pressure)
  //Compass B       I2C1
}






void put_char(char c, int destination)
{
  switch (destination)
  {
    case IMU:         USART_Tx(USART0, c);  break;
    case PDEM:        USART_Tx(USART1, c);  break;        //
    case Node:        USART_Tx(USART2, c);  break;        //
    case Thrusters:   USART_Tx(USART3, c);  break;        //
    case Expander:    USART_Tx(USART4, c);  break;        // spi
    case SDAS:        USART_Tx(USART5, c);  break;        //
    case FCPU:        USART_Tx (UART0, c);   break;
    case USBL:        USART_Tx (UART1, c);   break;

    default:          USART_Tx(USART2, c);          //
  }
}




void print_string(const char *str, int destination)
{
  while (*str)
  {
      put_char(*str, destination);  // Print each character
      str++;                        // Move to next character
  }
}




char USART_ReceiveChar(USART_TypeDef *usart)
{
  char input = 0;

    while (!(usart->STATUS & USART_STATUS_RXDATAV))     // Wait until data is available
    {
        // Wait for RX buffer to have data
    }
    input = USART_Rx(usart);

    return input;     // Read and return the received byte
}



