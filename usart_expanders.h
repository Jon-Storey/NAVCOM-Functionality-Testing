/**
 * @file max14830.h
 * @brief MAX14830 Quad UART SPI Interface Driver for EFM32GG11B
 * @author Generated Code
 * @date 2025
 * @version 1.0
 *
 * This header provides a complete interface for the MAX14830 quad UART expander
 * optimized for 4MHz crystal operation with the EFM32GG11B microcontroller.
 */

#ifndef USART_EXPANDERS_H
#define USART_EXPANDERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*==============================================================================
 * INCLUDES
 *============================================================================*/
#include <stdint.h>
#include <stdbool.h>

/*==============================================================================
 * MAX14830 REGISTER DEFINITIONS
 *============================================================================*/

/* MAX14830 Register Addresses */
#define MAX14830_RHR_REG        0x00  /**< Receive Holding Register (Read) */
#define MAX14830_THR_REG        0x00  /**< Transmit Holding Register (Write) */
#define MAX14830_IRQEN_REG      0x01  /**< Interrupt Enable Register */
#define MAX14830_ISR_REG        0x02  /**< Interrupt Status Register */
#define MAX14830_LSRINTEN_REG   0x03  /**< LSR Interrupt Enable Register */
#define MAX14830_LSR_REG        0x04  /**< LSR Status Register */
#define MAX14830_SPCLCHRINT_REG 0x05  /**< Special Character Interrupt Enable Register */
#define MAX14830_SPCLCHRSTS_REG 0x06  /**< Special Character Status Register */
#define MAX14830_STSINTEN_REG   0x07  /**< Status Interrupt Enable Register */
#define MAX14830_STSINT_REG     0x08  /**< Status Interrupt Register */
#define MAX14830_MODE1_REG      0x09  /**< Mode 1 Register */
#define MAX14830_MODE2_REG      0x0A  /**< Mode 2 Register */
#define MAX14830_LCR_REG        0x0B  /**< Line Control Register */
#define MAX14830_RXIMEOUT_REG   0x0C  /**< RX Timeout Register */
#define MAX14830_HDPLXDELAY_REG 0x0D  /**< Half Duplex Delay Register */
#define MAX14830_IRDA_REG       0x0E  /**< IrDA Register */
#define MAX14830_FLOWLVL_REG    0x0F  /**< Flow Control Level Register */
#define MAX14830_FIFOTRIGLVL_REG 0x10 /**< FIFO Trigger Level Register */
#define MAX14830_TXFIFOLVL_REG  0x11  /**< Transmit FIFO Level Register */
#define MAX14830_RXFIFOLVL_REG  0x12  /**< Receive FIFO Level Register */
#define MAX14830_FLOWCTRL_REG   0x13  /**< Flow Control Register */
#define MAX14830_XON1_REG       0x14  /**< XON1 Character Register */
#define MAX14830_XON2_REG       0x15  /**< XON2 Character Register */
#define MAX14830_XOFF1_REG      0x16  /**< XOFF1 Character Register */
#define MAX14830_XOFF2_REG      0x17  /**< XOFF2 Character Register */
#define MAX14830_GPIOCONFIG_REG 0x18  /**< GPIO Configuration Register */
#define MAX14830_GPIODATA_REG   0x19  /**< GPIO Data Register */
#define MAX14830_PLLCFG_REG     0x1A  /**< PLL Configuration Register */
#define MAX14830_BRGCFG_REG     0x1B  /**< Baud Rate Generator Configuration Register */
#define MAX14830_DIVLSB_REG     0x1C  /**< Divisor LSB Register */
#define MAX14830_DIVMSB_REG     0x1D  /**< Divisor MSB Register */
#define MAX14830_CLKSRC_REG     0x1E  /**< Clock Source Register */
#define MAX14830_GLOBALIRQ_REG  0x1F  /**< Global IRQ Register */
#define MAX14830_GLOBALCMD_REG  0x1F  /**< Global Command Register */

/* Global Registers */
#define MAX14830_TXSYNCH_REG    0x20  /**< TX Synchronization Register */
#define MAX14830_SYNCHDELAY1_REG 0x21 /**< Synchronization Delay 1 Register */
#define MAX14830_SYNCHDELAY2_REG 0x22 /**< Synchronization Delay 2 Register */
#define MAX14830_TIMER1_REG     0x23  /**< Timer 1 Register */
#define MAX14830_TIMER2_REG     0x24  /**< Timer 2 Register */
#define MAX14830_REVID_REG      0x25  /**< Revision ID Register */

/*==============================================================================
 * MAX14830 BIT FIELD DEFINITIONS
 *============================================================================*/

  /* IRQEn Register (0x01) Bit Definitions */
  #define MAX14830_IRQEN_CTSIEN           (1 << 7)  /**< CTS Interrupt Enable */
  #define MAX14830_IRQEN_RFIFOEMTYIEN     (1 << 6)  /**< RX FIFO Empty Interrupt Enable */
  #define MAX14830_IRQEN_TFIFOEMTYIEN     (1 << 5)  /**< TX FIFO Empty Interrupt Enable */
  #define MAX14830_IRQEN_TFIFOTRGIEN      (1 << 4)  /**< TX FIFO Trigger Interrupt Enable */
  #define MAX14830_IRQEN_RFIFOTRGIEN      (1 << 3)  /**< RX FIFO Trigger Interrupt Enable */
  #define MAX14830_IRQEN_STSIEN           (1 << 2)  /**< Status Interrupt Enable */
  #define MAX14830_IRQEN_SPCLCHRIEN       (1 << 1)  /**< Special Character Interrupt Enable */
  #define MAX14830_IRQEN_LSRERRIEN        (1 << 0)  /**< LSR Error Interrupt Enable */

  /* LSR Register (0x04) Bit Definitions */
  #define MAX14830_LSR_CTSBIT             (1 << 7)  /**< CTS Bit */
  #define MAX14830_LSR_RXNOISE            (1 << 5)  /**< RX Noise */
  #define MAX14830_LSR_RXBREAK            (1 << 4)  /**< RX Break */
  #define MAX14830_LSR_FRAMEERR           (1 << 3)  /**< Frame Error */
  #define MAX14830_LSR_RXPARITYERR        (1 << 2)  /**< RX Parity Error */
  #define MAX14830_LSR_RXOVERRUN          (1 << 1)  /**< RX Overrun */
  #define MAX14830_LSR_RTIMEOUT           (1 << 0)  /**< RX Timeout */

  /* LSRIntEn Register (0x03) Bit Definitions */
  #define MAX14830_LSRINTEN_RXNOISEIEN    (1 << 5)  /**< RX Noise Interrupt Enable */
  #define MAX14830_LSRINTEN_RBREAKIEN     (1 << 4)  /**< RX Break Interrupt Enable */
  #define MAX14830_LSRINTEN_FRAMEERRIEN   (1 << 3)  /**< Frame Error Interrupt Enable */
  #define MAX14830_LSRINTEN_PARITYIEN     (1 << 2)  /**< Parity Error Interrupt Enable */
  #define MAX14830_LSRINTEN_ROVERRIEN     (1 << 1)  /**< RX Overrun Interrupt Enable */
  #define MAX14830_LSRINTEN_RTIMEOUTIEN   (1 << 0)  /**< RX Timeout Interrupt Enable */

  /* MODE2 Register (0x0A) Bit Definitions */
  #define MAX14830_MODE2_ECHOSUPRS        (1 << 7)  /**< Echo Suppress */
  #define MAX14830_MODE2_MULTIDROP        (1 << 6)  /**< Multi-Drop */
  #define MAX14830_MODE2_LOOPBACK         (1 << 5)  /**< Loopback */
  #define MAX14830_MODE2_SPECIALCHR       (1 << 4)  /**< Special Character */
  #define MAX14830_MODE2_RXEMTYINV        (1 << 3)  /**< RX Empty Invert */
  #define MAX14830_MODE2_RXTRGINV         (1 << 2)  /**< RX Trigger Invert */
  #define MAX14830_MODE2_FIFORST          (1 << 1)  /**< FIFO Reset */
  #define MAX14830_MODE2_RST              (1 << 0)  /**< Reset */

  /* LCR Register (0x0B) Bit Definitions */
  #define MAX14830_LCR_RTSBIT             (1 << 7)  /**< RTS Bit */
  #define MAX14830_LCR_TXBREAK            (1 << 6)  /**< TX Break */
  #define MAX14830_LCR_FORCEPARITY        (1 << 5)  /**< Force Parity */
  #define MAX14830_LCR_EVENPARITY         (1 << 4)  /**< Even Parity */
  #define MAX14830_LCR_PARITYEN           (1 << 3)  /**< Parity Enable */
  #define MAX14830_LCR_STOPBITS           (1 << 2)  /**< Stop Bits */
  #define MAX14830_LCR_LENGTH1            (1 << 1)  /**< Length Bit 1 */
  #define MAX14830_LCR_LENGTH0            (1 << 0)  /**< Length Bit 0 */

  /* Word Length Definitions */
  #define MAX14830_LCR_WORD_LEN_5         0x00      /**< 5-bit word length */
  #define MAX14830_LCR_WORD_LEN_6         0x01      /**< 6-bit word length */
  #define MAX14830_LCR_WORD_LEN_7         0x02      /**< 7-bit word length */
  #define MAX14830_LCR_WORD_LEN_8         0x03      /**< 8-bit word length */

  /* CLKSource Register (0x1E) Bit Definitions - CORRECTED VALUES */
  #define MAX14830_CLKSOURCE_CLKTORTS     (1 << 7)  /**< Clock to RTS */
  #define MAX14830_CLKSOURCE_PLLBYPASS    (1 << 3)  /**< PLL Bypass */
  #define MAX14830_CLKSOURCE_PLLEN        (1 << 2)  /**< PLL Enable */
  #define MAX14830_CLKSOURCE_CRYSTALEN    (1 << 1)  /**< Crystal Enable */

  /* STSInt Register (0x08) Bit Definitions */
  #define MAX14830_STSINT_CLKREADY        (1 << 5)  /**< Clock Ready Interrupt */
  #define MAX14830_STSINT_GPI3INT         (1 << 3)  /**< GPI3 Interrupt */
  #define MAX14830_STSINT_GPI2INT         (1 << 2)  /**< GPI2 Interrupt */
  #define MAX14830_STSINT_GPI1INT         (1 << 1)  /**< GPI1 Interrupt */
  #define MAX14830_STSINT_GPI0INT         (1 << 0)  /**< GPI0 Interrupt */

  /* FIFOTrgLvl Register (0x10) Bit Definitions */
  #define MAX14830_FIFOTRIG_RX_MASK       0xF0      /**< RX Trigger Level Mask */
  #define MAX14830_FIFOTRIG_TX_MASK       0x0F      /**< TX Trigger Level Mask */
  #define MAX14830_FIFOTRIG_RX_SHIFT      4         /**< RX Trigger Level Shift */
  #define MAX14830_FIFOTRIG_TX_SHIFT      0         /**< TX Trigger Level Shift */

  /* Default Reset Values */
  #define MAX14830_REVID_DEFAULT          0xB4      /**< Revision ID Default */

  /* MAX14830 UART Channel Selection */
  #define MAX14830_UART0          0x00  /**< UART Channel 0 */
  #define MAX14830_UART1          0x01  /**< UART Channel 1 */
  #define MAX14830_UART2          0x02  /**< UART Channel 2 */
  #define MAX14830_UART3          0x03  /**< UART Channel 3 */

  /* SPI Configuration */
  #define MAX14830_SPI_WRITE      0x80  /**< Write bit for SPI command */
  #define MAX14830_SPI_READ       0x00  /**< Read bit for SPI command */


  #define EXPANDER_A  1
  #define EXPANDER_B  2
  #define EXPANDER_C  3


/*==============================================================================
 * FUNCTION PROTOTYPES
 *============================================================================*/

/**
 * @defgroup MAX14830_Low_Level Low Level SPI Functions
 * @brief Basic register read/write operations
 * @{
 */

/**
 * @brief Write a register on the MAX14830
 * @param uart_channel UART channel (0-3)
 * @param reg_addr Register address (0x00-0x25)
 * @param data Data to write
 */
void MAX14830_WriteRegister(uint8_t expander, uint8_t uart_channel, uint8_t reg_addr, char data);

/**
 * @brief Read a register from the MAX14830
 * @param uart_channel UART channel (0-3)
 * @param reg_addr Register address (0x00-0x25)
 * @return Register value
 */
uint8_t MAX14830_ReadRegister(uint8_t uart_channel, uint8_t reg_addr);

/** @} */

/**
 * @defgroup MAX14830_Init Initialization Functions
 * @brief UART initialization and configuration
 * @{
 */

/**
 * @brief Complete initialization function for MAX14830 UART1 with 4MHz crystal
 * @note Configures UART1 for 9600 baud, 8N1 format with standard settings
 */
void MAX14830_UART_Init(uint8_t expander);

/**
 * @brief Initialize UART1 with custom baud rate (4MHz crystal optimized)
 * @param baudRate Desired baud rate (1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200)
 */
void MAX14830_UART1_InitWithBaud(uint32_t baudRate);

/**
 * @brief Check if MAX14830 UART1 is ready for operation
 * @return 1 if ready, 0 if not ready
 */
uint8_t MAX14830_UART1_IsReady(void);

/** @} */

/**
 * @defgroup MAX14830_Data Data Transmission Functions
 * @brief Character and string transmission functions
 * @{
 */

/**
 * @brief Send a character through MAX14830 UART1
 * @param character Character to send (0x00-0xFF)
 */
void MAX14830_UART1_SendChar(char character);

/**
 * @brief Receive a character from MAX14830 UART1
 * @return Received character, or 0 if no data available
 */
uint8_t MAX14830_UART1_ReceiveChar(void);

/**
 * @brief Send a null-terminated string through MAX14830 UART1
 * @param str Pointer to null-terminated string to send
 */
void MAX14830_UART1_SendString(const char* str);

/** @} */

/**
 * @defgroup MAX14830_Status Status and Error Functions
 * @brief Data availability and error checking functions
 * @{
 */

/**
 * @brief Check if MAX14830 UART1 has data available to read
 * @return 1 if data available, 0 if no data
 */
uint8_t MAX14830_UART1_DataAvailable(void);

/**
 * @brief Check for UART errors on MAX14830 UART1
 * @return Error flags from LSR register (frame, parity, overrun, break errors)
 */
uint8_t MAX14830_UART1_GetErrors(void);

/**
 * @brief Clear UART errors on MAX14830 UART1
 * @note Clears error flags by reading status registers
 */
void MAX14830_UART1_ClearErrors(void);

/** @} */

/**
 * @defgroup MAX14830_Utility Utility Functions
 * @brief Helper functions for baud rate calculation and diagnostics
 * @{
 */

/**
 * @brief Get recommended divisor values for common baud rates with 4MHz crystal
 * @param baudRate Desired baud rate
 * @return Divisor value (0 if baud rate not recommended/supported)
 */
uint16_t MAX14830_GetDivisorFor4MHz(uint32_t baudRate);

/** @} */

/*==============================================================================
 * CONFIGURATION MACROS
 *============================================================================*/

/**
 * @defgroup MAX14830_Config Configuration Macros
 * @brief Compile-time configuration options
 * @{
 */

/** @brief Enable debug output for MAX14830 operations */
#ifndef MAX14830_DEBUG_ENABLE
#define MAX14830_DEBUG_ENABLE   0
#endif

/** @brief Default UART channel for single-channel applications */
#ifndef MAX14830_DEFAULT_UART
#define MAX14830_DEFAULT_UART   MAX14830_UART1
#endif

/** @brief Default baud rate for initialization */
#ifndef MAX14830_DEFAULT_BAUD
#define MAX14830_DEFAULT_BAUD   9600
#endif

/** @brief Crystal frequency in Hz */
#ifndef MAX14830_CRYSTAL_FREQ
#define MAX14830_CRYSTAL_FREQ   4000000UL
#endif

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* MAX14830_H */
