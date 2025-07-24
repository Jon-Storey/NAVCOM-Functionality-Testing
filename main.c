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
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

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
#include "menu.h"
#include "initialisation.h"
#include "ethernet_switch.h"
#include "usart_expanders.h"



NodeConfiguration NodeConfig = {
    .NodeMode = Flight,              // Use enum value, not character
    .EthernetSwitchEnable = 0,     // use char for bool values (not '0' ascii)
    .FCPU_Disable = 0,
    .Reg_3V3_Enable = 0,
    .PL_V1_Disable = 0,
    .PL_V2_Disable = 0,
    .RS232_A_Shutdown = 0,
    .RS232_B_Shutdown = 0,
    .Expander_A_Shutdown = 0,
    .Expander_B_Shutdown = 0,
    .Expander_C_Shutdown = 0,
    .EthernetSwitchReset = 0,       ///< Ethernet switch state (GPIO Port F, Pin 12)
    .SDAS_Reset = 0,                ///< SDAS Reset state (GPIO Port C, Pin 1)
    .PDEM_Reset = 0,                ///< PDEM Reset state (GPIO Port A, Pin 11)
    .FCPU_Reset = 0,                ///< FCPU Reset state (GPIO Port C, Pin 7)
    .IMU_Reset = 0,                 ///< IMU Reset state (GPIO Port A, Pin 11)
    .Antenna_Reset = 0,             ///< Antenna Reset state (GPIO Port B, Pin 6)
    .FCPU_GPIO_0 = 0,
    .Sensor_Caddy_GPIO_0 = 0,
    .Sensor_Caddy_GPIO_1 = 0,
    .PLA_GPIO_0 = 0,
    .PLA_GPIO_1 = 0,
    .PLB_GPIO_0 = 0,
    .PLB_GPIO_1 = 0,
    .PLC_GPIO_0 = 0,
    .PLD_GPIO_0 = 0,
    .PLE_GPIO_0 = 0

};

int main(void)
{
  Initialise_Node();                //instigate full initialisation process

  NodeConfiguration *pNodeConfig;   //create NodConfig ptr
  pNodeConfig = &NodeConfig;        // point it a NodeConfig STructure

  Set_5V_Power_State(On, pNodeConfig);
  hw_timer1_ms(100);
  Set_3V_Power_State(On, pNodeConfig);
  hw_timer1_ms(100);
  print_string("on.\n\r", Node);


  Set_Expander_A_Power_State(On, pNodeConfig );         //turn on all expanders, power required for high z state
  Set_Expander_B_Power_State(On, pNodeConfig );
  Set_Expander_C_Power_State(On, pNodeConfig );

  Set_Expander_A_CS_State(Deselected);
  Set_Expander_B_CS_State(Deselected);
  Set_Expander_C_CS_State(Deselected);                  // deselect the two unused expanders


 // Set_Ethernet_Switch_Power_State(On, pNodeConfig );

  GPIO_PinOutSet(gpioPortD, 3);                           // Pull reset high EXP3 = uSART b = pin 49 on efm
  GPIO_PinOutSet(gpioPortD, 2);                           // Pull reset high usart A
  GPIO_PinOutSet(gpioPortD, 4);

  Set_RS232_A_Power_State(On, pNodeConfig);
  Set_RS232_B_Power_State(On, pNodeConfig);

  hw_timer1_ms(100);

  MAX14830_UART_Init(EXPANDER_A);
  MAX14830_UART_Init(EXPANDER_B);
  MAX14830_UART_Init(EXPANDER_C);



//  hw_timer1_ms(100);

  while(1)
    {
      hw_timer1_ms(100);
     MAX14830_UART1_SendString("fuck it");
      print_string("x", Node);
    }

  char input = 0;

  while(1)
         {
           GPIO_PinOutSet(gpioPortC, 4);                           // deselect pin
           GPIO_PinOutSet(gpioPortB, 7);                           // deselect pin
           GPIO_PinOutSet(gpioPortB, 8);                           // deselect pin
           hw_timer1_ms(1);
           GPIO_PinOutClear(gpioPortC, 4);
           GPIO_PinOutClear(gpioPortB, 7);
           GPIO_PinOutClear(gpioPortB, 8);
           hw_timer1_ms(1);
         }



  while(1)
    {
      GPIO_PinOutSet(gpioPortC, 4);                           // deselect pin
      GPIO_PinOutSet(gpioPortB, 7);                           // deselect pin
      GPIO_PinOutSet(gpioPortB, 8);                           // deselect pin
      hw_timer1_ms(100);
      GPIO_PinOutClear(gpioPortC, 4);
      GPIO_PinOutClear(gpioPortB, 7);
      GPIO_PinOutClear(gpioPortB, 8);
      hw_timer1_ms(100);
    }




  menu_init();
 // input = USART_ReceiveChar(Node);
 // menu_process_input(input);
  //handle_main_menu(input);




  while(1)
  {
      input = USART_ReceiveChar(USART2);
      menu_process_input(input, pNodeConfig);
      print_node_modestate(pNodeConfig);

   }
}


  // Send a character





/*
  char input = 0;
    Initilise_Node ();
    initI2C();
    uint8_t result;
    while(1)
    {
        print_string("1 send who am i?   \n\r" , Node);
        input = USART_ReceiveChar(USART2);

        switch (input)
        {
          case '1':

           i2cStartReadByte();

           while (!i2cIsTransferDone());


           print_string("tx done\n\r" , Node);

           uint8_t result = i2cGetLastByte();

           binaryToAsciiHex(result, asciiStr);
           print_string("Read: ", Node);
           print_string(asciiStr, Node);
           print_string("\n\r", Node);

            break;
        }

        input = 0;





*/


















 /* char input = 0;
  Initilise_Node ();
  initI2C();
  uint8_t result;
  while(1)
  {
      print_string("1 send who am i?   \n\r" , Node);
      input = USART_ReceiveChar(USART2);

      switch (input)
      {
        case '1':


             bool success = i2cReadRegister(0x00, &result);

             if (success)
               {
                 binaryToAsciiString(result, asciiStr);

                 print_string("read this:", Node);
                 print_string(asciiStr, Node);
                 print_string("\n\r", Node);

             } else
               {
                 print_string("nothing \n\r", Node);
             }

          break;
      }

      input = 0;
*/

  //    clear_screen();
 //     print_node_modestate();










