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









#define BUFFER_SIZE 80
char buffer[BUFFER_SIZE];



void init (void)
{
    CHIP_Init();

    //set up clock routing
    CMU_ClockEnable(cmuClock_HFPER, true);    // Enable clock for TIMER0 and HFPER (High Frequency Peripheral Clock)
 //   CMU_ClockEnable(cmuClock_TIMER0, true);
 //   CMU_ClockEnable(cmuClock_TIMER1, true);
    CMU_ClockEnable(cmuClock_GPIO, true);       // GPIO clock
    CMU_ClockEnable(cmuClock_I2C0, true);       // I2C Clock
    CMU_ClockEnable(cmuClock_USART0, true);     // Node USART - ttl (for now)
    CMU_ClockEnable(cmuClock_USART1, true);     // Node USART - ttl (for now)
    CMU_ClockEnable(cmuClock_USART2, true);     // Node USART - ttl (for now)
    CMU_ClockEnable(cmuClock_USART3, true);     // Thruster USART   - RS485
    CMU_ClockEnable(cmuClock_USART4, true);     // Node USART - ttl (for now)
    CMU_ClockEnable(cmuClock_USART5, true);     // Node USART - ttl (for now)
    CMU_ClockEnable(cmuClock_UART0, true);     //
    CMU_ClockEnable(cmuClock_UART1, true);     //



    //set pin modes for all UART and USARTs
    GPIO_PinModeSet(gpioPortC, 10, gpioModeInput, 0);     //IMU USART0 LOC 2
    GPIO_PinModeSet(gpioPortC, 11, gpioModePushPull, 1);  //TX

    GPIO_PinModeSet(gpioPortD, 1, gpioModeInput, 0);      //PDEM USART1 LOC 1
    GPIO_PinModeSet(gpioPortD, 0, gpioModePushPull, 1);   //TX

    GPIO_PinModeSet(gpioPortF, 1, gpioModeInput, 0);      //Node USART2 LOC 5
    GPIO_PinModeSet(gpioPortF, 0, gpioModePushPull, 1);   //TX

    GPIO_PinModeSet(gpioPortE, 7, gpioModeInput, 0);      //Thruster USART3 LOC 1
    GPIO_PinModeSet(gpioPortE, 6, gpioModePushPull, 1);   //TX

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



    GPIO_PinOutClear(gpioPortB,2);    //Shutdown 3v3

    GPIO_PinOutClear(gpioPortA,4);    //Shutdown RS232 driver
    GPIO_PinOutClear(gpioPortA,5);    //Shutdown RS232 driver

    GPIO_PinOutClear(gpioPortD ,2);   // shutdown expanders
    GPIO_PinOutClear(gpioPortD ,3);
    GPIO_PinOutClear(gpioPortD ,4);

    GPIO_PinOutClear(gpioPortE ,10);  //shutdown Enet

    GPIO_PinOutClear(gpioPortA ,15);  //shutdown FCPU



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

 NodeStuff N1 = {'0','0','0','0','0','0','0','0'};

  char input = 0;
  init ();

  //buzz_sweep();

  while(1)
  {

      print_string("\r\nWelcome to NAVCOM \n\r\n\r ", Node);                             //send string to Node UART
  //    hw_timer0(5000);
      print_string("-------------------------  \n\r" , Node);
      print_string("1 Enable FCPU   \n\r" , Node);
      print_string("2 Shutdown FCPU \n\r", Node);
      print_string("3 Enable RS232 \n\r", Node);
      print_string("4 Shutdown RS232\n\r", Node);
      print_string("5 Enable 3V3\n\r", Node);
      print_string("6 Shutdown 3V3\n\r", Node);
      print_string("7 Enable Ethernet\n\r", Node);
      print_string("8 Shutdown Ethernet\n\r", Node);
      print_string("9 Enable Expanders\n\r", Node);
      print_string("a Shutdown Expanders\n\r", Node);             //send string to Node UART

      input = USART_ReceiveChar(USART2);
      print_string("\x1b[2J", Node);                                             //clear screen

      switch (input)
      {
        case '1':  GPIO_PinOutSet(gpioPortA ,15);     print_string("FCPU Enabled \n\r", Node); N1.FCPU_Disable='1'; break;   //set enables DCDC
        case '2':  GPIO_PinOutClear(gpioPortA ,15);   print_string("FCPU Shutdown \n\r", Node); N1.FCPU_Disable='0';break;     //clear shutsdown DCDC

        case '3':  GPIO_PinOutSet(gpioPortA,4); GPIO_PinOutSet(gpioPortA,5); print_string("RS232 Enabled\n\r", Node); N1.RS232_A_Shutdown = '1'; N1.RS232_B_Shutdown = '1'; break;
        case '4':  GPIO_PinOutClear(gpioPortA,4); GPIO_PinOutClear(gpioPortA,5); print_string("RS232 Shutdown\n\r", Node); N1.RS232_A_Shutdown = '0'; N1.RS232_B_Shutdown = '0'; ;break;

        case '5':  GPIO_PinOutSet(gpioPortB,2); print_string("3.3V Reg Enabled\n\r", Node); N1.Reg_3V3_Enable = '1'; break;
        case '6':  GPIO_PinOutClear(gpioPortB,2); print_string("3.3V Reg Shutdown\n\r", Node); N1.Reg_3V3_Enable = '0'; break;

        case '7':  GPIO_PinOutSet(gpioPortE ,10); print_string("Enet Switch Enabled \n\r", Node); N1.EthernetSwitch = '1'; break;       //Set Enable Enet
        case '8':  GPIO_PinOutClear(gpioPortE ,10); print_string("Enet switch Shutdown \n\r", Node); N1.EthernetSwitch = '0'; break;    //clear shutsdown Enet

        case '9':  GPIO_PinOutSet(gpioPortD ,2);GPIO_PinOutSet(gpioPortD ,3);GPIO_PinOutSet(gpioPortD ,4); print_string("Expanders Enabled\n\r", Node); N1.Expander_A_Shutdown = '1'; break;
        case 'a':  GPIO_PinOutClear(gpioPortD ,2);GPIO_PinOutClear(gpioPortD ,3);GPIO_PinOutClear(gpioPortD ,4); print_string("Expanders Shitdown\n\r", Node); N1.Expander_A_Shutdown = '0'; break;

        default:  print_string("something wrong \n\r", Node);
      }
  input = 0;

  print_string("\r\nFCPU is : ", Node);
  put_char(N1.FCPU_Disable, Node);
  print_string("\r\nRS232 is : ", Node);
  put_char(N1.RS232_A_Shutdown, Node);
  print_string("\r\n3v3 is : ", Node);
  put_char(N1.Reg_3V3_Enable, Node);
  print_string("\r\nEthernet is : ", Node);
  put_char(N1.EthernetSwitch, Node);
  print_string("\r\nExpanders is : ", Node);
  put_char(N1.Expander_A_Shutdown, Node);





  }
}






void USART_Test_Cycle(void)
{
    while(1)
    {

          print_string("hello from Node \n\r", Node);           // check works
          print_string("hello from IMU \n\r" , IMU);            // check works
          print_string("hello from PDEM \n\r", PDEM);           // check works
          print_string("hello from SDAS \n\r", SDAS);           // check works - confirmed over RS232
          print_string("hello from Thruster \n\r", Thrusters ); // check works
          print_string("hello from FCPU \n\r", FCPU);           // check works !no routing
          print_string("hello from USBL \n\r", USBL);           // check works ! no routing

    }
}




//int main(void)
//{
//  sl_system_init();
//  app_init();


//  while (1)
//  {
//    sl_system_process_action();
//    app_process_action();
 // }

//}
