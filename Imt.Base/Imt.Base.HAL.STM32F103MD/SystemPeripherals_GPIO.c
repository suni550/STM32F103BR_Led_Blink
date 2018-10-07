// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

// Project includes
#include "SystemPeripherals_GPIO.h"

// Imt.Base includes
#include <Imt.Base.Core.Diagnostics/Diagnostics.h>

//@{
// GPIO module register structure
//@}
typedef struct {
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_ModuleRegisters;

//@{
// Alternate Function I/O register structure
//@}
typedef struct {
    volatile uint32_t EVCR;
    volatile uint32_t MAPR;
    volatile uint32_t EXTICR[4];
    uint32_t RESERVED0;
    volatile uint32_t MAPR2;
} AFIO_ModuleRegisters;

// MAPR Register masks
#define LSB_MASK                    ((uint16_t)0xFFFF)
#define DBGAFR_POSITION_MASK        ((uint32_t)0x000F0000)
#define DBGAFR_SWJCFG_MASK          ((uint32_t)0xF0FFFFFF)
#define DBGAFR_LOCATION_MASK        ((uint32_t)0x00200000)
#define DBGAFR_NUMBITS_MASK         ((uint32_t)0x00100000)

void GPIO_Init(const GPIO_ModuleAddress module, const GPIO_InitStruct* const pInitStruct) {
    if (pInitStruct == NULL) {
        ASSERT_DEBUG(false);
        return;
    }

    GPIO_ModuleRegisters* const pGPIO = (GPIO_ModuleRegisters*)module;

    // GPIO Mode Configuration
    uint32_t currentmode = ((uint32_t)pInitStruct->Mode) & ((uint32_t)0x0F);

    if ((((uint32_t)pInitStruct->Mode) & ((uint32_t)0x10)) != 0x00) {
        // Output mode
        currentmode |= (uint32_t)pInitStruct->Speed;
    }

    // GPIO CRL Configuration
    // Configure the eight low port pins
    if (((uint32_t)pInitStruct->Pin & ((uint32_t)0x00FF)) != 0x00) {
        uint32_t tmpreg = pGPIO->CRL;

        for (uint32_t pinpos = 0x00; pinpos < 0x08; pinpos++) {
            uint32_t pos = ((uint32_t)0x01) << pinpos;
            // Get the port pins position
            const uint32_t currentpin = (pInitStruct->Pin) & pos;

            if (currentpin == pos) {
                pos = pinpos << 2;
                // Clear the corresponding low control register bits
                const uint32_t pinmask = ((uint32_t)0x0F) << pos;
                tmpreg &= ~pinmask;

                // Write the mode configuration in the corresponding bits
                tmpreg |= (currentmode << pos);

                // Reset the corresponding ODR bit
                if (pInitStruct->Mode == GPIO_Mode_IPD) {
                    pGPIO->BRR = (((uint32_t)0x01) << pinpos);
                }
                // Set the corresponding ODR bit
                if (pInitStruct->Mode == GPIO_Mode_IPU) {
                    pGPIO->BSRR = (((uint32_t)0x01) << pinpos);
                }
            }
        }
        pGPIO->CRL = tmpreg;
    }

    // GPIO CRH Configuration
    // Configure the eight high port pins
    if (pInitStruct->Pin > 0x00FF) {
        uint32_t tmpreg = pGPIO->CRH;
        for (uint32_t pinpos = 0x00; pinpos < 0x08; pinpos++) {
            uint32_t pos = (((uint32_t)0x01) << (pinpos + 0x08));
            // Get the port pins position
            const uint32_t currentpin = ((pInitStruct->Pin) & pos);
            if (currentpin == pos) {
                pos = pinpos << 2;
                // Clear the corresponding high control register bits
                const uint32_t pinmask = ((uint32_t)0x0F) << pos;
                tmpreg &= ~pinmask;

                // Write the mode configuration in the corresponding bits
                tmpreg |= (currentmode << pos);

                // Reset the corresponding ODR bit
                if (pInitStruct->Mode == GPIO_Mode_IPD) {
                    pGPIO->BRR = (((uint32_t)0x01) << (pinpos + 0x08));
                }
                // Set the corresponding ODR bit
                if (pInitStruct->Mode == GPIO_Mode_IPU) {
                    pGPIO->BSRR = (((uint32_t)0x01) << (pinpos + 0x08));
                }
            }
        }
        pGPIO->CRH = tmpreg;
    }
}

void GPIO_SetBits(const GPIO_ModuleAddress module, const uint16_t GPIO_Pin) {
    GPIO_ModuleRegisters* const pGPIO = (GPIO_ModuleRegisters*)module;
    pGPIO->BSRR = GPIO_Pin;
}

void GPIO_ResetBits(const GPIO_ModuleAddress module, const uint16_t GPIO_Pin) {
    GPIO_ModuleRegisters* const pGPIO = (GPIO_ModuleRegisters*)module;
    pGPIO->BRR = GPIO_Pin;
}

void GPIO_EXTILineConfig(const GPIO_PortSource portSource, const GPIO_PinSource pinSource) {
    AFIO_ModuleRegisters* const pAFIO = (AFIO_ModuleRegisters*)AFIO_BASE;

    const uint32_t tmp = ((uint32_t)0x0F) << (0x04 * ((uint8_t)pinSource & (uint8_t)0x03));
    pAFIO->EXTICR[(uint8_t)pinSource >> 0x02] &= ~tmp;
    pAFIO->EXTICR[(uint8_t)pinSource >> 0x02] |= (((uint32_t)portSource) << (0x04 * ((uint8_t)pinSource & (uint8_t)0x03)));
}

void GPIO_PinRemapConfig(const GPIO_Remap remap, const bool doEnable) {
    AFIO_ModuleRegisters* const pAFIO = (AFIO_ModuleRegisters*)AFIO_BASE;

    uint32_t tmpreg;
    if(((uint32_t)remap & 0x80000000) == 0x80000000) {
        tmpreg = pAFIO->MAPR2;
    }
    else {
        tmpreg = pAFIO->MAPR;
    }

    const uint32_t tmpmask = ((uint32_t)remap & DBGAFR_POSITION_MASK) >> 0x10;
    const uint32_t tmp = (uint32_t)remap & LSB_MASK;

    if (((uint32_t)remap & (DBGAFR_LOCATION_MASK | DBGAFR_NUMBITS_MASK)) == (DBGAFR_LOCATION_MASK | DBGAFR_NUMBITS_MASK)) {
        tmpreg &= DBGAFR_SWJCFG_MASK;
        pAFIO->MAPR &= DBGAFR_SWJCFG_MASK;
    }
    else if (((uint32_t)remap & DBGAFR_NUMBITS_MASK) == DBGAFR_NUMBITS_MASK) {
        const uint32_t tmp1 = ((uint32_t)0x03) << tmpmask;
        tmpreg &= ~tmp1;
        tmpreg |= ~DBGAFR_SWJCFG_MASK;
    }
    else {
        tmpreg &= ~(tmp << (((uint32_t)remap >> 0x15)*0x10));
        tmpreg |= ~DBGAFR_SWJCFG_MASK;
    }

    if (doEnable) {
        tmpreg |= (tmp << (((uint32_t)remap >> 0x15)*0x10));
    }

    if(((uint32_t)remap & 0x80000000) == 0x80000000) {
        pAFIO->MAPR2 = tmpreg;
    }
    else {
        pAFIO->MAPR = tmpreg;
    }
}
