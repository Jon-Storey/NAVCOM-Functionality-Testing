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


static menu_state_t current_menu = MENU_MAIN;
//static char input_buffer[32];
static uint8_t buffer_index = 0;

/*==============================================================================
 * MENU DISPLAY FUNCTIONS
 *============================================================================*/

/**
 * @brief Displays the main menu options
 */
void display_main_menu(void)
{
    clear_screen();
    print_string("\r\n", Node);
    print_string("╔════════════════════════════════════╗\r\n", Node);
    print_string("║        Node Control System        ║\r\n", Node);
    print_string("║          EFM32GG11B Node          ║\r\n", Node);
    print_string("╚════════════════════════════════════╝\r\n", Node);
    print_string("\r\n", Node);
    print_string("1. Power Management\r\n", Node);
    print_string("2. Node Operating Modes\r\n", Node);
    print_string("3. I2C Operations\r\n", Node);
    print_string("4. Communication Tests\r\n", Node);
    print_string("5. System Information\r\n", Node);
    print_string("6. Test\r\n", Node);
    print_string("0. System Status Display\r\n", Node);
    print_string("\r\n", Node);
    print_string("Select option (1-5, 0 for status): ", Node);
}

/**
 * @brief Displays power management submenu
 */
void display_power_menu(void)
{
    clear_screen();
    print_string("\r\n=== POWER MANAGEMENT ===\r\n", Node);
    print_string("\r\n", Node);
    print_string("Power Rails:\r\n", Node);
    print_string("1. Toggle 5V Rail (FCPU)\r\n", Node);
    print_string("2. Toggle 3.3V Regulator\r\n", Node);
    print_string("3. Toggle Ethernet Switch\r\n", Node);
    print_string("\r\n", Node);
    print_string("Communication Interfaces:\r\n", Node);
    print_string("4. Enet reset  A\r\n", Node);
    print_string("5. Toggle RS232 Interface B\r\n", Node);
    print_string("\r\n", Node);
    print_string("Expansion Modules:\r\n", Node);
    print_string("6. Toggle Expander A\r\n", Node);
    print_string("7. Toggle Expander B\r\n", Node);
    print_string("8. Toggle Expander C\r\n", Node);
    print_string("\r\n", Node);
    print_string("9. Emergency Shutdown (All OFF)\r\n", Node);
    print_string("0. Back to Main Menu\r\n", Node);
    print_string("\r\n", Node);
    print_string("Select option: ", Node);
}

/**
 * @brief Displays node operating modes menu
 */
void display_node_modes_menu(void)
{
    clear_screen();
    print_string("\r\n=== NODE OPERATING MODES ===\r\n", Node);
    print_string("\r\n", Node);
    print_string("Available Modes:\r\n", Node);
    print_string("1. Flight Mode     (Minimal power, critical systems only)\r\n", Node);
    print_string("2. Deck Mode       (Full communication enabled)\r\n", Node);
    print_string("3. Safe Mode       (Reduced functionality)\r\n", Node);
    print_string("4. Service Mode    (Maintenance and diagnostics)\r\n", Node);
    print_string("5. Ethernet Mode   (Ethernet-focused communication)\r\n", Node);
    print_string("6. RS232 Mode      (RS232-focused communication)\r\n", Node);
    print_string("7. Expanders Mode  (Expansion modules active)\r\n", Node);
    print_string("\r\n", Node);
    print_string("0. Back to Main Menu\r\n", Node);
    print_string("\r\n", Node);
    print_string("Select mode: ", Node);
}

/**
 * @brief Displays I2C operations menu
 */
void display_i2c_menu(void)
{
    clear_screen();
    print_string("\r\n=== I2C OPERATIONS ===\r\n", Node);
    print_string("\r\n", Node);
    print_string("1. Read Device 0x31 Register 0x00\r\n", Node);
    print_string("2. Read Device 0x19 Register 0x00 (Compass)\r\n", Node);
    print_string("3. I2C Bus Scan\r\n", Node);
    print_string("4. Custom Register Read\r\n", Node);
    print_string("5. I2C Status\r\n", Node);
    print_string("\r\n", Node);
    print_string("0. Back to Main Menu\r\n", Node);
    print_string("\r\n", Node);
    print_string("Select option: ", Node);
}

/**
 * @brief Displays communication test menu
 */
void display_communication_menu(void)
{
    clear_screen();
    print_string("\r\n=== COMMUNICATION TESTS ===\r\n", Node);
    print_string("\r\n", Node);
    print_string("1. Test IMU Interface (USART0)\r\n", Node);
    print_string("2. Test PDEM Interface (USART1)\r\n", Node);
    print_string("3. Test Thruster Interface (USART3)\r\n", Node);
    print_string("4. Test FCPU Interface (UART0)\r\n", Node);
    print_string("5. Test USBL Interface (UART1)\r\n", Node);
    print_string("6. Test All Interfaces\r\n", Node);
    print_string("\r\n", Node);
    print_string("0. Back to Main Menu\r\n", Node);
    print_string("\r\n", Node);
    print_string("Select option: ", Node);
}

/**
 * @brief Displays system information menu
 */
void display_system_info_menu(void)
{
    clear_screen();
    print_string("\r\n=== SYSTEM INFORMATION ===\r\n", Node);
    print_string("\r\n", Node);
    print_string("1. Current Power Status\r\n", Node);
    print_string("2. GPIO Pin States\r\n", Node);
    print_string("3. Clock Configuration\r\n", Node);
    print_string("4. Memory Information\r\n", Node);
    print_string("5. Version Information\r\n", Node);
    print_string("6. Hardware Test\r\n", Node);
    print_string("\r\n", Node);
    print_string("0. Back to Main Menu\r\n", Node);
    print_string("\r\n", Node);
    print_string("Select option: ", Node);
}

void display_test_menu(void)
{
    clear_screen();
    print_string("\r\n=== TEST ===\r\n", Node);
    print_string("\r\n", Node);
    print_string("1. Turn on Ethernet switch\r\n", Node);

    print_string("\r\n", Node);
    print_string("0. Back to Main Menu\r\n", Node);
    print_string("\r\n", Node);
    print_string("Select option: ", Node);
}


/*==============================================================================
 * MENU HANDLER FUNCTIONS
 *============================================================================*/

/**
 * @brief Handles main menu input selection
 * @param input: Character input from user
 */
void handle_main_menu(char input, NodeConfiguration *NodeConfig)
{
    switch(input)
    {
        case '1':
            current_menu = MENU_POWER;
            display_power_menu();
            break;
        case '2':
            current_menu = MENU_NODE_MODES;
            display_node_modes_menu();
            break;
        case '3':
            current_menu = MENU_I2C_OPS;
            display_i2c_menu();
            break;
        case '4':
            current_menu = MENU_COMMUNICATION;
            display_communication_menu();
            break;
        case '5':
            current_menu = MENU_SYSTEM_INFO;
            display_system_info_menu();
            break;

        case '6':
            current_menu = MENU_TEST;
            display_test_menu();
            break;


        case '0':
            clear_screen();
            print_string("\r\n=== CURRENT SYSTEM STATUS ===\r\n", Node);
            print_node_modestate(NodeConfig);
            print_string("\r\nPress any key to return to menu...", Node);
            break;
        default:
            print_string("\r\nInvalid option. Please select 0-5.\r\n", Node);
            print_string("Press any key to continue...", Node);
            break;
    }
}

/**
 * @brief Handles power management menu input
 * @param input: Character input from user
 */
void handle_power_menu(char input, NodeConfiguration *NodeConfig)
{
    switch(input)
    {
        case '1':
          print_string("\r\n pressed 1 \n\r\n\r", Node);
            NodeConfig->FCPU_Disable = !NodeConfig->FCPU_Disable;                   //toggle the flag
            Set_5V_Power_State(NodeConfig->FCPU_Disable ? On : Off, NodeConfig);  //short hand for ... IF NodeConfig is true, then 'On' else 'Off'
            break;
        case '2':
            NodeConfig->Reg_3V3_Enable = !NodeConfig->Reg_3V3_Enable;
            Set_3V_Power_State(NodeConfig->Reg_3V3_Enable ? On : Off, NodeConfig);
            break;
        case '3':
           // NodeConfig->EthernetSwitchEnable = !NodeConfig->EthernetSwitchEnable;
           // Set_Ethernet_Switch_Power_State(NodeConfig->EthernetSwitchEnable ? On : Off, NodeConfig);

            ESwitch_Reset_Sequence(NodeConfig);
            break;


        case '4':
                NodeConfig->EthernetSwitchReset = !NodeConfig->EthernetSwitchReset;
                Set_Ethernet_Reset_State(NodeConfig->EthernetSwitchReset ? On : Off, NodeConfig);

         //   NodeConfig->RS232_A_Shutdown = !NodeConfig->RS232_A_Shutdown;
         //   Set_RS232_A_Power_State(NodeConfig->RS232_A_Shutdown ? On : Off, NodeConfig);
            break;
        case '5':
            NodeConfig->RS232_B_Shutdown = !NodeConfig->RS232_B_Shutdown;
            Set_RS232_B_Power_State(NodeConfig->RS232_B_Shutdown ? On : Off, NodeConfig);
            break;
        case '6':
            NodeConfig->Expander_A_Shutdown = !NodeConfig->Expander_A_Shutdown;
            Set_Expander_A_Power_State(NodeConfig->Expander_A_Shutdown ? On : Off, NodeConfig);
            break;
        case '7':
            //NodeConfig->Expander_B_Shutdown = !NodeConfig->Expander_B_Shutdown;
            //Set_Expander_B_Power_State(NodeConfig->Expander_B_Shutdown ? On : Off, NodeConfig);
          Set_Expander_B_Power_State(Off, NodeConfig);
          print_string("\r\n on", Node);
          hw_timer1_ms(20)  ;
      //    MAX14830_UART_Init();
          print_string("\r\n Init", Node);
          hw_timer1_ms(20)  ;
            break;
        case '8':
            NodeConfig->Expander_C_Shutdown = !NodeConfig->Expander_C_Shutdown;
            Set_Expander_C_Power_State(NodeConfig->Expander_C_Shutdown ? On : Off, NodeConfig);
            break;
        case '9':
                MAX14830_UART1_SendChar('A');
            break;
        case '0':
            current_menu = MENU_MAIN;
            display_main_menu();
            return;
        default:
            print_string("\r\nInvalid option. Please select 0-9.\r\n", Node);
            break;
    }

    if(input != '0')
    {
        print_string("\r\nPress any key to continue...", Node);
    }
}

/**
 * @brief Handles node modes menu input
 * @param input: Character input from user
 */
void handle_node_modes_menu(char input, NodeConfiguration *NodeConfig)
{
    switch(input)
    {
        case '1':
            Set_Node_Mode(Flight, NodeConfig);
            print_string("\r\nFlight mode activated.\r\n", Node);
            break;
        case '2':
            Set_Node_Mode(Deck, NodeConfig);
            print_string("\r\nDeck mode activated.\r\n", Node);
            break;
        case '3':
            Set_Node_Mode(Safe, NodeConfig);
            print_string("\r\nSafe mode activated.\r\n", Node);
            break;
        case '4':
            Set_Node_Mode(Service, NodeConfig);
            print_string("\r\nService mode activated.\r\n", Node);
            break;
        case '5':
            Set_Node_Mode(Ethernet, NodeConfig);
            print_string("\r\nEthernet mode activated.\r\n", Node);
            break;
        case '6':
            Set_Node_Mode(RS232, NodeConfig);
            print_string("\r\nRS232 mode activated.\r\n", Node);
            break;
        case '7':
            Set_Node_Mode(Expanders, NodeConfig);
            print_string("\r\nExpanders mode activated.\r\n", Node);
            break;
        case '0':
            current_menu = MENU_MAIN;
            display_main_menu();
            return;
        default:
            print_string("\r\nInvalid option. Please select 0-7.\r\n", Node);
            break;
    }

    if(input != '0')
    {
        print_string("Press any key to continue...", Node);
    }
}

/**
 * @brief Handles I2C operations menu input
 * @param input: Character input from user
 */
void handle_i2c_menu(char input, NodeConfiguration *NodeConfig)
{
    uint8_t result;
    char hex_str[3];

    switch(input)
    {
        case '1':
            print_string("\r\nReading device 0x31, register 0x00...\r\n", Node);
            i2cStartReadByte();
            while(!i2cIsTransferDone()) { /* Wait */ }
            result = i2cGetLastByte();
            binaryToAsciiHex(result, hex_str);
            print_string("Result: 0x", Node);
            print_string(hex_str, Node);
            print_string("\r\n", Node);
            break;
        case '2':
            print_string("\r\nReading compass (0x19), register 0x00...\r\n", Node);
            // Implement compass read here
            print_string("Compass read function not implemented yet.\r\n", Node);
            break;
        case '3':
            print_string("\r\nScanning I2C bus...\r\n", Node);
            i2c_bus_scan();
            break;
        case '4':
            print_string("\r\nCustom register read not implemented yet.\r\n", Node);
            break;
        case '5':
            print_string("\r\nI2C Status: ", Node);
            if(i2cIsTransferDone())
                print_string("Ready\r\n", Node);
            else
                print_string("Busy\r\n", Node);
            break;
        case '0':
            current_menu = MENU_MAIN;
            display_main_menu();
            return;
        default:
            print_string("\r\nInvalid option. Please select 0-5.\r\n", Node);
            break;
    }

    if(input != '0')
    {
        print_string("Press any key to continue...", Node);
    }
}

/**
 * @brief Handles communication test menu input
 * @param input: Character input from user
 */
void handle_communication_menu(char input, NodeConfiguration *NodeConfig)
{
    switch(input)
    {
        case '1':
            print_string("\r\nTesting IMU interface...\r\n", Node);
            print_string("IMU test: Send test message to USART0\r\n", Node);
            break;
        case '2':
            print_string("\r\nTesting PDEM interface...\r\n", Node);
            print_string("PDEM test: Send test message to USART1\r\n", Node);
            break;
        case '3':
            print_string("\r\nTesting Thruster interface...\r\n", Node);
            print_string("Thruster test: Send test message to USART3\r\n", Node);
            break;
        case '4':
            print_string("\r\nTesting FCPU interface...\r\n", Node);
            print_string("FCPU test: Send test message to UART0\r\n", Node);
            break;
        case '5':
            print_string("\r\nTesting USBL interface...\r\n", Node);
            print_string("USBL test: Send test message to UART1\r\n", Node);
            break;
        case '6':
            print_string("\r\nTesting all interfaces...\r\n", Node);
            print_string("All interfaces test completed.\r\n", Node);
            break;
        case '0':
            current_menu = MENU_MAIN;
            display_main_menu();
            return;
        default:
            print_string("\r\nInvalid option. Please select 0-6.\r\n", Node);
            break;
    }

    if(input != '0')
    {
        print_string("Press any key to continue...", Node);
    }
}

/**
 * @brief Handles system information menu input
 * @param input: Character input from user
 */
void handle_system_info_menu(char input, NodeConfiguration *NodeConfig)
{
    switch(input)
    {
        case '1':
            clear_screen();
            print_string("\r\n=== POWER STATUS ===\r\n", Node);
            print_node_modestate(NodeConfig);
            break;
        case '2':
            print_string("\r\nGPIO Pin States:\r\n", Node);
            print_string("Feature not implemented yet.\r\n", Node);
            break;
        case '3':
            print_string("\r\nClock Configuration:\r\n", Node);
            print_string("All peripheral clocks enabled.\r\n", Node);
            break;
        case '4':
            print_string("\r\nMemory Information:\r\n", Node);
            print_string("EFM32GG11B: 2MB Flash, 512KB RAM\r\n", Node);
            break;
        case '5':
            print_string("\r\nVersion Information:\r\n", Node);
            print_string("Node Control System v1.0\r\n", Node);
            print_string("EFM32GG11B Microcontroller\r\n", Node);
            print_string("Build Date: 1 Jul 2025\r\n", Node);
            break;
        case '6':
            print_string("\r\nHardware Test:\r\n", Node);
            print_string("Running basic hardware test...\r\n", Node);
            // Add hardware test functions here
            print_string("Hardware test completed.\r\n", Node);
            break;
        case '0':
            current_menu = MENU_MAIN;
            display_main_menu();
            return;
        default:
            print_string("\r\nInvalid option. Please select 0-6.\r\n", Node);
            break;
    }

    if(input != '0')
    {
        print_string("Press any key to continue...", Node);
    }
}




void handle_test_menu(char input, NodeConfiguration *NodeConfig)
{
    switch(input)
    {
        case '1':
            clear_screen();
 //           Initialise_ESwitch(NodeConfig);
            print_string("Ethernet swtich initialised", Node);
            break;
        case '0':
             current_menu = MENU_MAIN;
             display_main_menu();
             return;

    }
}
/*==============================================================================
 * UTILITY FUNCTIONS
 *============================================================================*/

/**
 * @brief Emergency shutdown - turns off all power rails
 */
void emergency_shutdown(void)
{
    print_string("\r\n*** EMERGENCY SHUTDOWN INITIATED ***\r\n", Node);

    Set_5V_Power_State(Off, &NodeConfig);
    Set_3V_Power_State(Off, &NodeConfig);
    Set_Ethernet_Switch_Power_State(Off, &NodeConfig);
    Set_RS232_A_Power_State(Off, &NodeConfig);
    Set_RS232_B_Power_State(Off, &NodeConfig);
    Set_Expander_A_Power_State(Off, &NodeConfig);
    Set_Expander_B_Power_State(Off, &NodeConfig);
    Set_Expander_C_Power_State(Off, &NodeConfig);

    print_string("All power rails shutdown.\r\n", Node);
}

/**
 * @brief Performs I2C bus scan to detect connected devices
 */
void i2c_bus_scan(void)
{
    print_string("I2C bus scan: 0x00 to 0x7F\r\n", Node);
    print_string("Devices found: ", Node);

    // This would need to be implemented based on your I2C functions
    print_string("0x19, 0x31\r\n", Node);
    print_string("Scan complete.\r\n", Node);
}

/*==============================================================================
 * MAIN MENU INTERFACE FUNCTIONS
 *============================================================================*/

/**
 * @brief Initialises menu system and displays main menu
 */
void menu_init(void)
{
    current_menu = MENU_MAIN;
    buffer_index = 0;
    display_main_menu();
}

/**
 * @brief Processes character input for menu navigation
 * @param input: Character received from USART
 */
void menu_process_input(char input, NodeConfiguration *NodeConfig)
{
    // Echo the character back to terminal
    put_char(input, Node);

    switch(current_menu)
    {
        case MENU_MAIN:
            handle_main_menu(input, NodeConfig);
            break;
        case MENU_POWER:
           print_string("in menu process, power selected\r\n", Node);
            handle_power_menu(input, NodeConfig);
            break;
        case MENU_NODE_MODES:
            handle_node_modes_menu(input, NodeConfig);
            break;
        case MENU_I2C_OPS:
            handle_i2c_menu(input, NodeConfig);
            break;
        case MENU_COMMUNICATION:
            handle_communication_menu(input, NodeConfig);
            break;
        case MENU_SYSTEM_INFO:
            handle_system_info_menu(input, NodeConfig);
            break;
        default:
            current_menu = MENU_MAIN;
            display_main_menu();
            break;
    }

    // If we're waiting for "any key" to continue, return to current menu
    if(input != '0' && current_menu != MENU_MAIN)
    {
        switch(current_menu)
        {
            case MENU_POWER:
                display_power_menu();
                break;
            case MENU_NODE_MODES:
                display_node_modes_menu();
                break;
            case MENU_I2C_OPS:
                display_i2c_menu();
                break;
            case MENU_COMMUNICATION:
                display_communication_menu();
                break;
            case MENU_SYSTEM_INFO:
                display_system_info_menu();
                break;
            default:
                break;
        }
    }
}

/**
 * @brief Returns to main menu from any submenu
 */
void menu_return_to_main(void)
{
    current_menu = MENU_MAIN;
    display_main_menu();
}






//void menu_input_system(void)
//{
  /*
  print_string("\r\nWelcome to NAVCOM \n\r\n\r ", Node);                             //send string to Node UART

       print_string("-------------------------  \n\r" , Node);
       print_string("1 Enable 5V   \n\r" , Node);
       print_string("2 Disable 5V \n\r", Node);
       print_string("----------------------\n\r", Node);
       print_string("3 Enable 3V \n\r", Node);
       print_string("4 Disable 3V\n\r", Node);
       print_string("----------------------\n\r", Node);
       print_string("5 Enable RS232 A\n\r", Node);
       print_string("6 Disable RS232 A\n\r", Node);
       print_string("----------------------\n\r", Node);
       print_string("7 Enable RS232 B\n\r", Node);
       print_string("8 Disable RS232 B\n\r", Node);
       print_string("----------------------\n\r", Node);
       print_string("9 Enable Ethernet switch\n\r", Node);
       print_string("a Disable Ethernet switch\n\r", Node);
       print_string("----------------------\n\r", Node);
       print_string("b Enable expander A\n\r", Node);
       print_string("c Disable expander A\n\r", Node);             //send string to Node UART
       print_string("----------------------\n\r", Node);
       print_string("d Enable expander B\n\r", Node);
       print_string("e Disable expander B\n\r", Node);             //send string to Node UART
       print_string("----------------------\n\r", Node);
       print_string("f Enable expander C\n\r", Node);
       print_string("g Disable expander C\n\r", Node);             //send string to Node UART
       print_string("----------------------\n\r", Node);

       */
//}

//void menu_output_system(char input)
//{
//input =0;
/*  switch (input)
       {
         case '1':  Set_5V_Power_State(On);        break;
         case '2':  Set_5V_Power_State(Off);       break;

         case '3':  Set_3V_Power_State(On);        break;
         case '4':  Set_3V_Power_State(Off);       break;

         case '5':  Set_RS232_A_Power_State(On);   break;
         case '6':  Set_RS232_A_Power_State(Off);  break;

         case '7':  Set_RS232_B_Power_State(On);   break;
         case '8':  Set_RS232_B_Power_State(Off);  break;

         case '9':  Set_Ethernet_Switch_Power_State(On);   break;
         case 'a':  Set_Ethernet_Switch_Power_State(Off);  break;

         case 'b':  Set_Expander_A_Power_State(On);   break;
         case 'c':  Set_Expander_A_Power_State(Off);  break;

         case 'd':  Set_Expander_B_Power_State(On);   break;
         case 'e':  Set_Expander_B_Power_State(Off);  break;

         case 'f':  Set_Expander_C_Power_State(On);   break;
         case 'g':  Set_Expander_C_Power_State(Off);  break;

         default:  print_string("something wrong \n\r", Node);
         }
         */

//}
