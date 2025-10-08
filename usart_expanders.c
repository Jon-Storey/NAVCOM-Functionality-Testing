#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_usart.h"
#include "em_gpio.h"
#include "defines.h"
#include "helpers.h"
#include "usart_expanders.h"
#include "hw_timer.h"




/**
 * @brief Complete initialization function for MAX14830 UART1 with 4MHz crystal
 * Configures UART1 for 9600 baud, 8N1 format with standard settings
 */
void MAX14830_UART_Init(uint8_t expander)
{
    MAX14830_WriteRegister(expander,MAX14830_UART0, MAX14830_MODE2_REG, MAX14830_MODE2_RST);     // Step 1: Reset the specific UART channel first (optional but recommended)
    hw_timer1_ms(2);                                                                             // Wait for reset to complete
    MAX14830_WriteRegister(expander, MAX14830_UART0, MAX14830_CLKSRC_REG, MAX14830_CLKSOURCE_CRYSTALEN | MAX14830_CLKSOURCE_PLLEN);     // Step 2: Configure Clock Source - Enable crystal oscillator and PLL !!! MUST BE WRITTEN TO USART_0!!!
    MAX14830_WriteRegister(expander, MAX14830_UART0, MAX14830_PLLCFG_REG, 0x48);                // Step 3: Configure PLL for 4 MHz crystal,PLL config 0x48: predivider=8, factor=1 gives good internal clock for UART
    hw_timer1_ms(5);                                                                            // Wait for PLL to stabilize




    MAX14830_WriteRegister(expander, MAX14830_UART0, MAX14830_DIVLSB_REG, 156);                  // Step 4: Configure Baud Rate Generator for 9600 baud with 4MHz crystal
    MAX14830_WriteRegister(expander, MAX14830_UART0, MAX14830_DIVMSB_REG, 0);                   // With 4MHz and PLL settings: Divisor ≈ 26 for 9600 baud,     // Actual baud rate will be ~9615 (0.16% error - acceptable)
    MAX14830_WriteRegister(expander, MAX14830_UART0, MAX14830_BRGCFG_REG, 0x04);                //
    MAX14830_WriteRegister(expander, MAX14830_UART0, MAX14830_LCR_REG, MAX14830_LCR_WORD_LEN_8);// Step 5: Configure Line Control Register for 8N1 format,     // 8 data bits, no parity, 1 stop bit
    MAX14830_WriteRegister(expander, MAX14830_UART0, MAX14830_FIFOTRIGLVL_REG,(1 << MAX14830_FIFOTRIG_RX_SHIFT) | (1 << MAX14830_FIFOTRIG_TX_SHIFT));     // Step 6: Configure FIFO trigger levels,     // RX trigger at 1 character, TX trigger at 1 character for responsive operation
    MAX14830_WriteRegister(expander, MAX14830_UART0, MAX14830_MODE1_REG, 0x00);                 // Step 7: Configure MODE1 register - normal UART operation,     // All special functions disabled for standard UART behavior
    MAX14830_WriteRegister(expander, MAX14830_UART0, MAX14830_MODE2_REG, 0x00);                 // Step 8: Configure MODE2 register - clear reset and special modes , // Ensure FIFO is not in reset state, normal operation mode
    MAX14830_WriteRegister(expander, MAX14830_UART0, MAX14830_FLOWCTRL_REG, 0x00);              // Step 9: Configure Flow Control - disabled for basic operation,    // No hardware or software flow control
    MAX14830_WriteRegister(expander, MAX14830_UART0, MAX14830_RXIMEOUT_REG, 0x00);              // Step 10: Configure RX timeout - disabled for this basic setup
 //   uint8_t temp = MAX14830_ReadRegister(MAX14830_UART1, MAX14830_ISR_REG);                   // Step 11: Clear any pending interrupts by reading the ISR
  //  (void)temp;                                                                               // Suppress unused variable warning
    MAX14830_WriteRegister(expander, MAX14830_UART0, MAX14830_IRQEN_REG,0x00);                  // Disable all interrupts, must poll the ISR instead
    MAX14830_WriteRegister(expander, MAX14830_UART0, MAX14830_LSRINTEN_REG,0x00);               // Disable the line status interrupts
    MAX14830_WriteRegister(expander, MAX14830_UART0, MAX14830_SPCLCHRINT_REG,0x00);             // Disable special character interrupts
    MAX14830_WriteRegister(expander, MAX14830_UART0, MAX14830_STSINTEN_REG,0x00);               // Disable system interrupt interrupts
  //  uint8_t temp = MAX14830_ReadRegister(MAX14830_UART1, MAX14830_STSINT_REG);                // use to check if clock is ready
  //  MAX14830_WriteRegister(expander, MAX14830_UART0, MAX14830_MODE1_REG,0x00);                  // enables TX and RX, see mode 1 reg
  //  MAX14830_WriteRegister(expander, MAX14830_UART0, MAX14830_GLOBALCMD_REG, 0x02);             // Step 13: Enable UART1 via Global Command Register,     // Bit 1 (0x02) enables UART1 transmitter and receiver





    MAX14830_WriteRegister(expander, MAX14830_UART1, MAX14830_DIVLSB_REG, 156);                  // Step 4: Configure Baud Rate Generator for 9600 baud with 4MHz crystal
    MAX14830_WriteRegister(expander, MAX14830_UART1, MAX14830_DIVMSB_REG, 0);                   // With 4MHz and PLL settings: Divisor ≈ 26 for 9600 baud,     // Actual baud rate will be ~9615 (0.16% error - acceptable)
    MAX14830_WriteRegister(expander, MAX14830_UART1, MAX14830_BRGCFG_REG, 0x04);                //
    MAX14830_WriteRegister(expander, MAX14830_UART1, MAX14830_LCR_REG, MAX14830_LCR_WORD_LEN_8);// Step 5: Configure Line Control Register for 8N1 format,     // 8 data bits, no parity, 1 stop bit
    MAX14830_WriteRegister(expander, MAX14830_UART1, MAX14830_FIFOTRIGLVL_REG,(1 << MAX14830_FIFOTRIG_RX_SHIFT) | (1 << MAX14830_FIFOTRIG_TX_SHIFT));     // Step 6: Configure FIFO trigger levels,     // RX trigger at 1 character, TX trigger at 1 character for responsive operation
    MAX14830_WriteRegister(expander, MAX14830_UART1, MAX14830_MODE1_REG, 0x00);                 // Step 7: Configure MODE1 register - normal UART operation,     // All special functions disabled for standard UART behavior
    MAX14830_WriteRegister(expander, MAX14830_UART1, MAX14830_MODE2_REG, 0x00);                 // Step 8: Configure MODE2 register - clear reset and special modes , // Ensure FIFO is not in reset state, normal operation mode
    MAX14830_WriteRegister(expander, MAX14830_UART1, MAX14830_FLOWCTRL_REG, 0x00);              // Step 9: Configure Flow Control - disabled for basic operation,    // No hardware or software flow control
    MAX14830_WriteRegister(expander, MAX14830_UART1, MAX14830_RXIMEOUT_REG, 0x00);              // Step 10: Configure RX timeout - disabled for this basic setup
    //   uint8_t temp = MAX14830_ReadRegister(MAX14830_UART1, MAX14830_ISR_REG);                   // Step 11: Clear any pending interrupts by reading the ISR
    //  (void)temp;                                                                               // Suppress unused variable warning
    MAX14830_WriteRegister(expander, MAX14830_UART1, MAX14830_IRQEN_REG,0x00);                  // Disable all interrupts, must poll the ISR instead
    MAX14830_WriteRegister(expander, MAX14830_UART1, MAX14830_LSRINTEN_REG,0x00);               // Disable the line status interrupts
    MAX14830_WriteRegister(expander, MAX14830_UART1, MAX14830_SPCLCHRINT_REG,0x00);             // Disable special character interrupts
    MAX14830_WriteRegister(expander, MAX14830_UART1, MAX14830_STSINTEN_REG,0x00);               // Disable system interrupt interrupts
    //  uint8_t temp = MAX14830_ReadRegister(MAX14830_UART1, MAX14830_STSINT_REG);                // use to check if clock is ready
 //   MAX14830_WriteRegister(expander, MAX14830_UART1, MAX14830_MODE1_REG,0x00);                  // enables TX and RX, see mode 1 reg
  //  MAX14830_WriteRegister(expander, MAX14830_UART1, MAX14830_GLOBALCMD_REG, 0x02);             // Step 13: Enable UART1 via Global Command Register,     // Bit 1 (0x02) enables UART1 transmitter and receiver




    MAX14830_WriteRegister(expander, MAX14830_UART2, MAX14830_DIVLSB_REG, 156);                  // Step 4: Configure Baud Rate Generator for 9600 baud with 4MHz crystal
    MAX14830_WriteRegister(expander, MAX14830_UART2, MAX14830_DIVMSB_REG, 0);                   // With 4MHz and PLL settings: Divisor ≈ 26 for 9600 baud,     // Actual baud rate will be ~9615 (0.16% error - acceptable)
    MAX14830_WriteRegister(expander, MAX14830_UART2, MAX14830_BRGCFG_REG, 0x04);                //
    MAX14830_WriteRegister(expander, MAX14830_UART2, MAX14830_LCR_REG, MAX14830_LCR_WORD_LEN_8);// Step 5: Configure Line Control Register for 8N1 format,     // 8 data bits, no parity, 1 stop bit
    MAX14830_WriteRegister(expander, MAX14830_UART2, MAX14830_FIFOTRIGLVL_REG,(1 << MAX14830_FIFOTRIG_RX_SHIFT) | (1 << MAX14830_FIFOTRIG_TX_SHIFT));     // Step 6: Configure FIFO trigger levels,     // RX trigger at 1 character, TX trigger at 1 character for responsive operation
    MAX14830_WriteRegister(expander, MAX14830_UART2, MAX14830_MODE1_REG, 0x00);                 // Step 7: Configure MODE1 register - normal UART operation,     // All special functions disabled for standard UART behavior
    MAX14830_WriteRegister(expander, MAX14830_UART2, MAX14830_MODE2_REG, 0x00);                 // Step 8: Configure MODE2 register - clear reset and special modes , // Ensure FIFO is not in reset state, normal operation mode
    MAX14830_WriteRegister(expander, MAX14830_UART2, MAX14830_FLOWCTRL_REG, 0x00);              // Step 9: Configure Flow Control - disabled for basic operation,    // No hardware or software flow control
    MAX14830_WriteRegister(expander, MAX14830_UART2, MAX14830_RXIMEOUT_REG, 0x00);              // Step 10: Configure RX timeout - disabled for this basic setup
    //   uint8_t temp = MAX14830_ReadRegister(MAX14830_UART1, MAX14830_ISR_REG);                   // Step 11: Clear any pending interrupts by reading the ISR
    //  (void)temp;                                                                               // Suppress unused variable warning
    MAX14830_WriteRegister(expander, MAX14830_UART2, MAX14830_IRQEN_REG,0x00);                  // Disable all interrupts, must poll the ISR instead
    MAX14830_WriteRegister(expander, MAX14830_UART2, MAX14830_LSRINTEN_REG,0x00);               // Disable the line status interrupts
    MAX14830_WriteRegister(expander, MAX14830_UART2, MAX14830_SPCLCHRINT_REG,0x00);             // Disable special character interrupts
    MAX14830_WriteRegister(expander, MAX14830_UART2, MAX14830_STSINTEN_REG,0x00);               // Disable system interrupt interrupts
    //  uint8_t temp = MAX14830_ReadRegister(MAX14830_UART1, MAX14830_STSINT_REG);                // use to check if clock is ready
  //  MAX14830_WriteRegister(expander, MAX14830_UART2, MAX14830_MODE1_REG,0x00);                  // enables TX and RX, see mode 1 reg
  //  MAX14830_WriteRegister(expander, MAX14830_UART2, MAX14830_GLOBALCMD_REG, 0x02);             // Step 13: Enable UART1 via Global Command Register,     // Bit 1 (0x02) enables UART1 transmitter and receiver




    MAX14830_WriteRegister(expander, MAX14830_UART3, MAX14830_DIVLSB_REG, 156);                  // Step 4: Configure Baud Rate Generator for 9600 baud with 4MHz crystal
    MAX14830_WriteRegister(expander, MAX14830_UART3, MAX14830_DIVMSB_REG, 0);                   // With 4MHz and PLL settings: Divisor ≈ 26 for 9600 baud,     // Actual baud rate will be ~9615 (0.16% error - acceptable)
    MAX14830_WriteRegister(expander, MAX14830_UART3, MAX14830_BRGCFG_REG, 0x04);                //
    MAX14830_WriteRegister(expander, MAX14830_UART3, MAX14830_LCR_REG, MAX14830_LCR_WORD_LEN_8);// Step 5: Configure Line Control Register for 8N1 format,     // 8 data bits, no parity, 1 stop bit
    MAX14830_WriteRegister(expander, MAX14830_UART3, MAX14830_FIFOTRIGLVL_REG,(1 << MAX14830_FIFOTRIG_RX_SHIFT) | (1 << MAX14830_FIFOTRIG_TX_SHIFT));     // Step 6: Configure FIFO trigger levels,     // RX trigger at 1 character, TX trigger at 1 character for responsive operation
    MAX14830_WriteRegister(expander, MAX14830_UART3, MAX14830_MODE1_REG, 0x00);                 // Step 7: Configure MODE1 register - normal UART operation,     // All special functions disabled for standard UART behavior
    MAX14830_WriteRegister(expander, MAX14830_UART3, MAX14830_MODE2_REG, 0x00);                 // Step 8: Configure MODE2 register - clear reset and special modes , // Ensure FIFO is not in reset state, normal operation mode
    MAX14830_WriteRegister(expander, MAX14830_UART3, MAX14830_FLOWCTRL_REG, 0x00);              // Step 9: Configure Flow Control - disabled for basic operation,    // No hardware or software flow control
    MAX14830_WriteRegister(expander, MAX14830_UART3, MAX14830_RXIMEOUT_REG, 0x00);              // Step 10: Configure RX timeout - disabled for this basic setup
    //   uint8_t temp = MAX14830_ReadRegister(MAX14830_UART1, MAX14830_ISR_REG);                   // Step 11: Clear any pending interrupts by reading the ISR
    //  (void)temp;                                                                               // Suppress unused variable warning
    MAX14830_WriteRegister(expander, MAX14830_UART3, MAX14830_IRQEN_REG,0x00);                  // Disable all interrupts, must poll the ISR instead
    MAX14830_WriteRegister(expander, MAX14830_UART3, MAX14830_LSRINTEN_REG,0x00);               // Disable the line status interrupts
    MAX14830_WriteRegister(expander, MAX14830_UART3, MAX14830_SPCLCHRINT_REG,0x00);             // Disable special character interrupts
    MAX14830_WriteRegister(expander, MAX14830_UART3, MAX14830_STSINTEN_REG,0x00);               // Disable system interrupt interrupts
    //  uint8_t temp = MAX14830_ReadRegister(MAX14830_UART1, MAX14830_STSINT_REG);                // use to check if clock is ready
 //   MAX14830_WriteRegister(expander, MAX14830_UART3, MAX14830_MODE1_REG,0x00);                  // enables TX and RX, see mode 1 reg
 //   MAX14830_WriteRegister(expander, MAX14830_UART3, MAX14830_GLOBALCMD_REG, 0x02);             // Step 13: Enable UART1 via Global Command Register,     // Bit 1 (0x02) enables UART1 transmitter and receiver




    hw_timer1_ms(2);                                                                              // Final delay to ensure UART is fully operational
}





/**
 * @brief Get recommended divisor values for common baud rates with 4MHz crystal
 * @param baudRate Desired baud rate
 * @return Divisor value (0 if baud rate not recommended)
 */
uint16_t MAX14830_GetDivisorFor4MHz(uint32_t baudRate)
{
    switch(baudRate)
    {
        case 1200:   return 208;  // 0.16% error
        case 2400:   return 104;  // 0.16% error
        case 4800:   return 52;   // 0.16% error
        case 9600:   return 26;   // 0.16% error
        case 19200:  return 13;   // 0.16% error
        case 38400:  return 6;    // 4.17% error (acceptable)
        case 57600:  return 4;    // 4.17% error (marginal)
        case 115200: return 2;    // 8.33% error (not recommended)
        default:     return 0;    // Calculate manually
    }
}









/**
 * @brief Write a register on the MAX14830
 * @param uart_channel UART channel (0-3)
 * @param reg_addr Register address
 * @param data Data to write
 */
void MAX14830_WriteRegister(uint8_t expander, uint8_t uart_channel, uint8_t reg_addr, char data)
{
    uint8_t command_byte = 0x80 |                                               // Set W/R bit for write
                          ((uart_channel & 0x03) << 5) |                        // Set U1,U0 bits
                          (reg_addr & 0x1F);                                    // Set address bits A4-A0

    switch (expander)                                                           // Select appropriate CS for the UART channel
    {
      case EXPANDER_A: Set_Expander_A_CS_State(Selected); break;
      case EXPANDER_B: Set_Expander_B_CS_State(Selected); break;
      case EXPANDER_C: Set_Expander_C_CS_State(Selected); break;
    }

    hw_timer0_us_short(1);
    USART_SpiTransfer(USART4, command_byte);                                    // Send command byte with write bit
    USART_SpiTransfer(USART4, data);                                            // Send data byte
    hw_timer0_us_short(1);
    switch (expander)
    {
      case EXPANDER_A: Set_Expander_A_CS_State(Deselected); break;
      case EXPANDER_B: Set_Expander_B_CS_State(Deselected); break;
      case EXPANDER_C: Set_Expander_C_CS_State(Deselected); break;
    }

}

/**
 * @brief Read a register from the MAX14830
 * @param uart_channel UART channel (0-3)  // FIXED: Added missing parameter
 * @param reg_addr Register address
 * @return Register value
 */
uint8_t MAX14830_ReadRegister(uint8_t uart_channel, uint8_t reg_addr)
{
    uint8_t command_byte = 0x00 |                           // Clear W/R bit for read (bit 7 = 0)
                          ((uart_channel & 0x03) << 5) |    // Set U1,U0 bits
                          (reg_addr & 0x1F);                // Set address bits A4-A0
    uint8_t result;

    Set_Expander_B_CS_State(Selected);
    hw_timer0_us(2);
    USART_SpiTransfer(USART4, command_byte);  // Send command byte
    result = USART_SpiTransfer(USART4, 0x00); // Read data byte (send dummy)
    Set_Expander_B_CS_State(Deselected);

    return result;
}

/**
 * @brief Send a character through MAX14830 UART1
 * @param character Character to send
 */
void MAX14830_SendChar(uint8_t expander, uint8_t uart_channel, char character)
{
    // Wait while TX FIFO is full (128 bytes max)
    // FIXED: Added uart_channel parameter to ReadRegister call
  //  while(MAX14830_ReadRegister(MAX14830_UART1, MAX14830_TXFIFOLVL_REG) >= 128);



      MAX14830_WriteRegister(expander, uart_channel, MAX14830_THR_REG, character);


}

/**
 * @brief Receive a character from MAX14830 UART1
 * @return Received character, or 0 if no data available
 */
uint8_t MAX14830_UART1_ReceiveChar(void)
{
    // Check if data is available in RX FIFO
    if(MAX14830_ReadRegister(MAX14830_UART1, MAX14830_RXFIFOLVL_REG) > 0)
    {
        return MAX14830_ReadRegister(MAX14830_UART1, MAX14830_RHR_REG);
    }
    return 0; // No data available
}

/**
 * @brief Check if MAX14830 UART1 has data available
 * @return 1 if data available, 0 if not
 */
uint8_t MAX14830_UART1_DataAvailable(void)
{
    return (MAX14830_ReadRegister(MAX14830_UART1, MAX14830_RXFIFOLVL_REG) > 0) ? 1 : 0;
}





/**
 * @brief Send a string through MAX14830 UART1
 * @param str Null-terminated string to send
 */
void MAX14830_SendString(uint8_t expander, uint8_t uart_channel, const char* str)
{
    while(*str)
    {
        MAX14830_SendChar(expander, uart_channel, *str);
        str++;
    }
}





/**
 * @brief Check for UART errors on MAX14830 UART1
 * @return Error flags from LSR register
 */
uint8_t MAX14830_UART1_GetErrors(void)
{
    uint8_t lsr = MAX14830_ReadRegister(MAX14830_UART1, MAX14830_LSR_REG);
    return lsr & (MAX14830_LSR_FRAMEERR | MAX14830_LSR_RXPARITYERR |
                  MAX14830_LSR_RXOVERRUN | MAX14830_LSR_RXBREAK);
}

/**
 * @brief Clear UART errors on MAX14830 UART1
 */
void MAX14830_UART1_ClearErrors(void)
{
    // Reading LSR register clears most error flags
    uint8_t temp = MAX14830_ReadRegister(MAX14830_UART1, MAX14830_LSR_REG);
    (void)temp; // Suppress unused variable warning

    // Clear any pending error interrupts
    temp = MAX14830_ReadRegister(MAX14830_UART1, MAX14830_ISR_REG);
    (void)temp;
}

