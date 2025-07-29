/*
 * menu.c
 *
 * @brief Complete command line menu system for EFM32GG11B node control
 * @description Provides hierarchical menu structure for controlling all node
 *              subsystems including power management, communication interfaces,
 *              I2C operations, and system configuration.
 *
 *  Created on: 1 Jul 2025
 *      Author: JonathanStorey
 *    Hardware: EFM32GG11B Microcontroller
 *     Version: 1.0
 *
 * @note Uses character-based input for embedded system compatibility
 * @note Integrates with existing helper functions and NodeConfiguration structure
 *
 *
├── 1. Power Management
│   ├── 1. Toggle 5V Rail (FCPU)
│   ├── 2. Toggle 3.3V Regulator
│   ├── 3. Toggle Ethernet Switch
│   ├── 4. Toggle RS232 Interface A
│   ├── 5. Toggle RS232 Interface B
│   ├── 6. Toggle Expander A
│   ├── 7. Toggle Expander B
│   ├── 8. Toggle Expander C
│   ├── 9. Emergency Shutdown (All OFF)
│   └── 0. Back to Main Menu
├── 2. Node Operating Modes
│   ├── 1. Flight Mode (Minimal power, critical systems only)
│   ├── 2. Deck Mode (Full communication enabled)
│   ├── 3. Safe Mode (Reduced functionality)
│   ├── 4. Service Mode (Maintenance and diagnostics)
│   ├── 5. Ethernet Mode (Ethernet-focused communication)
│   ├── 6. RS232 Mode (RS232-focused communication)
│   ├── 7. Expanders Mode (Expansion modules active)
│   └── 0. Back to Main Menu
├── 3. I2C Operations
│   ├── 1. Read Device 0x31 Register 0x00
│   ├── 2. Read Device 0x19 Register 0x00 (Compass)
│   ├── 3. I2C Bus Scan
│   ├── 4. Custom Register Read
│   ├── 5. I2C Status
│   └── 0. Back to Main Menu
├── 4. Communication Tests
│   ├── 1. Test IMU Interface (USART0)
│   ├── 2. Test PDEM Interface (USART1)
│   ├── 3. Test Thruster Interface (USART3)
│   ├── 4. Test FCPU Interface (UART0)
│   ├── 5. Test USBL Interface (UART1)
│   ├── 6. Test All Interfaces
│   └── 0. Back to Main Menu
├── 5. System Information
│   ├── 1. Current Power Status
│   ├── 2. GPIO Pin States
│   ├── 3. Clock Configuration
│   ├── 4. Memory Information
│   ├── 5. Version Information
│   ├── 6. Hardware Test
│   └── 0. Back to Main Menu
└── 0. System Status Display (Returns to Main Menu)
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "defines.h"
#include "helpers.h"
#include "usart.h"
#include "i2c.h"
#include "menu.h"
#include "ethernet_switch.h"
#include "hw_timer.h"
#include "usart_expanders.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "usart.h"


// Global menu state
menu_state state = {
        .current_menu =0,
        .menu_level =0,
        .selected_index = 0};


//typedef struct
//{
//    const char *description;        // Pointer to string (no copying)
//    void (*function_ptr)(void);     // Function pointer
//} menu_item;


// Structure for menu list
//typedef struct
//{
//    const menu_item *items;         // Pointer to array of menu items
//    uint8_t count;                  // Number of items
//    const char *title;              // Menu title
//} menu_list;



// Main menu items (static const - stored in ROM)
static const menu_item main_items[] =       // this is an array main menu items.
{                                           // it allows grouping of function onto new lists
    {"USBL Functions",   show_usbl_menu},   // manually add item here, {description, *function pointer}
    {"FCPU Functions",   show_fcpu_menu},   // update the manu_list details below
    {"IMU Functions",    show_imu_menu},
    {"PDEM Functions",   show_pdem_menu},
    {"NODE Functions",   show_node_menu},
    {"THRUSTER Functions", show_thruster_menu},
    {"EXPANDER Functions",  show_expander_menu},
    {"SDAS Functions",   show_sdas_menu},
    {"Random Functions", show_random_menu}
};



// Menu lists (static const - stored in ROM)
static const menu_list main_menu =          // this is a MENU_LIST
{                                           // it tells how mant items are on the list
    main_items,                             // pointer of type menu_items, pointing to array of main items
    9,                                      // how many items in main menu
    "Main Menu"                             // list name
};







//=============================================================================
// Menu Configuration
//=============================================================================
/**
 * @brief USBL submenu items array
 *
 * Static constant array containing menu items for USBL (Ultra-Short Baseline)
 * positioning system functions. Each item contains a description string and
 * function pointer for the corresponding USBL operation.
 *
 * @note Stored in ROM to conserve RAM on embedded system
 */
static const menu_item usbl_items[] =
{
    {"USBL Function A", usbl_function_a},
    {"USBL Function B", usbl_function_b},
    {"USBL Function C", usbl_function_c}
};

static const menu_list usbl_menu =
{
    usbl_items,     // Pointer to menu items array
    3,              // Number of items in menu
    "USBL Functions" // Menu title displayed to user
};




//=============================================================================
// FCPU Menu Configuration
//=============================================================================
static const menu_item fcpu_items[] =
{
    {"FCPU Function A", fcpu_function_a},
    {"FCPU Function B", fcpu_function_b},
    {"FCPU Function C", fcpu_function_c}
};

static const menu_list fcpu_menu =
{
    fcpu_items,      // Pointer to menu items array
    3,               // Number of items in menu
    "FCPU Functions" // Menu title displayed to user
};



//=============================================================================
// IMU Menu Configuration
//=============================================================================
static const menu_item imu_items[] =
{
    {"IMU Function A", imu_function_a},
    {"IMU Function B", imu_function_b},
    {"IMU Function C", imu_function_c}
};

static const menu_list imu_menu =
{
    imu_items,      // Pointer to menu items array
    3,               // Number of items in menu
    "IMU Functions" // Menu title displayed to user
};


//=============================================================================
// PDEM Menu Configuration
//=============================================================================
static const menu_item pdem_items[] =
{
    {"IMU Function A", pdem_function_a},
    {"IMU Function B", pdem_function_b},
    {"IMU Function C", pdem_function_c}
};

static const menu_list pdem_menu =
{
    pdem_items,      // Pointer to menu items array
    3,               // Number of items in menu
    "PDEM Functions" // Menu title displayed to user
};


//=============================================================================
// NODE Menu Configuration
//=============================================================================
static const menu_item node_items[] =
{
    {"Node Function A", node_function_a},
    {"Node Function B", node_function_b},
    {"Node Function C", node_function_c}
};

static const menu_list node_menu =
{
    node_items,      // Pointer to menu items array
    3,               // Number of items in menu
    "Node Functions" // Menu title displayed to user
};



//=============================================================================
// Thrusters Menu Configuration
//=============================================================================
static const menu_item thruster_items[] =
{
    {"Thruster Function A", thruster_function_a},
    {"Thruster Function B", thruster_function_b},
    {"Thruster Function C", thruster_function_c}
};

static const menu_list thruster_menu =
{
    thruster_items,      // Pointer to menu items array
    3,               // Number of items in menu
    "Thruster Functions" // Menu title displayed to user
};




//=============================================================================
// Expander Menu Configuration
//=============================================================================
static const menu_item expander_items[] =
{
    {"Expander Function A", expander_function_a},
    {"Expander Function B", expander_function_b},
    {"Expander Function C", expander_function_c}
};

static const menu_list expander_menu =
{
    expander_items,      // Pointer to menu items array
    3,               // Number of items in menu
    "expander Functions" // Menu title displayed to user
};



//=============================================================================
// Expander Menu Configuration
//=============================================================================
static const menu_item random_items[] =
{
    {"Random Function A", random_function_a},
    {"Random Function B", random_function_b},
    {"Random Function C", random_function_c}
};

static const menu_list random_menu =
{
    random_items,      // Pointer to menu items array
    3,               // Number of items in menu
    "Random Functions" // Menu title displayed to user
};



//=============================================================================
// SDAS Menu Configuration
//=============================================================================
static const menu_item sdas_items[] =
{
    {"SDAS Function A", sdas_function_a},
    {"SDAS Function B", sdas_function_b},
    {"SDAS Function C", sdas_function_c}
};

static const menu_list sdas_menu =
{
    sdas_items,
    3,
    "SDAS Functions"
};






// Print a number (simple helper)
void print_number(uint8_t num)
{
    if (num >= 10)
    {
        print_number(num / 10);
    }
    put_char('0' + (num % 10), Node);
}

// Display current menu
void print_menu(void)
{
    print_string("\n\r--- ", Node);
    print_string(state.current_menu->title, Node);
    print_string(" ---\n\r", Node);

    for (uint8_t i = 0; i < state.current_menu->count; i++)
    {
        if (i == state.selected_index)
        {
            print_string("> ", Node);
        }
        else
        {
            print_string("  ", Node);
        }

        print_number(i + 1);
        print_string(". ", Node);
        print_string(state.current_menu->items[i].description, Node);
        print_string("\n\r", Node);
    }

    if (state.menu_level > 0)
    {
        print_string("  0. Back\n\r", Node);
    }
}



// Navigation functions
void menu_up(void)
{
    if (state.selected_index > 0)
    {
        state.selected_index--;
    }
}

void menu_down(void)
{
    if (state.selected_index < state.current_menu->count - 1)
      {
        state.selected_index++;
    }
}

void menu_select(void)
{
    if (state.current_menu->items[state.selected_index].function_ptr != 0)
      {
        state.current_menu->items[state.selected_index].function_ptr();
    }
}

void menu_back(void)
{
    if (state.menu_level > 0)
      {
        state.current_menu = &main_menu;
        state.selected_index = 0;
        state.menu_level = 0;
    }
}


// Menu transition functions
void show_usbl_menu(void)
{
    state.current_menu = &usbl_menu;
    state.selected_index = 0;
    state.menu_level = 1;
}

void show_fcpu_menu(void)
{
    state.current_menu = &fcpu_menu;
    state.selected_index = 0;
    state.menu_level = 1;
}

void show_imu_menu(void)
{
    state.current_menu = &imu_menu;
    state.selected_index = 0;
    state.menu_level = 1;
}

void show_pdem_menu(void)
{
    state.current_menu = &pdem_menu;
    state.selected_index = 0;
    state.menu_level = 1;
}


void show_node_menu(void)
{
    state.current_menu = &node_menu;
    state.selected_index = 0;
    state.menu_level = 1;
}

void show_thruster_menu(void)
{
    state.current_menu = &thruster_menu;
    state.selected_index = 0;
    state.menu_level = 1;
}

void show_expander_menu(void)
{
    state.current_menu = &expander_menu;
    state.selected_index = 0;
    state.menu_level = 1;
}

void show_sdas_menu(void)
{
    state.current_menu = &sdas_menu;
    state.selected_index = 0;
    state.menu_level = 1;
}

void show_random_menu(void)
{
    state.current_menu = &random_menu;
    state.selected_index = 0;
    state.menu_level = 1;
}



// Get user input
char get_input(void)
{
    return USART_ReceiveChar(USART2);
}

// Initialize menu system
void init_menu_system(void)
{
    state.current_menu = &main_menu;
    state.selected_index = 0;
    state.menu_level = 0;
}



// Main menu loop
void run_menu_system(void)
{
    char input;

    while (1)
      {
        clear_screen();
        print_menu();
        input = get_input();


        switch (input)
        {
            case 'W':             menu_up();    break;
            case 'S':             menu_down();  break;
            case '\r': case '\n': menu_select(); break;
            case 'B':             menu_back();  break;

         /*
            case '1':
                state.selected_index = 0;
                menu_select();
                break;
            case '2':
                if (state.current_menu->count > 1)
                  {
                    state.selected_index = 1;
                    menu_select();
                }
                break;
            case '3':
                if (state.current_menu->count > 2)
                  {
                    state.selected_index = 2;
                    menu_select();
                }
                break;
            */
            case '0':
                menu_back();
                break;

            case 'Q':
                return;

        }
    }
}




// USBL Functions
void usbl_function_a(void)
{
    print_string("\n\rExecuting USBL Function A\n\r", USBL);
    print_string("Press any key...\n\r", Node);
    get_input();
}

void usbl_function_b(void)
{
    print_string("\n\rExecuting USBL Function B\n\r", USBL);
    print_string("Press any key...\n\r", Node);
    get_input();
}

void usbl_function_c(void)
{
    print_string("\n\rExecuting USBL Function C\n\r", USBL);
    print_string("Press any key...\n\r", Node);
    get_input();
}


// FCPU Functions
void fcpu_function_a(void)
{
    print_string("\n\rExecuting FCPU Function A\n\r", FCPU);
    print_string("Press any key...\n\r", Node);
    get_input();
}
void fcpu_function_b(void)
{
    print_string("\n\rExecuting FCPU Function B\n\r", FCPU);
    print_string("Press any key...\n\r", Node);
    get_input();
}
void fcpu_function_c(void)
{
    print_string("\n\rExecuting FCPU Function C\n\r", FCPU);
    print_string("Press any key...\n\r", Node);
    get_input();
}

// IMU Functions
void imu_function_a(void)
{
    print_string("\n\rExecuting IMU Function A\n\r", IMU);
    print_string("Press any key...\n\r", Node);
    get_input();
}
void imu_function_b(void)
{
    print_string("\n\rExecuting IMU Function B\n\r", IMU);
    print_string("Press any key...\n\r", Node);
    get_input();
}
void imu_function_c(void)
{
    print_string("\n\rExecuting IMU Function C\n\r", IMU);
    print_string("Press any key...\n\r", Node);
    get_input();
}

// PDEM Functions
void pdem_function_a(void)
{
    print_string("\n\rExecuting PDEM Function A\n\r", PDEM);
    print_string("Press any key...\n\r", Node);
    get_input();
}
void pdem_function_b(void)
{
    print_string("\n\rExecuting PDEM Function B\n\r", PDEM);
    print_string("Press any key...\n\r", Node);
    get_input();
}
void pdem_function_c(void)
{
    print_string("\n\rExecuting PDEM Function C\n\r", PDEM);
    print_string("Press any key...\n\r", Node);
    get_input();
}

// NODE Functions
void node_function_a(void)
{
    print_string("\n\rExecuting NODE Function A\n\r", Node);
    print_string("Press any key...\n\r", Node);
    get_input();
}
void node_function_b(void)
{
    print_string("\n\rExecuting NODE Function B\n\r", Node);
    print_string("Press any key...\n\r", Node);
    get_input();
}
void node_function_c(void)
{
    print_string("\n\rExecuting NODE Function C\n\r", Node);
    print_string("Press any key...\n\r", Node);
    get_input();
}

// THRUST Functions
void thruster_function_a(void)
{
    print_string("\n\rExecuting THRUST Function A\n\r", Thrusters);
    print_string("Press any key...\n\r", Node);
    get_input();
}
void thruster_function_b(void)
{
    print_string("\n\rExecuting THRUST Function B\n\r", Thrusters);
    print_string("Press any key...\n\r", Node);
    get_input();
}
void thruster_function_c(void)
{
    print_string("\n\rExecuting THRUST Function C\n\r", Thrusters);
    print_string("Press any key...\n\r", Node);
    get_input();
}

// EXPANDER Functions
void expander_function_a(void)
{
    print_string("\n\rExecuting EXPANDER Function A\n\r", Expander);
    print_string("Press any key...\n\r", Node);
    get_input();
}
void expander_function_b(void)
{
    print_string("\n\rExecuting EXPANDER Function B\n\r", Expander);
    print_string("Press any key...\n\r", Node);
    get_input();
}
void expander_function_c(void)
{
    print_string("\n\rExecuting EXPANDER Function C\n\r", Expander);
    print_string("Press any key...\n\r", Node);
    get_input();
}

// RANDOM Functions
void random_function_a(void)
{
    print_string("\n\rExecuting RANDOM Function A\n\r", Node);
    print_string("Press any key...\n\r", Node);
    get_input();
}
void random_function_b(void)
{
    print_string("\n\rExecuting RANDOM Function B\n\r", Node);
    print_string("Press any key...\n\r", Node);
    get_input();
}
void random_function_c(void)
{
    print_string("\n\rExecuting RANDOM Function C\n\r", Node);
    print_string("Press any key...\n\r", Node);
    get_input();
}

// SDAS Functions
void sdas_function_a(void)
{
    print_string("\n\rExecuting SDAS Function A\n\r", SDAS);
    print_string("Press any key...\n\r", Node);
    get_input();
}

void sdas_function_b(void)
{
    print_string("\n\rExecuting SDAS Function B\n\r", SDAS);
    print_string("Press any key...\n\r", Node);
    get_input();
}

void sdas_function_c(void)
{
    print_string("\n\rExecuting SDAS Function C\n\r", SDAS);
    print_string("Press any key...\n\r", Node);
    get_input();
}
