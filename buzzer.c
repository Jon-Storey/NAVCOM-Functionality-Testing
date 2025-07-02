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
          hw_timer0(sweep_start);
          GPIO_PinOutToggle(gpioPortC, 2);
      }

    sweep_start = sweep_start  + 1;
  }
}

void buzz_one_second(void)
{
  while(1)
  {
      hw_timer0(delay);
      GPIO_PinOutToggle(gpioPortC, 2);
  }
}
