// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#ifndef SYSTEMPERIPHERALS_SYSTICK_H
#define SYSTEMPERIPHERALS_SYSTICK_H

// Must be very first include
#include <Imt.Base.Core.Platform/Platform.h>

// Determine if a C++ compiler is being used.  If so, ensure that standard C is used to process the API information.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//@{
// System timer (SysTick) peripheral modul
//
// Reference: Cortex-M3 Devices Generic User Guide DUI0552A Chapter 4.4
// @author lbreitenmoser
//@}

//@{
// Configure the system tick with the given counterValue (fixed to processor clock)
// @param  counterValue: number of processor clock ticks before the interrupt is fired
//@}
void SysTick_ConfigureCounterValue(const uint32_t counterValue);

//@{
// Enable or disable the system tick interrupt
// @param bool enabled
// @return void
//@}
void SysTick_EnableInterrupt(const bool enabled);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SYSTEMPERIPHERALS_SYSTICK_H