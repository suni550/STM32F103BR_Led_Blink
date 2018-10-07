// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#include "SystemPeripherals_ADC.h"

// Imt.Base includes
#include <Imt.Base.Core.Diagnostics/Diagnostics.h>

// Project includes
#include "SystemPeripherals_RCC.h"
#include "SystemMemoryMap.h"

//@{
// ADC module register structure
//@}
typedef struct {
    volatile uint32_t SR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMPR1;
    volatile uint32_t SMPR2;
    volatile uint32_t JOFR1;
    volatile uint32_t JOFR2;
    volatile uint32_t JOFR3;
    volatile uint32_t JOFR4;
    volatile uint32_t HTR;
    volatile uint32_t LTR;
    volatile uint32_t SQR1;
    volatile uint32_t SQR2;
    volatile uint32_t SQR3;
    volatile uint32_t JSQR;
    volatile uint32_t JDR1;
    volatile uint32_t JDR2;
    volatile uint32_t JDR3;
    volatile uint32_t JDR4;
    volatile uint32_t DR;
} ADC_ModuleRegisters;

//@{
// ADC CR2 mask
//@}
#define CR1_CLEAR_Mask              ((uint32_t)0xFFF0FEFF)

//@{
// ADC CR2 mask
//@}
#define CR2_CLEAR_Mask              ((uint32_t)0xFFF1F7FD)
#define CR2_ADON_Set                ((uint32_t)0x00000001)
#define CR2_ADON_Reset              ((uint32_t)0xFFFFFFFE)
#define CR2_CAL_Set                 ((uint32_t)0x00000004)
#define CR2_RSTCAL_Set              ((uint32_t)0x00000008)
#define CR2_EXTTRIG_SWSTART_Set     ((uint32_t)0x00500000)
#define CR2_EXTTRIG_SWSTART_Reset   ((uint32_t)0xFFAFFFFF)
#define CR2_DMA_Set                 ((uint32_t)0x00000100)
#define CR2_DMA_Reset               ((uint32_t)0xFFFFFEFF)

//@{
// ADC SMPx mask
//@}
#define SMPR1_SMP_Set               ((uint32_t)0x00000007)
#define SMPR2_SMP_Set               ((uint32_t)0x00000007)

//@{
// ADC SQRx mask
//@}
#define SQR3_SQ_Set                 ((uint32_t)0x0000001F)
#define SQR2_SQ_Set                 ((uint32_t)0x0000001F)
#define SQR1_CLEAR_Mask             ((uint32_t)0xFF0FFFFF)


void ADC_DeInit(const ADC_ModuleAddress adcSel) {
    switch(adcSel) {
        case ADC_ModuleAddress_ADC1:
            // Enable reset state
            RCC_ResetAPB2Peripheral(RCC_APB2Periph_ADC1, true);
            // Release from reset state
            RCC_ResetAPB2Peripheral(RCC_APB2Periph_ADC1, false);
            break;
        case ADC_ModuleAddress_ADC2:
            // Enable reset state
            RCC_ResetAPB2Peripheral(RCC_APB2Periph_ADC2, true);
            // Release from reset state
            RCC_ResetAPB2Peripheral(RCC_APB2Periph_ADC2, false);
            break;
        default:
            break;
    }
}

void ADC_Init(const ADC_ModuleAddress adcSel, const ADC_InitStruct* const pAdcInitStruct) {
    if (pAdcInitStruct == NULL) {
        ASSERT_DEBUG(false);
        return;
    }

    ADC_ModuleRegisters* const pAdcSel = (ADC_ModuleRegisters*)adcSel;

    /*-------------------------- ADCx CR1 Configuration -----------------*/
    // Get the ADCx CR1 value
    uint32_t tmpReg1 = pAdcSel->CR1;
    // Clear DUALMOD and SCAN bits
    tmpReg1 &= CR1_CLEAR_Mask;
    // Configure ADCx: Dual mode and scan conversion mode
    // Set DUALMOD bits according to ADC_Mode value
    // Set SCAN bit according to ADC_ScanConvMode value
    tmpReg1 |= ((uint32_t)pAdcInitStruct->Mode | (uint32_t)pAdcInitStruct->ScanConvMode);
    // Write to ADCx CR1
    pAdcSel->CR1 = tmpReg1;

    /*-------------------------- ADCx CR2 Configuration -----------------*/
    // Get the ADCx CR2 value
    tmpReg1 = pAdcSel->CR2;
    // Clear CONT, ALIGN and EXTSEL bits
    tmpReg1 &= CR2_CLEAR_Mask;
    // Configure ADCx: external trigger event and continuous conversion mode
    // Set ALIGN bit according to ADC_DataAlign value
    // Set EXTSEL bits according to ADC_ExternalTrigConv value
    // Set CONT bit according to ADC_ContinuousConvMode value
    tmpReg1 |= ((uint32_t)pAdcInitStruct->DataAlign | (uint32_t)pAdcInitStruct->StartConvTriggerSource | (uint32_t)pAdcInitStruct->ContinuousConvMode);
    // Write to ADCx CR2
    pAdcSel->CR2 = tmpReg1;

    /*------------------------- ADCx SQR1 Configuration -----------------*/
    // Get the ADCx SQR1 value
    tmpReg1 = pAdcSel->SQR1;
    // Clear L bits
    tmpReg1 &= SQR1_CLEAR_Mask;
    // Configure ADCx: regular channel sequence length
    // Set L bits according to ADC_NbrOfChannel value
    tmpReg1 |= (uint32_t)pAdcInitStruct->NbrOfChannel;
    // Write to ADCx SQR1
    pAdcSel->SQR1 = tmpReg1;
}

void ADC_RegularChannelConfig(const ADC_ModuleAddress adcSel, const ADC_Channel adcChannel, const ADC_Rank rank, const ADC_SampleTime adcSampleTime) {
    ADC_ModuleRegisters* const pAdcSel = (ADC_ModuleRegisters*)adcSel;

    // Set sample time
    if (adcChannel > ADC_Channel_9) {
        // ADC_Channel include in ADC_Channel_[10..17]

        // Get the old register value
        uint32_t tmpreg1 = pAdcSel->SMPR1;
        // Calculate the mask to clear
        uint32_t tmpreg2 = SMPR1_SMP_Set << (3 * ((uint8_t)adcChannel - 10));
        // Clear the old channel sample time
        tmpreg1 &= ~tmpreg2;
        // Calculate the mask to set
        tmpreg2 = (uint32_t)adcSampleTime << (3 * ((uint8_t)adcChannel - 10));
        // Set the new channel sample time
        tmpreg1 |= tmpreg2;
        // Store the new register value
        pAdcSel->SMPR1 = tmpreg1;
    }
    else {
        // Get the old register value
        uint32_t tmpreg1 = pAdcSel->SMPR2;
        // Calculate the mask to clear
        uint32_t tmpreg2 = SMPR2_SMP_Set << (3 * (uint8_t)adcChannel);
        // Clear the old channel sample time
        tmpreg1 &= ~tmpreg2;
        // Calculate the mask to set
        tmpreg2 = (uint32_t)adcSampleTime << (3 * (uint8_t)adcChannel);
        // Set the new channel sample time
        tmpreg1 |= tmpreg2;
        // Store the new register value
        pAdcSel->SMPR2 = tmpreg1;
    }

    // Set the rank
    if ((uint8_t)rank < 7) {
        // For Rank 1 to 6
        // Get the old register value
        uint32_t tmpreg1 = pAdcSel->SQR3;
        // Calculate the mask to clear
        uint32_t tmpreg2 = SQR3_SQ_Set << (5 * ((uint8_t)rank - 1));
        // Clear the old SQx bits for the selected rank
        tmpreg1 &= ~tmpreg2;
        // Calculate the mask to set
        tmpreg2 = (uint32_t)adcChannel << (5 * ((uint8_t)rank - 1));
        // Set the SQx bits for the selected rank
        tmpreg1 |= tmpreg2;
        // Store the new register value
        pAdcSel->SQR3 = tmpreg1;
    }
    else if ((uint8_t)rank < 13) {
        // For Rank 7 to 12
        // Get the old register value
        uint32_t tmpreg1 = pAdcSel->SQR2;
        // Calculate the mask to clear
        uint32_t tmpreg2 = SQR2_SQ_Set << (5 * ((uint8_t)rank - 7));
        // Clear the old SQx bits for the selected rank
        tmpreg1 &= ~tmpreg2;
        // Calculate the mask to set
        tmpreg2 = (uint32_t)adcChannel << (5 * ((uint8_t)rank - 7));
        // Set the SQx bits for the selected rank
        tmpreg1 |= tmpreg2;
        // Store the new register value
        pAdcSel->SQR2 = tmpreg1;
    }
    else {
        // Selected rank not possible
        ASSERT_DEBUG(false);
    }
}

void ADC_Enable(const ADC_ModuleAddress adcSel, const bool doEnable) {
    ADC_ModuleRegisters* const pAdcSel = (ADC_ModuleRegisters*)adcSel;
    if (doEnable) {
        // Set the ADON bit to wake up the ADC from power down mode
        pAdcSel->CR2 |= CR2_ADON_Set;
    }
    else {
        // Disable the selected ADC peripheral
        pAdcSel->CR2 &= CR2_ADON_Reset;
    }
}

void ADC_DMAEnable(const ADC_ModuleAddress adcSel, const bool doEnable) {
    ADC_ModuleRegisters* const pAdcSel = (ADC_ModuleRegisters*)adcSel;
    if (doEnable) {
        // Enable the selected ADC DMA request
        pAdcSel->CR2 |= CR2_DMA_Set;
    }
    else {
        // Disable the selected ADC DMA request
        pAdcSel->CR2 &= CR2_DMA_Reset;
    }
}

void ADC_ResetCalibration(const ADC_ModuleAddress adcSel) {
    ADC_ModuleRegisters* const pAdcSel = (ADC_ModuleRegisters*)adcSel;
    // Resets the selected ADC calibration registers
    pAdcSel->CR2 |= CR2_RSTCAL_Set;
}

bool ADC_GetResetCalibrationStatus(const ADC_ModuleAddress adcSel) {
    const ADC_ModuleRegisters* const pAdcSel = (ADC_ModuleRegisters*)adcSel;
    // Check the status of RSTCAL bit
    return (pAdcSel->CR2 & CR2_RSTCAL_Set) != 0;
}

void ADC_StartCalibration(const ADC_ModuleAddress adcSel) {
    ADC_ModuleRegisters* const pAdcSel = (ADC_ModuleRegisters*)adcSel;
    // Enable the selected ADC calibration process
    pAdcSel->CR2 |= CR2_CAL_Set;
}

bool ADC_GetCalibrationStatus(const ADC_ModuleAddress adcSel) {
    const ADC_ModuleRegisters* const pAdcSel = (ADC_ModuleRegisters*)adcSel;
    return (pAdcSel->CR2 & CR2_CAL_Set) != 0;
}

void ADC_SoftwareStartConv(const ADC_ModuleAddress adcSel, const bool doEnable) {
    ADC_ModuleRegisters* const pAdcSel = (ADC_ModuleRegisters*)adcSel;
    if (doEnable) {
        // Enable the selected ADC conversion on external event and start the selected ADC conversion */
        pAdcSel->CR2 |= CR2_EXTTRIG_SWSTART_Set;
    }
    else {
        // Disable the selected ADC conversion on external event and stop the selected ADC conversion
        pAdcSel->CR2 &= CR2_EXTTRIG_SWSTART_Reset;
    }
}

