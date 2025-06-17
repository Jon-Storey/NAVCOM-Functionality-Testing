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


enum power_state
{
  On,
  Off
};



enum node_mode_state
{
  Flight,
  Deck,
  Safe,
  Service
};


typedef struct
{
  int NodeMode;
  char EthernetSwitchEnable;
  char FCPU_Disable;
  char Reg_3V3_Enable;
  char PL_V1_Disable;
  char PL_V2_Disable;
  char RS232_A_Shutdown;
  char RS232_B_Shutdown;
  char Expander_A_Shutdown;
  char Expander_B_Shutdown;
  char Expander_C_Shutdown;
} NodeConfiguration;


#endif /* DEFINES_H_ */
