/*
 * sw_delay.h
 *
 * @brief Header file for improved software delay functions
 * @description Provides function declarations and definitions for accurate,
 *              compiler-optimisation resistant delay functions with multiple
 *              timing options for embedded applications.
 *
 *  Created on: 2 Jul 2025
 *      Author: JonathanStorey
 *    Hardware: EFM32GG11B Microcontroller
 *     Version: 2.0
 *
 * @note Include this header in any module requiring delay functionality
 * @note Call delay_init() during system initialisation for optimal performance
 */

#ifndef SW_DELAY_H_
#define SW_DELAY_H_

#include <stdint.h>
#include <stdbool.h>

/*==============================================================================
 * CONFIGURATION CONSTANTS
 *============================================================================*/

/// Default calibration factor for delay timing
#define DELAY_CALIBRATION_FACTOR    10

/// Maximum safe delay value to prevent overflow (in milliseconds)
#define DELAY_MAX_MS               (0xFFFFFFFF / 1000)

/// Maximum safe delay value to prevent overflow (in microseconds)
#define DELAY_MAX_US               (0xFFFFFFFF / 1000000)

/*==============================================================================
 * BASIC DELAY FUNCTION DECLARATIONS
 * @brief Standard blocking delay functions with different time units
 *============================================================================*/

/**
 * @brief Compiler-optimisation resistant delay loop
 * @param cycles: Number of loop iterations to perform
 * @return None
 * @note Uses volatile variable to prevent compiler removal
 */
void delay_cycles(uint32_t cycles);

/**
 * @brief Microsecond delay function
 * @param microseconds: Delay time in microseconds (1-999,999)
 * @return None
 * @note Accuracy depends on CPU clock frequency and calibration
 * @example delay_us(100); // Wait 100 microseconds
 */
void delay_us(uint32_t microseconds);

/**
 * @brief Millisecond delay function
 * @param milliseconds: Delay time in milliseconds (1-4,294,967)
 * @return None
 * @note More accurate than multiple microsecond calls
 * @example delay_ms(500); // Wait 500 milliseconds
 */
void delay_ms(uint32_t milliseconds);

/**
 * @brief Second delay function
 * @param seconds: Delay time in seconds (1-4,294,967)
 * @return None
 * @note Implemented as multiple millisecond delays to avoid overflow
 * @example delay_s(2); // Wait 2 seconds
 */
void delay_s(uint32_t seconds);

/*==============================================================================
 * ADVANCED DELAY FUNCTION DECLARATIONS
 * @brief High-precision and non-blocking delay functions
 *============================================================================*/

/**
 * @brief High-precision microsecond delay using DWT cycle counter
 * @param microseconds: Delay time in microseconds
 * @return None
 * @note Requires DWT (Data Watchpoint and Trace) unit - most accurate method
 * @note Falls back to delay_us() if DWT not available
 * @example delay_us_precise(10); // Precise 10µs delay for protocol timing
 */
void delay_us_precise(uint32_t microseconds);

/**
 * @brief Non-blocking delay check function
 * @param start_time: Start time from delay_get_time()
 * @param delay_ms: Delay duration in milliseconds
 * @return true if delay period has elapsed, false otherwise
 * @note Use with delay_get_time() for non-blocking delays
 * @example
 *   uint32_t start = delay_get_time();
 *   if(delay_elapsed(start, 1000)) { // Check if 1 second passed }
 */
bool delay_elapsed(uint32_t start_time, uint32_t delay_ms);

/**
 * @brief Get current system time in milliseconds
 * @return Current time in milliseconds (wraps around at ~49 days)
 * @note Uses DWT cycle counter or SysTick for timing reference
 * @note Time reference starts from system boot or delay_init() call
 * @example uint32_t now = delay_get_time();
 */
uint32_t delay_get_time(void);

/*==============================================================================
 * UTILITY AND CALIBRATION FUNCTION DECLARATIONS
 *============================================================================*/

/**
 * @brief Calibrate delay timing for improved accuracy
 * @return Calibration factor for current CPU frequency
 * @note Call this once during initialisation for better timing accuracy
 * @note Automatically adjusts for different CPU frequencies
 */
uint32_t delay_calibrate(void);

/**
 * @brief Initialise delay system with calibration and DWT setup
 * @return None
 * @note Call during system initialisation for optimal performance
 * @note Enables DWT cycle counter if available
 * @note Should be called after CMU (Clock Management Unit) initialisation
 */
void delay_init(void);

/*==============================================================================
 * LEGACY COMPATIBILITY FUNCTION DECLARATIONS
 *============================================================================*/

/**
 * @brief Legacy compatibility function - replaces old sw_delay
 * @param x: Delay multiplier (approximately milliseconds)
 * @return None
 * @note Provided for backward compatibility with existing code
 * @note New code should use delay_ms() instead for clarity
 * @example sw_delay(100); // Approximately 100ms delay
 */
void sw_delay(int x);

/*==============================================================================
 * EXAMPLE AND DEMONSTRATION FUNCTION DECLARATIONS
 * @brief Educational examples showing proper delay usage patterns
 *============================================================================*/

/**
 * @brief Example of non-blocking delay usage in main loop
 * @return None
 * @note Demonstrates how to implement non-blocking delays
 * @note Shows pattern for periodic actions without blocking main loop
 */
void delay_example_non_blocking(void);

/**
 * @brief Example of precise timing for communication protocols
 * @return None
 * @note Shows microsecond-level precision for protocol timing
 * @note Demonstrates RS485 direction control timing
 */
void delay_example_precise_timing(void);

/*==============================================================================
 * INLINE UTILITY MACROS
 * @brief Convenient macros for common delay operations
 *============================================================================*/

/// Quick millisecond delay macro
#define DELAY_MS(ms)        delay_ms(ms)

/// Quick microsecond delay macro
#define DELAY_US(us)        delay_us(us)

/// Quick second delay macro
#define DELAY_S(s)          delay_s(s)

/// Get current time macro
#define GET_TIME()          delay_get_time()

/// Check if time has elapsed macro
#define TIME_ELAPSED(start, duration)  delay_elapsed(start, duration)

/*==============================================================================
 * CONDITIONAL COMPILATION FEATURES
 *============================================================================*/

// Enable high-precision timing if DWT is available
#ifdef DWT_BASE
    #define DELAY_HAS_PRECISE_TIMING    1
#else
    #define DELAY_HAS_PRECISE_TIMING    0
#endif

// Feature availability indicators
#define DELAY_HAS_NON_BLOCKING         1
#define DELAY_HAS_AUTO_CALIBRATION     1
#define DELAY_HAS_MULTIPLE_UNITS       1

/*==============================================================================
 * USAGE EXAMPLES IN COMMENTS
 *============================================================================*/

/*
Example 1: Basic blocking delays
    delay_ms(100);              // Wait 100 milliseconds
    delay_us(50);               // Wait 50 microseconds
    delay_s(2);                 // Wait 2 seconds

Example 2: Non-blocking delays in main loop
    void main_loop(void) {
        static uint32_t last_print = 0;

        // Main processing here...

        if(delay_elapsed(last_print, 1000)) {
            print_status();
            last_print = delay_get_time();
        }
    }

Example 3: Precise communication timing
    GPIO_PinOutSet(gpioPortC, 8);       // Set RTS
    delay_us_precise(10);               // Precise setup time
    send_data();
    delay_us_precise(5);                // Precise hold time
    GPIO_PinOutClear(gpioPortC, 8);     // Clear RTS

Example 4: System initialisation
    int main(void) {
        CHIP_Init();
        CMU_ClockEnable(...);           // Enable clocks first
        delay_init();                   // Then initialise delays
        // Rest of initialisation...
    }
*/

#endif /* SW_DELAY_H_ */
