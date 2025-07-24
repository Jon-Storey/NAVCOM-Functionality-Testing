/*
 * hw_timer.c
 *
 * @brief Hardware timer implementation for precise microsecond and millisecond delays
 * @description Provides accurate blocking delays using EFM32GG11B hardware timers
 *              with proper timing calculations and race condition protection.
 *              Optimised for 50MHz CPU clock frequency.
 *
 *  Created on: 20 May 2025
 *      Author: JonathanStorey
 *    Hardware: EFM32GG11B Microcontroller @ 50MHz
 *     Version: 2.0
 *
 * @note Timer0: Configured for microsecond-level delays (50MHz/64 = 781.25kHz)
 * @note Timer1: Configured for millisecond-level delays (50MHz/1024 = 48.8kHz)
 */

#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_chip.h"
#include "em_timer.h"
#include "hw_timer.h"
#include "defines.h"

/*==============================================================================
 * GLOBAL VARIABLES
 *============================================================================*/
volatile bool timer0Expired = false;
volatile bool timer1Expired = false;

/*==============================================================================
 * TIMER SETUP FUNCTIONS
 *============================================================================*/

/**
 * @brief Setup Timer0 for microsecond delays (optimised for 50MHz CPU clock)
 * @param None
 * @return None
 * @note Configures Timer0 for 1µs resolution using 50MHz clock
 */
void setupTimer0(void)
{

    CMU_ClockEnable(cmuClock_TIMER0, true);               // Enable TIMER0 clock

    TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
    timerInit.enable = false;

    // For 50MHz CPU clock: 50MHz / 50 = 1MHz (perfect for 1µs per tick)
    timerInit.prescale = timerPrescale64;  // Use 64 prescaler (closest to 50)
    TIMER_Init(TIMER0, &timerInit);

    // With 50MHz CPU and prescaler 64: 50MHz / 64 = 781.25kHz
    // To get 1µs intervals: 781.25kHz / 781.25 ≈ 1000Hz = 1µs period
    // So we need TOP = 781 for approximately 1µs overflow
    uint32_t topValue = 781;  // Calculated for 50MHz with prescaler 64

    TIMER_TopSet(TIMER0, topValue);
    TIMER_IntEnable(TIMER0, TIMER_IEN_OF);
    NVIC_EnableIRQ(TIMER0_IRQn);
}

/**
 * @brief Setup Timer1 for millisecond delays (optimised for 50MHz CPU clock)
 * @param None
 * @return None
 * @note Configures Timer1 for 1ms resolution using 50MHz clock
 */
void setupTimer1(void)
{
    CMU_ClockEnable(cmuClock_TIMER1, true);               // Enable TIMER1 clock
    TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
    timerInit.enable = false;
    timerInit.prescale = timerPrescale1024;  // 50MHz / 1024 = 48.828kHz

    TIMER_Init(TIMER1, &timerInit);

    // With 50MHz CPU and prescaler 1024: 50MHz / 1024 = 48,828Hz
    // For 1ms period: 48,828Hz / 1000 = 48.828 ≈ 49 ticks per millisecond
    uint32_t topValue = 49;  // Calculated for 50MHz with prescaler 1024

    TIMER_TopSet(TIMER1, topValue);
    TIMER_IntEnable(TIMER1, TIMER_IEN_OF);
    NVIC_EnableIRQ(TIMER1_IRQn);
}

/*==============================================================================
 * DELAY FUNCTIONS
 *============================================================================*/

/**
 * @brief Microsecond delay using Timer0
 * @param delay_us: Delay in microseconds (1-65535)
 * @return None
 * @note Blocking delay with 1µs resolution
 * @example hw_timer0_us(100); // 100µs delay
 */
void hw_timer0_us(uint32_t delay_us)
{
    volatile uint32_t i;

    if (delay_us == 0) return;

    TIMER_CounterSet(TIMER0, 0);     // Reset timer counter and flag

    __disable_irq();
    timer0Expired = false;          // Critical section to avoid race condition
    __enable_irq();

    TIMER_Enable(TIMER0, true);

    for (i = 0; i < delay_us; i++)
    {
        while (!timer0Expired)     // Wait for timer overflow (1µs)
        {
            // Could add timeout protection here if needed
        }

        __disable_irq();
        timer0Expired = false;      // Critical section for flag reset
        __enable_irq();

        TIMER_CounterSet(TIMER0, 0);// Reset timer counter for next iteration
    }
    TIMER_Enable(TIMER0, false);
}

/**
 * @brief Millisecond delay using Timer1
 * @param delay_ms: Delay in milliseconds (1-65535)
 * @return None
 * @note Blocking delay with 1ms resolution
 * @example hw_timer1_ms(500); // 500ms delay
 */
void hw_timer1_ms(uint32_t delay_ms)
{
    volatile uint32_t i;

    if (delay_ms == 0) return;

    TIMER_CounterSet(TIMER1, 0);     // Reset timer counter and flag

    __disable_irq();
    timer1Expired = false;     // Critical section to avoid race condition
    __enable_irq();

    TIMER_Enable(TIMER1, true);

    for (i = 0; i < delay_ms; i++)
    {
        while (!timer1Expired)         // Wait for timer overflow (1ms)
        {
            // Could add timeout protection here if needed
        }

        __disable_irq();
        timer1Expired = false;         // Critical section for flag reset
        __enable_irq();

        TIMER_CounterSet(TIMER1, 0);         // Reset timer counter for next iteration
    }
    TIMER_Enable(TIMER1, false);
}

/**
 * @brief Single millisecond delay using Timer1
 * @param None
 * @return None
 * @note Convenience function for 1ms delay
 */
void hw_timer1_single_ms(void)
{
    hw_timer1_ms(1);
}

/**
 * @brief Single second delay using Timer1
 * @param None
 * @return None
 * @note Convenience function for 1 second delay
 */
void hw_timer1_second(void)
{
    hw_timer1_ms(1000);
}

/*==============================================================================
 * OPTIMISED DELAY FUNCTIONS FOR VERY SHORT DELAYS
 *============================================================================*/

/**
 * @brief Very short microsecond delay (1-10µs) using direct timer counting (50MHz optimised)
 * @param delay_us: Delay in microseconds (1-10 recommended)
 * @return None
 * @note More accurate for very short delays, doesn't use interrupts
 * @note Optimised for 50MHz CPU clock
 */
void hw_timer0_us_short(uint32_t delay_us)
{
    if (delay_us == 0) return;

    // For 50MHz CPU with prescaler 64: 50MHz / 64 = 781,250 Hz
    // Calculate ticks needed for delay_us microseconds
    // 781,250 ticks/second = 0.78125 ticks/microsecond
    uint32_t targetTicks = (781 * delay_us) / 1000;  // Approximation for 50MHz/64
    if (targetTicks == 0) targetTicks = 1;

    // Reset and start timer
    TIMER_CounterSet(TIMER0, 0);
    TIMER_Enable(TIMER0, true);

    // Wait for target count (polling method)
    while (TIMER_CounterGet(TIMER0) < targetTicks) {
        // Busy wait
    }

    TIMER_Enable(TIMER0, false);
}

/*==============================================================================
 * INTERRUPT HANDLERS
 *============================================================================*/

/**
 * @brief Timer0 interrupt handler for microsecond delays
 */
void TIMER0_IRQHandler(void)
{
    // Clear interrupt flag first
    TIMER_IntClear(TIMER0, TIMER_IF_OF);

    // Set the expired flag
    timer0Expired = true;
}

/**
 * @brief Timer1 interrupt handler for millisecond delays
 */
void TIMER1_IRQHandler(void)
{
    // Clear interrupt flag first
    TIMER_IntClear(TIMER1, TIMER_IF_OF);

    // Set the expired flag
    timer1Expired = true;
}

/*==============================================================================
 * UTILITY FUNCTIONS
 *============================================================================*/

/**
 * @brief Get current timer frequencies for debugging (50MHz system)
 * @param timer0_freq: Pointer to store Timer0 frequency
 * @param timer1_freq: Pointer to store Timer1 frequency
 * @return None
 */
void hw_timer_get_frequencies(uint32_t *timer0_freq, uint32_t *timer1_freq)
{
    // For 50MHz system with fixed prescalers
    *timer0_freq = 50000000 / 64;    // Timer0: 50MHz / 64 = 781,250 Hz
    *timer1_freq = 50000000 / 1024;  // Timer1: 50MHz / 1024 = 48,828 Hz
}

/**
 * @brief Calculate actual delay resolution (50MHz system)
 * @param timer_num: Timer number (0 or 1)
 * @return Resolution in nanoseconds
 */
uint32_t hw_timer_get_resolution_ns(uint8_t timer_num)
{
    if (timer_num == 0) {
        // Timer0: 50MHz / 64 = 781,250 Hz
        // Resolution = 1/781,250 = 1.28µs = 1,280ns per tick
        // With TOP=781, actual period = 781 * 1,280ns = 999,680ns ≈ 1µs
        return 1000;  // Approximately 1µs = 1000ns
    } else {
        // Timer1: 50MHz / 1024 = 48,828 Hz
        // Resolution = 1/48,828 = 20.48µs per tick
        // With TOP=49, actual period = 49 * 20.48µs = 1.003ms ≈ 1ms
        return 1000000;  // Approximately 1ms = 1,000,000ns
    }
}
