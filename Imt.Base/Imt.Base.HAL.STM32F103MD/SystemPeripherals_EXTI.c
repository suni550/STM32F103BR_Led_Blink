// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#include "SystemPeripherals_EXTI.h"

// Imt.Base includes
#include <Imt.Base.Core.Diagnostics/Diagnostics.h>

// Project includes
#include "SystemMemoryMap.h"

//@{
// EXTI module register structure
//@}
typedef struct {
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
} EXTI_ModuleRegisters;

void EXTI_Init(const EXTI_InitStruct* const extiInitStruct) {
    if (extiInitStruct == NULL) {
        ASSERT_DEBUG(false);
        return;
    }
    EXTI_ModuleRegisters* const pEXTI = (EXTI_ModuleRegisters*)EXTI_BASE;

    uint32_t tmp = (uint32_t)EXTI_BASE;
    if (extiInitStruct->EXTI_Enabled) {
        // Clear EXTI line configuration
        pEXTI->IMR &= ~(uint32_t)extiInitStruct->Line;
        pEXTI->EMR &= ~(uint32_t)extiInitStruct->Line;

        tmp += (uint32_t)extiInitStruct->Mode;

        *(volatile uint32_t*)tmp |= (uint32_t)extiInitStruct->Line;

        // Clear Rising Falling edge configuration
        pEXTI->RTSR &= ~(uint32_t)extiInitStruct->Line;
        pEXTI->FTSR &= ~(uint32_t)extiInitStruct->Line;

        // Select the trigger for the selected external interrupts
        if (extiInitStruct->Trigger == EXTI_Trigger_Rising_Falling) {
            // Rising and falling edge
            pEXTI->RTSR |= (uint32_t)extiInitStruct->Line;
            pEXTI->FTSR |= (uint32_t)extiInitStruct->Line;
        }
        else {
            tmp = (uint32_t)EXTI_BASE;
            tmp += (uint32_t)extiInitStruct->Trigger;

            *(volatile uint32_t*)tmp |= (uint32_t)extiInitStruct->Line;
        }
    }
    else {
        tmp += (uint32_t)extiInitStruct->Mode;

        // Disable the selected external lines
        *(volatile uint32_t*)tmp &= ~(uint32_t)extiInitStruct->Line;
    }
}

void EXTI_ClearITPendingBit(const EXTI_Line line) {
    EXTI_ModuleRegisters* const pEXTI = (EXTI_ModuleRegisters*)EXTI_BASE;
    pEXTI->PR = (uint32_t)line;
}

bool EXTI_IsITPending(const EXTI_Line line) {
    const EXTI_ModuleRegisters* const pEXTI = (EXTI_ModuleRegisters*)EXTI_BASE;
    return (pEXTI->PR & (uint32_t)line) > 0U;
}
