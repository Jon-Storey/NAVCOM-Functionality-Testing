/***************************************************************************//**
 * @file main.c
 * @brief main() function.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
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
#include "sw_delay.h"
#include "hw_timer.h"
#include "usart.h"
#include "buzzer.h"
#include "defines.h"
#include "i2c.h"
#include "helpers.h"


void Initilise_Node (void);
void USART_Test_Cycle(void);
void Set_5V_Power_State(char);
void Set_3V_Power_State(char);
void print_node_modestate(void);
void clear_screen(void);
void Set_RS232_A_Power_State(char);
void Set_RS232_B_Power_State(char);
void Set_Ethernet_Switch_Power_State(char);
void Set_Expander_A_Power_State(char);
void Set_Expander_B_Power_State(char);
void Set_Expander_C_Power_State(char);
void Set_Node_Mode (char);

#define BUFFER_SIZE 80
char buffer[BUFFER_SIZE];

NodeConfiguration NodeConfig = {'0','0','0','0','0','0','0','0', '0', '0','0'};    //create a structure of type NodeConfiguration called NodeConfig and init with zeros





void Set_Node_Mode (char node_mode_state)  //populates node config structure with hardware config for the specific mode/state
{
  switch (node_mode_state)
  {
    case Flight:
      NodeConfig.NodeMode = Flight;
      NodeConfig.EthernetSwitchEnable = 0;
      NodeConfig.FCPU_Disable = 0;
      NodeConfig.Reg_3V3_Enable = 0;
      NodeConfig.PL_V1_Disable = 0;
      NodeConfig.PL_V2_Disable = 0;
      NodeConfig.RS232_A_Shutdown = 0;
      NodeConfig.RS232_B_Shutdown = 0;
      NodeConfig.Expander_A_Shutdown = 0;
      NodeConfig.Expander_B_Shutdown = 0;
      NodeConfig.Expander_C_Shutdown = 0;
    break;


    case Deck:
      NodeConfig.NodeMode = Deck;
      NodeConfig.EthernetSwitchEnable = 0;
      NodeConfig.FCPU_Disable = 0;
      NodeConfig.Reg_3V3_Enable = 0;
      NodeConfig.PL_V1_Disable = 0;
      NodeConfig.PL_V2_Disable = 0;
      NodeConfig.RS232_A_Shutdown = 0;
      NodeConfig.RS232_B_Shutdown = 0;
      NodeConfig.Expander_A_Shutdown = 0;
      NodeConfig.Expander_B_Shutdown = 0;
      NodeConfig.Expander_C_Shutdown = 0;
    break;


    case Safe:
      NodeConfig.NodeMode = Safe;
      NodeConfig.EthernetSwitchEnable = 0;
      NodeConfig.FCPU_Disable = 0;
      NodeConfig.Reg_3V3_Enable = 0;
      NodeConfig.PL_V1_Disable = 0;
      NodeConfig.PL_V2_Disable = 0;
      NodeConfig.RS232_A_Shutdown = 0;
      NodeConfig.RS232_B_Shutdown = 0;
      NodeConfig.Expander_A_Shutdown = 0;
      NodeConfig.Expander_B_Shutdown = 0;
      NodeConfig.Expander_C_Shutdown = 0;
    break;


    case Service:
      NodeConfig.NodeMode = Service;
      NodeConfig.EthernetSwitchEnable = 0;
      NodeConfig.FCPU_Disable = 0;
      NodeConfig.Reg_3V3_Enable = 0;
      NodeConfig.PL_V1_Disable = 0;
      NodeConfig.PL_V2_Disable = 0;
      NodeConfig.RS232_A_Shutdown = 0;
      NodeConfig.RS232_B_Shutdown = 0;
      NodeConfig.Expander_A_Shutdown = 0;
      NodeConfig.Expander_B_Shutdown = 0;
      NodeConfig.Expander_C_Shutdown = 0;
    break;

    default :
      NodeConfig.NodeMode = Flight;
      NodeConfig.EthernetSwitchEnable = 0;
      NodeConfig.FCPU_Disable = 0;
      NodeConfig.Reg_3V3_Enable = 0;
      NodeConfig.PL_V1_Disable = 0;
      NodeConfig.PL_V2_Disable = 0;
      NodeConfig.RS232_A_Shutdown = 0;
      NodeConfig.RS232_B_Shutdown = 0;
      NodeConfig.Expander_A_Shutdown = 0;
      NodeConfig.Expander_B_Shutdown = 0;
      NodeConfig.Expander_C_Shutdown = 0;

  }


  // sequentually go through the modes and enable/disable the desired elements
  // A 1 in the structure indicates the device is turned on, NOT that the signal is 1.
  // Some devices are active zero, and some interface via a MOS which inverts signal polarity
  // Correct logic for this is handled in the  'switch power state' functions.
  if( NodeConfig.EthernetSwitchEnable)
  {
      Set_Ethernet_Switch_Power_State(On);
  }
  else
  {
      Set_Ethernet_Switch_Power_State(Off);
  }

  if( NodeConfig.FCPU_Disable)
  {
      Set_5V_Power_State(On);
  }
  else
  {
      Set_5V_Power_State(Off);
  }

  if( NodeConfig.Reg_3V3_Enable)
  {
      Set_3V_Power_State(On);
  }
  else
  {
      Set_3V_Power_State(Off);
  }

  if( NodeConfig.PL_V1_Disable)
  {
      Set_3V_Power_State(On);
  }
  else
  {
      Set_3V_Power_State(Off);
  }


  if( NodeConfig.PL_V2_Disable)
  {
      Set_3V_Power_State(On);
  }
  else
  {
      Set_3V_Power_State(Off);
  }


  if( NodeConfig.RS232_A_Shutdown)
  {
      Set_RS232_A_Power_State(On);
  }
  else
  {
      Set_RS232_A_Power_State(Off);
  }

  if( NodeConfig.RS232_B_Shutdown)
  {
      Set_RS232_B_Power_State(On);
  }
  else
  {
      Set_RS232_B_Power_State(Off);
  }

  if( NodeConfig.Expander_A_Shutdown)
  {
      Set_Expander_A_Power_State(On);
  }
  else
  {
      Set_Expander_A_Power_State(Off);
  }

  if( NodeConfig.Expander_B_Shutdown)
  {
      Set_Expander_B_Power_State(On);
  }
  else
  {
      Set_Expander_B_Power_State(Off);
  }
  if( NodeConfig.Expander_B_Shutdown)
  {
      Set_Expander_C_Power_State(On);
  }
  else
  {
      Set_Expander_C_Power_State(Off);
  }


}
















void Initilise_Node (void)
{
    CHIP_Init();

    //set up clock routing
    CMU_ClockEnable(cmuClock_HFPER, true);    // Enable clock for TIMER0 and HFPER (High Frequency Peripheral Clock)
 //   CMU_ClockEnable(cmuClock_TIMER0, true);
 //   CMU_ClockEnable(cmuClock_TIMER1, true);
    CMU_ClockEnable(cmuClock_GPIO, true);       // GPIO clock
    CMU_ClockEnable(cmuClock_I2C0, true);       // I2C Clock
    CMU_ClockEnable(cmuClock_USART0, true);     // Node USAR
    CMU_ClockEnable(cmuClock_USART1, true);     // Node USART
    CMU_ClockEnable(cmuClock_USART2, true);     // Node USART
    CMU_ClockEnable(cmuClock_USART3, true);     // Thruster USART
    CMU_ClockEnable(cmuClock_USART4, true);     // Node USART
    CMU_ClockEnable(cmuClock_USART5, true);     // Node USART
    CMU_ClockEnable(cmuClock_UART0, true);     //
    CMU_ClockEnable(cmuClock_UART1, true);     //



    //set pin modes for all UART and USARTs
    GPIO_PinModeSet(gpioPortC, 10, gpioModeInput, 0);     //IMU USART0 LOC 2
    GPIO_PinModeSet(gpioPortC, 11, gpioModePushPull, 1);  //TX
    GPIO_PinModeSet(gpioPortC, 8, gpioModePushPull, 1);   //RTS on the 485 driver, we'll manually control

    GPIO_PinModeSet(gpioPortD, 1, gpioModeInput, 0);      //PDEM USART1 LOC 1
    GPIO_PinModeSet(gpioPortD, 0, gpioModePushPull, 1);   //TX

    GPIO_PinModeSet(gpioPortF, 1, gpioModeInput, 0);      //Node USART2 LOC 5
    GPIO_PinModeSet(gpioPortF, 0, gpioModePushPull, 1);   //TX
    GPIO_PinModeSet(gpioPortF, 5, gpioModePushPull, 1);   //RTS on the 485 driver, we'll manually control

    GPIO_PinModeSet(gpioPortE, 7, gpioModeInput, 0);      //Thruster USART3 LOC 1
    GPIO_PinModeSet(gpioPortE, 6, gpioModePushPull, 1);   //TX
    GPIO_PinModeSet(gpioPortE, 4, gpioModePushPull, 1);   //RTS on the 485 driver, we'll manually control

    GPIO_PinModeSet(gpioPortB, 8, gpioModeInput, 0);      //Expander USART4 LOC 0 MISO
    GPIO_PinModeSet(gpioPortB, 7, gpioModePushPull, 1);   //MOSI
    GPIO_PinModeSet(gpioPortC, 4, gpioModePushPull, 1);   //CLK

    GPIO_PinModeSet(gpioPortB, 1, gpioModeInput, 0);      //SDAS USART5 LOC 2 !!
    GPIO_PinModeSet(gpioPortA, 6, gpioModePushPull, 1);   //TX          LOC 1

    GPIO_PinModeSet(gpioPortE, 1, gpioModeInput, 0);      //FCPU UART0  LOC1
    GPIO_PinModeSet(gpioPortE, 0, gpioModePushPull, 1);   //TX

    GPIO_PinModeSet(gpioPortE, 3, gpioModeInput, 0);      //USBL UART1  LOC3
    GPIO_PinModeSet(gpioPortE, 2, gpioModePushPull, 1);   //TX

    // GPIO setup and implement default state
    GPIO_PinModeSet (gpioPortA, 4, gpioModePushPull, 1);   //RS232_A_SHDN
    GPIO_PinOutClear(gpioPortA, 4);

    GPIO_PinModeSet (gpioPortA, 5, gpioModePushPull, 1);   //RS232_B_SHDN
    GPIO_PinOutClear(gpioPortA, 5);

    GPIO_PinModeSet (gpioPortC, 2, gpioModePushPull, 1);   //BUZZER              -- CHECKED FUNCTIONAL
    GPIO_PinOutClear(gpioPortC,2);    //

    GPIO_PinModeSet (gpioPortB, 2, gpioModePushPull, 1);   //3V3 Enable
    GPIO_PinOutClear(gpioPortB ,2);

    GPIO_PinModeSet (gpioPortA, 15,gpioModePushPull, 1);   //FCPU disable
    GPIO_PinOutClear(gpioPortA ,15);

    GPIO_PinModeSet (gpioPortE, 10,gpioModePushPull, 1);   //Ethernet Switch disable
    GPIO_PinOutClear(gpioPortE ,10);


    GPIO_PinModeSet (gpioPortD, 2,gpioModePushPull, 1);   //EXP USART A RESET
    GPIO_PinOutClear(gpioPortD ,2);

    GPIO_PinModeSet (gpioPortD, 3,gpioModePushPull, 1);   //EXP USART B RESET
    GPIO_PinOutClear(gpioPortD ,3);

    GPIO_PinModeSet (gpioPortD, 4,gpioModePushPull, 1);   //EXP USART C RESET
    GPIO_PinOutClear(gpioPortD ,4);


    //Set up I2C pins
 //   GPIO_PinModeSet(gpioPortD, 7, gpioModeWiredAndPullUpFilter, 1);   //sensor caddy SCL
 //   GPIO_PinModeSet(gpioPortD, 6, gpioModeWiredAndPullUpFilter, 1);   //sensor caddy SDA

//    GPIO_PinModeSet(gpioPortE, 15, gpioModePushPull, 1);   //PL_V1 disable
//    GPIO_PinModeSet(gpioPortE, 14, gpioModePushPull, 1);   //PL_V2 disable

    //GPIO_PinModeSet(gpioPortB, 2, gpioModePushPull, 1);



    //Perform start up


//    GPIO_PinOutClear(gpioPortB,2);    //Shutdown 3v3
    GPIO_PinOutSet(gpioPortA ,15);  //start 5.1v
    GPIO_PinOutSet(gpioPortB,2);      //Start 3v3


 //   GPIO_PinOutClear(gpioPortA,4);    //Shutdown RS232 driver
 //   GPIO_PinOutClear(gpioPortA,5);    //Shutdown RS232 driver

    GPIO_PinOutSet(gpioPortA,4);    //Start RS232 driver
    GPIO_PinOutSet(gpioPortA,5);    //Start RS232 driver

    GPIO_PinOutClear(gpioPortD ,2);   // shutdown expanders
    GPIO_PinOutClear(gpioPortD ,3);
    GPIO_PinOutClear(gpioPortD ,4);

    GPIO_PinOutClear(gpioPortE ,10);  //shutdown Enet

  //  GPIO_PinOutClear(gpioPortA ,15);  //shutdown FCPU



//    GPIO_PinOutClear(gpioPortE,13);
   // GPIO_PinOutSet(gpioPortB,2);


    setupTimer0();
//    setupTimer1();
    usart_init();


}




/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  char input = 0;
  Initilise_Node ();


  //buzz_sweep();

  while(1)
  {

      print_string("\r\nWelcome to NAVCOM \n\r\n\r ", Node);                             //send string to Node UART
  //    hw_timer0(5000);
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
      input = USART_ReceiveChar(USART2);



      switch (input)
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
  input = 0;

  clear_screen();
  print_node_modestate();

  }
}


void Set_Expander_A_Power_State(char power_state)
{
  switch (power_state)
   {
        case On:                                    //if DCDC need switching ON
          GPIO_PinOutSet(gpioPortD ,2);             //Enable the DCDC with GPIO
          print_string("Expander A Enabled\n\r", Node);    //Print message to Terminal
          NodeConfig.Expander_A_Shutdown = '1';            //Update the NodeConfig structure
        break;

        case Off:                                     //if DCDC need switching ON
          GPIO_PinOutClear(gpioPortD ,2);            //Enable the DCDC with GPIO
          print_string("Expander A Shutdown\n\r", Node);   //Print message to Terminal
          NodeConfig.Expander_A_Shutdown = '0';              //Update the NodeConfig structure
        break;

      default:
   }
}



void Set_Expander_B_Power_State(char power_state)
{
  switch (power_state)
   {
        case On:                                    //if DCDC need switching ON
          GPIO_PinOutSet(gpioPortD ,3);             //Enable the DCDC with GPIO
          print_string("Expander B Enabled\n\r", Node);    //Print message to Terminal
          NodeConfig.Expander_B_Shutdown = '1';            //Update the NodeConfig structure
        break;

        case Off:                                     //if DCDC need switching ON
          GPIO_PinOutClear(gpioPortD ,3);            //Enable the DCDC with GPIO
          print_string("Expander B Shutdown\n\r", Node);   //Print message to Terminal
          NodeConfig.Expander_B_Shutdown = '0';              //Update the NodeConfig structure
        break;

      default:
   }
}

void Set_Expander_C_Power_State(char power_state)
{
  switch (power_state)
   {
        case On:                                    //if DCDC need switching ON
          GPIO_PinOutSet(gpioPortD ,4);             //Enable the DCDC with GPIO
          print_string("Expander C Enabled\n\r", Node);    //Print message to Terminal
          NodeConfig.Expander_C_Shutdown = '1';            //Update the NodeConfig structure
        break;

        case Off:                                     //if DCDC need switching ON
          GPIO_PinOutClear(gpioPortD ,4);            //Enable the DCDC with GPIO
          print_string("Expander C Shutdown\n\r", Node);   //Print message to Terminal
          NodeConfig.Expander_C_Shutdown = '0';              //Update the NodeConfig structure
        break;

      default:
   }
}

void Set_Ethernet_Switch_Power_State(char power_state)
{
  switch (power_state)
   {
        case On:                                    //if DCDC need switching ON
          GPIO_PinOutSet(gpioPortE ,10);              //Enable the DCDC with GPIO
          print_string("Enet Switch Enabled \n\r", Node);    //Print message to Terminal
          NodeConfig.EthernetSwitchEnable = '1';            //Update the NodeConfig structure
        break;

        case Off:                                     //if DCDC need switching ON
          GPIO_PinOutClear(gpioPortE ,10);            //Enable the DCDC with GPIO
          print_string("Enet switch Shutdown \n\r", Node);   //Print message to Terminal
          NodeConfig.EthernetSwitchEnable = '0';              //Update the NodeConfig structure
        break;

      default:
   }
}



void Set_RS232_A_Power_State(char power_state)
{
  switch (power_state)
  {
       case On:                                    //if DCDC need switching ON
         GPIO_PinOutSet(gpioPortA,4);              //Enable the DCDC with GPIO
         print_string("RS232 A Enabled\n\r", Node);    //Print message to Terminal
         NodeConfig.RS232_A_Shutdown = '1';             //Update the NodeConfig structure
       break;

       case Off:                                     //if DCDC need switching ON
         GPIO_PinOutClear(gpioPortA,4);             //Enable the DCDC with GPIO
         print_string("RS232 Disabled\n\r", Node);   //Print message to Terminal
         NodeConfig.RS232_A_Shutdown = '0';               //Update the NodeConfig structure
       break;

     default:
  }
}


void Set_RS232_B_Power_State(char power_state)
{
  switch (power_state)
   {
       case On:                                    //if DCDC need switching ON
         GPIO_PinOutSet(gpioPortA,5);              //Enable the DCDC with GPIO
         print_string("RS232 B Enabled\n\r", Node);     //Print message to Terminal
         NodeConfig.RS232_B_Shutdown = '1';             //Update the NodeConfig structure
       break;

       case Off:                                     //if DCDC need switching ON
         GPIO_PinOutClear(gpioPortA,5);          //Enable the DCDC with GPIO
         print_string("RS232 B Disabled\n\r", Node);   //Print message to Terminal
         NodeConfig.RS232_B_Shutdown = '0';             //Update the NodeConfig structure
       break;

     default:
   }
}



void Set_5V_Power_State(char power_state)
{
  switch (power_state)
  {
      case On:                                    //if DCDC need switching ON
      GPIO_PinOutSet(gpioPortA ,15);              //Enable the DCDC with GPIO
      print_string("FCPU Enabled \n\r", Node);    //Print message to Terminal
      NodeConfig.FCPU_Disable='1'   ;             //Update the NodeConfig structure
      break;

    case Off:                                     //if DCDC need switching ON
      GPIO_PinOutClear(gpioPortA ,15);            //Enable the DCDC with GPIO
      print_string("FCPU Shutdown \n\r", Node);   //Print message to Terminal
      NodeConfig.FCPU_Disable='0' ;               //Update the NodeConfig structure
      break;

    default:                                        //unknown command - do not enable ??
      GPIO_PinOutClear(gpioPortA ,15);              //Enable the DCDC with GPIO
      print_string("FCPU Shutdown - but somehitng went wrong\n\r", Node);     //Print message to Terminal
      NodeConfig.FCPU_Disable='0' ;                 //Update the NodeConfig structure
  }
}


void Set_3V_Power_State(char power_state)
{
  switch (power_state)
  {
      case On:                                    //if DCDC need switching ON
        GPIO_PinOutSet(gpioPortB,2);              //Enable the DCDC with GPIO
        print_string("3.3V Reg Enabled\n\r", Node);    //Print message to Terminal
        NodeConfig.Reg_3V3_Enable = '1';             //Update the NodeConfig structure
      break;

      case Off:                                     //if DCDC need switching ON
        GPIO_PinOutClear(gpioPortB,2);
        print_string("3.3V Reg Shutdown\n\r", Node);   //Print message to Terminal
        NodeConfig.Reg_3V3_Enable = '0';               //Update the NodeConfig structure
      break;

    default:                                        //unknown command - do not enable ??

  }
}



void print_node_modestate(void)
{
    print_string("\r\n5 Volt is : \t\t", Node);
    put_char(NodeConfig.FCPU_Disable, Node);
    print_string("\r\n3 Volt is : \t\t", Node);
    put_char(NodeConfig.Reg_3V3_Enable, Node);

    print_string("\r\nRS232 A is : \t\t", Node);
    put_char(NodeConfig.RS232_A_Shutdown, Node);
    print_string("\r\nRS232 B is : \t\t", Node);
    put_char(NodeConfig.RS232_B_Shutdown, Node);

    print_string("\r\nEthernet is : \t\t", Node);
    put_char(NodeConfig.EthernetSwitchEnable, Node);

    print_string("\r\nExpanders A is : \t", Node);
    put_char(NodeConfig.Expander_A_Shutdown, Node);

    print_string("\r\nExpanders B is : \t", Node);
    put_char(NodeConfig.Expander_B_Shutdown, Node);

    print_string("\r\nExpanders C is : \t", Node);
    put_char(NodeConfig.Expander_C_Shutdown, Node);
}


void clear_screen(void)
{
  print_string("\x1b[2J", Node);                                             //clear screen
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




