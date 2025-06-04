/*
 * hw_timer.c
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
#include "sw_delay.h"
#include "em_timer.h"
#include "hw_timer.h"
#include "defines.h"


volatile bool timer0Expired = false;
volatile bool timer1Expired = false;

void setupTimer0(void)
{
    TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;

    timerInit.enable = false;                                   // Don't start yet
    timerInit.prescale = timerPrescale1024;                     // Divide clock by 1024

    TIMER_Init(TIMER0, &timerInit);
    //uint32_t topValue = ((CMU_ClockFreqGet(cmuClock_TIMER0) / (1 << timerInit.prescale))) *1 ; // 1 Second
    //uint32_t topValue = (CMU_ClockFreqGet(cmuClock_TIMER0) / (1 << timerInit.prescale)) / 1000;  // 1 uSecond
    uint32_t topValue = (CMU_ClockFreqGet(cmuClock_TIMER0) / (1 << timerInit.prescale)) / 10000;  // 0.1 uSecond

    TIMER_TopSet(TIMER0, topValue);                           // Set TOP value to generate 1-second overflow
    TIMER_IntEnable(TIMER0, TIMER_IEN_OF);                    // Enable TIMER0 overflow interrupt
    NVIC_EnableIRQ(TIMER0_IRQn);                              // Enable IRQ
}


void setupTimer1(void)
{
    TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;

    timerInit.enable = false;                                   // Don't start yet
    timerInit.prescale = timerPrescale1024;                     // Divide clock by 1024

    TIMER_Init(TIMER1, &timerInit);
    uint32_t topValue = ((CMU_ClockFreqGet(cmuClock_TIMER1) / (1 << timerInit.prescale))) *1 ; // 1 Second

    TIMER_TopSet(TIMER1, topValue);                           // Set TOP value to generate 1-second overflow
    TIMER_IntEnable(TIMER1, TIMER_IEN_OF);                    // Enable TIMER0 overflow interrupt
    NVIC_EnableIRQ(TIMER1_IRQn);                              // Enable IRQ
}


void hw_timer0(int delay)
{
  int i = 0;
  TIMER_Enable(TIMER0, true);         // Start the timer
  for(i = 0; i <delay; i++)
  {
      while (timer0Expired == false);    //while the timer has not yet overflow'ed stay here

      timer0Expired = false;             //reset the flag
  }
  TIMER_Enable(TIMER0, false);          // Stop the timer
}


void hw_timer1(void)
{
  TIMER_Enable(TIMER1, true);         // Start the timer

      while (timer1Expired == false);    //while the timer has not yet overflow'ed stay here
      timer1Expired = false;             //reset the flag

  TIMER_Enable(TIMER1, false);          // Stop the timer
}


void TIMER0_IRQHandler(void)
{
    TIMER_IntClear(TIMER0, TIMER_IF_OF);      // Clear interrupt flag
    timer0Expired = true;                      // Set flag or handle your timer event
}

void TIMER1_IRQHandler(void)
{
    TIMER_IntClear(TIMER1, TIMER_IF_OF);      // Clear interrupt flag
    timer1Expired = true;                      // Set flag or handle your timer event
}
