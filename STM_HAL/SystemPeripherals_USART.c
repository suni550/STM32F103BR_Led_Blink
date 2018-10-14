// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#include "SystemPeripherals_USART.h"

// Imt.Base includes
#include <Imt.Base.Core.Diagnostics/Diagnostics.h>

// Project includes
#include "SystemPeripherals_RCC.h"

//@{
// Universal synchronous asynchronous receiver transmitter module register structure (USART1..USART3)
//@}
typedef struct {
    volatile uint16_t SR;
    uint16_t  RESERVED0;
    volatile uint16_t DR;
    uint16_t  RESERVED1;
    volatile uint16_t BRR;
    uint16_t  RESERVED2;
    volatile uint16_t CR1;
    uint16_t  RESERVED3;
    volatile uint16_t CR2;
    uint16_t  RESERVED4;
    volatile uint16_t CR3;
    uint16_t  RESERVED5;
    volatile uint16_t GTPR;
    uint16_t  RESERVED6;
} USART_ModuleRegisters;

//@{
// USART CR1 bit definitions
//@}
// USART CR1 Mask
#define CR1_CLEAR_Mask            ((uint16_t)0xE9F3)
// USART OverSampling-8 Mask
#define CR1_OVER8_Set             ((uint16_t)0x8000)
// USART CR1 Mask
#define CR1_UE_Mask               ((uint16_t)0x2000)

//@{
// USART CR2 bit definitions
//@}
// USART CR2 STOP Bits Mask
#define CR2_STOP_CLEAR_Mask       ((uint16_t)0xCFFF)

//@{
// USART CR3 bit definitions
//@}
// USART CR3 Mask
#define CR3_CLEAR_Mask            ((uint16_t)0xFCFF)

//@{
// USART SR bit definitions
//@}
#define SR_RXNE                   ((uint16_t)0x0020)
#define SR_TC                     ((uint16_t)0x0040)
#define SR_TXE                    ((uint16_t)0x0080)

void USART_DeInit(const USART_ModuleAddress usartModule) {
    switch (usartModule) {
        case USART_ModuleAddress_USART1:
            RCC_ResetAPB2Peripheral(RCC_APB2Periph_USART1, true);
            RCC_ResetAPB2Peripheral(RCC_APB2Periph_USART1, false);
            break;
        case USART_ModuleAddress_USART2:
            RCC_ResetAPB1Peripheral(RCC_APB1Periph_USART2, true);
            RCC_ResetAPB1Peripheral(RCC_APB1Periph_USART2, false);
            break;
        case USART_ModuleAddress_USART3:
            RCC_ResetAPB1Peripheral(RCC_APB1Periph_USART3, true);
            RCC_ResetAPB1Peripheral(RCC_APB1Periph_USART3, false);
            break;
        default:
            ASSERT_DEBUG(false);
            break;
    }
}

void USART_Init(const USART_ModuleAddress usartModule, const USART_InitStruct* const pUsartInitStruct) {
    if (pUsartInitStruct == NULL) {
       // ASSERT_DEBUG(false);
        return;
    }

    USART_ModuleRegisters* const pUsart = (USART_ModuleRegisters*)usartModule;

    // USART CR2 Configuration
    uint32_t tmpreg = pUsart->CR2;
    // Clear STOP[13:12] bits
    tmpreg &= CR2_STOP_CLEAR_Mask;
    // Configure the USART Stop Bits, Clock, CPOL, CPHA and LastBit
    // Set STOP[13:12] bits according to StopBits value
    tmpreg |= (uint32_t)pUsartInitStruct->StopBits;
    // Write to USART CR2
    pUsart->CR2 = (uint16_t)tmpreg;

    // USART CR1 Configuration
    tmpreg = pUsart->CR1;
    // Clear M, PCE, PS, TE and RE bits
    tmpreg &= CR1_CLEAR_Mask;
    // Configure the USART Word Length, Parity and mode
    // Set the M bits according to DataBits value
    // Set PCE and PS bits according to Parity value
    // Set TE and RE bits according to Mode value
    tmpreg |= (uint32_t)pUsartInitStruct->DataBits
              | pUsartInitStruct->Parity
              | pUsartInitStruct->Mode;
    // Write to USART CR1
    pUsart->CR1 = (uint16_t)tmpreg;

    // USART CR3 Configuration
    tmpreg = pUsart->CR3;
    // Clear CTSE and RTSE bits */
    tmpreg &= CR3_CLEAR_Mask;
    // Configure the USART HFC
    // Set CTSE and RTSE bits according to USART_HardwareFlowControl value
    tmpreg |= pUsartInitStruct->HardwareFlowControl;
    // Write to USART CR3
    pUsart->CR3 = (uint16_t)tmpreg;

    // USART BRR Configuration
    // Configure the USART Baud Rate
    RCC_Clocks rccClock = RCC_GetClocksFreq();
    uint32_t apbClock = 0x00;
    if (usartModule == USART_ModuleAddress_USART1) {
        apbClock = rccClock.PCLK2_Frequency;
    }
    else {
        apbClock = rccClock.PCLK1_Frequency;
    }

    // Determine the integer part
    uint32_t integerDivider = 0U;
    if ((pUsart->CR1 & CR1_OVER8_Set) != 0) {
        // Integer part computing in case Oversampling mode is 8 Samples
        integerDivider = ((25 * apbClock) / (2 * (pUsartInitStruct->BaudRate)));
    }
    else {
        // Integer part computing in case Oversampling mode is 16 Samples
        integerDivider = ((25 * apbClock) / (4 * (pUsartInitStruct->BaudRate)));
    }
    tmpreg = (integerDivider / 100) << 4;

    // Determine the fractional part
    uint32_t fractionalDivider = integerDivider - (100 * (tmpreg >> 4));

    // Implement the fractional part in the register */
    if ((pUsart->CR1 & CR1_OVER8_Set) != 0) {
        tmpreg |= ((((fractionalDivider * 8) + 50) / 100)) & ((uint8_t)0x07);
    }
    else {
        tmpreg |= ((((fractionalDivider * 16) + 50) / 100)) & ((uint8_t)0x0F);
    }

    // Write to USART BRR
    pUsart->BRR = (uint16_t)tmpreg;
}

void USART_Enable(const USART_ModuleAddress usartModule, const bool doEnable) {
    USART_ModuleRegisters* const pUsart = (USART_ModuleRegisters*)usartModule;
    if (doEnable) {
        pUsart->CR1 |= CR1_UE_Mask;
    }
    else {
        pUsart->CR1 &= ~(CR1_UE_Mask);
    }
}

void USART_EnableInterrupt(const USART_ModuleAddress usartModule, const USART_Irq irq, const bool doEnable) {
    USART_ModuleRegisters* const pUsart = (USART_ModuleRegisters*)usartModule;
    switch (irq) {
        case USART_Irq_CR1_PE: // fall through
        case USART_Irq_CR1_TXE: // fall through
        case USART_Irq_CR1_TC: // fall through
        case USART_Irq_CR1_RXNE: // fall through
        case USART_Irq_CR1_IDLE:
            if (doEnable) {
                pUsart->CR1 |= (uint32_t)(irq);
            }
            else {
                pUsart->CR1 &= ~((uint32_t)(irq));
            }
            break;
        case USART_Irq_CR3_CTS: // fall through
        case USART_Irq_CR3_ERR:
            if (doEnable) {
                pUsart->CR3 |= (uint32_t)(irq);
            }
            else {
                pUsart->CR3 &= ~((uint32_t)(irq));
            }
            break;
        default:
           // ASSERT_DEBUG(false);
            break;
    }
}

void USART_SendData(const USART_ModuleAddress usartModule, uint16_t data) {
    USART_ModuleRegisters* const pUsart = (USART_ModuleRegisters*)usartModule;
    pUsart->DR = (data & (uint16_t)0x01FF);
}

uint16_t USART_ReceiveData(const USART_ModuleAddress usartModule) {
    USART_ModuleRegisters* const pUsart = (USART_ModuleRegisters*)usartModule;
    return (uint16_t)(pUsart->DR & (uint16_t)0x01FF);
}

bool USART_IsReadDataRegisterNotEmpty(const USART_ModuleAddress usartModule) {
    USART_ModuleRegisters* const pUsart = (USART_ModuleRegisters*)usartModule;
    return ((pUsart->SR & SR_RXNE) != 0U);
}

bool USART_IsTransmissionComplete(const USART_ModuleAddress usartModule) {
    USART_ModuleRegisters* const pUsart = (USART_ModuleRegisters*)usartModule;
    return ((pUsart->SR & SR_TC) != 0U);
}

bool USART_IsTransmitDataRegisterEmpty(const USART_ModuleAddress usartModule) {
    USART_ModuleRegisters* const pUsart = (USART_ModuleRegisters*)usartModule;
    return ((pUsart->SR & SR_TXE) != 0U);
}