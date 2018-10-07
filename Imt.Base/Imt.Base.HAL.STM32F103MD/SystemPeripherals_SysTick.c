// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#include "SystemPeripherals_SysTick.h"

// Project includes
#include "SystemMemoryMap.h"

//@{
// SysTick module register structure
//@}
typedef struct {
    // SysTick Control and Status Register
    volatile uint32_t SYST_CSR;
    // SysTick Reload Value Register
    volatile uint32_t SYST_RVR;
    // SysTick Current Value Register
    volatile uint32_t SYS_CVR;
    // SysTick Calibration Value Register
    volatile uint32_t SYST_CALIB;
} SysTick_ModuleRegisters;
#define SYSTICK ((SysTick_ModuleRegisters*)SYSTICK_BASE)

#define SYST_CSR_ENABLE_SET                 ((uint32_t)0x00000001)
#define SYST_CSR_ENABLE_RESET               ((uint32_t)0xFFFFFFFE)
#define SYST_CSR_TICKINT_SET                ((uint32_t)0x00000002)
#define SYST_CSR_TICKINT_RESET              ((uint32_t)0xFFFFFFFD)
#define SYST_CSR_CLKSOURCE_PROCESSOR        ((uint32_t)0x00000004)

void SysTick_ConfigureCounterValue(const uint32_t counterValue) {
    SYSTICK->SYST_RVR = counterValue;
    SYSTICK->SYST_CSR |= SYST_CSR_CLKSOURCE_PROCESSOR;
}

void SysTick_EnableInterrupt(const bool enabled) {
    // enable counter
    // enable interrupt
    if (enabled) {
        SYSTICK->SYST_CSR |= SYST_CSR_TICKINT_SET;
        SYSTICK->SYST_CSR |= SYST_CSR_ENABLE_SET;
    }
    else {
        SYSTICK->SYST_CSR &= SYST_CSR_TICKINT_RESET;
        SYSTICK->SYST_CSR &= SYST_CSR_ENABLE_RESET;
    }
}
