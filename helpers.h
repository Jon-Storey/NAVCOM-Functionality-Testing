/*
* helpers.h
 *
 * @brief Helper functions for EFM32GG11B node power management and utilities
 * @description This header provides function declarations for controlling various
 *              power rails (5V, 3.3V), communication interfaces (RS232 A/B, Ethernet),
 *              expansion modules (A/B/C), and utility functions for the node system.
 *
 *  Created on: 11 Jun 2025
 *      Author: JonathanStorey
 *    Hardware: EFM32GG11B Microcontroller
 *     Version: 1.0
 *
 * @note All power control functions update both GPIO states and NodeConfiguration flags
 * @note Power state parameter: Use 'On'/'Off' enums as defined in defines.h
 */

#ifndef HELPERS_H_
#define HELPERS_H_

#include <stdint.h>  // For uint8_t


/*==============================================================================
 * POWER CONTROL FUNCTIONS
 * @brief Functions to control individual power rails and update configuration
 * @note Each function controls specific GPIO pins and updates NodeConfig flags
 *============================================================================*/
void Set_5V_Power_State(char power_state, NodeConfiguration *NodeConfig);
void Set_3V_Power_State(char power_state, NodeConfiguration *NodeConfig);
void Set_RS232_A_Power_State(char power_state, NodeConfiguration *NodeConfig);
void Set_RS232_B_Power_State(char power_state, NodeConfiguration *NodeConfig);
void Set_Ethernet_Switch_Power_State(char power_state, NodeConfiguration *NodeConfig);
void Set_Expander_A_Power_State(char power_state, NodeConfiguration *NodeConfig);
void Set_Expander_B_Power_State(char power_state, NodeConfiguration *NodeConfig);
void Set_Expander_C_Power_State(char power_state, NodeConfiguration *NodeConfig);
void Set_PHY_Power_State(char power_state, NodeConfiguration *NodeConfig);
void Set_PLV1_Power_State(char power_state, NodeConfiguration *NodeConfig);
void Set_PLV2_Power_State(char power_state, NodeConfiguration *NodeConfig);

/*==============================================================================
 * RESET CONTROL FUNCTIONS
 * @brief Functions to control reset signal for subsystems
 * @note Each function controls specific GPIO pins and updates NodeConfig flags
 *============================================================================*/

void Set_Ethernet_Switch_Reset_State(char reset_state, NodeConfiguration *NodeConfig);
void Set_SDAS_Reset_State(char reset_state, NodeConfiguration *NodeConfig);
void Set_PDEM_Reset_State(char reset_state, NodeConfiguration *NodeConfig);
void Set_FCPU_Reset_State(char reset_state, NodeConfiguration *NodeConfig);
void Set_IMU_Reset_State(char reset_state, NodeConfiguration *NodeConfig);
void Set_Antenna_Reset_State(char reset_state, NodeConfiguration *NodeConfig);



void Set_FCPU_SPI_MOSI_State(char GPIO_state, NodeConfiguration *NodeConfig);
void Set_FCPU_SPI_MISO_State(char GPIO_state, NodeConfiguration *NodeConfig);
void Set_FCPU_SPI_CLK_State(char GPIO_state, NodeConfiguration *NodeConfig);
void Set_FCPU_SPI_CS_State(char GPIO_state, NodeConfiguration *NodeConfig);
void Set_FCPU_Disable_State(char GPIO_state, NodeConfiguration *NodeConfig);

/*==============================================================================
 * CHIP SELECT CONNTROL FUNCTIONS
 * @brief Functions to control CS signal for subsystems
 * @note Each function controls specific GPIO pins and updates NodeConfig flags
 *============================================================================*/
void Set_Expander_A_CS_State(char CS_state);
void Set_Expander_B_CS_State(char CS_state);
void Set_Expander_C_CS_State(char CS_state);


/*==============================================================================
 * GPIO CONTROL FUNCTIONS
 * @brief
 *============================================================================*/
void Set_FCPU_GPIO_0_State(char GPIO_state, NodeConfiguration *NodeConfig);
void Set_SENSOR_CADDY_GPIO_0_State(char GPIO_state, NodeConfiguration *NodeConfig);
void Set_SENSOR_CADDY_GPIO_1_State(char GPIO_state,NodeConfiguration *NodeConfig);
void Set_PLA_GPIO_0_State(char GPIO_state, NodeConfiguration *NodeConfig);
void Set_PLA_GPIO_1_State(char GPIO_state, NodeConfiguration *NodeConfig);
void Set_PLB_GPIO_0_State(char GPIO_state, NodeConfiguration *NodeConfig);
void Set_PLB_GPIO_1_State(char GPIO_state, NodeConfiguration *NodeConfig);
void Set_PLC_GPIO_0_State(char GPIO_state, NodeConfiguration *NodeConfig);
void Set_PLD_GPIO_0_State(char GPIO_state, NodeConfiguration *NodeConfig);
void Set_PLE_GPIO_0_State(char GPIO_state, NodeConfiguration *NodeConfig);

/*==============================================================================
 * NODE MANAGEMENT FUNCTIONS
 * @brief High-level node configuration and status functions
 *============================================================================*/
void Set_Node_Mode(char node_mode_state, NodeConfiguration *NodeConfig);
void print_node_modestate(NodeConfiguration *NodeConfig);

/*==============================================================================
 * UTILITY FUNCTIONS
 * @brief General purpose utility functions for display and data conversion
 *============================================================================*/
void clear_screen(void);
void binaryToAsciiString(uint8_t value, char *asciiStr);
void binaryToAsciiHex(uint8_t value, char *asciiStr);
void USART_Test_Cycle(void);









#endif /* HELPERS_H_ */
