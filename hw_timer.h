/*
 * hw_timer.h
 *
 *  Created on: 20 May 2025
 *      Author: JonathanStorey
 */

#ifndef HW_TIMER_H_
#define HW_TIMER_H_

void setupTimer0(void);
void setupTimer1(void);
void hw_timer0(int);
void hw_timer1(void);
void TIMER0_IRQHandler(void);
void TIMER1_IRQHandler(void);

#endif /* HW_TIMER_H_ */
