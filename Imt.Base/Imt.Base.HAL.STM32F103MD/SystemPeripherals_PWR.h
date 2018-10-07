// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#ifndef SYSTEMPERIPHERALS_PWR_H
#define SYSTEMPERIPHERALS_PWR_H

// Must be very first include
#include <Imt.Base.Core.Platform/Platform.h>

// Determine if a C++ compiler is being used.  If so, ensure that standard C is used to process the API information.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//@{
// Power control (PWR) peripheral module.
//
// Reference: ST_CortexM3_STM32F103_TRM_Rev15.pdf Chapter 5
// @author lbreitenmoser
//@}

//@{
// PWR Regulator regulator state in STOP mode
//@}
typedef enum {
    // STOP mode with regulator ON
    PWR_Regulator_ON       = ((uint32_t)0x00000000),
    // STOP mode with regulator in low power mode
    PWR_Regulator_LowPower = ((uint32_t)0x00000001)
} PWR_RegulatorState;

//@{
// PWR STOP mode entering with WFI or WFE instruction
//@}
typedef enum {
    // enter STOP mode with WFI instruction
    PWR_STOPEntry_WFI = ((uint8_t)0x01),
    // enter STOP mode with WFE instruction
    PWR_STOPEntry_WFE = ((uint8_t)0x02)
} PWR_StopModeEntryInstruction;

//@ {
// Enters STOP mode.
// @param  pwrRegulator: specifies the regulator state in STOP mode
//                       This parameter can be a value of @see PWR_RegulatorState_t
// @param  pwrStopModeEntryInstrunction: secifies if STOP mode in entered with WFI or WFE instruction.
//                                       This parameter can be a value of @PWR_StopModeEntryInstruction_t
//@ }
void PWR_EnterSTOPMode(const PWR_RegulatorState pwrRegulatorState, const PWR_StopModeEntryInstruction pwrStopModeEntryInstrunction);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // #ifndef SYSTEMPERIPHERALS_PWR_H
