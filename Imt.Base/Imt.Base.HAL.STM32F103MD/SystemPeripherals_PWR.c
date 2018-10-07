// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#include "SystemPeripherals_PWR.h"
// Project includes
#include "Core_CortexM3.h"

//@{
// PWR register structure
//@}
//lint -save
//lint -e754 // local structure member not referenced (offset required for correct register access)
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t CSR;
} PWR_ModuleRegisters;
//lint -restore

//@{
// Definition of PWR
//@}
#define PWR ((PWR_ModuleRegisters*)PWR_BASE)

//@{
// CR register bit mask
//@}
#define CR_DS_MASK               ((uint32_t)0xFFFFFFFC)

void PWR_EnterSTOPMode(const PWR_RegulatorState pwrRegulatorState, const PWR_StopModeEntryInstruction pwrStopModeEntryInstrunction) {
    // Select the regulator state in STOP mode
    uint32_t tmpreg = PWR->CR;
    // Clear PDDS and LPDS bits
    tmpreg &= CR_DS_MASK;
    // Set LPDS bit according to PWR_Regulator value
    tmpreg |= (uint32_t)pwrRegulatorState;
    // Store the new value
    PWR->CR = tmpreg;
    // Set SLEEPDEEP bit of Cortex System Control Register
    SCB->SCR |= SCB_SCR_SLEEPDEEP;

    // Select STOP mode entry
    if(pwrStopModeEntryInstrunction == PWR_STOPEntry_WFI) {
        // Data barrier
        asm volatile ("DSB");
        // Instruction barrier
        asm volatile ("ISB");
        // Request Wait For Interrupt
        asm volatile ("WFI");
    }
    else {
        // Data barrier
        asm volatile ("DSB");
        // Instruction barrier
        asm volatile ("ISB");
        // Request Wait For Event
        asm volatile ("WFE");
    }

    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP);
}
