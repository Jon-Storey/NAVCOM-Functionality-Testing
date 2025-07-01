/*
 * sw_delay.c
 *
 * @brief Improved software delay functions for EFM32GG11B
 * @description Provides accurate, compiler-optimisation resistant delay functions
 *              with multiple timing options for embedded applications.
 *
 *  Created on: 2 Jul 2025
 *      Author: JonathanStorey
 *    Hardware: EFM32GG11B Microcontroller
 *     Version: 2.0
 *
 * @note These delays are calibrated for typical EFM32GG11B clock speeds
 * @note For precision timing, use hardware timers instead
 */

#include <stdint.h>
#include "em_device.h"
#include "em_cmu.h"

/*==============================================================================
 * CONFIGURATION AND CALIBRATION
 *============================================================================*/

// Calibration factor - adjust based on your actual clock speed
// Default assumes ~80MHz CPU clock
#define DELAY_CALIBRATION_FACTOR    10

// Volatile variable to prevent compiler optimisation
static volatile uint32_t delay_counter;

/*==============================================================================
 * BASIC DELAY FUNCTIONS
 *============================================================================*/

/**
 * @brief Compiler-optimisation resistant delay loop
 * @param cycles: Number of loop iterations to perform
 * @return None
 * @note Uses volatile variable to prevent compiler removal
 */
void delay_cycles(uint32_t cycles)
{
    volatile uint32_t i;
    for(i = 0; i < cycles; i++)
    {
        delay_counter++;  // Volatile operation prevents optimisation
    }
}

/**
 * @brief Microsecond delay function
 * @param microseconds: Delay time in microseconds
 * @return None
 * @note Accuracy depends on CPU clock frequency and calibration
 */
void delay_us(uint32_t microseconds)
{
    uint32_t cpu_freq = CMU_ClockFreqGet(cmuClock_CORE);
    uint32_t cycles = (cpu_freq / 1000000) * microseconds / DELAY_CALIBRATION_FACTOR;

    delay_cycles(cycles);
}

/**
 * @brief Millisecond delay function
 * @param milliseconds: Delay time in milliseconds
 * @return None
 * @note More accurate than multiple microsecond calls
 */
void delay_ms(uint32_t milliseconds)
{
    uint32_t cpu_freq = CMU_ClockFreqGet(cmuClock_CORE);
    uint32_t cycles = (cpu_freq / 1000) * milliseconds / DELAY_CALIBRATION_FACTOR;

    delay_cycles(cycles);
}

/**
 * @brief Second delay function
 * @param seconds: Delay time in seconds
 * @return None
 * @note Implemented as multiple millisecond delays to avoid overflow
 */
void delay_s(uint32_t seconds)
{
    for(uint32_t i = 0; i < seconds; i++)
    {
        delay_ms(1000);
    }
}

/*==============================================================================
 * ADVANCED DELAY FUNCTIONS
 *============================================================================*/

/**
 * @brief High-precision microsecond delay using DWT cycle counter
 * @param microseconds: Delay time in microseconds
 * @return None
 * @note Requires DWT (Data Watchpoint and Trace) unit - most accurate method
 * @note Only works if DWT is available and enabled
 */
void delay_us_precise(uint32_t microseconds)
{
    #ifdef DWT_BASE
    // Enable DWT cycle counter if not already enabled
    if(!(DWT->CTRL & DWT_CTRL_CYCCNTENA_Msk))
    {
        CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
        DWT->CYCCNT = 0;
        DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    }

    uint32_t cpu_freq = CMU_ClockFreqGet(cmuClock_CORE);
    uint32_t cycles_needed = (cpu_freq / 1000000) * microseconds;
    uint32_t start_cycles = DWT->CYCCNT;

    while((DWT->CYCCNT - start_cycles) < cycles_needed)
    {
        // Wait for required cycles
    }
    #else
    // Fallback to standard microsecond delay
    delay_us(microseconds);
    #endif
}

/**
 * @brief Non-blocking delay check function
 * @param start_time: Start time from delay_get_time()
 * @param delay_ms: Delay duration in milliseconds
 * @return true if delay period has elapsed, false otherwise
 * @note Use with delay_get_time() for non-blocking delays
 */
bool delay_elapsed(uint32_t start_time, uint32_t delay_ms)
{
    uint32_t current_time = delay_get_time();
    uint32_t elapsed = current_time - start_time;

    // Handle overflow case
    if(current_time < start_time)
    {
        elapsed = (0xFFFFFFFF - start_time) + current_time + 1;
    }

    return (elapsed >= delay_ms);
}

/**
 * @brief Get current system time in milliseconds
 * @return Current time in milliseconds (wraps around at ~49 days)
 * @note Uses SysTick or DWT counter for timing reference
 */
uint32_t delay_get_time(void)
{
    #ifdef DWT_BASE
    // Use DWT cycle counter if available
    if(DWT->CTRL & DWT_CTRL_CYCCNTENA_Msk)
    {
        uint32_t cpu_freq = CMU_ClockFreqGet(cmuClock_CORE);
        return DWT->CYCCNT / (cpu_freq / 1000);
    }
    #endif

    // Fallback: use SysTick counter
    uint32_t systick_freq = CMU_ClockFreqGet(cmuClock_CORE);
    return (0xFFFFFF - SysTick->VAL) / (systick_freq / 1000);
}

/*==============================================================================
 * UTILITY AND CALIBRATION FUNCTIONS
 *============================================================================*/

/**
 * @brief Calibrate delay timing against hardware timer
 * @return Calibration factor for improved accuracy
 * @note Call this once during initialisation for better timing accuracy
 */
uint32_t delay_calibrate(void)
{
    // This would use a hardware timer to measure actual delay
    // For now, return default calibration
    uint32_t cpu_freq = CMU_ClockFreqGet(cmuClock_CORE);

    // Adjust calibration based on CPU frequency
    if(cpu_freq > 80000000)      return 12;  // High speed
    else if(cpu_freq > 40000000) return 10;  // Medium speed
    else                         return 8;   // Lower speed
}

/**
 * @brief Legacy compatibility function - replaces your old sw_delay
 * @param x: Delay multiplier (approximately milliseconds)
 * @return None
 * @note Provided for backward compatibility with existing code
 */
void sw_delay(int x)
{
    if(x > 0)
    {
        delay_ms((uint32_t)x);
    }
}

/*==============================================================================
 * EXAMPLE USAGE FUNCTIONS
 *============================================================================*/

/**
 * @brief Example of non-blocking delay usage
 * @return None
 * @note Shows how to implement non-blocking delays in main loop
 */
void delay_example_non_blocking(void)
{
    static uint32_t last_action_time = 0;
    static bool led_state = false;

    // Check if 500ms have elapsed since last action
    if(delay_elapsed(last_action_time, 500))
    {
        // Toggle LED or perform action
        led_state = !led_state;

        // Update timestamp for next action
        last_action_time = delay_get_time();
    }

    // Rest of main loop continues without blocking
}

/**
 * @brief Example of precise timing for communication protocols
 * @return None
 * @note Shows microsecond-level precision for protocol timing
 */
void delay_example_precise_timing(void)
{
    // RS485 direction control timing example
    // Set RTS high
    delay_us_precise(10);  // 10µs setup time

    // Send data here

    delay_us_precise(5);   // 5µs hold time
    // Clear RTS low
}

/*==============================================================================
 * INITIALISATION FUNCTION
 *============================================================================*/

/**
 * @brief Initialise delay system with calibration
 * @return None
 * @note Call during system initialisation for optimal performance
 */
void delay_init(void)
{
    // Initialise delay counter
    delay_counter = 0;

    // Enable DWT if available for high-precision timing
    #ifdef DWT_BASE
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    #endif

    // Could add automatic calibration here if desired
}
