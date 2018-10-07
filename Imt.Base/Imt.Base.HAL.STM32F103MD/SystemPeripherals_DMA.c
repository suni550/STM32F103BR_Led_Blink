// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#include "SystemPeripherals_DMA.h"

// Imt.Base includes
#include <Imt.Base.Core.Diagnostics/Diagnostics.h>

//@{
// DMA channel register structure
//@}
typedef struct {
    volatile uint32_t CCR;
    volatile uint32_t CNDTR;
    volatile uint32_t CPAR;
    volatile uint32_t CMAR;
} DMA_ChannelRegisters;

//@{
// DMA common registers structure
//@}
//lint -save
//lint -e754 // local structure member not referenced (offset required for correct register access)
typedef struct {
    volatile uint32_t ISR;
    volatile uint32_t IFCR;
} DMA_ModuleRegisters;
//lint -restore

//@{
// CCR clear register masks
//@}
#define CCR_CLEAR_Mask          ((uint32_t)0xFFFF800F)

//@{
// Bit definition for DMA CCR register
//@}
// Channel enable
#define  DMA_CCR_EN              ((uint16_t)0x0001)

void DMA_DeInit(const DMA_ChannelAddress dmaYChannelX) {
    DMA_ChannelRegisters* const pDmaYChannelX = (DMA_ChannelRegisters*)dmaYChannelX; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety

    // Disable the selected DMAy Channelx
    pDmaYChannelX->CCR &= (uint16_t)(~DMA_CCR_EN);

    // Reset DMAy Channelx control register
    pDmaYChannelX->CCR  = 0U;

    // Reset DMAy Channelx remaining bytes register
    pDmaYChannelX->CNDTR = 0U;

    // Reset DMAy Channelx peripheral address register
    pDmaYChannelX->CPAR  = 0U;

    // Reset DMAy Channelx memory address register
    pDmaYChannelX->CMAR = 0U;

    // Reset interrupt pending bits for DMAy Channelx
    if(dmaYChannelX == DMA_ChannelAddress_DMA1_Channel1) {
        DMA_ClearPendingInterrupt(DMA1_IrqFlag_Ch1_GL);
    }
    else if (dmaYChannelX == DMA_ChannelAddress_DMA1_Channel2) {
        DMA_ClearPendingInterrupt(DMA1_IrqFlag_Ch2_GL);
    }
    else if (dmaYChannelX == DMA_ChannelAddress_DMA1_Channel3) {
        DMA_ClearPendingInterrupt(DMA1_IrqFlag_Ch3_GL);
    }
    else if (dmaYChannelX == DMA_ChannelAddress_DMA1_Channel4) {
        DMA_ClearPendingInterrupt(DMA1_IrqFlag_Ch4_GL);
    }
    else if (dmaYChannelX == DMA_ChannelAddress_DMA1_Channel5) {
        DMA_ClearPendingInterrupt(DMA1_IrqFlag_Ch5_GL);
    }
    else {
        // nothing to do
    }
}

void DMA_Init(const DMA_ChannelAddress dmaYChannelX, const DMA_InitStruct* const pDmaInitStruct) {
    if (pDmaInitStruct == NULL) {
        ASSERT_DEBUG(false);
        return;
    }

    DMA_ChannelRegisters* const pDmaYChannelX = (DMA_ChannelRegisters*)dmaYChannelX; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety

    //----------------- DMAy Channelx CCR Configuration -----------------
    // Get the DMAy_Channelx CCR value
    uint32_t tmpreg = pDmaYChannelX->CCR;
    // Clear MEM2MEM, PL, MSIZE, PSIZE, MINC, PINC, CIRC and DIR bits
    tmpreg &= CCR_CLEAR_Mask;
    // Configure DMAy Channelx: data transfer, data size, priority level and mode
    // Set DIR bit according to pDmaInitStruct->DIR value
    // Set CIRC bit according to pDmaInitStruct->Mode value
    // Set PINC bit according to pDmaInitStruct->PeripheralInc value
    // Set MINC bit according to pDmaInitStruct->MemoryInc value
    // Set PSIZE bits according to pDmaInitStruct->PeripheralDataSize value
    // Set MSIZE bits according to pDmaInitStruct->MemoryDataSize value
    // Set PL bits according to pDmaInitStruct->Priority value
    // Set the MEM2MEM bit according to pDmaInitStruct->M2M value
    tmpreg |=   (uint32_t)pDmaInitStruct->DIR
              | (uint32_t)pDmaInitStruct->Mode
              | (uint32_t)pDmaInitStruct->PeripheralInc
              | (uint32_t)pDmaInitStruct->MemoryInc
              | (uint32_t)pDmaInitStruct->PeripheralDataSize
              | (uint32_t)pDmaInitStruct->MemoryDataSize
              | (uint32_t)pDmaInitStruct->Priority
              | (uint32_t)pDmaInitStruct->M2M;

    // Write to DMAy Channelx CCR
    pDmaYChannelX->CCR = tmpreg;

    //----------------- DMAy Channelx CNDTR Configuration ---------------
    // Write to DMAy Channelx CNDTR
    pDmaYChannelX->CNDTR = pDmaInitStruct->BufferSize;

    //----------------- DMAy Channelx CPAR Configuration ----------------
    // Write to DMAy Channelx CPAR
    pDmaYChannelX->CPAR = pDmaInitStruct->PeripheralBaseAddr;

    //----------------- DMAy Channelx CMAR Configuration ----------------
    // Write to DMAy Channelx CMAR
    pDmaYChannelX->CMAR = pDmaInitStruct->MemoryBaseAddr;
}

void DMA_Enable(const DMA_ChannelAddress dmaYChannelX, const bool doEnable) {
    DMA_ChannelRegisters* const pDmaYChannelX = (DMA_ChannelRegisters*)dmaYChannelX; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety

    if (doEnable) {
        // Enable the selected DMAy Channelx
        pDmaYChannelX->CCR |= DMA_CCR_EN;
    }
    else {
        // Disable the selected DMAy Channelx
        pDmaYChannelX->CCR &= (uint16_t)(~DMA_CCR_EN);
    }
}

void DMA_SetCurrDataCounter(const DMA_ChannelAddress dmaYChannelX, const uint16_t nrOfDataToTransfer) {
    DMA_ChannelRegisters* const pDmaYChannelX = (DMA_ChannelRegisters*)dmaYChannelX; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    pDmaYChannelX->CNDTR = nrOfDataToTransfer;
}

void DMA_SetMemoryBaseAddress(const DMA_ChannelAddress dmaYChannelX, const uint32_t memoryBaseAddr) {
    DMA_ChannelRegisters* const pDmaYChannelX = (DMA_ChannelRegisters*)dmaYChannelX; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    pDmaYChannelX->CMAR = memoryBaseAddr;
}

void DMA_EnableInterrupt(const DMA_ChannelAddress dmaYChannelX, const DMA_Irq irq, const bool doEnable) {
    DMA_ChannelRegisters* const pDmaYChannelX = (DMA_ChannelRegisters*)dmaYChannelX; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    if (doEnable) {
        pDmaYChannelX->CCR |= (uint32_t)irq;
    }
    else {
        pDmaYChannelX->CCR &= ~((uint32_t)irq);
    }
}

void DMA_ClearPendingInterrupt(const DMA_IrqFlag irqFlag) {
    DMA_ModuleRegisters* const pDMA1 = (DMA_ModuleRegisters*)DMA1_BASE; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    pDMA1->IFCR = (uint32_t)irqFlag;
}
