// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#ifndef SYSTEMPERIPHERALS_ADC_H
#define SYSTEMPERIPHERALS_ADC_H

// Must be very first include
#include <Imt.Base.Core.Platform/Platform.h>

// Project includes
#include "SystemMemoryMap.h"

// Determine if a C++ compiler is being used.  If so, ensure that standard C is used to process the API information.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//@{
// Analog-to-digital converter (ADC) peripheral module.
// The 12-bit ADC is a successive approximation analog-to-digital converter.
// It has up to 18 multiplexed channels allowing it measure signals from 16 external and two internal sources.
// A/D conversion of the various channels can be performed in single, continuous, scan or discontinuous mode.
// The result of the ADC is stored in a left-aligned or right-aligned 16-bit data register.
//
// Reference: ST_CortexM3_STM32F103_TRM_Rev15.pdf Chapter 11
// @author lbreitenmoser
//@}

//@{
// Enumeration of the available ADC modules
//@}
typedef enum {
    ADC_ModuleAddress_ADC1 = ADC1_BASE,
    ADC_ModuleAddress_ADC2 = ADC2_BASE
} ADC_ModuleAddress;

//@{
// ADC mode
//@}
typedef enum {
    ADC_Mode_Independent = ((uint32_t)0x00000000)
} ADC_Mode;

//@{
// Scan mode
//@}
typedef enum {
    ADC_ScanMode_MultiChannel = ((uint32_t)0x00000100)
} ADC_ScanMode;

//@{
// Conversion mode
//@}
typedef enum {
    ADC_ConvMode_Single = ((uint32_t)0x00000000),
    ADC_ConvMode_Continuous = ((uint32_t)0x0000002)
} ADC_ConvMode;

//@{
// External trigger source for starting a regular channel conversion
//@}
typedef enum {
    ADC_ExtStartConvTriggerSource_Software = ((uint32_t)0x000E0000)
} ADC_ExtStartConvTriggerSource;

//@{
// External trigger source for starting a regular channel conversion
//@}
typedef enum {
    ADC_DataAlign_Right = ((uint32_t)0x00000000)
} ADC_DataAlign;

//@{
// Number of channels to convert
//@}
typedef enum {
    ADC_NrOfChannels_1 = ((uint32_t)0x00000000),
    ADC_NrOfChannels_2 = ((uint32_t)0x00100000),
    ADC_NrOfChannels_3 = ((uint32_t)0x00200000),
    ADC_NrOfChannels_4 = ((uint32_t)0x00300000),
    ADC_NrOfChannels_5 = ((uint32_t)0x00400000),
    ADC_NrOfChannels_6 = ((uint32_t)0x00500000),
    ADC_NrOfChannels_7 = ((uint32_t)0x00600000),
    ADC_NrOfChannels_8 = ((uint32_t)0x00700000),
    ADC_NrOfChannels_9 = ((uint32_t)0x00800000),
    ADC_NrOfChannels_10 = ((uint32_t)0x00900000)
} ADC_NrOfChannel;

//@{
// ADC init structure definition
//@}
typedef struct {
    // Configures the ADC to operate in independent or dual mode.
    ADC_Mode Mode;

    // Specifies whether the conversion is performed in Scan (multi channels) or Single (one channel) mode.
    ADC_ScanMode ScanConvMode;

    // Specifies whether the conversion is performed in Continuous or Single mode.
    ADC_ConvMode ContinuousConvMode;

    // Defines the external trigger used to start the analog to digital conversion of regular channels.
    ADC_ExtStartConvTriggerSource StartConvTriggerSource;

    // Specifies whether the ADC data alignment is left or right.
    ADC_DataAlign DataAlign;

    // Specifies the number of ADC channels that will be converted using the sequencer for regular channel group.
    ADC_NrOfChannel NbrOfChannel;
} ADC_InitStruct;

//@{
// ADC channels
//@}
typedef enum {
    ADC_Channel_6 = ((uint8_t)0x06),
    ADC_Channel_7 = ((uint8_t)0x07),
    ADC_Channel_8 = ((uint8_t)0x08),
    ADC_Channel_9 = ((uint8_t)0x09),
    ADC_Channel_10 = ((uint8_t)0x0A),
    ADC_Channel_11 = ((uint8_t)0x0B),
    ADC_Channel_12 = ((uint8_t)0x0C),
    ADC_Channel_13 = ((uint8_t)0x0D),
    ADC_Channel_14 = ((uint8_t)0x0E),
    ADC_Channel_15 = ((uint8_t)0x0F)
} ADC_Channel;

//@{
// ADC rank of a channel
//@}
typedef enum {
    ADC_Rank_1 = ((uint8_t)0x01),
    ADC_Rank_2 = ((uint8_t)0x02),
    ADC_Rank_3 = ((uint8_t)0x03),
    ADC_Rank_4 = ((uint8_t)0x04),
    ADC_Rank_5 = ((uint8_t)0x05),
    ADC_Rank_6 = ((uint8_t)0x06),
    ADC_Rank_7 = ((uint8_t)0x07),
    ADC_Rank_8 = ((uint8_t)0x08),
    ADC_Rank_9 = ((uint8_t)0x09),
    ADC_Rank_10 = ((uint8_t)0x0A)
} ADC_Rank;

//@{
// ADC rank of a channel
//@}
typedef enum {
    ADC_SampleTime_1Cycles5 = ((uint8_t)0x00),
    ADC_SampleTime_7Cycles5 = ((uint8_t)0x01),
    ADC_SampleTime_13Cycles5 = ((uint8_t)0x02),
    ADC_SampleTime_28Cycles5 = ((uint8_t)0x03),
    ADC_SampleTime_41Cycles5 = ((uint8_t)0x04),
    ADC_SampleTime_55Cycles5 = ((uint8_t)0x05),
    ADC_SampleTime_71Cycles5 = ((uint8_t)0x06),
    ADC_SampleTime_239Cycles5 = ((uint8_t)0x07)
} ADC_SampleTime;

//@ {
// Deinitializes the ADCx peripheral registers to their default reset values.
// @param  adcSel: Select the ADC peripheral.
//@ }
void ADC_DeInit(const ADC_ModuleAddress adcSel);

//@ {
// Initializes the ADC peripheral according to the specified parameters
// in the adcInitStruct.
// @param  pAdcSel: Select the ADC peripheral.
// @param  pAdcInitStruct: pointer to a ADC_InitStruct structure that contains the configuration information for the specific ADC peripheral.
//@ }
void ADC_Init(const ADC_ModuleAddress adcSel, const ADC_InitStruct* const pAdcInitStruct);

//@ {
// Configures for the selected ADC regular channel its corresponding rank
// in the sequencer and its sample time.
// @param  pAdcSel: Select the ADC peripheral.
// @param  adcChannel: The ADC channel to configure
//                     This parameter can be a value of @see ADC_Channel
// @param  rank: The rank in the regular group sequencer.
//               This parameter can be a value of @see ADC_Rank
// @param  adcSampleTime: The sample time value to be set for the
//                        selected channel.
//                        This parameter can be a value of @see ADC_SampleTime
//@ }
void ADC_RegularChannelConfig(const ADC_ModuleAddress adcSel, const ADC_Channel adcChannel, const ADC_Rank rank, const ADC_SampleTime adcSampleTime);

//@ {
// Enables or disables the specified ADC peripheral.
// @param  pAdcSel: Select the ADC peripheral.
// @param  doEnable: true ADC would be enabled
//                   false ADC would be disabled
//@ }
void ADC_Enable(const ADC_ModuleAddress adcSel, const bool doEnable);

//@ {
// Enables or disables the specified ADC DMA request.
// @param  pAdcSel: Select the ADC peripheral.
// @param  doEnable: true ADC DMA requests would be enabled
//                   false fADC DMA requests would be disabled
//@ }
void ADC_DMAEnable(const ADC_ModuleAddress adcSel, const bool doEnable);

//@ {
// Resets the selected ADC calibration registers.
// @param  pAdcSel: Select the ADC peripheral.
//@ }
void ADC_ResetCalibration(const ADC_ModuleAddress adcSel);

//@ {
// Gets the selected ADC reset calibration registers status.
// @param  pAdcSel: Select the ADC peripheral.
// @return The state of ADC reset calibration registers (true = SET or false = RESET).
//@ }
bool ADC_GetResetCalibrationStatus(const ADC_ModuleAddress adcSel);

//@ {
// Starts the selected ADC calibration process.
// @param  pAdcSel: Select the ADC peripheral.
//@ }
void ADC_StartCalibration(const ADC_ModuleAddress adcSel);

//@ {
// Gets the selected ADC calibration status.
// @param  pAdcSel: Select the ADC peripheral.
// @return The new state of ADC calibration (true = SET or false = RESET).
//@ }
bool ADC_GetCalibrationStatus(const ADC_ModuleAddress adcSel);

//@ {
// Enables or disables the selected ADC software start conversion.
// @param  pAdcSel: Select the ADC peripheral.
// @param  doEnable: New state of the selected ADC software start conversion
//@ }
void ADC_SoftwareStartConv(const ADC_ModuleAddress adcSel, const bool doEnable);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // #ifndef SYSTEMPERIPHERALS_ADC_H
