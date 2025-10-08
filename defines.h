
/*
 * defines.h
 *
 * @brief Global definitions, enumerations, and data structures for EFM32GG11B node system
 * @description This header contains all system-wide constants, enumerations for device
 *              communication, power states, operating modes, and the main node configuration
 *              structure. Also includes I2C state machine definitions.
 *
 *  Created on: 20 May 2025
 *      Author: JonathanStorey
 *    Hardware: EFM32GG11B Microcontroller
 *     Version: 1.0
 *
 * @note This file should be included by all modules requiring system definitions
 * @note Global variables are declared extern - define them in main.c or appropriate module
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#include <stdint.h>
#include <stdbool.h>


/*==============================================================================
 * SYSTEM CONSTANTS
 *============================================================================*/
#define BUFFER_SIZE 80              ///< Size for general purpose communication buffers

/*==============================================================================
 * GLOBAL BUFFER DECLARATIONS
 * @note These are declared here but should be defined in main.c
 *============================================================================*/
extern char buffer[BUFFER_SIZE];    ///< General purpose communication buffer
extern char asciiStr[4];            ///< ASCII conversion buffer (max uint8_t = 255 → 3 digits + null)


/*==============================================================================
 * COMMUNICATION DESTINATION ENUMERATION
 * @brief Defines target devices for message routing and communication
 *============================================================================*/
typedef enum {
    IMU,                            ///< Inertial Measurement Unit
    PDEM,                           ///< Power Distribution and Energy Management
    Node,                           ///< This node (local terminal/debug output)
    Thrusters,                      ///< Thruster control system
    Expander,                       ///< Expansion module interface
    SDAS,                           ///< System Data Acquisition System
    FCPU,                           ///< Flight Computer Processing Unit
    USBL                            ///< Ultra-Short Baseline acoustic positioning
} destination_t;

/*==============================================================================
 * POWER STATE ENUMERATION
 * @brief Defines ON/OFF states for power control functions
 *============================================================================*/
typedef enum {
    Off = 0,                        ///< Power OFF state
    On = 1                          ///< Power ON state
} power_state_t;



/*==============================================================================
 * SELECTED STATE ENUMERATION
 * @brief Defines ON/OFF states for CS control functions
 *============================================================================*/
typedef enum {
    Deselected = 0,                        ///< Power OFF state
    Selected = 1                          ///< Power ON state
} CS_state_t;

/*==============================================================================
 * NODE OPERATING MODE ENUMERATION
 * @brief Defines different operational modes for the node system
 * @note Each mode configures different combinations of active subsystems
 *============================================================================*/
typedef enum {
    Flight,                         ///< Flight mode - minimal power, critical systems only
    Deck,                           ///< Deck operations mode - full communication
    Safe,                           ///< Safe mode - reduced functionality for troubleshooting
    Service,                        ///< Service mode - maintenance and diagnostics
    Ethernet,                       ///< Ethernet-focused communication mode
    RS232,                          ///< RS232-focused communication mode
    Expanders                       ///< Expander modules active mode
} node_mode_state_t;

/*==============================================================================
 * NODE CONFIGURATION STRUCTURE
 * @brief Main configuration structure containing all subsystem states
 * @note Flag meanings: '1' = device enabled, '0' = device disabled
 * @note Some hardware uses active-low signals - GPIO polarity handled in power functions
 *============================================================================*/
typedef struct {
    int NodeMode;                   ///< Current operating mode (from node_mode_state_t)
// subsystem enable signals
    char EthernetSwitchEnable;      ///< Ethernet switch state (GPIO Port E, Pin 10)
    char FCPU_Disable;              ///< 5V/FCPU power state (GPIO Port A, Pin 15)
    char Reg_3V3_Enable;            ///< 3.3V regulator state (GPIO Port B, Pin 2)
    char PL_V1_Disable;             ///< Payload V1 power state (uses 3V rail)
    char PL_V2_Disable;             ///< Payload V2 power state (uses 3V rail)
    char RS232_A_Shutdown;          ///< RS232 Interface A state (GPIO Port A, Pin 4)
    char RS232_B_Shutdown;          ///< RS232 Interface B state (GPIO Port A, Pin 5)
    char Expander_A_Shutdown;       ///< Expander A module state (GPIO Port D, Pin 2)
    char Expander_B_Shutdown;       ///< Expander B module state (GPIO Port D, Pin 3)
    char Expander_C_Shutdown;       ///< Expander C module state (GPIO Port D, Pin 4)
// Reset signals
    char EthernetSwitchReset;       ///< Ethernet switch state (GPIO Port F, Pin 12)
    char SDAS_Reset;                ///< SDAS Reset state (GPIO Port C, Pin 1)
    char PDEM_Reset;                ///< PDEM Reset state (GPIO Port A, Pin 11)
    char FCPU_Reset;                ///< FCPU Reset state (GPIO Port C, Pin 7)
    char IMU_Reset;                 ///< IMU Reset state (GPIO Port A, Pin 11)
    char Antenna_Reset;             ///< Antenna Reset state (GPIO Port B, Pin 6)
// GPIO signals
    char FCPU_GPIO_0;
    char Sensor_Caddy_GPIO_0;
    char Sensor_Caddy_GPIO_1;
    char PLA_GPIO_0;
    char PLA_GPIO_1;
    char PLB_GPIO_0;
    char PLB_GPIO_1;
    char PLC_GPIO_0;
    char PLD_GPIO_0;
    char PLE_GPIO_0;

} NodeConfiguration;

/*==============================================================================
 * GLOBAL NODE CONFIGURATION INSTANCE
 * @brief External declaration of the main node configuration structure
 * @note Must be defined in main.c or appropriate module
 *============================================================================*/
extern NodeConfiguration NodeConfig;

/*==============================================================================
 * I2C STATE MACHINE ENUMERATION
 * @brief Defines states for interrupt-driven I2C communication
 * @note Used by I2C interrupt handler for non-blocking register reads
 *============================================================================*/
typedef enum {
    I2C_STATE_IDLE,                 ///< I2C bus idle, ready for new transaction
    I2C_STATE_SEND_ADDR,            ///< Sending device address (write mode)
    I2C_STATE_SEND_REG,             ///< Sending register address to read from
    I2C_STATE_RESTART,              ///< Sending repeated start condition
    I2C_STATE_READ,                 ///< Reading data from device
    I2C_STATE_DONE,                 ///< Transaction completed successfully
    I2C_STATE_ERROR,                ///< Error occurred during transaction
    I2C_STATE_WAITSTOP              ///< Waiting for stop condition completion
} I2C_State_t;



/*==============================================================================
 * MENU STATE MANAGEMENT
 *============================================================================*/
typedef enum {
    MENU_MAIN,
    MENU_POWER,
    MENU_NODE_MODES,
    MENU_I2C_OPS,
    MENU_COMMUNICATION,
    MENU_SYSTEM_INFO,
    MENU_TEST
} menu_state_t;



#define EFM32_HFXO_FREQ (50000000UL)
















#endif /* DEFINES_H_ */
