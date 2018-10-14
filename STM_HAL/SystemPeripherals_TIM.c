// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#include "SystemPeripherals_TIM.h"

// Imt.Base includes
#include <Imt.Base.Core.Diagnostics/Diagnostics.h>

//@{
// General purpose timer module register structure (TIM2..TIM5)
//@}
typedef struct {
    volatile uint16_t CR1;
    uint16_t reserved0;
    volatile uint16_t CR2;
    uint16_t reserved1;
    volatile uint16_t SMCR;
    uint16_t reserved2;
    volatile uint16_t DIER;
    uint16_t reserved3;
    volatile uint16_t SR;
    uint16_t reserved4;
    volatile uint16_t EGR;
    uint16_t reserved5;
    volatile uint16_t CCMR1;
    uint16_t reserved6;
    volatile uint16_t CCMR2;
    uint16_t reserved7;
    volatile uint16_t CCER;
    uint16_t reserved8;
    volatile uint16_t CNT;
    uint16_t reserved9;
    volatile uint16_t PSC;
    uint16_t reserved10;
    volatile uint16_t ARR;
    uint16_t reserved11;
    uint16_t reserved12;
    uint16_t reserved13;
    volatile uint16_t CCR1;
    uint16_t reserved14;
    volatile uint16_t CCR2;
    uint16_t reserved15;
    volatile uint16_t CCR3;
    uint16_t reserved16;
    volatile uint16_t CCR4;
    uint16_t reserved17;
    uint16_t reserved18;
    uint16_t reserved19;
    volatile uint16_t DCR;
    uint16_t reserved20;
    volatile uint16_t DMAR;
    uint16_t reserved21;
} TIM_GeneralPurposeModuleRegisters;

//@{
// TIM CR1 bit definitions
//@}
// Counter enable
#define  TIM_CR1_CEN            ((uint16_t)0x0001)
// Update request source
#define  TIM_CR1_URS            ((uint16_t)0x0004)
// One-pulse mode
#define  TIM_CR1_OPM            ((uint16_t)0x0008)
// Direction
#define  TIM_CR1_DIR            ((uint16_t)0x0010)
// CMS[1:0] bits (Center-aligned mode selection)
#define  TIM_CR1_CMS            ((uint16_t)0x0060)
// Auto-reload preload enable
#define  TIM_CR1_ARPE           ((uint16_t)0x0080)
// CKD[1:0] bits (clock division)
#define  TIM_CR1_CKD            ((uint16_t)0x0300)

//@{
// TIM EGR bit definitions
//@}
// Update generation
#define  TIM_EGR_UG             ((uint16_t)0x0001)

//@{
// TIM CCER bit definitions
//@}
#define TIM_CCER_CC4E           ((uint16_t)0x1000)
#define TIM_CCER_CC4P           ((uint16_t)0x2000)

//@{
// TIM CCMR2 bit definitions
//@}
#define TIM_CCMR2_CC4S           ((uint16_t)0x0300)
#define TIM_CCMR2_OC4PE          ((uint16_t)0x0800)
#define TIM_CCMR2_OC4M           ((uint16_t)0x7000)

void TIM_TimeBaseInit(const TIM_ModuleAddress timerModule, const TIM_TimeBaseInitStruct* const pTimInitStruct) {
    if (pTimInitStruct == NULL) {
       // ASSERT_DEBUG(false);
        return;
    }
    TIM_GeneralPurposeModuleRegisters* const pTIM = (TIM_GeneralPurposeModuleRegisters*)timerModule; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    uint16_t tmpcr1 = pTIM->CR1;

    // Select the Counter Mode
    tmpcr1 &= (~(TIM_CR1_DIR | TIM_CR1_CMS));
    tmpcr1 |= (uint16_t)pTimInitStruct->CounterMode;

    // Save CR1
    pTIM->CR1 = tmpcr1;

    // Set the Autoreload value
    pTIM->ARR = pTimInitStruct->Period;

    // Set the Prescaler value
    pTIM->PSC = pTimInitStruct->Prescaler;

    // Generate an update event to reload the prescaler value immediately
    pTIM->EGR = TIM_EGR_UG;
}

void TIM_Enable(const TIM_ModuleAddress timerModule, const bool doEnable) {
    TIM_GeneralPurposeModuleRegisters* const pTIM = (TIM_GeneralPurposeModuleRegisters*)timerModule; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    if (doEnable) {
        // Enable the TIM Counter
        pTIM->CR1 |= TIM_CR1_CEN;
    }
    else {
        // Disable the TIM Counter
        pTIM->CR1 &= (~TIM_CR1_CEN);
    }
}

uint16_t TIM_GetCounter(const TIM_ModuleAddress timerModule) {
    const TIM_GeneralPurposeModuleRegisters* const pTIM = (TIM_GeneralPurposeModuleRegisters*)timerModule; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    return pTIM->CNT;
}

void TIM_OCInit(const TIM_ModuleAddress timerModule, const TIM_Channel channel, const TIM_OCInitStruct* const pOcInitStruct) {
    if (pOcInitStruct == NULL) {
        ASSERT_DEBUG(false);
        return;
    }

    TIM_GeneralPurposeModuleRegisters* const pTIM = (TIM_GeneralPurposeModuleRegisters*)timerModule; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    switch (channel) {
        case TIM_Channel4:
            {
                // Disable the Channel 4 Capture Compare: Reset the CC4E Bit
                pTIM->CCER &= (uint16_t)(~(uint16_t)TIM_CCER_CC4E);

                // Get CCER, CCMR2 register values
                uint16_t tmpCCER = pTIM->CCER;
                uint16_t tmpCCMR2 = pTIM->CCMR2;

                // Reset the Output Compare mode and Capture/Compare selection Bits
                tmpCCMR2 &= (~TIM_CCMR2_OC4M);
                tmpCCMR2 &= (~TIM_CCMR2_CC4S);
                // Select the Output Compare Mode
                tmpCCMR2 |= (uint16_t)((uint16_t)pOcInitStruct->OCMode << 8U);

                // Reset the Output Polarity level
                tmpCCER &= (~TIM_CCER_CC4P);
                // Set the Output Compare Polarity
                tmpCCER |= (uint16_t)((uint16_t)pOcInitStruct->OutputPolarity << 12U);
                // Enable/Disable Capture Compare
                tmpCCER |= (pOcInitStruct->CaptureCompareEnable) ? TIM_CCER_CC4E : 0x0000U;

                // Write back CCER, CCMR2, CCR4 register values
                pTIM->CCMR2 = tmpCCMR2;
                pTIM->CCR4 = pOcInitStruct->CaptureCompareValue;
                pTIM->CCER = tmpCCER;
            }
            break;
        default:
            // Invalid channel selected -> do noting
            ASSERT_DEBUG(false);
            break;
    }
}

void TIM_OCPreloadConfig(const TIM_ModuleAddress timerModule, const TIM_Channel channel, const TIM_OCPreloadState ocPreloadState) {
    TIM_GeneralPurposeModuleRegisters* const pTIM = (TIM_GeneralPurposeModuleRegisters*)timerModule; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety

    switch (channel) {
        case TIM_Channel4: {
                // Modify the OC4PE Bit
                uint16_t tmpCCMR2 = pTIM->CCMR2;
                tmpCCMR2 &= ~(TIM_CCMR2_OC4PE);
                tmpCCMR2 |= (uint16_t)((uint16_t)ocPreloadState << 8U);
                pTIM->CCMR2 = tmpCCMR2;
            }
            break;
        default:
            // Invalid channel
            ASSERT_DEBUG(false);
            break;
    }
}

void TIM_CaptureCompareEnable(const TIM_ModuleAddress timerModule, const TIM_Channel channel, const bool doEnable) {
    TIM_GeneralPurposeModuleRegisters* const pTIM = (TIM_GeneralPurposeModuleRegisters*)timerModule; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety

    // Modify the CCxE bit
    const uint16_t mask = (uint16_t)(0x0001U << ((uint16_t)channel));
    if (doEnable) {
        pTIM->CCER |= mask;
    }
    else {
        pTIM->CCER &= (~mask);
    }
}

void TIM_SetCompareValue(const TIM_ModuleAddress timerModule, const TIM_Channel channel, const uint16_t captureCompareValue) {
    TIM_GeneralPurposeModuleRegisters* const pTIM = (TIM_GeneralPurposeModuleRegisters*)timerModule; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety

    switch (channel) {
        case TIM_Channel4: {
                // Modify the Capture Compare Register value
                pTIM->CCR1 = captureCompareValue;
            }
            break;
        default:
            // Invalid channel
         //   ASSERT_DEBUG(false);
            break;
    }
}

void TIM_EnableInterrupt(const TIM_ModuleAddress timerModule, const TIM_Irq irq, const bool doEnable) {
    TIM_GeneralPurposeModuleRegisters* const pTIM = (TIM_GeneralPurposeModuleRegisters*)timerModule; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    if (doEnable) {
        pTIM->DIER |= (uint16_t)irq;
    }
    else {
        pTIM->DIER &= ~((uint16_t)irq);
    }
}

void TIM_ClearPendingInterrupt(const TIM_ModuleAddress timerModule, const TIM_IrqFlag flagToClear) {
    TIM_GeneralPurposeModuleRegisters* const pTIM = (TIM_GeneralPurposeModuleRegisters*)timerModule; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    pTIM->SR = ~(uint16_t)(flagToClear);
}

void TIM_SetOnePulseMode(const TIM_ModuleAddress timerModule, const TIM_OnePulseMode opmMode) {
    TIM_GeneralPurposeModuleRegisters* const pTIM = (TIM_GeneralPurposeModuleRegisters*)timerModule; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    // Reset OPM bit
    pTIM->CR1 &= ~(uint16_t)(TIM_CR1_OPM);
    // Configure OPM Mode
    pTIM->CR1 |= (uint16_t)(opmMode);
}

void TIM_EnableAutoReloadRegisterBuffering(const TIM_ModuleAddress timerModule, const bool doEnable) {
    TIM_GeneralPurposeModuleRegisters* const pTIM = (TIM_GeneralPurposeModuleRegisters*)timerModule; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    if (doEnable) {
        pTIM->CR1 |= (uint16_t)TIM_CR1_ARPE;
    }
    else {
        pTIM->CR1 &= ~(uint16_t)TIM_CR1_ARPE;
    }
}

void TIM_SetAutoreloadRegister(const TIM_ModuleAddress timerModule, const uint16_t newValue) {
    TIM_GeneralPurposeModuleRegisters* const pTIM = (TIM_GeneralPurposeModuleRegisters*)timerModule; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    pTIM->ARR = newValue;
}

void TIM_SetUpdateRequestSource(const TIM_ModuleAddress timerModule, const TIM_UpdateRequestSource source) {
    TIM_GeneralPurposeModuleRegisters* const pTIM = (TIM_GeneralPurposeModuleRegisters*)timerModule; //lint !e923 cast from int to pointer [MISRA C++ Rule 5-2-7], [MISRA C++ Rule 5-2-8]. Justification: With this construct we reach more type safety
    if (source != TIM_UptateRequestSource_Global) {
        // Set the URS Bit
        pTIM->CR1 |= TIM_CR1_URS;
    }
    else {
        // Reset the URS Bit
        pTIM->CR1 &= ~(uint16_t)TIM_CR1_URS;
    }
}
