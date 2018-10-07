// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#ifndef SYSTEMPERIPHERALS_DMA_H
#define SYSTEMPERIPHERALS_DMA_H

// Must be very first include
#include <Imt.Base.Core.Platform/Platform.h>

// Project includes
#include "SystemMemoryMap.h"

// Determine if a C++ compiler is being used.  If so, ensure that standard C is used to process the API information.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//@{
// Direct memory access (DMA) is used in order to provide high-speed data transfer between peripherals and memory as well as memory to memory.
// Data can be quickly moved by DMA without any CPU actions. This keeps CPU resources free for other operations.
//
// Reference: ST_CortexM3_STM32F103_TRM_Rev15.pdf Chapter 13
// @author lbreitenmoser
//@}

//@{
// Enumeration of the available DMA channels
//@}
typedef enum {
    DMA_ChannelAddress_DMA1_Channel1 = DMA1_Channel1_BASE,
    DMA_ChannelAddress_DMA1_Channel2 = DMA1_Channel2_BASE,
    DMA_ChannelAddress_DMA1_Channel3 = DMA1_Channel3_BASE,
    DMA_ChannelAddress_DMA1_Channel4 = DMA1_Channel4_BASE,
    DMA_ChannelAddress_DMA1_Channel5 = DMA1_Channel5_BASE
} DMA_ChannelAddress;

//@{
// DMA data transfer direction
//@}
typedef enum {
    DMA_DIR_PeripheralSRC = ((uint32_t)0x00000000),
    DMA_DIR_PeripheralDST = ((uint32_t)0x00000010)
} DMA_DatatTransferDir;

//@{
// DMA peripheral increment mode
//@}
typedef enum {
    DMA_PeripheralInc_Disable = ((uint32_t)0x00000000)
} DMA_PeripheralInc;

//@{
// DMA memory increment mode
//@}
typedef enum {
    DMA_MemoryInc_Enable = ((uint32_t)0x00000080)
} DMA_MemoryInc;

//@{
// DMA peripheral data size
//@}
typedef enum {
    DMA_PeripheralDataSize_Byte     = ((uint32_t)0x00000000),
    DMA_PeripheralDataSize_HalfWord = ((uint32_t)0x00000100),
    DMA_PeripheralDataSize_Word     = ((uint32_t)0x00000200)
} DMA_PeripheralDataSize;

//@{
// DMA memory data size
//@}
typedef enum {
    DMA_MemoryDataSize_Byte     = ((uint32_t)0x00000000),
    DMA_MemoryDataSize_HalfWord = ((uint32_t)0x00000400),
    DMA_MemoryDataSize_Word     = ((uint32_t)0x00000800)
} DMA_MemoryDataSize;

//@{
// DMA mode
//@}
typedef enum {
    DMA_Mode_Normal   = ((uint32_t)0x00000000),
    DMA_Mode_Circular = ((uint32_t)0x00000020)
} DMA_Mode;

//@{
// DMA priority level
//@}
typedef enum {
    DMA_Priority_VeryHigh = ((uint32_t)0x00003000),
    DMA_Priority_High     = ((uint32_t)0x00002000),
    DMA_Priority_Medium   = ((uint32_t)0x00001000),
    DMA_Priority_Low      = ((uint32_t)0x00000000)
} DMA_Priority;

//@{
// DMA memory to memory
//@}
typedef enum {
    DMA_M2M_Disable = ((uint32_t)0x00000000)
} DMA_M2M;

//@{
// Enumeration of the available DMA channel interrupts
//@}
typedef enum {
    DMA_Irq_TransferComplete     = ((uint32_t)0x00000002),
    DMA_Irq_HalfTransferComplete = ((uint32_t)0x00000004),
    DMA_Irq_TransferError        = ((uint32_t)0x00000008)
} DMA_Irq;

//@{
// Enumeration of the available DMA channel pending interrupt flags
//@}
typedef enum {
    // Channel x Global interrupt flag
    DMA1_IrqFlag_Ch1_GL = ((uint32_t)0x00000001),
    DMA1_IrqFlag_Ch2_GL = ((uint32_t)0x00000010),
    DMA1_IrqFlag_Ch3_GL = ((uint32_t)0x00000100),
    DMA1_IrqFlag_Ch4_GL = ((uint32_t)0x00001000),
    DMA1_IrqFlag_Ch5_GL = ((uint32_t)0x00010000),
    // Channel x Transfer complete flag
    DMA1_IrqFlag_Ch1_TC = ((uint32_t)0x00000002),
    DMA1_IrqFlag_Ch2_TC = ((uint32_t)0x00000020),
    DMA1_IrqFlag_Ch3_TC = ((uint32_t)0x00000200),
    DMA1_IrqFlag_Ch4_TC = ((uint32_t)0x00002000),
    DMA1_IrqFlag_Ch5_TC = ((uint32_t)0x00020000),
    // Channel x half transfer flag
    DMA1_IrqFlag_Ch1_HT = ((uint32_t)0x00000004),
    DMA1_IrqFlag_Ch2_HT = ((uint32_t)0x00000040),
    DMA1_IrqFlag_Ch3_HT = ((uint32_t)0x00000400),
    DMA1_IrqFlag_Ch4_HT = ((uint32_t)0x00004000),
    DMA1_IrqFlag_Ch5_HT = ((uint32_t)0x00040000),
    // Channel x transfer error flag
    DMA1_IrqFlag_Ch1_TE = ((uint32_t)0x00000008),
    DMA1_IrqFlag_Ch2_TE = ((uint32_t)0x00000080),
    DMA1_IrqFlag_Ch3_TE = ((uint32_t)0x00000800),
    DMA1_IrqFlag_Ch4_TE = ((uint32_t)0x00008000),
    DMA1_IrqFlag_Ch5_TE = ((uint32_t)0x00080000)
} DMA_IrqFlag;

//@{
// ADC init structure definition
//@}
typedef struct {
    // Specifies the peripheral base address for DMAy Channelx.
    uint32_t PeripheralBaseAddr;

    // Specifies the memory base address for DMAy Channelx.
    // @see: With DMA_SetMemoryBaseAddress the value can be modified after initialization
    uint32_t MemoryBaseAddr;

    // Specifies if the peripheral is the source or destination.
    DMA_DatatTransferDir DIR;

    // Specifies the buffer size, in data unit, of the specified Channel.
    // The data unit is equal to the configuration set in DMA_PeripheralDataSize or DMA_MemoryDataSize members depending in the transfer direction.
    // @see: With DMA_SetCurrDataCounter the value can be modified after initialization
    uint32_t BufferSize;

    // Specifies whether the Peripheral address register is incremented or not.
    DMA_PeripheralInc PeripheralInc;

    // Specifies whether the memory address register is incremented or not.
    DMA_MemoryInc MemoryInc;

    // Specifies the Peripheral data width.
    DMA_PeripheralDataSize PeripheralDataSize;

    // Specifies the Memory data width.
    DMA_MemoryDataSize MemoryDataSize;

    // Specifies the operation mode of the DMAy Channelx.
    // Note: The circular buffer mode cannot be used if the memory-to-memory data transfer is configured on the selected Channel
    DMA_Mode Mode;

    // Specifies the software priority for the DMAy Channelx.
    DMA_Priority Priority;

    // Specifies if the DMAy Channelx will be used in memory-to-memory transfer.
    DMA_M2M M2M;
} DMA_InitStruct;

//-------------------------------------------------------------------------
// DMA functions
//-------------------------------------------------------------------------
//@ {
// Deinitializes the DMAy Channelx registers to their default reset values.
// @param  pDmaYChannelX: where y can be 1 to select the DMA and
//                        x can be 1 to 7 for DMA1.
// @param  adcInitStruct: pointer to a DMA_InitTypeDef structure that
//                        contains the configuration information for
//                        the specified DMA Channel.
//@ }
void DMA_DeInit(const DMA_ChannelAddress dmaYChannelX);

//@ {
// Initializes the DMAy Channelx according to the specified
// parameters in the DMA_InitStruct.
// @param  pDmaYChannelX: where y can be 1 to select the DMA and
//                        x can be 1 to 7 for DMA1.
// @param  adcInitStruct: pointer to a DMA_InitTypeDef structure that
//                        contains the configuration information for
//                        the specified DMA Channel.
//@ }
void DMA_Init(const DMA_ChannelAddress dmaYChannelX, const DMA_InitStruct* const pDmaInitStruct);

//@ {
// Enables or disables the specified DMAy Channelx.
// @param  pDmaYChannelX: where y can be 1 to select the DMA and
//                        x can be 1 to 7 for DMA1.
// @param  doEnable: true channel would be enabled
//                   false channel would be disabled
//@ }
void DMA_Enable(const DMA_ChannelAddress dmaYChannelX, const bool doEnable);

//@ {
// Sets the number of data units in the current DMAy Channelx transfer.
// @param  pDmaYChannelX: where y can be 1 to select the DMA and
//                        x can be 1 to 7 for DMA1.
// @param  nrOfDataToTransfer: The number of data units in the current DMAy Channelx
//                             transfer.
// @note This function can only be used when the DMAy Channelx is disabled.
//@ }
void DMA_SetCurrDataCounter(const DMA_ChannelAddress dmaYChannelX, const uint16_t nrOfDataToTransfer);

//@{
// Sets a new Memory base address of the the current DMAy Channelx transfer.
// @param  pDmaYChannelX: where y can be 1 to select the DMA and
//                        x can be 1 to 7 for DMA1.
// @param memoryBaseAddr: Beschreibung des entsprechenden Parameters.
// @note It is not recommended to modify the memory base address if the channel
//       is enabled.
//@}
void DMA_SetMemoryBaseAddress(const DMA_ChannelAddress dmaYChannelX, const uint32_t memoryBaseAddr);

//@{
// Enables or disables the specified DMAy Channelx interrupts.
// @param  pDmaYChannelX: where y can be 1 to select the DMA and
//                        x can be 1 to 7 for DMA1.
// @param irq: Specifies the DMA interrupts sources to be enabled or disabled.
// @param doEnable: true channel interrupt would be enabled
//                  false channel interrupt channel would be disabled
//@}
void DMA_EnableInterrupt(const DMA_ChannelAddress dmaYChannelX, const DMA_Irq irq, const bool doEnable);

//@{
// Clears the DMAy Channelx's interrupt pending bits.
// @param irqFlag: Specifies the DMAy interrupt pending bit to clear.
//@}
void DMA_ClearPendingInterrupt(const DMA_IrqFlag irqFlag);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // #ifndef SYSTEMPERIPHERALS_DMA_H
