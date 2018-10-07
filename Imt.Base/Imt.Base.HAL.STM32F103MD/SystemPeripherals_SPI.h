// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#ifndef SYSTEMPERIPHERALS_SPI_H
#define SYSTEMPERIPHERALS_SPI_H

// Must be very first include
#include <Imt.Base.Core.Platform/Platform.h>

// Project includes
#include "SystemMemoryMap.h"

// Determine if a C++ compiler is being used.  If so, ensure that standard C is used to process the API information.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//@{
// Serial peripheral interface (SPI).
// The serial peripheral interface (SPI)allows half / full - duplex, synchronous, serial
// communication with external devices.The interface can be configured as the master and in
// this case it provides the communication clock(SCK) to the external slave device.The
// interface is also capable of operating in multimaster configuration.
// It may be used for a variety of purposes, including simplex synchronous transfers on two
// lines with a possible bidirectional data line or reliable communication using CRC checking.
//
// Reference: ST_CortexM3_STM32F103_TRM_Rev15.pdf Chapter 25
// @author lbreitenmoser
//@}

//@{
// Enumeration of the available SPI modules
//@}
typedef enum {
    SPI_ModuleAddress_SPI1 = SPI1_BASE,
    SPI_ModuleAddress_SPI2 = SPI2_BASE
} SPI_ModuleAddress;

//@{
// Enumeration of data register addresses of the available SPI modules
//@}
typedef enum {
    SPI_DataRegisterAddress_SPI1 = SPI1_BASE + 0x0000000C,
    SPI_DataRegisterAddress_SPI2 = SPI2_BASE + 0x0000000C
} SPI_DataRegisterAddress;

//@{
// Enumeration of the available SPI direction modes
//@}
typedef enum {
    SPI_Direction_2Lines_FullDuplex = ((uint16_t)0x0000),
    SPI_Direction_2Lines_RxOnly     = ((uint16_t)0x0400),
    SPI_Direction_1Line_Rx          = ((uint16_t)0x8000),
    SPI_Direction_1Line_Tx          = ((uint16_t)0xC000)
} SPI_Direction;

//@{
// Enumeration of the available SPI modes
//@}
typedef enum {
    SPI_Mode_Master = ((uint16_t)0x0104),
    SPI_Mode_Slave  = ((uint16_t)0x0000)
} SPI_Mode;

//@{
// Enumeration of the available SPI data frame format
//@}
typedef enum {
    SPI_DataFrameFormat_8Bit  = ((uint16_t)0x0000),
    SPI_DataFrameFormat_16Bit = ((uint16_t)0x0800)
} SPI_DataFrameFormat;

//@{
// Enumeration of the available SPI clock polarities
//@}
typedef enum {
    SPI_CPOL_Low  = ((uint16_t)0x0000),
    SPI_CPOL_High = ((uint16_t)0x0002)
} SPI_CPOL;

//@{
// Enumeration of the available SPI clock phases
//@}
typedef enum {
    SPI_CPHA_1Edge = ((uint16_t)0x0000),
    SPI_CPHA_2Edge = ((uint16_t)0x0001)
} SPI_CPHA;

//@{
// Enumeration of the available slave select management options
//@}
typedef enum {
    SPI_SlaveSelectManagement_ByHardware = ((uint16_t)0x0000),
    SPI_SlaveSelectManagement_BySoftware = ((uint16_t)0x0200)
} SPI_SlaveSelectManagement;

//@{
// Enumeration of the available baud rate prescaler.
// @note the SPI clock is derived from PCLK1 or PCLK2.
//@}
typedef enum {
    SPI_BaudRatePrescaler_2   = ((uint16_t)0x0000),
    SPI_BaudRatePrescaler_4   = ((uint16_t)0x0008),
    SPI_BaudRatePrescaler_8   = ((uint16_t)0x0010),
    SPI_BaudRatePrescaler_16  = ((uint16_t)0x0018),
    SPI_BaudRatePrescaler_32  = ((uint16_t)0x0020),
    SPI_BaudRatePrescaler_64  = ((uint16_t)0x0028),
    SPI_BaudRatePrescaler_128 = ((uint16_t)0x0030),
    SPI_BaudRatePrescaler_256 = ((uint16_t)0x0038)
} SPI_BaudRatePrescaler;

//@{
// Defines whether a data transfer starts from MSB or LSB bit.
//@}
typedef enum {
    SPI_FirstBit_MSB = ((uint16_t)0x0000),
    SPI_FirstBit_LSB = ((uint16_t)0x0080)
} SPI_FirstBit;

//@{
// Enumeration of the available SPI DMA requests.
//@}
typedef enum {
    SPI_DmaReq_Rx = ((uint16_t)0x0001),
    SPI_DmaReq_Tx = ((uint16_t)0x0002)
} SPI_DmaReq;

//@{
// SPI init structure definition
//@}
typedef struct {
    // Specifies the SPI unidirectional or bidirectional data mode.
    SPI_Direction Direction;

    // Specifies the SPI operating mode.
    SPI_Mode Mode;

    // Specifies the SPI data frame format
    SPI_DataFrameFormat DataFrameFormat;

    // Specifies the serial clock steady state.
    SPI_CPOL ClockPolarity;

    // Specifies the clock active edge for the bit capture.
    SPI_CPHA ClockPhase;

    // Specifies whether the NSS signal is managed by
    // hardware(NSS pin) or by software using the SSI bit
    SPI_SlaveSelectManagement SlaveSelectManagement;

    // Specifies the Baud Rate prescaler value which will be
    // used to configure the transmit and receive SCK clock.
    SPI_BaudRatePrescaler BaudRatePrescaler;

    // Specifies whether data transfers start from MSB or LSB bit.
    SPI_FirstBit FirstBit;

    // Specifies the polynomial used for the CRC calculation.
    uint16_t CRCPolynomial;
} SPI_InitStruct;

//@{
// Initializes the SPI peripheral according to the specified parameters
// in the pSpiInitStruct.
// @param spiSel: Select the SPI peripheral.
// @param pSpiInitStruct: Pointer to a SPI_InitStruct structure that contains
//                        the configuration information for the specific SPI peripheral.
//@}
void SPI_Init(const SPI_ModuleAddress spiSel, const SPI_InitStruct* const pSpiInitStruct);

//@{
// Enables or disables the specified SPI peripheral.
// @param spiSel: Select the SPI peripheral.
// @param enable: true = ENABLE, false = DISABLE
//@}
void SPI_SetState(const SPI_ModuleAddress spiSel, const bool enable);

//@{
// Enables or disables the SPI DMA transfer requests.
// @param spiSel: Select the SPI peripheral.
// @param dmaReq: Specifies the SPI DMA transfer request to be enabled or disabled.
// @param bool enable: true = ENABLE, false = DISABLE
//@}
void SPI_SetDmaState(const SPI_ModuleAddress spiSel, const SPI_DmaReq dmaReq, const bool enable);

//@{
// Checks whether the Tx buffer is empty (TXE) or not.
// @note: Tx buffer empty means not that the transmission is completed, because
//        Tx buffer is empty as soon that the data is transfered from the
//        Tx buffer into the shift register, which means the transfer is may
//        still running when TXE is asserted.
// @param spiSel: Select the SPI peripheral.
// @return bool: true if the Tx buffer is empty, else false
//@}
bool SPI_IsTxBufferEmpty(const SPI_ModuleAddress spiSel);

//@{
// Checks whether the Rx buffer is not empty (RXNE) or not.
// @param spiSel: Select the SPI peripheral.
// @return bool: true if the Rx buffer is not empty, else false
//@}
bool SPI_IsRxBufferNotEmpty(const SPI_ModuleAddress spiSel);

//@{
// Checks whether the SPI is busy or not.
// @param spiSel: Select the SPI peripheral.
// @return bool: true if the SP buffer is busy, else false
//@}
bool SPI_IsBusy(const SPI_ModuleAddress spiSel);

//@{
// Sends data through the selected SPI peripheral.
// @param spiSel: Select the SPI peripheral.
// @param data: Data to be send
//@}
void SPI_SendData(const SPI_ModuleAddress spiSel, const uint16_t data);

//@{
// Returns the most recent received data by the selected SPI peripheral.
// @param spiSel: Select the SPI peripheral.
// @return uint16_t: The value of the received data
//@}
uint16_t SPI_ReceiveData(const SPI_ModuleAddress spiSel);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // #ifndef SYSTEMPERIPHERALS_SPI_H
