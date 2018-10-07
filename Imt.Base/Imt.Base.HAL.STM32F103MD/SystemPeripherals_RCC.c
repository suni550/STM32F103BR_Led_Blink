// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#include "SystemPeripherals_RCC.h"

// Project includes
#include "SystemMemoryMap.h"

// Private typedef for RCC registers
//lint -save
//lint -e754 // local structure member not referenced (offset required for correct register access)
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
} RCC_ModuleRegisters;
//lint -restore

#define RCC ((RCC_ModuleRegisters*)RCC_BASE)

// CFGR register bit mask
#define CFGR_SWS_Mask             ((uint32_t)0x0000000C)
#define CFGR_SW_Reset_Mask        ((uint32_t)0xFFFFFFFC)
#define CFGR_PLLMull_Mask         ((uint32_t)0x003C0000)
#define CFGR_PLLSRC_Mask          ((uint32_t)0x00010000)
#define CFGR_PLLXTPRE_Mask        ((uint32_t)0x00020000)
#define CFGR_HPRE_Reset_Mask      ((uint32_t)0xFFFFFF0F)
#define CFGR_HPRE_Set_Mask        ((uint32_t)0x000000F0)
#define CFGR_PPRE1_Reset_Mask     ((uint32_t)0xFFFFF8FF)
#define CFGR_PPRE1_Set_Mask       ((uint32_t)0x00000700)
#define CFGR_PPRE2_Reset_Mask     ((uint32_t)0xFFFFC7FF)
#define CFGR_PPRE2_Set_Mask       ((uint32_t)0x00003800)
#define CFGR_ADCPRE_Set_Mask      ((uint32_t)0x0000C000)
#define CFGR_MCO_Reset_Mask       ((uint32_t)0xF8FFFFFF)

// CSR register bit masks
#define CSR_WWDGRSTF_Mask         ((uint32_t)0x40000000)
#define CSR_RMVF_Mask             ((uint32_t)0x01000000)

// Alias word addresses
#define RCC_CR_OFFSET             0x00
#define CR_PLLON_BitNumber        24
#define CR_PLLRDY_BitNumber       25
#define CR_PLLON_BITBAND          BITBAND_PERIPH((RCC_BASE + RCC_CR_OFFSET), CR_PLLON_BitNumber)
#define CR_PLLRDY_BITBAND         BITBAND_PERIPH((RCC_BASE + RCC_CR_OFFSET), CR_PLLRDY_BitNumber)

// Typical Value of the HSI in Hz
#define HSI_Value                 ((uint32_t)8000000)
// Value of the External oscillator in Hz
#define HSE_Value                 ((uint32_t)8000000)

// HSI used as system clock
#define CFGR_SWS_HSI_VALUE        (0x00)
// HSE used as system clock
#define CFGR_SWS_HSE_VALUE        (0x04)
// PLL used as system clock
#define CFGR_SWS_PLL_VALUE        (0x08)


void RCC_EnableAPB1PeripheralClock(const RCC_APB1Periph module, const bool enabled) {
    if (enabled) {
        RCC->APB1ENR |= (uint32_t)module;
    }
    else {
        RCC->APB1ENR &= ~((uint32_t)module);
    }
}

void RCC_EnableAPB2PeripheralClock(const RCC_APB2Periph module, const bool enabled) {
  if (enabled) {
    RCC->APB2ENR |= (uint32_t)module;
  }
  else {
    RCC->APB2ENR &= ~((uint32_t)module);
  }
}

void RCC_ResetAPB1Peripheral(const RCC_APB1Periph module, const bool doReset) {
    if(doReset) {
        RCC->APB1RSTR |= module;
    }
    else {
        RCC->APB1RSTR &= (~module);
    }
}


void RCC_ResetAPB2Peripheral(const RCC_APB2Periph module, const bool doReset) {
    if(doReset) {
        RCC->APB2RSTR |= module;
    }
    else {
        RCC->APB2RSTR &= (~module);
    }
}

void RCC_EnableAHBPeriphClock(const RCC_AHBPeriph module, const bool enabled) {
    if (enabled) {
        RCC->AHBENR |= (uint32_t)module;
    }
    else {
        RCC->AHBENR &= ~((uint32_t)module);
    }
}

RCC_Clocks RCC_GetClocksFreq(void) {
    RCC_Clocks clocks;
    uint32_t tmp = 0;
    uint32_t pllmull = 0;
    uint32_t pllsource = 0;
    uint32_t presc = 0;
    static uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
    static uint8_t ADCPrescTable[4] = {2, 4, 6, 8};

    // Get SYSCLK source -------------------------------------------------------
    tmp = RCC->CFGR & CFGR_SWS_Mask;

    switch (tmp) {
        case CFGR_SWS_HSI_VALUE:
            clocks.SYSCLK_Frequency = HSI_Value;
            break;
        case CFGR_SWS_HSE_VALUE:
            clocks.SYSCLK_Frequency = HSE_Value;
            break;
        case CFGR_SWS_PLL_VALUE:
            // Get PLL clock source and multiplication factor ----------------------
            pllmull = RCC->CFGR & CFGR_PLLMull_Mask;
            pllmull = ( pllmull >> 18) + 2;

            pllsource = RCC->CFGR & CFGR_PLLSRC_Mask;

            if (pllsource == 0x00) {
                // HSI oscillator clock divided by 2 selected as PLL clock entry
                clocks.SYSCLK_Frequency = (HSI_Value >> 1) * pllmull;
            }
            else {
                // HSE selected as PLL clock entry
                if ((RCC->CFGR & CFGR_PLLXTPRE_Mask) != 0) {
                    // HSE oscillator clock divided by 2
                    clocks.SYSCLK_Frequency = (HSE_Value >> 1) * pllmull;
                }
                else {
                    clocks.SYSCLK_Frequency = HSE_Value * pllmull;
                }
            }
            break;
        default:
            clocks.SYSCLK_Frequency = HSI_Value;
            break;
    }

    // Compute HCLK, PCLK1, PCLK2 and ADCCLK clocks frequencies ----------------
    // Get HCLK prescaler
    tmp = RCC->CFGR & CFGR_HPRE_Set_Mask;
    tmp = tmp >> 4;
    presc = APBAHBPrescTable[tmp];

    // HCLK clock frequency
    clocks.HCLK_Frequency = clocks.SYSCLK_Frequency >> presc;

    // Get PCLK1 prescaler
    tmp = RCC->CFGR & CFGR_PPRE1_Set_Mask;
    tmp = tmp >> 8;
    presc = APBAHBPrescTable[tmp];

    // PCLK1 clock frequency
    clocks.PCLK1_Frequency = clocks.HCLK_Frequency >> presc;

    // Get PCLK2 Prescaler
    tmp = RCC->CFGR & CFGR_PPRE2_Set_Mask;
    tmp = tmp >> 11;
    presc = APBAHBPrescTable[tmp];

    // PCLK2 clock frequency
    clocks.PCLK2_Frequency = clocks.HCLK_Frequency >> presc;

    // Get ADCCLK Prescaler
    tmp = RCC->CFGR & CFGR_ADCPRE_Set_Mask;
    tmp = tmp >> 14;
    presc = ADCPrescTable[tmp];

    // ADCCLK clock frequency
    clocks.ADCCLK_Frequency = clocks.PCLK2_Frequency / presc;

    return clocks;
}

bool RCC_IsWindowWatchdogReset(void) {
    const bool isWindowWatchdogReset = ((RCC->CSR & CSR_WWDGRSTF_Mask) != 0);
    return isWindowWatchdogReset;
}

void RCC_ClearResetFlags(void) {
    // Set RMVF bit to clear the reset flags
    RCC->CSR |= CSR_RMVF_Mask;
}

void RCC_SetMcoClockSource(const RCC_McoClkSrc mcoClockSource) {
    uint32_t tempReg = RCC->CFGR;
    // Modify MCO[2:0] bits
    tempReg &= CFGR_MCO_Reset_Mask;
    tempReg |= (uint32_t)mcoClockSource;
    RCC->CFGR = tempReg;
}

void RCC_HCLKConfig(const RCC_SysclkDiv sysclkDiv) {
    uint32_t tempReg = RCC->CFGR;
    // Modify HPRE[3:0] bits
    tempReg &= CFGR_HPRE_Reset_Mask;
    tempReg |= (uint32_t)sysclkDiv;
    RCC->CFGR = tempReg;
}

void RCC_PCLK1Config(const RCC_HclkDiv hclkDiv) {
    uint32_t tempReg = RCC->CFGR;
    // Modify PPRE1[2:0] bits
    tempReg &= CFGR_PPRE1_Reset_Mask;
    tempReg |= (uint32_t)hclkDiv;
    RCC->CFGR = tempReg;
}

void RCC_PCLK2Config(const RCC_HclkDiv hclkDiv) {
    const uint32_t OFFSET_FROM_PPRE1 = 3U;
    uint32_t tempReg = RCC->CFGR;
    // Modify PPRE2[2:0] bits
    tempReg &= CFGR_PPRE2_Reset_Mask;
    tempReg |= ((uint32_t)hclkDiv << OFFSET_FROM_PPRE1);
    RCC->CFGR = tempReg;
}

void RCC_PllConfig(const RCC_PllClkSrc pllClkSrc, const RCC_PllMul pllMul) {
    uint32_t tempReg = RCC->CFGR;
    // Modify PLLSRC, PLLXTPRE and PLLMUL[3:0] bits
    tempReg &= ~(CFGR_PLLMull_Mask | CFGR_PLLSRC_Mask | CFGR_PLLXTPRE_Mask);
    tempReg |= ((uint32_t)pllClkSrc | (uint32_t)pllMul);
    RCC->CFGR = tempReg;
}

void RCC_SetPllState(const bool enable) {
    // Modify PLLON bit of the CR register
    CR_PLLON_BITBAND = (uint32_t)enable;
}

bool RCC_IsPllReady(void) {
    // Check PLLRDY bit of the CR register
    return (CR_PLLRDY_BITBAND != 0U);
}

void RCC_SYSCLKConfig(const RCC_SysclkSrc sysclkSrc) {
    uint32_t tempReg = RCC->CFGR;
    // Modify SW[1:0] bits
    tempReg &= CFGR_SW_Reset_Mask;
    tempReg |= (uint32_t)sysclkSrc;
    RCC->CFGR = tempReg;
}

RCC_SysclkSrc RCC_GetSYSCLKSource(void) {
    const uint32_t OFFSET_FROM_SW = 2U;
    // Read SW[1:0]
    uint32_t tempReg = (RCC->CFGR & CFGR_SWS_Mask);
    // Map to return enum
    tempReg = tempReg >> OFFSET_FROM_SW;
    return (RCC_SysclkSrc)tempReg;
}

