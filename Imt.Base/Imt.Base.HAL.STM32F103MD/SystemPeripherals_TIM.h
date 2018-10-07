// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#ifndef SYSTEMPERIPHERALS_TIM_H
#define SYSTEMPERIPHERALS_TIM_H

// Must be very first include
#include <Imt.Base.Core.Platform/Platform.h>

// Project includes
#include "SystemMemoryMap.h"

// Determine if a C++ compiler is being used.  If so, ensure that standard C is used to process the API information.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//@{
// Timer (TIM) peripheral module.
// The general-purpose timers consist of a 16-bit auto-reload counter driven by a programmable prescaler
// Note: Only the general-purpose timers (TIM2 to TIM4) are implemented.
//
// Reference: ST_CortexM3_STM32F103_TRM_Rev15.pdf Chapter 15
// @author lbreitenmoser
//@}

//@{
// Enumeration of the available TIM modules
//@}
typedef enum {
    TIM_ModuleAddress_TIM2 = TIM2_BASE,
    TIM_ModuleAddress_TIM3 = TIM3_BASE,
    TIM_ModuleAddress_TIM4 = TIM4_BASE
} TIM_ModuleAddress;

//@{
// TIM counter mode
// @see ST_CortexM3_STM32F103_TRM_Rev15.pdf Chapter 15.3.2 Counter modes
//@}
typedef enum {
    // Upcounter edge-aligned mode
    TIM_CounterModeUp = ((uint16_t)0x0000)
} TIM_CounterMode;

//@{
// Enumeration of the available TIM channel output compare and PWM modes.
//@}
typedef enum {
    TIM_OCMode_Timing   = ((uint16_t)0x0000),
    TIM_OCMode_Active   = ((uint16_t)0x0010),
    TIM_OCMode_Inactive = ((uint16_t)0x0020),
    TIM_OCMode_Toggle   = ((uint16_t)0x0030),
    TIM_OCMode_PWM1     = ((uint16_t)0x0060),
    TIM_OCMode_PWM2     = ((uint16_t)0x0070)
} TIM_OCMode;

//@{
// Enumeration of the available TIM channel output compare polarity.
//@}
typedef enum {
    TIM_OCPolarity_ActiveHigh = ((uint16_t)0x0000),
    TIM_OCPolarity_ActiveLow  = ((uint16_t)0x0002)
} TIM_OCPolarity;

//@{
// Enumeration of the available TIM channel preload register state.
//@}
typedef enum {
    TIM_OCPreloadState_Enable  = ((uint16_t)0x0008),
    TIM_OCPreloadState_Disable = ((uint16_t)0x0000)
} TIM_OCPreloadState;

//@{
// Enumeration of the available TIM channels.
//@}
typedef enum {
    TIM_Channel4 = ((uint16_t)0x000C)
} TIM_Channel;

//@{
// Enumeration of the available TIM interrupts.
//@}
typedef enum {
    TIM_Irq_UpdateInterrupt = ((uint16_t)0x0001)
} TIM_Irq;

//@{
// Enumeration of the available TIM status flags.
//@}
typedef enum {
    TIM_IrqFlag_UpdateInterrupt = ((uint16_t)0x0001)
} TIM_IrqFlag;

//@{
// Enumeration of the available one pulse modes.
// @see ST_CortexM3_STM32F103_TRM_Rev15.pdf Chapter 15.4.1
//@}
typedef enum {
    TIM_OnePulseMode_Repetitive = ((uint16_t)0x0000),
    TIM_OnePulseMode_Single     = ((uint16_t)0x0008)
} TIM_OnePulseMode;

//@{
// Enumeration of the available Update request source.
// @see ST_CortexM3_STM32F103_TRM_Rev15.pdf Chapter 15.4.1
//@}
typedef enum {
    // Source of update is the counter overflow / underflow or the setting of UG bit,
    // or an update generation through the slave mode controller.
    TIM_UptateRequestSource_Global,
    // Source of update is counter overflow/underflow.
    TIM_UptateRequestSource_Regular
} TIM_UpdateRequestSource;

//@{
// TIM init structure definition
//@}
typedef struct {
    // Specifies the prescaler value used to divide the TIM clock.
    // This parameter can be a number between 0x0000 and 0xFFFF
    uint16_t Prescaler;

    // Specifies the counter mode.
    TIM_CounterMode CounterMode;

    // Specifies the period value to be loaded into the active Auto-Reload Register at the next update event.
    // This parameter must be a number between 0x0000 and 0xFFFF.
    uint16_t Period;
} TIM_TimeBaseInitStruct;

//@{
// TIM Channel output compare init structure definition
//@}
typedef struct {
    // Specifies the TIM channel output compare and PWM mode.
    TIM_OCMode OCMode;

    // Enables or disables the Capture Compare.
    bool CaptureCompareEnable;

    // Specifies the pulse value to be loaded into the Capture Compare Register.
    // This parameter can be a number between 0x0000 and 0xFFFF
    uint16_t CaptureCompareValue;

    // Specifies the output polarity.
    TIM_OCPolarity OutputPolarity;
} TIM_OCInitStruct;

//@ {
// Initializes the TIMx Time Base Unit peripheral according to the specified parameters in the TIM_TimeBaseInit_t.
// @param timerModule: Select the TIM peripheral.
// @param pTimInitStruct: Pointer to a TIM_TimeBaseInitStruct
//                        structure that contains the configuration information for the
//                        specified TIM peripheral.
//@ }
void TIM_TimeBaseInit(const TIM_ModuleAddress timerModule, const TIM_TimeBaseInitStruct* const pTimInitStruct);

//@ {
// Enables or disables the specified TIM peripheral.
// @param timerModule: Select the TIM peripheral.
// @param doEnable: true TIM would be enabled
//                   false TIM would be disabled
//@ }
void TIM_Enable(const TIM_ModuleAddress timerModule, const bool doEnable);

//@ {
// Gets the counter value of the specified TIM peripheral.
// @param timerModule: Select the TIM peripheral.
// @return uint16_t: counter register value
//@}
uint16_t TIM_GetCounter(const TIM_ModuleAddress timerModule);
void TIM_SetCounter(const TIM_ModuleAddress timerModule, const uint16_t setCounter) ;
//@{
// Initializes the selected channel of the selected TIM peripheral according to the
// specified parameters in the pOcInitStruct.
// @param timerModule: Select the TIM peripheral.
// @param channel: Select the channel.
// @param pOcInitStruct: Pointer to a pOcInitStruct structure that contains
//                       the configuration information for the TIM channel.
//@}
void TIM_OCInit(const TIM_ModuleAddress timerModule, const TIM_Channel channel, const TIM_OCInitStruct* const pOcInitStruct);

//@{
// Enables or disables the preload register of the selected channel of the selected
// TIM peripheral.
// @note If disabled a write of the capture/compare register is immediately taken into account.
// @param timerModule: Select the TIM peripheral.
// @param channel: Select the channel.
// @param ocPreloadState: The new preload register state.
//@}
void TIM_OCPreloadConfig(const TIM_ModuleAddress timerModule, const TIM_Channel channel, const TIM_OCPreloadState ocPreloadState);

//@{
// Enables or disables the Capture Compare of the selected channel of the selected
// TIM peripheral.
// @param timerModule: Select the TIM peripheral.
// @param channel: Select the channel.
// @param doEnable: true capture compare would be enabled
//                  false capture compare would be disabled
//@}
void TIM_CaptureCompareEnable(const TIM_ModuleAddress timerModule, const TIM_Channel channel, const bool doEnable);

//@{
// Sets the Capture Compare Register value of the selected channel of the selected
// TIM peripheral.
// @param timerModule: Select the TIM peripheral.
// @param channel: Select the channel.
// @param captureCompareValue: Specifies the new Capture Compare register value.
//@}
void TIM_SetCompareValue(const TIM_ModuleAddress timerModule, const TIM_Channel channel, const uint16_t captureCompareValue);

//@{
// Enables or disables the specified TIM interrupts.
// @param timerModule: Select the TIM peripheral.
// @param irq: Specifies the TIM interrupts sources to be enabled or disabled.
// @param doEnable: true interrupt would be enabled
//                  false interrupt channel would be disabled
//@}
void TIM_EnableInterrupt(const TIM_ModuleAddress timerModule, const TIM_Irq irq, const bool doEnable);

//@{
// Clears the TIM interrupt pending bits.
// @param timerModule: Select the TIM peripheral.
// @param flagToClear: Specifies the flag to be cleared.
//@}
void TIM_ClearPendingInterrupt(const TIM_ModuleAddress timerModule, const TIM_IrqFlag irqFlag);

//@{
// Sets the one pulse mode.
// @param timerModule: Select the TIM peripheral.
// @param const opmMode: Specifies the one pulse mode.
//@}
void TIM_SetOnePulseMode(const TIM_ModuleAddress timerModule, const TIM_OnePulseMode opmMode);

//@{
// Enables or disables write buffering of auto reload register.
// @param timerModule: Select the TIM peripheral.
// @param doEnable: true writes to auto reload register are buffered
//                  false writes to auto reload register are not buffered
//@}
void TIM_EnableAutoReloadRegisterBuffering(const TIM_ModuleAddress timerModule, const bool doEnable);

//@{
// Sets the auto-reload register value
// @param timerModule: Select the TIM peripheral.
// @param newValue: Specifies the new auto-reload register value
//@}
void TIM_SetAutoreloadRegister(const TIM_ModuleAddress timerModule, const uint16_t newValue);

//@{
// Sets update request interrupt source.
// @param timerModule: Select the TIM peripheral.
// @param source: Specifies the source of an update request
//@}
void TIM_SetUpdateRequestSource(const TIM_ModuleAddress timerModule, const TIM_UpdateRequestSource source);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // #ifndef SYSTEMPERIPHERALS_TIM_H
