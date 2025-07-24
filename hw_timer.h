/*
 * hw_timer.h
 *
 * @brief Header file for hardware timer microsecond and millisecond delays
 * @description Provides function declarations for precise timing using EFM32GG11B
 *              hardware timers with microsecond and millisecond resolution.
 *
 *  Created on: 20 May 2025
 *      Author: JonathanStorey
 *    Hardware: EFM32GG11B Microcontroller
 *     Version: 2.0
 *
 * @note Timer0: Optimised for microsecond delays (1µs - 65535µs)
 * @note Timer1: Optimised for millisecond delays (1ms - 65535ms)
 */

#ifndef HW_TIMER_H_
#define HW_TIMER_H_

#include <stdint.h>
#include <stdbool.h>

/*==============================================================================
 * TIMER SETUP FUNCTION DECLARATIONS
 *============================================================================*/

/**
 * @brief Initialise Timer0 for microsecond-precision delays
 * @param None
 * @return None
 * @note Call during system initialisation before using microsecond delays
 * @note Uses adaptive prescaling based on CPU frequency for optimal resolution
 */
void setupTimer0(void);

/**
 * @brief Initialise Timer1 for millisecond-precision delays
 * @param None
 * @return None
 * @note Call during system initialisation before using millisecond delays
 * @note Uses 1024 prescaler for stable millisecond timing
 */
void setupTimer1(void);

/*==============================================================================
 * DELAY FUNCTION DECLARATIONS
 *============================================================================*/

/**
 * @brief Blocking microsecond delay using Timer0
 * @param delay_us: Delay time in microseconds (1-65535)
 * @return None
 * @note Provides 1µs resolution blocking delay
 * @note Uses interrupt-based timing for accuracy
 * @example hw_timer0_us(100);  // 100 microsecond delay
 * @example hw_timer0_us(1500); // 1.5 millisecond delay
 */
void hw_timer0_us(uint32_t delay_us);

/**
 * @brief Blocking millisecond delay using Timer1
 * @param delay_ms: Delay time in milliseconds (1-65535)
 * @return None
 * @note Provides 1ms resolution blocking delay
 * @note Uses interrupt-based timing for accuracy
 * @example hw_timer1_ms(100);  // 100 millisecond delay
 * @example hw_timer1_ms(1500); // 1.5 second delay
 */
void hw_timer1_ms(uint32_t delay_ms);

/**
 * @brief Single millisecond delay convenience function
 * @param None
 * @return None
 * @note Equivalent to hw_timer1_ms(1)
 * @example hw_timer1_single_ms(); // 1ms delay
 */
void hw_timer1_single_ms(void);

/**
 * @brief Single second delay convenience function
 * @param None
 * @return None
 * @note Equivalent to hw_timer1_ms(1000)
 * @example hw_timer1_second(); // 1 second delay
 */
void hw_timer1_second(void);

/**
 * @brief Very short microsecond delay using direct counting
 * @param delay_us: Delay time in microseconds (1-10 recommended)
 * @return None
 * @note More accurate for very short delays (1-10µs)
 * @note Uses polling instead of interrupts for minimal overhead
 * @note Best for precise timing critical applications
 * @example hw_timer0_us_short(5); // 5µs delay with high precision
 */
void hw_timer0_us_short(uint32_t delay_us);

/*==============================================================================
 * INTERRUPT HANDLER DECLARATIONS
 *============================================================================*/

/**
 * @brief Timer0 interrupt handler
 * @param None
 * @return None
 * @note Automatically called by hardware - do not call directly
 */
void TIMER0_IRQHandler(void);

/**
 * @brief Timer1 interrupt handler
 * @param None
 * @return None
 * @note Automatically called by hardware - do not call directly
 */
void TIMER1_IRQHandler(void);

/*==============================================================================
 * UTILITY FUNCTION DECLARATIONS
 *============================================================================*/

/**
 * @brief Get current timer frequencies for debugging
 * @param timer0_freq: Pointer to store Timer0 effective frequency
 * @param timer1_freq: Pointer to store Timer1 effective frequency
 * @return None
 * @note Useful for debugging timing calculations
 * @example
 *   uint32_t freq0, freq1;
 *   hw_timer_get_frequencies(&freq0, &freq1);
 */
void hw_timer_get_frequencies(uint32_t *timer0_freq, uint32_t *timer1_freq);

/**
 * @brief Calculate actual delay resolution for specified timer
 * @param timer_num: Timer number (0 for Timer0, 1 for Timer1)
 * @return Resolution in nanoseconds
 * @note Returns the smallest delay increment possible
 * @example uint32_t res = hw_timer_get_resolution_ns(0); // Get Timer0 resolution
 */
uint32_t hw_timer_get_resolution_ns(uint8_t timer_num);

/*==============================================================================
 * CONVENIENCE MACROS
 *============================================================================*/

/// Quick microsecond delay macro
#define DELAY_US(us)        hw_timer0_us(us)

/// Quick millisecond delay macro
#define DELAY_MS(ms)        hw_timer1_ms(ms)

/// Quick short microsecond delay macro for precise timing
#define DELAY_US_SHORT(us)  hw_timer0_us_short(us)

/// Quick second delay macro
#define DELAY_S(s)          hw_timer1_ms((s) * 1000)

/*==============================================================================
 * CONFIGURATION CONSTANTS
 *============================================================================*/

/// Maximum microsecond delay value
#define HW_TIMER_MAX_US     65535

/// Maximum millisecond delay value
#define HW_TIMER_MAX_MS     65535

/// Minimum recommended delay for hw_timer0_us_short()
#define HW_TIMER_SHORT_MIN_US   1

/// Maximum recommended delay for hw_timer0_us_short()
#define HW_TIMER_SHORT_MAX_US   10


#endif
