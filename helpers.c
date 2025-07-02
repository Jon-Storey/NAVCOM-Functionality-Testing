/*
 * helpers.c
 *
 *  Created on: 11 Jun 2025
 *      Author: JonathanStorey
 */


#include "sl_component_catalog.h"
#include "sl_system_init.h"
#include "sl_system_process_action.h"

#include <stdio.h>
#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_chip.h"
#include "em_timer.h"
#include "em_i2c.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "EFM32GG11B420F2048GQ100.h"
//#include "sw_delay.h"
#include "hw_timer.h"
#include "usart.h"
#include "buzzer.h"
#include "defines.h"
#include "i2c.h"
#include "helpers.h"



/**
 * @brief Sets node operating mode and configures all hardware subsystems accordingly
 * @param node_mode_state: Operating mode to configure (Flight, Seabed, Deck or Service)
 * @param NodeConfig: Pointer to global NodeConfiguration structure to update and apply
 * @return None
 *
 * @description This function is the master configuration routine that:
 *              1. Sets configuration flags based on the specified mode
 *              2. Sequentially applies power states to all subsystems
 *              3. Handles hardware-specific signal polarity through power state functions
 *
 * @note Configuration Logic:
 *       - A '1' in the structure indicates the device should be ON (not its signal level)
 *       - Some devices are active-low, others use inverted MOS interfaces
 *       - Actual GPIO signal polarity is handled by individual 'set_xxx_power_state' functions
 *
 * @note Current Modes:
 *       - Flight: All subsystems disabled (flags set to 0)
 *       - Default: Falls back to Flight mode configuration
 *
 * @subsystems_controlled:
 *       - Ethernet Switch    (Port E, Pin 10)
 *       - 5V Rail/FCPU       (Port A, Pin 15)
 *       - 3.3V Regulator     (Port B, Pin 2)
 *       - PL_V1 & PL_V2      (both use 3V power state)
 *       - RS232 Interface A  (Port A, Pin 4)
 *       - RS232 Interface B  (Port A, Pin 5)
 *       - Expander A         (Port D, Pin 2)
 *       - Expander B         (Port D, Pin 3)
 *       - Expander C         (Port D, Pin 4)
 *
 */
void Set_Node_Mode (char node_mode_state, NodeConfiguration *NodeConfig )
{
  switch (node_mode_state)                   //populates node structure with hardware config for the specific mode/state
  {
    case Flight:
      NodeConfig->NodeMode = Flight;
      NodeConfig->EthernetSwitchEnable = 0;
      NodeConfig->FCPU_Disable = 0;
      NodeConfig->Reg_3V3_Enable = 0;
      NodeConfig->PL_V1_Disable = 0;
      NodeConfig->PL_V2_Disable = 0;
      NodeConfig->RS232_A_Shutdown = 0;
      NodeConfig->RS232_B_Shutdown = 0;
      NodeConfig->Expander_A_Shutdown = 0;
      NodeConfig->Expander_B_Shutdown = 0;
      NodeConfig->Expander_C_Shutdown = 0;
    break;

    case Ethernet:
      NodeConfig->NodeMode = Ethernet;
      NodeConfig->EthernetSwitchEnable = 1;
      NodeConfig->FCPU_Disable = 1;
      NodeConfig->Reg_3V3_Enable = 1;
      NodeConfig->PL_V1_Disable = 0;
      NodeConfig->PL_V2_Disable = 0;
      NodeConfig->RS232_A_Shutdown = 0;
      NodeConfig->RS232_B_Shutdown = 0;
      NodeConfig->Expander_A_Shutdown = 0;
      NodeConfig->Expander_B_Shutdown = 0;
      NodeConfig->Expander_C_Shutdown = 0;
    break;

    case RS232:
      NodeConfig->NodeMode = RS232;
      NodeConfig->EthernetSwitchEnable = 0;
      NodeConfig->FCPU_Disable = 1;
      NodeConfig->Reg_3V3_Enable = 1;
      NodeConfig->PL_V1_Disable = 0;
      NodeConfig->PL_V2_Disable = 0;
      NodeConfig->RS232_A_Shutdown = 1;
      NodeConfig->RS232_B_Shutdown = 1;
      NodeConfig->Expander_A_Shutdown = 0;
      NodeConfig->Expander_B_Shutdown = 0;
      NodeConfig->Expander_C_Shutdown = 0;
    break;

    case Expanders:
      NodeConfig->NodeMode = Expanders;
      NodeConfig->EthernetSwitchEnable = 0;
      NodeConfig->FCPU_Disable = 1;
      NodeConfig->Reg_3V3_Enable = 1;
      NodeConfig->PL_V1_Disable = 0;
      NodeConfig->PL_V2_Disable = 0;
      NodeConfig->RS232_A_Shutdown = 0;
      NodeConfig->RS232_B_Shutdown = 0;
      NodeConfig->Expander_A_Shutdown = 1;
      NodeConfig->Expander_B_Shutdown = 1;
      NodeConfig->Expander_C_Shutdown = 1;
    break;

    default :
      NodeConfig->NodeMode = Flight;
      NodeConfig->EthernetSwitchEnable = 0;
      NodeConfig->FCPU_Disable = 0;
      NodeConfig->Reg_3V3_Enable = 0;
      NodeConfig->PL_V1_Disable = 0;
      NodeConfig->PL_V2_Disable = 0;
      NodeConfig->RS232_A_Shutdown = 0;
      NodeConfig->RS232_B_Shutdown = 0;
      NodeConfig->Expander_A_Shutdown = 0;
      NodeConfig->Expander_B_Shutdown = 0;
      NodeConfig->Expander_C_Shutdown = 0;
  }

  // With the Global structure updated, now configure the subsystems accordingly
  if( NodeConfig->EthernetSwitchEnable)
  {
      Set_Ethernet_Switch_Power_State(On, NodeConfig);
  }
  else
  {
      Set_Ethernet_Switch_Power_State(Off, NodeConfig);
  }

  if( NodeConfig->FCPU_Disable)
  {
      Set_5V_Power_State(On, NodeConfig);
  }
  else
  {
      Set_5V_Power_State(Off, NodeConfig);
  }

  if( NodeConfig->Reg_3V3_Enable)
  {
      Set_3V_Power_State(On, NodeConfig);
  }
  else
  {
      Set_3V_Power_State(Off, NodeConfig);
  }

  if( NodeConfig->PL_V1_Disable)
  {
      Set_3V_Power_State(On, NodeConfig);
  }
  else
  {
      Set_3V_Power_State(Off, NodeConfig);
  }


  if( NodeConfig->PL_V2_Disable)
  {
      Set_3V_Power_State(On, NodeConfig);
  }
  else
  {
      Set_3V_Power_State(Off, NodeConfig);
  }


  if( NodeConfig->RS232_A_Shutdown)
  {
      Set_RS232_A_Power_State(On, NodeConfig);
  }
  else
  {
      Set_RS232_A_Power_State(Off, NodeConfig);
  }

  if( NodeConfig->RS232_B_Shutdown)
  {
      Set_RS232_B_Power_State(On, NodeConfig);
  }
  else
  {
      Set_RS232_B_Power_State(Off, NodeConfig);
  }

  if( NodeConfig->Expander_A_Shutdown)
  {
      Set_Expander_A_Power_State(On, NodeConfig);
  }
  else
  {
      Set_Expander_A_Power_State(Off, NodeConfig);
  }

  if( NodeConfig->Expander_B_Shutdown)
  {
      Set_Expander_B_Power_State(On, NodeConfig);
  }
  else
  {
      Set_Expander_B_Power_State(Off, NodeConfig);
  }

  if( NodeConfig->Expander_C_Shutdown)
  {
      Set_Expander_C_Power_State(On, NodeConfig);
  }
  else
  {
      Set_Expander_C_Power_State(Off, NodeConfig);
  }
}





/**
 * @brief Controls power state of Expander A and updates configuration
 * @param power_state: On/Off command for the power state
 * @param NodeConfig: Pointer to NodeConfiguration structure to update
 * @return None
 * @note Sets/clears GPIO Port D Pin 2, prints status message, updates Expander_A_Shutdown flag
 */
void Set_Expander_A_Power_State(char power_state, NodeConfiguration *NodeConfig)
{
  switch (power_state)
   {
        case On:                                    //if DCDC need switching ON
          GPIO_PinOutSet(gpioPortD ,2);             //Enable the DCDC with GPIO
          print_string("Expander A Enabled\n\r", Node);    //Print message to Terminal
          NodeConfig->Expander_A_Shutdown = '1';            //Update the NodeConfig structure
        break;

        case Off:                                     //if DCDC need switching ON
          GPIO_PinOutClear(gpioPortD ,2);            //Enable the DCDC with GPIO
          print_string("Expander A Shutdown\n\r", Node);   //Print message to Terminal
          NodeConfig->Expander_A_Shutdown = '0';              //Update the NodeConfig structure
        break;

      default:
   }
}




/**
 * @brief Controls power state of Expander B and updates configuration
 * @param power_state: On/Off command for the power state
 * @param NodeConfig: Pointer to NodeConfiguration structure to update
 * @return None
 * @note Sets/clears GPIO Port D Pin 3, prints status message, updates Expander_B_Shutdown flag
 */
void Set_Expander_B_Power_State(char power_state, NodeConfiguration *NodeConfig)
{
  switch (power_state)
   {
        case On:                                    //if DCDC need switching ON
          GPIO_PinOutSet(gpioPortD ,3);             //Enable the DCDC with GPIO
          print_string("Expander B Enabled\n\r", Node);    //Print message to Terminal
          NodeConfig->Expander_B_Shutdown = '1';            //Update the NodeConfig structure
        break;

        case Off:                                     //if DCDC need switching ON
          GPIO_PinOutClear(gpioPortD ,3);            //Enable the DCDC with GPIO
          print_string("Expander B Shutdown\n\r", Node);   //Print message to Terminal
          NodeConfig->Expander_B_Shutdown = '0';              //Update the NodeConfig structure
        break;

      default:
   }
}




/**
 * @brief Controls power state of Expander C and updates configuration
 * @param power_state: On/Off command for the power state
 * @param NodeConfig: Pointer to NodeConfiguration structure to update
 * @return None
 * @note Sets/clears GPIO Port D Pin 4, prints status message, updates Expander_C_Shutdown flag
 */
void Set_Expander_C_Power_State(char power_state, NodeConfiguration *NodeConfig)
{
  switch (power_state)
   {
        case On:                                    //if DCDC need switching ON
          GPIO_PinOutSet(gpioPortD ,4);             //Enable the DCDC with GPIO
          print_string("Expander C Enabled\n\r", Node);    //Print message to Terminal
          NodeConfig->Expander_C_Shutdown = '1';            //Update the NodeConfig structure
        break;

        case Off:                                     //if DCDC need switching ON
          GPIO_PinOutClear(gpioPortD ,4);            //Enable the DCDC with GPIO
          print_string("Expander C Shutdown\n\r", Node);   //Print message to Terminal
          NodeConfig->Expander_C_Shutdown = '0';              //Update the NodeConfig structure
        break;

      default:
   }
}



/**
 * @brief Controls power state of Ethernet Switch and updates configuration
 * @param power_state: On/Off command for the power state
 * @param NodeConfig: Pointer to NodeConfiguration structure to update
 * @return None
 * @note Sets/clears GPIO Port E Pin 10, prints status message, updates EthernetSwitchEnable flag
 */
void Set_Ethernet_Switch_Power_State(char power_state, NodeConfiguration *NodeConfig)
{
  switch (power_state)
   {
        case On:                                    //if DCDC need switching ON
          GPIO_PinOutSet(gpioPortE ,10);              //Enable the DCDC with GPIO
          print_string("Enet Switch Enabled \n\r", Node);    //Print message to Terminal
          NodeConfig->EthernetSwitchEnable = '1';            //Update the NodeConfig structure
        break;

        case Off:                                     //if DCDC need switching ON
          GPIO_PinOutClear(gpioPortE ,10);            //Enable the DCDC with GPIO
          print_string("Enet switch Shutdown \n\r", Node);   //Print message to Terminal
          NodeConfig->EthernetSwitchEnable = '0';              //Update the NodeConfig structure
        break;

      default:
   }
}




/**
 * @brief Controls power state of RS232 Interface A and updates configuration
 * @param power_state: On/Off command for the power state
 * @param NodeConfig: Pointer to NodeConfiguration structure to update
 * @return None
 * @note Sets/clears GPIO Port A Pin 4, prints status message, updates RS232_A_Shutdown flag
 */
void Set_RS232_A_Power_State(char power_state, NodeConfiguration *NodeConfig)
{
  switch (power_state)
  {
       case On:                                    //if DCDC need switching ON
         GPIO_PinOutSet(gpioPortA,4);              //Enable the DCDC with GPIO
         print_string("RS232 A Enabled\n\r", Node);    //Print message to Terminal
         NodeConfig->RS232_A_Shutdown = '1';             //Update the NodeConfig structure
       break;

       case Off:                                     //if DCDC need switching ON
         GPIO_PinOutClear(gpioPortA,4);             //Enable the DCDC with GPIO
         print_string("RS232 Disabled\n\r", Node);   //Print message to Terminal
         NodeConfig->RS232_A_Shutdown = '0';               //Update the NodeConfig structure
       break;

     default:
  }
}




/**
 * @brief Controls power state of RS232 Interface B and updates configuration
 * @param power_state: On/Off command for the power state
 * @param NodeConfig: Pointer to NodeConfiguration structure to update
 * @return None
 * @note Sets/clears GPIO Port A Pin 5, prints status message, updates RS232_B_Shutdown flag
 */
void Set_RS232_B_Power_State(char power_state, NodeConfiguration *NodeConfig)
{
  switch (power_state)
   {
       case On:                                    //if DCDC need switching ON
         GPIO_PinOutSet(gpioPortA,5);              //Enable the DCDC with GPIO
         print_string("RS232 B Enabled\n\r", Node);     //Print message to Terminal
         NodeConfig->RS232_B_Shutdown = '1';             //Update the NodeConfig structure
       break;

       case Off:                                     //if DCDC need switching ON
         GPIO_PinOutClear(gpioPortA,5);          //Enable the DCDC with GPIO
         print_string("RS232 B Disabled\n\r", Node);   //Print message to Terminal
         NodeConfig->RS232_B_Shutdown = '0';             //Update the NodeConfig structure
       break;

     default:
   }
}





/**
 * @brief Controls 5V power rail (FCPU) state and updates configuration
 * @param power_state: On/Off command for the power state
 * @param NodeConfig: Pointer to NodeConfiguration structure to update
 * @return None
 * @note Sets/clears GPIO Port A Pin 15, prints status message, updates FCPU_Disable flag
 *       Includes default case for error handling
 */
void Set_5V_Power_State(char power_state, NodeConfiguration *NodeConfig)
{
  switch (power_state)
  {
      case On:                                    //if DCDC need switching ON
      GPIO_PinOutSet(gpioPortA ,15);              //Enable the DCDC with GPIO
      print_string("FCPU Enabled \n\r", Node);    //Print message to Terminal
      NodeConfig->FCPU_Disable='1'   ;             //Update the NodeConfig structure
      break;

    case Off:                                     //if DCDC need switching ON
      GPIO_PinOutClear(gpioPortA ,15);            //Enable the DCDC with GPIO
      print_string("FCPU Shutdown \n\r", Node);   //Print message to Terminal
      NodeConfig->FCPU_Disable='0' ;               //Update the NodeConfig structure
      break;

    default:                                        //unknown command - do not enable ??
      GPIO_PinOutClear(gpioPortA ,15);              //Enable the DCDC with GPIO
      print_string("FCPU Shutdown - but something went wrong\n\r", Node);     //Print message to Terminal
      NodeConfig->FCPU_Disable='0' ;                 //Update the NodeConfig structure
  }
}





/**
 * @brief Controls 3.3V power regulator state and updates configuration
 * @param power_state: On/Off command for the power state
 * @param NodeConfig: Pointer to NodeConfiguration structure to update
 * @return None
 * @note Sets/clears GPIO Port B Pin 2, prints status message, updates Reg_3V3_Enable flag
 */
void Set_3V_Power_State(char power_state, NodeConfiguration *NodeConfig)
{
  switch (power_state)
  {
      case On:                                    //if DCDC need switching ON
        GPIO_PinOutSet(gpioPortB,2);              //Enable the DCDC with GPIO
        print_string("3.3V Reg Enabled\n\r", Node);    //Print message to Terminal
        NodeConfig->Reg_3V3_Enable = '1';             //Update the NodeConfig structure
      break;

      case Off:                                     //if DCDC need switching ON
        GPIO_PinOutClear(gpioPortB,2);
        print_string("3.3V Reg Shutdown\n\r", Node);   //Print message to Terminal
        NodeConfig->Reg_3V3_Enable = '0';               //Update the NodeConfig structure
      break;

    default:                                        //unknown command - do not enable ??

  }
}








void Set_Ethernet_Reset_State(char reset_state, NodeConfiguration *NodeConfig)
{
  switch (reset_state)
   {
        case On:
          GPIO_PinOutSet(gpioPortF ,12);
          print_string("Ethernet Reset active \n\r", Node);
          NodeConfig->EthernetSwitchReset = '1';
        break;

        case Off:
          GPIO_PinOutClear(gpioPortF ,12);
          print_string("Ethernet reset  deactiveated \n\r", Node);
          NodeConfig->EthernetSwitchReset = '0';
        break;

      default:
   }
}


void Set_SDAS_Reset_State(char reset_state, NodeConfiguration *NodeConfig)
{
  switch (reset_state)
   {
        case On:
          GPIO_PinOutSet(gpioPortC ,1);
          print_string("SDAS Reset active \n\r", Node);
          NodeConfig->SDAS_Reset = '1';
        break;

        case Off:
          GPIO_PinOutClear(gpioPortC ,1);
          print_string("SDAS deactiveated \n\r", Node);
          NodeConfig->SDAS_Reset = '0';
        break;

      default:
   }
}



void Set_PDEM_Reset_State(char reset_state, NodeConfiguration *NodeConfig)
{
  switch (reset_state)
   {
        case On:
          GPIO_PinOutSet(gpioPortA ,11);
          print_string("PDEM Reset active \n\r", Node);
          NodeConfig->PDEM_Reset = '1';
        break;

        case Off:
          GPIO_PinOutClear(gpioPortA ,11);
          print_string("PDEM deactiveated \n\r", Node);
          NodeConfig->PDEM_Reset = '0';
        break;

      default:
   }
}


void Set_FCPU_Reset_State(char reset_state, NodeConfiguration *NodeConfig)
{
  switch (reset_state)
   {
        case On:
          GPIO_PinOutSet(gpioPortC ,7);
          print_string("PDEM Reset active \n\r", Node);
          NodeConfig->FCPU_Reset = '1';
        break;

        case Off:
          GPIO_PinOutClear(gpioPortC ,7);
          print_string("FCPU reset deactiveated \n\r", Node);
          NodeConfig->FCPU_Reset = '0';
        break;

      default:
   }
}

void Set_IMU_Reset_State(char reset_state, NodeConfiguration *NodeConfig)
{
  switch (reset_state)
   {
        case On:
          GPIO_PinOutSet(gpioPortC ,9);
          print_string("IMU Reset active \n\r", Node);
          NodeConfig->IMU_Reset = '1';
        break;

        case Off:
          GPIO_PinOutClear(gpioPortC ,9);
          print_string("IMU reset deactiveated \n\r", Node);
          NodeConfig->IMU_Reset = '0';
        break;

      default:
   }
}


void Set_Antenna_Reset_State(char reset_state, NodeConfiguration *NodeConfig)
{
  switch (reset_state)
   {
        case On:
          GPIO_PinOutSet(gpioPortB ,6);
          print_string("Antenna Reset active \n\r", Node);
          NodeConfig->Antenna_Reset = '1';
        break;

        case Off:
          GPIO_PinOutClear(gpioPortB ,6);
          print_string("Antenna reset deactiveated \n\r", Node);
          NodeConfig->Antenna_Reset = '0';
        break;

      default:
   }
}







/**
 * @brief Prints current status of all node power states to terminal
 * @param NodeConfig: Pointer to NodeConfiguration structure to read from
 * @return None
 * @note Displays formatted status of 5V, 3V, RS232 A/B, Ethernet, and Expanders A/B/C
 *       Output shows current flag values ('0' or '1') for each subsystem
 */
void print_node_modestate(NodeConfiguration *NodeConfig)
{
    print_string("\r\n5 Volt is : \t\t", Node);
    put_char(NodeConfig->FCPU_Disable, Node);
    print_string("\r\n3 Volt is : \t\t", Node);
    put_char(NodeConfig->Reg_3V3_Enable, Node);

    print_string("\r\nRS232 A is : \t\t", Node);
    put_char(NodeConfig->RS232_A_Shutdown, Node);
    print_string("\r\nRS232 B is : \t\t", Node);
    put_char(NodeConfig->RS232_B_Shutdown, Node);

    print_string("\r\nEthernet is : \t\t", Node);
    put_char(NodeConfig->EthernetSwitchEnable, Node);

    print_string("\r\nExpanders A is : \t", Node);
    put_char(NodeConfig->Expander_A_Shutdown, Node);

    print_string("\r\nExpanders B is : \t", Node);
    put_char(NodeConfig->Expander_B_Shutdown, Node);

    print_string("\r\nExpanders C is : \t", Node);
    put_char(NodeConfig->Expander_C_Shutdown, Node);
}



/**
 * @brief Clears the terminal screen using ANSI escape sequence
 * @param None
 * @return None
 * @note Sends ANSI escape sequence "\x1b[2J" to clear entire screen
 */


void clear_screen(void)
{
  print_string("\x1b[2J", Node);                                             //clear screen
}



/**
 * @brief Converts 8-bit binary value to 2-character ASCII hex string
 * @param value: 8-bit value to convert (0-255)
 * @param asciiStr: Pointer to char array (minimum 3 bytes) to store result
 * @return None
 * @note Output format: "AB" for value 0xAB, null-terminated
 *       Example: value=255 outputs "FF\0"
 */
void binaryToAsciiHex(uint8_t value, char *asciiStr)
{
    const char hexDigits[] = "0123456789ABCDEF";
    asciiStr[0] = hexDigits[(value >> 4) & 0x0F];     // High nibble
    asciiStr[1] = hexDigits[value & 0x0F];            // Low nibble
    asciiStr[2] = '\0';                               // Null terminator
}

/**
 * @brief Converts 8-bit binary value to ASCII decimal string
 * @param value: 8-bit value to convert (0-255)
 * @param asciiStr: Pointer to char array (minimum 4 bytes) to store result
 * @return None
 * @note Output format: decimal string representation, null-terminated
 *       Example: value=123 outputs "123\0", value=0 outputs "0\0"
 *       Handles values 0-255 with up to 3 digits plus null terminator
 */
void binaryToAsciiString(uint8_t value, char *asciiStr)
{
    char buffer[4]; // Max 3 digits for uint8_t + null terminator
    int i = 0;

    if (value == 0)
    {
        asciiStr[0] = '0';
        asciiStr[1] = '\0';
        return;
    }

     while (value > 0 && i < 3)               // Extract digits from the end
     {
         buffer[i++] = (value % 10) + '0';
         value /= 10;
     }

     // Reverse the string into output
     for (int j = 0; j < i; j++)
     {
         asciiStr[j] = buffer[i - j - 1];
     }
     asciiStr[i] = '\0';
}


void USART_Test_Cycle(void)
{
  GPIO_PinOutSet(gpioPortC,8);      //set IMU rs485 driver into tx, confirmed working
  GPIO_PinOutSet(gpioPortE,4);      //set THRUSTER rs485 driver into tx, confirmed working
    while(1)
    {
          print_string("hello from Node \n\r", Node);           // check works
          print_string("hello from IMU \n\r" , IMU);            // check works - confirmed over RS485, no fix required
          print_string("hello from PDEM \n\r", PDEM);           // check works - RS232 tested, need routing to connector though!
          print_string("hello from SDAS \n\r", SDAS);           // check works - confirmed over RS232, no fix required
          print_string("hello from Thruster \n\r", Thrusters ); // check works
          print_string("hello from FCPU \n\r", FCPU);           // check works !no routing
          print_string("hello from USBL \n\r", USBL);           // check works ! no routing

    }
}


