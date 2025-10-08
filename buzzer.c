/*
 * buzzer.c
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
#include "buzzer.h"
#include "defines.h"




#define TIMER_FREQ     1000000  // 1 MHz timer frequency
#define PWM_DUTY_CYCLE 50       // 50% duty cycle



void buzzer_init(void)
{
  // Route TIMER2 CC0 (not CC2!) to PC2 using location 5
     TIMER2->ROUTELOC0 = (TIMER2->ROUTELOC0 & ~_TIMER_ROUTELOC0_CC0LOC_MASK) | TIMER_ROUTELOC0_CC0LOC_LOC5;
     TIMER2->ROUTEPEN |= TIMER_ROUTEPEN_CC0PEN;  // Enable CC0, not CC2!

     // Initialize TIMER2
     TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
     timerInit.prescale = timerPrescale1;
     timerInit.enable = false;
     TIMER_Init(TIMER2, &timerInit);

     // Configure CC0 (not CC2!) for PWM
     TIMER_InitCC_TypeDef timerCCInit = TIMER_INITCC_DEFAULT;
     timerCCInit.mode = timerCCModePWM;
     timerCCInit.cmoa = timerOutputActionToggle;
     timerCCInit.cofoa = timerOutputActionClear;
     TIMER_InitCC(TIMER2, 0, &timerCCInit);  // Channel 0, not 2!
}


void buzzer_play_note(note_t note, uint32_t duration_ms)
{

  if (note == NOTE_OFF || note == 0)
     {
         TIMER_Enable(TIMER2, false);
         GPIO_PinOutClear(gpioPortC, 2);
     }
     else
     {
         // Stop timer first
         TIMER_Enable(TIMER2, false);

         // Reset counter
         TIMER_CounterSet(TIMER2, 0);

         uint32_t top_value = (TIMER_FREQ / note) - 1;
         TIMER_TopSet(TIMER2, top_value);
         uint32_t compare_value = (top_value * PWM_DUTY_CYCLE) / 100;
         TIMER_CompareSet(TIMER2, 0, compare_value);

         // Restart timer
         TIMER_Enable(TIMER2, true);
     }

     // Delay
     for (volatile uint32_t i = 0; i < duration_ms * 1000; i++);

     TIMER_Enable(TIMER2, false);
     GPIO_PinOutClear(gpioPortC, 2);
 }












/*

int delay = 1;

void set_buzz_frequency(int freq)
{
  delay = freq;
}

void buzz_sweep(void)
{
  int sweep_step = 1000;
  int sweep_start = 1; //0.1uS or 10kHz
  int sweep_stop = 10; //1uS or 1kHz
  int i = 0;

  while(sweep_start < sweep_stop)
  {
      for(i = 0; i < sweep_step ; i++ )
      {
  //        hw_timer0(sweep_start);
          GPIO_PinOutToggle(gpioPortC, 2);
      }

    sweep_start = sweep_start  + 1;
  }
}

void buzz_one_second(void)
{
  while(1)
  {
 //     hw_timer0(delay);
      GPIO_PinOutToggle(gpioPortC, 2);
  }
}

*/
