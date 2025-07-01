/*
 * Initialisation.c
 *
 * @brief System initialisation module for EFM32GG11B node hardware
 * @description This module handles complete system initialisation including:
 *              - Clock management for all peripherals
 *              - GPIO configuration for communication interfaces
 *              - Power control pin setup with safe default states
 *              - Peripheral initialization (USART, I2C, Timers)
 *
 *  Created on: 1 Jul 2025
 *      Author: JonathanStorey
 *    Hardware: EFM32GG11B Microcontroller
 *     Version: 1.0
 *
 * @note This function should be called once at system startup before main loop
 * @note All power rails start in OFF state for safe initialisation
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "sl_component_catalog.h"
#include "sl_system_init.h"
#include "sl_system_process_action.h"
#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_chip.h"
#include "em_timer.h"
#include "em_i2c.h"
#include "em_emu.h"
#include "EFM32GG11B420F2048GQ100.h"

#include "sw_delay.h"
#include "hw_timer.h"
#include "usart.h"
#include "buzzer.h"
#include "defines.h"
#include "i2c.h"
#include "helpers.h"
#include "menu.h"
#include "initialisation.h"

/**
 * @brief Complete system initialisation for EFM32GG11B node
 * @param None
 * @return None
 *
 * @description Performs comprehensive system initialisation in the following order:
 *              1. Chip-level initialisation
 *              2. Clock tree configuration for all peripherals
 *              3. GPIO pin configuration for communication interfaces
 *              4. Power control GPIO setup with safe defaults
 *              5. Peripheral module initialisation
 *
 * @note Initialisation Sequence:
 *       - All communication interfaces are configured but not enabled
 *       - All power rails start in OFF state for safety
 *       - Timers, USART, and I2C are initialised and ready for use
 *
 * @communication_interfaces:
 *       - IMU:       USART0 LOC2 (PC10/PC11) with RS485 control (PC8)
 *       - PDEM:      USART1 LOC1 (PD0/PD1)
 *       - Node:      USART2 LOC5 (PF0/PF1) with RS485 control (PF5)
 *       - Thrusters: USART3 LOC1 (PE6/PE7) with RS485 control (PE4)
 *       - Expander:  USART4 LOC0 (PB7/PB8/PC4) SPI mode
 *       - SDAS:      USART5 LOC1/2 (PA6/PB1)
 *       - FCPU:      UART0 LOC1 (PE0/PE1)
 *       - USBL:      UART1 LOC3 (PE2/PE3)
 *
 * @power_control_pins:
 *       - RS232_A:   PA4 (initialised OFF)
 *       - RS232_B:   PA5 (initialised OFF)
 *       - 3V3_REG:   PB2 (initialised OFF)
 *       - FCPU_5V:   PA15 (initialised OFF)
 *       - ETHERNET:  PE10 (initialised OFF)
 *       - EXP_A:     PD2 (initialised OFF)
 *       - EXP_B:     PD3 (initialised OFF)
 *       - EXP_C:     PD4 (initialised OFF)
 *       - BUZZER:    PC2 (initialised OFF)
 *
 * @dependencies: Requires setupTimer0(), usart_init(), and initI2C() functions
 *
 * @safety_note: All power control pins are set to OFF state during initialisation
 *               to prevent accidental device damage during startup
 */
void Initialise_Node(void)
{
    // Initialise chip-level hardware
    CHIP_Init();

    /*==========================================================================
     * CLOCK TREE CONFIGURATION
     * Enable clocks for all required peripherals
     *========================================================================*/
    CMU_ClockEnable(cmuClock_HFPER, true);      // High Frequency Peripheral Clock
    CMU_ClockEnable(cmuClock_GPIO, true);       // GPIO clock
    CMU_ClockEnable(cmuClock_I2C0, true);       // I2C Clock

    // USART and UART clocks
    CMU_ClockEnable(cmuClock_USART0, true);     // IMU interface
    CMU_ClockEnable(cmuClock_USART1, true);     // PDEM interface
    CMU_ClockEnable(cmuClock_USART2, true);     // Node interface
    CMU_ClockEnable(cmuClock_USART3, true);     // Thruster interface
    CMU_ClockEnable(cmuClock_USART4, true);     // Expander interface (SPI)
    CMU_ClockEnable(cmuClock_USART5, true);     // SDAS interface
    CMU_ClockEnable(cmuClock_UART0, true);      // FCPU interface
    CMU_ClockEnable(cmuClock_UART1, true);      // USBL interface

    /*==========================================================================
     * COMMUNICATION INTERFACE GPIO CONFIGURATION
     * Configure pins for all USART and UART interfaces
     *========================================================================*/

    // IMU - USART0 LOC2 with RS485 control
    GPIO_PinModeSet(gpioPortC, 10, gpioModeInput, 0);       // RX
    GPIO_PinModeSet(gpioPortC, 11, gpioModePushPull, 1);    // TX
    GPIO_PinModeSet(gpioPortC, 8, gpioModePushPull, 1);     // RS485 RTS control

    // PDEM - USART1 LOC1
    GPIO_PinModeSet(gpioPortD, 1, gpioModeInput, 0);        // RX
    GPIO_PinModeSet(gpioPortD, 0, gpioModePushPull, 1);     // TX

    // Node - USART2 LOC5 with RS485 control
    GPIO_PinModeSet(gpioPortF, 1, gpioModeInput, 0);        // RX
    GPIO_PinModeSet(gpioPortF, 0, gpioModePushPull, 1);     // TX
    GPIO_PinModeSet(gpioPortF, 5, gpioModePushPull, 1);     // RS485 RTS control

    // Thrusters - USART3 LOC1 with RS485 control
    GPIO_PinModeSet(gpioPortE, 7, gpioModeInput, 0);        // RX
    GPIO_PinModeSet(gpioPortE, 6, gpioModePushPull, 1);     // TX
    GPIO_PinModeSet(gpioPortE, 4, gpioModePushPull, 1);     // RS485 RTS control

    // Expander - USART4 LOC0 (SPI mode)
    GPIO_PinModeSet(gpioPortB, 8, gpioModeInput, 0);        // MISO
    GPIO_PinModeSet(gpioPortB, 7, gpioModePushPull, 1);     // MOSI
    GPIO_PinModeSet(gpioPortC, 4, gpioModePushPull, 1);     // CLK

    // SDAS - USART5 LOC1/2 (mixed locations)
    GPIO_PinModeSet(gpioPortB, 1, gpioModeInput, 0);        // RX (LOC2)
    GPIO_PinModeSet(gpioPortA, 6, gpioModePushPull, 1);     // TX (LOC1)

    // FCPU - UART0 LOC1
    GPIO_PinModeSet(gpioPortE, 1, gpioModeInput, 0);        // RX
    GPIO_PinModeSet(gpioPortE, 0, gpioModePushPull, 1);     // TX

    // USBL - UART1 LOC3
    GPIO_PinModeSet(gpioPortE, 3, gpioModeInput, 0);        // RX
    GPIO_PinModeSet(gpioPortE, 2, gpioModePushPull, 1);     // TX

    /*==========================================================================
     * POWER CONTROL GPIO CONFIGURATION
     * Configure power control pins and set safe default states (all OFF)
     *========================================================================*/

    // RS232 Interface Power Control
    GPIO_PinModeSet(gpioPortA, 4, gpioModePushPull, 1);     // RS232_A_SHDN
    GPIO_PinOutClear(gpioPortA, 4);                         // Initialize OFF

    GPIO_PinModeSet(gpioPortA, 5, gpioModePushPull, 1);     // RS232_B_SHDN
    GPIO_PinOutClear(gpioPortA, 5);                         // Initialize OFF

    // System Power Rails
    GPIO_PinModeSet(gpioPortB, 2, gpioModePushPull, 1);     // 3V3 Regulator Enable
    GPIO_PinOutClear(gpioPortB, 2);                         // Initialize OFF

    GPIO_PinModeSet(gpioPortA, 15, gpioModePushPull, 1);    // FCPU 5V Disable
    GPIO_PinOutClear(gpioPortA, 15);                        // Initialize OFF

    GPIO_PinModeSet(gpioPortE, 10, gpioModePushPull, 1);    // Ethernet Switch
    GPIO_PinOutClear(gpioPortE, 10);                        // Initialize OFF

    // Expander Module Power Control
    GPIO_PinModeSet(gpioPortD, 2, gpioModePushPull, 1);     // Expander A Reset
    GPIO_PinOutClear(gpioPortD, 2);                         // Initialize OFF

    GPIO_PinModeSet(gpioPortD, 3, gpioModePushPull, 1);     // Expander B Reset
    GPIO_PinOutClear(gpioPortD, 3);                         // Initialize OFF

    GPIO_PinModeSet(gpioPortD, 4, gpioModePushPull, 1);     // Expander C Reset
    GPIO_PinOutClear(gpioPortD, 4);                         // Initialize OFF

    // System Feedback
    GPIO_PinModeSet(gpioPortC, 2, gpioModePushPull, 1);     // Buzzer Control
    GPIO_PinOutClear(gpioPortC, 2);                         // Initialize OFF

    /*==========================================================================
     * PERIPHERAL INITIALIZATION
     * Initialize configured peripherals
     *========================================================================*/
    setupTimer0();          // Hardware timer initialization
    usart_init();           // All USART/UART interfaces
    initI2C();              // I2C interface for sensor communication

    // System is now ready for operation
}
