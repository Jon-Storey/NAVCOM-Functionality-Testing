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


// Structure for menu items
typedef struct
{
    const char *description;
    void (*function_ptr)(void *param);  // Function pointer with parameter
    void *param;
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






// USART function prototypes
void show_usart_menu(void);
void usart_function_a(void *param);
void usart_function_b(void *param);
void usart_function_c(void *param);

// Ethernet function prototypes
void show_ethernet_menu(void);
void ethernet_function_a(void *param);


// Expander function prototypes
void show_expander_menu(void);
void expander_function_a(void *param);
void expander_function_b(void *param);


// Buzzer function prototypes
void show_buzzer_menu(void);
void buzzer_function_a(void *param);
void buzzer_function_b(void *param);




extern menu_state state;



#endif /* MENU_H_ */
