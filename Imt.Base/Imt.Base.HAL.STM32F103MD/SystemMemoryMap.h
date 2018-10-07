// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#ifndef SYSTEMMEMORYMAP_H
#define SYSTEMMEMORYMAP_H

// Must be very first include
#include <Imt.Base.Core.Platform/Platform.h>

//@{
// Definition of hardware memory map.
// @author mguntli
//@}

//------------------------------------------------------------------------------
// CORTEX-M3 generic base address
// Reference: Cortex-M3 Devices Generic User Guide DUI0552A Table 4-1
//------------------------------------------------------------------------------
// System timer base address
#define SYSTICK_BASE          ((uint32_t)0xE000E010)
// System Control Space Base Address
#define SCS_BASE              ((uint32_t)0xE000E000)
// NVIC Base Address
#define NVIC_BASE             (SCS_BASE + 0x0100)
// System Control Block Base Address
#define SCB_BASE              (SCS_BASE + 0x0D00)

//------------------------------------------------------------------------------
// Peripheral memory map of STM32F103
// Reference: ST_CortexM3_STM32F103_TRM_Rev15.pdf Chapter 3.3
//------------------------------------------------------------------------------
// FLASH base address in the alias region
#define FLASH_BASE            ((uint32_t)0x08000000)
// SRAM base address in the alias region
#define SRAM_BASE             ((uint32_t)0x20000000)
// Peripheral base address in the alias region
#define PERIPH_BASE           ((uint32_t)0x40000000)

//------------------------------------------------------------------------------
// Bus specific base address for medium-density STM32F103x8 and STM32F103xB
// Reference: ST_CortexM3_STM32F103_Datasheet_Rev16.pdf for peripheral availability
//------------------------------------------------------------------------------
#define APB1PERIPH_BASE       (PERIPH_BASE)
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)

//------------------------------------------------------------------------------
// Peripheral module base address for medium-density STM32F103x8 and STM32F103xB
// Reference: ST_CortexM3_STM32F103_TRM_Rev15.pdf Table 3 Register boundary addresses
// Reference: ST_CortexM3_STM32F103_Datasheet_Rev16.pdf for peripheral availability
//------------------------------------------------------------------------------
#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000)
#define TIM3_BASE             (APB1PERIPH_BASE + 0x0400)
#define TIM4_BASE             (APB1PERIPH_BASE + 0x0800)
#define RTC_BASE              (APB1PERIPH_BASE + 0x2800)
#define WWDG_BASE             (APB1PERIPH_BASE + 0x2C00)
#define IWDG_BASE             (APB1PERIPH_BASE + 0x3000)
#define SPI2_BASE             (APB1PERIPH_BASE + 0x3800)
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400)
#define USART3_BASE           (APB1PERIPH_BASE + 0x4800)
#define I2C1_BASE             (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASE             (APB1PERIPH_BASE + 0x5800)
#define CAN_BASE              (APB1PERIPH_BASE + 0x6400)
#define BKP_BASE              (APB1PERIPH_BASE + 0x6C00)
#define PWR_BASE              (APB1PERIPH_BASE + 0x7000)

#define AFIO_BASE             (APB2PERIPH_BASE + 0x0000)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x0400)
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x0C00)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400)
#define GPIOE_BASE            (APB2PERIPH_BASE + 0x1800)
#define ADC1_BASE             (APB2PERIPH_BASE + 0x2400)
#define ADC2_BASE             (APB2PERIPH_BASE + 0x2800)
#define TIM1_BASE             (APB2PERIPH_BASE + 0x2C00)
#define SPI1_BASE             (APB2PERIPH_BASE + 0x3000)
#define USART1_BASE           (APB2PERIPH_BASE + 0x3800)

#define DMA1_BASE             (AHBPERIPH_BASE + 0x0000)
#define RCC_BASE              (AHBPERIPH_BASE + 0x1000)
#define FLASH_MEMORY_IFC_BASE (AHBPERIPH_BASE + 0x2000)
#define CRC_BASE              (AHBPERIPH_BASE + 0x3000)

//------------------------------------------------------------------------------
// Base addresses for DMA channels
// Reference: ST_CortexM3_STM32F103_TRM_Rev15.pdf Section 13.4.7 DMA register map
//------------------------------------------------------------------------------
#define DMA1_Channel1_BASE    (DMA1_BASE + 0x0008)
#define DMA1_Channel2_BASE    (DMA1_BASE + 0x001C)
#define DMA1_Channel3_BASE    (DMA1_BASE + 0x0030)
#define DMA1_Channel4_BASE    (DMA1_BASE + 0x0044)
#define DMA1_Channel5_BASE    (DMA1_BASE + 0x0058)
#define DMA1_Channel6_BASE    (DMA1_BASE + 0x006C)
#define DMA1_Channel7_BASE    (DMA1_BASE + 0x0080)

//------------------------------------------------------------------------------
// Macro for bit banding: Direct bit access to registers
// Reference: ST_CortexM3_STM32F103_TRM_Rev15.pdf Section 3.3.2 Bit banding
//------------------------------------------------------------------------------
#define BITBAND_SRAM_BASE     (0x22000000) /* SRAM base address in the bit-band region */
#define BITBAND_PERIPH_BASE   (0x42000000) /* Peripheral base address in the bit-band region */

// Bit banding in the peripheral memory area
// VarAddr:   address of the byte in the bit-band region that contains the targeted bit
// BitNumber: the bit position of the targeted bit
#define BITBAND_PERIPH(VarAddr, BitNumber) (*(volatile uint32_t *) (BITBAND_PERIPH_BASE | (((VarAddr) - PERIPH_BASE) << 5) | ((BitNumber) << 2)))

// Bit banding in the SRAM memory area
// VarAddr:   address of the byte in the bit-band region that contains the targeted bit
// BitNumber: the bit position of the targeted bit
#define BITBAND_SRAM(VarAddr, BitNumber) (*(volatile uint32_t *) (BITBAND_SRAM_BASE | (((VarAddr) - SRAM_BASE) << 5) | ((BitNumber) << 2)))

//------------------------------------------------------------------------------
// Offset for direct pin access to GPIOx via bit banding
//------------------------------------------------------------------------------
#define GPIOX_IDR_OFFSET 0x08 /* Offset from GPIO Port to Port input data register */
#define GPIOX_ODR_OFFSET 0x0C /* Offset from GPIO Port to Port output data register */
//------------------------------------------------------------------------------
// GPIO PortA write
//------------------------------------------------------------------------------
#define GPIOA_0_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 0)
#define GPIOA_1_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 1)
#define GPIOA_2_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 2)
#define GPIOA_3_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 3)
#define GPIOA_4_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 4)
#define GPIOA_5_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 5)
#define GPIOA_6_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 6)
#define GPIOA_7_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 7)
#define GPIOA_8_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 8)
#define GPIOA_9_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 9)
#define GPIOA_10_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 10)
#define GPIOA_11_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 11)
#define GPIOA_12_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 12)
#define GPIOA_13_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 13)
#define GPIOA_14_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 14)
#define GPIOA_15_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 15)
#define GPIOA_16_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 16)
#define GPIOA_17_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 17)
#define GPIOA_18_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 18)
#define GPIOA_19_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 19)
#define GPIOA_20_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 20)
#define GPIOA_21_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 21)
#define GPIOA_22_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 22)
#define GPIOA_23_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 23)
#define GPIOA_24_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 24)
#define GPIOA_25_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 25)
#define GPIOA_26_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 26)
#define GPIOA_27_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 27)
#define GPIOA_28_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 28)
#define GPIOA_29_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 29)
#define GPIOA_30_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 30)
#define GPIOA_31_WRITE_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_ODR_OFFSET), 31)
//------------------------------------------------------------------------------
// GPIO PortA read
//------------------------------------------------------------------------------
#define GPIOA_0_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 0)
#define GPIOA_1_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 1)
#define GPIOA_2_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 2)
#define GPIOA_3_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 3)
#define GPIOA_4_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 4)
#define GPIOA_5_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 5)
#define GPIOA_6_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 6)
#define GPIOA_7_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 7)
#define GPIOA_8_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 8)
#define GPIOA_9_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 9)
#define GPIOA_10_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 10)
#define GPIOA_11_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 11)
#define GPIOA_12_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 12)
#define GPIOA_13_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 13)
#define GPIOA_14_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 14)
#define GPIOA_15_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 15)
#define GPIOA_16_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 16)
#define GPIOA_17_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 17)
#define GPIOA_18_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 18)
#define GPIOA_19_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 19)
#define GPIOA_20_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 20)
#define GPIOA_21_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 21)
#define GPIOA_22_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 22)
#define GPIOA_23_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 23)
#define GPIOA_24_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 24)
#define GPIOA_25_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 25)
#define GPIOA_26_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 26)
#define GPIOA_27_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 27)
#define GPIOA_28_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 28)
#define GPIOA_29_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 29)
#define GPIOA_30_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 30)
#define GPIOA_31_READ_ADDR BITBAND_PERIPH((GPIOA_BASE + GPIOX_IDR_OFFSET), 31)
//------------------------------------------------------------------------------
// GPIO PortB write
//------------------------------------------------------------------------------
#define GPIOB_0_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 0)
#define GPIOB_1_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 1)
#define GPIOB_2_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 2)
#define GPIOB_3_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 3)
#define GPIOB_4_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 4)
#define GPIOB_5_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 5)
#define GPIOB_6_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 6)
#define GPIOB_7_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 7)
#define GPIOB_8_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 8)
#define GPIOB_9_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 9)
#define GPIOB_10_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 10)
#define GPIOB_11_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 11)
#define GPIOB_12_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 12)
#define GPIOB_13_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 13)
#define GPIOB_14_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 14)
#define GPIOB_15_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 15)
#define GPIOB_16_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 16)
#define GPIOB_17_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 17)
#define GPIOB_18_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 18)
#define GPIOB_19_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 19)
#define GPIOB_20_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 20)
#define GPIOB_21_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 21)
#define GPIOB_22_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 22)
#define GPIOB_23_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 23)
#define GPIOB_24_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 24)
#define GPIOB_25_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 25)
#define GPIOB_26_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 26)
#define GPIOB_27_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 27)
#define GPIOB_28_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 28)
#define GPIOB_29_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 29)
#define GPIOB_30_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 30)
#define GPIOB_31_WRITE_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_ODR_OFFSET), 31)
//------------------------------------------------------------------------------
// GPIO PortB read
//------------------------------------------------------------------------------
#define GPIOB_0_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 0)
#define GPIOB_1_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 1)
#define GPIOB_2_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 2)
#define GPIOB_3_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 3)
#define GPIOB_4_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 4)
#define GPIOB_5_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 5)
#define GPIOB_6_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 6)
#define GPIOB_7_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 7)
#define GPIOB_8_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 8)
#define GPIOB_9_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 9)
#define GPIOB_10_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 10)
#define GPIOB_11_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 11)
#define GPIOB_12_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 12)
#define GPIOB_13_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 13)
#define GPIOB_14_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 14)
#define GPIOB_15_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 15)
#define GPIOB_16_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 16)
#define GPIOB_17_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 17)
#define GPIOB_18_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 18)
#define GPIOB_19_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 19)
#define GPIOB_20_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 20)
#define GPIOB_21_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 21)
#define GPIOB_22_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 22)
#define GPIOB_23_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 23)
#define GPIOB_24_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 24)
#define GPIOB_25_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 25)
#define GPIOB_26_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 26)
#define GPIOB_27_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 27)
#define GPIOB_28_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 28)
#define GPIOB_29_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 29)
#define GPIOB_30_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 30)
#define GPIOB_31_READ_ADDR BITBAND_PERIPH((GPIOB_BASE + GPIOX_IDR_OFFSET), 31)
//------------------------------------------------------------------------------
// GPIO PortC write
//------------------------------------------------------------------------------
#define GPIOC_0_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 0)
#define GPIOC_1_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 1)
#define GPIOC_2_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 2)
#define GPIOC_3_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 3)
#define GPIOC_4_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 4)
#define GPIOC_5_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 5)
#define GPIOC_6_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 6)
#define GPIOC_7_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 7)
#define GPIOC_8_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 8)
#define GPIOC_9_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 9)
#define GPIOC_10_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 10)
#define GPIOC_11_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 11)
#define GPIOC_12_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 12)
#define GPIOC_13_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 13)
#define GPIOC_14_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 14)
#define GPIOC_15_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 15)
#define GPIOC_16_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 16)
#define GPIOC_17_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 17)
#define GPIOC_18_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 18)
#define GPIOC_19_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 19)
#define GPIOC_20_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 20)
#define GPIOC_21_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 21)
#define GPIOC_22_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 22)
#define GPIOC_23_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 23)
#define GPIOC_24_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 24)
#define GPIOC_25_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 25)
#define GPIOC_26_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 26)
#define GPIOC_27_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 27)
#define GPIOC_28_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 28)
#define GPIOC_29_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 29)
#define GPIOC_30_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 30)
#define GPIOC_31_WRITE_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_ODR_OFFSET), 31)
//------------------------------------------------------------------------------
// GPIO PortC read
//------------------------------------------------------------------------------
#define GPIOC_0_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 0)
#define GPIOC_1_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 1)
#define GPIOC_2_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 2)
#define GPIOC_3_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 3)
#define GPIOC_4_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 4)
#define GPIOC_5_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 5)
#define GPIOC_6_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 6)
#define GPIOC_7_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 7)
#define GPIOC_8_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 8)
#define GPIOC_9_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 9)
#define GPIOC_10_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 10)
#define GPIOC_11_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 11)
#define GPIOC_12_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 12)
#define GPIOC_13_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 13)
#define GPIOC_14_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 14)
#define GPIOC_15_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 15)
#define GPIOC_16_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 16)
#define GPIOC_17_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 17)
#define GPIOC_18_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 18)
#define GPIOC_19_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 19)
#define GPIOC_20_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 20)
#define GPIOC_21_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 21)
#define GPIOC_22_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 22)
#define GPIOC_23_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 23)
#define GPIOC_24_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 24)
#define GPIOC_25_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 25)
#define GPIOC_26_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 26)
#define GPIOC_27_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 27)
#define GPIOC_28_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 28)
#define GPIOC_29_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 29)
#define GPIOC_30_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 30)
#define GPIOC_31_READ_ADDR BITBAND_PERIPH((GPIOC_BASE + GPIOX_IDR_OFFSET), 31)
//------------------------------------------------------------------------------
// GPIO PortD write
//------------------------------------------------------------------------------
#define GPIOD_0_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 0)
#define GPIOD_1_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 1)
#define GPIOD_2_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 2)
#define GPIOD_3_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 3)
#define GPIOD_4_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 4)
#define GPIOD_5_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 5)
#define GPIOD_6_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 6)
#define GPIOD_7_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 7)
#define GPIOD_8_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 8)
#define GPIOD_9_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 9)
#define GPIOD_10_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 10)
#define GPIOD_11_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 11)
#define GPIOD_12_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 12)
#define GPIOD_13_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 13)
#define GPIOD_14_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 14)
#define GPIOD_15_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 15)
#define GPIOD_16_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 16)
#define GPIOD_17_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 17)
#define GPIOD_18_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 18)
#define GPIOD_19_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 19)
#define GPIOD_20_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 20)
#define GPIOD_21_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 21)
#define GPIOD_22_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 22)
#define GPIOD_23_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 23)
#define GPIOD_24_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 24)
#define GPIOD_25_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 25)
#define GPIOD_26_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 26)
#define GPIOD_27_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 27)
#define GPIOD_28_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 28)
#define GPIOD_29_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 29)
#define GPIOD_30_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 30)
#define GPIOD_31_WRITE_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_ODR_OFFSET), 31)
//------------------------------------------------------------------------------
// GPIO PortD read
//------------------------------------------------------------------------------
#define GPIOD_0_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 0)
#define GPIOD_1_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 1)
#define GPIOD_2_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 2)
#define GPIOD_3_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 3)
#define GPIOD_4_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 4)
#define GPIOD_5_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 5)
#define GPIOD_6_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 6)
#define GPIOD_7_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 7)
#define GPIOD_8_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 8)
#define GPIOD_9_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 9)
#define GPIOD_10_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 10)
#define GPIOD_11_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 11)
#define GPIOD_12_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 12)
#define GPIOD_13_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 13)
#define GPIOD_14_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 14)
#define GPIOD_15_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 15)
#define GPIOD_16_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 16)
#define GPIOD_17_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 17)
#define GPIOD_18_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 18)
#define GPIOD_19_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 19)
#define GPIOD_20_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 20)
#define GPIOD_21_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 21)
#define GPIOD_22_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 22)
#define GPIOD_23_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 23)
#define GPIOD_24_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 24)
#define GPIOD_25_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 25)
#define GPIOD_26_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 26)
#define GPIOD_27_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 27)
#define GPIOD_28_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 28)
#define GPIOD_29_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 29)
#define GPIOD_30_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 30)
#define GPIOD_31_READ_ADDR BITBAND_PERIPH((GPIOD_BASE + GPIOX_IDR_OFFSET), 31)
//------------------------------------------------------------------------------
// GPIO PortE write
//------------------------------------------------------------------------------
#define GPIOE_0_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 0)
#define GPIOE_1_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 1)
#define GPIOE_2_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 2)
#define GPIOE_3_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 3)
#define GPIOE_4_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 4)
#define GPIOE_5_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 5)
#define GPIOE_6_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 6)
#define GPIOE_7_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 7)
#define GPIOE_8_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 8)
#define GPIOE_9_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 9)
#define GPIOE_10_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 10)
#define GPIOE_11_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 11)
#define GPIOE_12_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 12)
#define GPIOE_13_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 13)
#define GPIOE_14_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 14)
#define GPIOE_15_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 15)
#define GPIOE_16_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 16)
#define GPIOE_17_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 17)
#define GPIOE_18_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 18)
#define GPIOE_19_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 19)
#define GPIOE_20_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 20)
#define GPIOE_21_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 21)
#define GPIOE_22_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 22)
#define GPIOE_23_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 23)
#define GPIOE_24_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 24)
#define GPIOE_25_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 25)
#define GPIOE_26_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 26)
#define GPIOE_27_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 27)
#define GPIOE_28_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 28)
#define GPIOE_29_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 29)
#define GPIOE_30_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 30)
#define GPIOE_31_WRITE_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_ODR_OFFSET), 31)
//------------------------------------------------------------------------------
// GPIO PortE read
//------------------------------------------------------------------------------
#define GPIOE_0_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 0)
#define GPIOE_1_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 1)
#define GPIOE_2_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 2)
#define GPIOE_3_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 3)
#define GPIOE_4_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 4)
#define GPIOE_5_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 5)
#define GPIOE_6_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 6)
#define GPIOE_7_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 7)
#define GPIOE_8_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 8)
#define GPIOE_9_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 9)
#define GPIOE_10_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 10)
#define GPIOE_11_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 11)
#define GPIOE_12_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 12)
#define GPIOE_13_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 13)
#define GPIOE_14_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 14)
#define GPIOE_15_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 15)
#define GPIOE_16_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 16)
#define GPIOE_17_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 17)
#define GPIOE_18_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 18)
#define GPIOE_19_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 19)
#define GPIOE_20_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 20)
#define GPIOE_21_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 21)
#define GPIOE_22_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 22)
#define GPIOE_23_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 23)
#define GPIOE_24_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 24)
#define GPIOE_25_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 25)
#define GPIOE_26_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 26)
#define GPIOE_27_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 27)
#define GPIOE_28_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 28)
#define GPIOE_29_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 29)
#define GPIOE_30_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 30)
#define GPIOE_31_READ_ADDR BITBAND_PERIPH((GPIOE_BASE + GPIOX_IDR_OFFSET), 31)

#endif // SYSTEMMEMORYMAP_H
