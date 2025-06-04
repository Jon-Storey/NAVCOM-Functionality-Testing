/*
 * defines.h
 *
 *  Created on: 20 May 2025
 *      Author: JonathanStorey
 */

#ifndef DEFINES_H_
#define DEFINES_H_


enum destination
{
  IMU,
  PDEM,
  Node,
  Thrusters,
  Expander,
  SDAS,
  FCPU,
  USBL
};



typedef struct
{
  char EthernetSwitch;
  char FCPU_Disable;
  char Reg_3V3_Enable;
  char PL_V1_Disable;
  char PL_V2_Disable;
  char RS232_A_Shutdown;
  char RS232_B_Shutdown;
  char Expander_A_Shutdown;
//  char Expander_B_Shutdown = 0;
//  char Expander_B_Shutdown = 0;
} NodeStuff;


#endif /* DEFINES_H_ */
