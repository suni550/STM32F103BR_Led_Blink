// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#ifndef SYSTEMPERIPHERALS_USART_H
#define SYSTEMPERIPHERALS_USART_H

// Must be very first include
#include <Imt.Base.Core.Platform/Platform.h>

// Project includes
#include "SystemMemoryMap.h"

// Determine if a C++ compiler is being used.  If so, ensure that standard C is used to process the API information.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//@{
// Universal synchronous asynchronous receiver transmitter (USART).
//
// Reference: ST_CortexM3_STM32F103_TRM_Rev15.pdf Chapter 27
// Reference: ST_CortexM3_STM32F103_Datasheet_Rev16.pdf Chapter 2.3.17
// @author lbreitenmoser
//@}

//@{
// Enumeration of the available I2C modules
//@}
typedef enum {
    USART_ModuleAddress_USART1 = USART1_BASE,
    USART_ModuleAddress_USART2 = USART2_BASE,
    USART_ModuleAddress_USART3 = USART3_BASE
} USART_ModuleAddress;

//@{
// Enumeration of the supported data bit types
//@}
typedef enum {
    USART_DataBits_8b = ((uint16_t)0x0000),
    USART_DataBits_9b = ((uint16_t)0x1000)
} USART_DataBits;

//@{
// Enumeration of the supported stop bits
//@}
typedef enum {
    USART_StopBits_1   = ((uint16_t)0x0000),
    USART_StopBits_0_5 = ((uint16_t)0x1000),
    USART_StopBits_2   = ((uint16_t)0x2000),
    USART_StopBits_1_5 = ((uint16_t)0x3000)
} USART_StopBits;

//@{
// Enumeration of the supported parity modes
//@}
typedef enum {
    USART_Parity_No   = ((uint16_t)0x0000),
    USART_Parity_Even = ((uint16_t)0x0400),
    USART_Parity_Odd  = ((uint16_t)0x0600)
} USART_Parity;

//@{
// Enumeration of the supported USART modes
//@}
typedef enum {
    USART_Mode_Rx = ((uint16_t)0x0004),
    USART_Mode_Tx = ((uint16_t)0x0008),
    USART_Mode_RxTx = ((uint16_t)(USART_Mode_Rx | USART_Mode_Tx))
} USART_Mode;

//@{
// Enumeration of the supported  hardware flow control modes
//@}
typedef enum {
    USART_HardwareFlowControl_None    = ((uint16_t)0x0000),
    USART_HardwareFlowControl_RTS     = ((uint16_t)0x0100),
    USART_HardwareFlowControl_CTS     = ((uint16_t)0x0200),
    USART_HardwareFlowControl_RTS_CTS = ((uint16_t)0x0300)
} USART_HardwareFlowControl;

//@{
// Enumeration of the available USART interrupts.
//@}
typedef enum {
    USART_Irq_CR1_IDLE = ((uint16_t)0x0010),
    USART_Irq_CR1_RXNE = ((uint16_t)0x0020),
    USART_Irq_CR1_TC   = ((uint16_t)0x0040),
    USART_Irq_CR1_TXE  = ((uint16_t)0x0080),
    USART_Irq_CR1_PE   = ((uint16_t)0x0100),
    USART_Irq_CR3_ERR  = ((uint16_t)0x0001),
    USART_Irq_CR3_CTS  = ((uint16_t)0x0400)
} USART_Irq;

//@{
// USART init structure definition
//@}
typedef struct {
    // This member configures the USART communication baud rate.
    // The baud rate is computed using the following formula :
    // -IntegerDivider = ((PCLKx) / (16 * (USART_InitStruct->USART_BaudRate)))
    // - FractionalDivider = ((IntegerDivider - ((u32)IntegerDivider)) * 16) + 0.5
    uint32_t BaudRate;

    // Specifies the number of data bits transmitted or received in a frame
    USART_DataBits DataBits;

    // Specifies the number of stop bits transmitted.
    USART_StopBits StopBits;

    // Specifies the parity mode.
    // @note When parity is enabled, the computed parity is inserted
    // at the MSB position of the transmitted data(9th bit when
    // the word length is set to 9 data bits; 8th bit when the
    // word length is set to 8 data bits)
    USART_Parity Parity;

    // Specifies whether the Receive or Transmit mode is enabled or disabled.
    USART_Mode Mode;

    // Specifies whether the hardware flow control mode is enabled or disabled.
    USART_HardwareFlowControl HardwareFlowControl;
} USART_InitStruct;


//@ {
// Deinitializes the USARTx peripheral registers to their default reset values.
//@ }
void USART_DeInit(const USART_ModuleAddress usartModule);

//@ {
// Initializes the specified USART peripheral according to the specified parameters in the pUsartInitStruct.
// @param usartModule: Select the USART peripheral.
// @param pUsartInitStruct: Pointer to a USART_InitStruct
//                        structure that contains the configuration information for the
//                        specified USART peripheral.
//@ }
void USART_Init(const USART_ModuleAddress usartModule, const USART_InitStruct* const pUsartInitStruct);

//@ {
// Enables or disables the specified USART peripheral.
// @param timerModule: Select the USART peripheral.
// @param doEnable: true TIM would be enabled
//                   false TIM would be disabled
//@ }
void USART_Enable(const USART_ModuleAddress usartModule, const bool doEnable);

//@{
// Enables or disables the specified USART interrupts.
// @param usartModule: Select the USART peripheral.
// @param irq: Specifies the USART interrupts sources to be enabled or disabled.
// @param doEnable: true interrupt would be enabled
//                  false interrupt channel would be disabled
//@}
void USART_EnableInterrupt(const USART_ModuleAddress usartModule, const USART_Irq irq, const bool doEnable);

//@ {
// Transmits single data through the selected peripheral.
// @param usartModule: Select the USART peripheral.
// @param data: the data to transmit.
//@ }
void USART_SendData(const USART_ModuleAddress usartModule, uint16_t data);

//@ {
// Returns the most recent received data by the selected peripheral.
// @param usartModule: Select the USART peripheral.
// @return data: The received data.
//@ }
uint16_t USART_ReceiveData(const USART_ModuleAddress usartModule);

//@ {
// Returns true if data is received and ready to read.
//@ }
bool USART_IsReadDataRegisterNotEmpty(const USART_ModuleAddress usartModule);

//@ {
// Returns true if if the transmission of the last data is completed.
//@ }
bool USART_IsTransmissionComplete(const USART_ModuleAddress usartModule);

//@ {
// Returns true if if a new byte can be send.
//@ }
bool USART_IsTransmitDataRegisterEmpty(const USART_ModuleAddress usartModule);
void USART2_IT(const USART_ModuleAddress usartModule);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // #ifndef SYSTEMPERIPHERALS_USART_H
