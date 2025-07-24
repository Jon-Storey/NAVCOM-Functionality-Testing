/*
 * ethernet_switch.c
 *
 *  Created on: 6 Jul 2025
 *      Author: JonathanStorey
 */

#include "ethernet_switch.h"
#include "defines.h"
#include "helpers.h"
#include "hw_timer.h"



void ESwitch_Reset_Sequence(NodeConfiguration *NodeConfig)
{
  //Assumes 5v and 3v3 have been turned on
  Set_Ethernet_Switch_Power_State(Off, NodeConfig);         // regardless of current situation, turn off power to the chip
  hw_timer1_ms(5);                                          // wait for the chip to power down and settle
  Set_Ethernet_Switch_Power_State(On, NodeConfig);          // re-apply power to the chip
  hw_timer1_ms(5);                                          // wait 5ms after powering on chip
  Set_Ethernet_Switch_Reset_State(Off, NodeConfig);                // Set Reset low, which resets chip
  hw_timer1_ms(15);                                         // wait 15 ms with RESET low for warm reset
  Set_Ethernet_Switch_Reset_State(On, NodeConfig);                 // Set Reset high. Strap on values are read on the rising edge (includes a reading time)
  hw_timer1_ms(150);                                        // wait for chip tp settle, unmanaged network should begin operating
}


void ESwitch_Shutdown_Sequence(NodeConfiguration *NodeConfig)
{
  //Assumes 5v and 3v3 have been turned on
  Set_Ethernet_Reset_State(Off, NodeConfig);                // Set Reset low, which resets chip
  hw_timer1_ms(5);                                          // wait 15 ms with RESET low, this shuts the chip down
  Set_Ethernet_Switch_Power_State(Off, NodeConfig);         // turn off power to the chip
}

