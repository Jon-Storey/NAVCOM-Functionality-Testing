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

#include "sw_delay.h"
#include "hw_timer.h"
#include "usart.h"
#include "buzzer.h"
#include "defines.h"
#include "i2c.h"
#include "helpers.h"
#include "menu.h"
#include "initialisation.h"



NodeConfiguration NodeConfig = {'0','0','0','0','0','0','0','0', '0', '0','0'};


int main(void)
{
  Initialise_Node();
  NodeConfiguration *pNodeConfig;   //create NodConfig ptr
  pNodeConfig = &NodeConfig;        // point it a NodeConfig STructure

  while(1)
  {
      Set_Node_Mode (Flight, pNodeConfig );
   }
}


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










