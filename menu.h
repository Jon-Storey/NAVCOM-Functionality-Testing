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


#include <stdint.h>



typedef struct
{
    const char *description;        // Pointer to string (no copying)
    void (*function_ptr)(void);     // Function pointer
} menu_item;



// Structure for menu list
typedef struct
{
    const menu_item *items;         // Pointer to array of menu items
    uint8_t count;                  // Number of items
    const char *title;              // Menu title
} menu_list;



// Structure for menu state
typedef struct
{
    const menu_list *current_menu;  // Current active menu
    uint8_t selected_index;         // Selected item index
    uint8_t menu_level;             // 0 = main, 1 = submenu
} menu_state;

// Public function prototypes
void init_menu_system(void);
void run_menu_system(void);
void print_menu(void);

// Navigation functions
void menu_up(void);
void menu_down(void);
void menu_select(void);
void menu_back(void);


// Utility functions
void print_number(uint8_t num);
char get_input(void);

// Menu transition function prototypes
void show_usbl_menu(void);
void show_fcpu_menu(void);
void show_imu_menu(void);
void show_pdem_menu(void);
void show_node_menu(void);
void show_thruster_menu(void);
void show_expander_menu(void);
void show_sdas_menu(void);
void show_random_menu(void);

// USBL function prototypes
void usbl_function_a(void);
void usbl_function_b(void);
void usbl_function_c(void);

// FCPU function prototypes
void fcpu_function_a(void);
void fcpu_function_b(void);
void fcpu_function_c(void);

// IMU function prototypes
void imu_function_a(void);
void imu_function_b(void);
void imu_function_c(void);

// PDEM function prototypes
void pdem_function_a(void);
void pdem_function_b(void);
void pdem_function_c(void);

// NODE function prototypes
void node_function_a(void);
void node_function_b(void);
void node_function_c(void);

// THRUST function prototypes
void thruster_function_a(void);
void thruster_function_b(void);
void thruster_function_c(void);

// EXPANDER function prototypes
void expander_function_a(void);
void expander_function_b(void);
void expander_function_c(void);

// SDAS function prototypes
void sdas_function_a(void);
void sdas_function_b(void);
void sdas_function_c(void);

// RANDOM function prototypes
void random_function_a(void);
void random_function_b(void);
void random_function_c(void);


extern menu_state state;



#endif /* MENU_H_ */
