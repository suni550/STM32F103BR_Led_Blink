// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#include "SystemPeripherals_SPI.h"

// Imt.Base includes
#include <Imt.Base.Core.Diagnostics/Diagnostics.h>

//@{
// SPI module register structure
//@}
typedef struct {
    volatile uint16_t CR1;
    uint16_t  RESERVED0;
    volatile uint16_t CR2;
    uint16_t  RESERVED1;
    volatile uint16_t SR;
    uint16_t  RESERVED2;
    volatile uint16_t DR;
    uint16_t  RESERVED3;
    volatile uint16_t CRCPR;
    uint16_t  RESERVED4;
    volatile uint16_t RXCRCR;
    uint16_t  RESERVED5;
    volatile uint16_t TXCRCR;
    uint16_t  RESERVED6;
    volatile uint16_t I2SCFGR;
    uint16_t  RESERVED7;
    volatile uint16_t I2SPR;
    uint16_t  RESERVED8;
} SPI_ModuleRegisters;

//@{
// SPI CR1 mask
//@}
#define CR1_Clear_Mask                  ((uint16_t)0x3040)
#define CR1_SPE_Mask                    ((uint16_t)0x0040)

//@{
// SPI CR2 mask
//@}

//@{
// SPI I2SCFGR mask
//@}
#define I2SCFGR_I2SMOD_Reset_Mask       ((uint16_t)0xF7FF)

//@{
// SPI SR mask
//@}
#define SR_TXE_Mask                     ((uint16_t)0x0002)
#define SR_RXNE_Mask                    ((uint16_t)0x0001)
#define SR_BSY_Mask                     ((uint16_t)0x0080)

void SPI_Init(const SPI_ModuleAddress spiSel, const SPI_InitStruct* const pSpiInitStruct) {
    if (pSpiInitStruct == NULL) {
        ASSERT_DEBUG(false);
        return;
    }

    SPI_ModuleRegisters* const pSpiSel = (SPI_ModuleRegisters*)spiSel; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety

    //---------------------------- CR1 Configuration ---------------------------
    // Get the CR1 value
    uint16_t tempReg = pSpiSel->CR1;

    // Clear BIDIMODE, BIDIOE, DFF, RXONLY, SSM, SSI, LSBFIRST, BR[2:0], MSTR, CPOL and CPHA bits
    tempReg &= CR1_Clear_Mask;

    // Configure: direction, NSS management, first transmitted bit, BaudRate prescaler,
    // master/salve mode, CPOL and CPHA:
    // Set BIDIMODE, BIDIOE and RXONLY bits according to Direction value
    // Set SSM, SSI and MSTR bits according to Mode and pSpiInitStruct->SlaveSelectManagement values
    // Set LSBFirst bit according to pSpiInitStruct->FirstBit value
    // Set BR bits according to pSpiInitStruct->BaudRatePrescaler value
    // Set CPOL bit according to pSpiInitStruct->ClockPolarity value
    // Set CPHA bit according to pSpiInitStruct->ClockPhase value
    tempReg |= (  (uint16_t)pSpiInitStruct->Direction
                | (uint16_t)pSpiInitStruct->Mode
                | (uint16_t)pSpiInitStruct->DataFrameFormat
                | (uint16_t)pSpiInitStruct->ClockPolarity
                | (uint16_t)pSpiInitStruct->ClockPhase
                | (uint16_t)pSpiInitStruct->SlaveSelectManagement
                | (uint16_t)pSpiInitStruct->BaudRatePrescaler
                | (uint16_t)pSpiInitStruct->FirstBit);
    pSpiSel->CR1 = tempReg;

    // Activate the SPI mode
    pSpiSel->I2SCFGR &= I2SCFGR_I2SMOD_Reset_Mask;

    //---------------------------- CRCPOLY Configuration -----------------------
    pSpiSel->CRCPR = pSpiInitStruct->CRCPolynomial;
}

void SPI_SetState(const SPI_ModuleAddress spiSel, const bool enable) {
    SPI_ModuleRegisters* const pSpiSel = (SPI_ModuleRegisters*)spiSel; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    if (enable) {
        pSpiSel->CR1 |= CR1_SPE_Mask;
    }
    else {
        pSpiSel->CR1 &= (~CR1_SPE_Mask);
    }
}

void SPI_SetDmaState(const SPI_ModuleAddress spiSel, const SPI_DmaReq dmaReq, const bool enable) {
    SPI_ModuleRegisters* const pSpiSel = (SPI_ModuleRegisters*)spiSel; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    if (enable) {
        pSpiSel->CR2 |= (uint16_t)dmaReq;
    }
    else {
        pSpiSel->CR2 &= ~((uint16_t)dmaReq);
    }
}

bool SPI_IsTxBufferEmpty(const SPI_ModuleAddress spiSel) {
    const SPI_ModuleRegisters* const pSpiSel = (SPI_ModuleRegisters*)spiSel; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    return ((pSpiSel->SR & SR_TXE_Mask) != 0U);
}

bool SPI_IsRxBufferNotEmpty(const SPI_ModuleAddress spiSel) {
    const SPI_ModuleRegisters* const pSpiSel = (SPI_ModuleRegisters*)spiSel; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    return ((pSpiSel->SR & SR_RXNE_Mask) != 0U);
}

bool SPI_IsBusy(const SPI_ModuleAddress spiSel) {
    const SPI_ModuleRegisters* const pSpiSel = (SPI_ModuleRegisters*)spiSel; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    return ((pSpiSel->SR & SR_BSY_Mask) != 0U);
}

void SPI_SendData(const SPI_ModuleAddress spiSel, const uint16_t data) {
    SPI_ModuleRegisters* const pSpiSel = (SPI_ModuleRegisters*)spiSel; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    pSpiSel->DR = data;
}

uint16_t SPI_ReceiveData(const SPI_ModuleAddress spiSel) {
    const SPI_ModuleRegisters* const pSpiSel = (SPI_ModuleRegisters*)spiSel; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    return (pSpiSel->DR);
}
