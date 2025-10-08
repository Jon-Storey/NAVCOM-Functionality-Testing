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
#include "em_gpio.h"

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
#include "buzzer.h"





//=============================================================================
// Menu Configuration
//=============================================================================

menu_state state = {           // Global menu state
        .current_menu =0,
        .menu_level =0,
        .selected_index = 0};


                                                                                // Main menu items (static const - stored in ROM)
static const menu_item main_items[] =                                           // this is an array main menu items.
{                                                                               // it allows grouping of function onto new lists
    {"USART Functions",        show_usart_menu, NULL  },                          // manually add item here, {description, *function pointer}
    {"Ethernet Functions",     show_ethernet_menu, &NodeConfig} ,                           // update the manu_list details below
    {"Expander Functions",     show_expander_menu, &NodeConfig} ,
    {"Buzzer Functions",       show_buzzer_menu, NULL}                            // update the manu_list details below


};



// Menu lists (static const - stored in ROM)
static const menu_list main_menu =          // this is a MENU_LIST
{                                           // it tells how mant items are on the list
    main_items,                             // pointer of type menu_items, pointing to array of main items
    4,                                      // how many items in main menu
    "Main Menu"                             // list name
};








//=============================================================================
// Sub-Menu Configuration - USART
//=============================================================================
static const menu_item usart_items[] =
{
    {"Enable all the DCDC and LDOS",    usart_function_a,     &NodeConfig},
    {"USART loop all",                  usart_function_b,     &NodeConfig},
    {"Send Hello to PLA1",              usart_function_c,     &NodeConfig}


};

static const menu_list usart_menu =
{
    usart_items,     // Pointer to menu items array
    7,              // Number of items in menu
    "USART Functions" // Menu title displayed to user
};

void show_usart_menu(void)
{
    state.current_menu = &usart_menu;
    state.selected_index = 0;
    state.menu_level = 1;
}

// USART Functions
void usart_function_a(void *param)
{
  NodeConfiguration *pNodeConfig = (NodeConfiguration*)param;                   //lets this function point to Node config structure

  Set_5V_Power_State(On, pNodeConfig);                                            //enable the core LDOs and drivers
  hw_timer1_ms(1000);
  Set_3V_Power_State(On, pNodeConfig);
  hw_timer1_ms(1000);

  Set_RS232_A_Power_State(On, pNodeConfig);                                       //REQURIED FOR RS232 COMMS
  Set_RS232_B_Power_State(On, pNodeConfig);
  hw_timer1_ms(1000);
}

void usart_function_b (void *param)
{
 // NodeConfiguration *pNodeConfig = (NodeConfiguration*)param;
  print_string("PEntering infinite USART loop\n\r", Node);
  hw_timer1_ms(1000);
  USART_Test_Cycle();
}

void usart_function_c(void *param)
{
  NodeConfiguration *pNodeConfig = (NodeConfiguration*)param;
  print_string("\n\r Add PDEM message here... \n\r", Node);
  print_string("\n\r Add PDEM message here... \n\r", PDEM);
}


//=============================================================================
// Ethernet Menu Configuration
//=============================================================================


static const menu_item ethernet_items[] =
{
    {"Enable Switch  "  , ethernet_function_a     ,&NodeConfig}
 //   {"Buzz tone"        , buzzer_function_b     ,&NodeConfig}

};


static const menu_list ethernet_menu =
{
    ethernet_items,                                                             // Pointer to menu items array
    1,                                                                          // Number of items in menu
    "Ethernet Switch Functions"                                                 // Menu title displayed to user
};


void show_ethernet_menu(void)
{
    state.current_menu = &ethernet_menu;
    state.selected_index = 0;
    state.menu_level = 1;
}



// Ethernet Functions
void ethernet_function_a(void *param)
{
    NodeConfiguration *pNodeConfig = (NodeConfiguration*)param;

    //REQURIED FOR ETHERNET SWITCH COMMS
    Set_Ethernet_Switch_Power_State(Off, pNodeConfig);         // regardless of current situation, turn off power to the chip
    hw_timer1_ms(100);                                          // wait for the chip to power down and settle
    Set_Ethernet_Switch_Power_State(On, pNodeConfig);          // re-apply power to the chip
    hw_timer1_ms(10);                                          // wait 5ms after powering on chip
    Set_Ethernet_Switch_Reset_State(Off, pNodeConfig);                // Set Reset low, which resets chip
    hw_timer1_ms(150);                                         // wait 15 ms with RESET low for warm reset
    Set_Ethernet_Switch_Reset_State(On, pNodeConfig);                 // Set Reset high. Strap on values are read on the rising edge (includes a reading time)
    hw_timer1_ms(150);

   // Set_RS232_A_Power_State(On, pNodeConfig);
   // Set_RS232_B_Power_State(On, pNodeConfig);
    hw_timer1_ms(3000);


}




//=============================================================================
// Expander Menu Configuration
//=============================================================================


static const menu_item expander_items[] =
{
    {"Enable expanders  "  , expander_function_a     ,&NodeConfig},
    {"send hello to PLA1"  , expander_function_b     ,&NodeConfig}

};


static const menu_list expander_menu =
{
    expander_items,                                                             // Pointer to menu items array
    2,                                                                          // Number of items in menu
    "Expander Functions"                                                 // Menu title displayed to user
};


void show_expander_menu(void)
{
    state.current_menu = &expander_menu;
    state.selected_index = 0;
    state.menu_level = 1;
}



void expander_function_a(void *param)
{

  NodeConfiguration *pNodeConfig = (NodeConfiguration*)param;


  Set_5V_Power_State(On, pNodeConfig);                                            //enable the core LDOs and drivers
  hw_timer1_ms(1000);
  Set_3V_Power_State(On, pNodeConfig);
  hw_timer1_ms(1000);

  Set_RS232_A_Power_State(On, pNodeConfig);                                       //REQURIED FOR RS232 COMMS
  Set_RS232_B_Power_State(On, pNodeConfig);
  hw_timer1_ms(1000);


  Set_Expander_A_Power_State(On, pNodeConfig );                                 //turn on all expanders, power required for high z state! cant leave any off
  Set_Expander_B_Power_State(On, pNodeConfig );
  Set_Expander_C_Power_State(On, pNodeConfig );

  Set_Expander_A_CS_State(Deselected);
  Set_Expander_B_CS_State(Deselected);
  Set_Expander_C_CS_State(Deselected);                                          // deselect the  expanders

  GPIO_PinOutSet(gpioPortD, 3);                                                 // Pull reset high EXP3 = uSART b = pin 49 on efm
  GPIO_PinOutSet(gpioPortD, 2);                                                 // Pull reset high usart A
  GPIO_PinOutSet(gpioPortD, 4);                                                 // MAKE IONTO A HELPER FUNCTION FOR EASY READING

  hw_timer1_ms(100);

  MAX14830_UART_Init(EXPANDER_A);
  MAX14830_UART_Init(EXPANDER_B);
  MAX14830_UART_Init(EXPANDER_C);

  hw_timer1_ms(100);

  while(1)
  {
      hw_timer1_ms(10);
      MAX14830_SendString(EXPANDER_A,  MAX14830_UART0, "Hello World");
      print_string("x", Node);
    }
}


void expander_function_b(void *param)
{


}





//=============================================================================
// Buzzer Menu Configuration
//=============================================================================


static const menu_item buzzer_items[] =
{
    {"Sing happy song"  , buzzer_function_a     ,&NodeConfig},
    {"Buzz tone"        , buzzer_function_b     ,&NodeConfig}

};


static const menu_list buzzer_menu =
{
    buzzer_items,     // Pointer to menu items array
    2,              // Number of items in menu
    "Buzzer Functions" // Menu title displayed to user
};


void show_buzzer_menu(void)
{
    state.current_menu = &buzzer_menu;
    state.selected_index = 0;
    state.menu_level = 1;
}

// Buzzer Functions
void buzzer_function_a(void *param)
{
    print_string("Buzzing a happy song\n\r", Node);
    while (1)
      {
            // Play C major scale
            buzzer_play_note(NOTE_C4, 1000);  // C for 500ms
            buzzer_play_note(NOTE_OFF, 1000);  // 50ms pause
            buzzer_play_note(NOTE_C5, 1000);  // C for 500ms
            buzzer_play_note(NOTE_OFF, 1000);  // 50ms pause
            buzzer_play_note(NOTE_C6, 1000);  // C for 500ms
            buzzer_play_note(NOTE_OFF, 1000);  // 50ms pause
            buzzer_play_note(NOTE_C7, 1000);  // C for 500ms
            buzzer_play_note(NOTE_OFF, 1000);  // 50ms pause

      }
}

void buzzer_function_b(void *param)
{
  print_string("\n\r Add USBL message here... \n\r", Node);
  print_string("\n\r Add USBL message here... \n\r", USBL);
}

















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
        // Get the menu item
        const menu_item *item = &state.current_menu->items[state.selected_index];

        // Call the function with its parameter
        item->function_ptr(item->param);
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
            case 'W':  case 'w':            menu_up();    break;
            case 'S':  case 's':            menu_down();  break;
            case '\r': case '\n':           menu_select(); break;
            case 'B':  case 'b':            menu_back();  break;

            case '0':
                menu_back();
                break;

            case 'Q':
                return;

        }
    }
}




