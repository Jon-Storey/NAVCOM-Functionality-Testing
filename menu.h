/*
 * menu.h
 *
 * @brief Header file for complete command line menu system
 * @description Provides function declarations and type definitions for hierarchical
 *              menu structure controlling all EFM32GG11B node subsystems including
 *              power management, communication interfaces, I2C operations, and
 *              system configuration.
 *
 *  Created on: 1 Jul 2025
 *      Author: JonathanStorey
 *    Hardware: EFM32GG11B Microcontroller
 *     Version: 1.0
 *
 * @note Uses character-based input for embedded system compatibility
 * @note Requires defines.h, helpers.h, usart.h, and i2c.h to be included
 * @note Call menu_init() during system startup to initialise menu system
 */


#ifndef MENU_H_
#define MENU_H_

#include <stdint.h>
#include <stdbool.h>

void menu_input_system(void);
void menu_output_system(char);




/*==============================================================================
 * MENU SYSTEM CONSTANTS
 *============================================================================*/

/// Maximum length for input buffer
#define MENU_INPUT_BUFFER_SIZE      32

/// Menu timeout in milliseconds (0 = no timeout)
#define MENU_TIMEOUT_MS             0

void display_main_menu(void);
void display_power_menu(void);
void display_node_modes_menu(void);
void display_i2c_menu(void);
void display_communication_menu(void);
void display_system_info_menu(void);
void display_test_menu(void);


void handle_main_menu(char input, NodeConfiguration *NodeConfig);
void handle_power_menu(char input, NodeConfiguration *ANodeConfig);
void handle_node_modes_menu(char input, NodeConfiguration *NodeConfig);
void handle_i2c_menu(char input, NodeConfiguration *NodeConfig);
void handle_communication_menu(char input, NodeConfiguration *NodeConfig);
void handle_test_menu(char input, NodeConfiguration *NodeConfig);

void menu_process_input(char input, NodeConfiguration *NodeConfig);

void handle_system_info_menu(char input, NodeConfiguration *NodeConfig);
void emergency_shutdown(void);
void i2c_bus_scan(void);
void menu_init(void);

void menu_return_to_main(void);



/*==============================================================================
 * MENU INTEGRATION MACROS
 * @brief Convenient macros for menu system integration
 *============================================================================*/

///// Quick menu initialisation macro
//#define MENU_INIT()                 menu_init()

/// Process input macro for main loop
//#define MENU_PROCESS(ch)            menu_process_input(ch)

///// Return to main menu macro
//#define MENU_HOME()                 menu_return_to_main()

#endif /* MENU_H_ */
