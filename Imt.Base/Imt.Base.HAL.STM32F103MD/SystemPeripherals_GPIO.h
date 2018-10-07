// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#ifndef SYSTEMPERIPHERALS_GPIO_H
#define SYSTEMPERIPHERALS_GPIO_H

// Must be very first include
#include <Imt.Base.Core.Platform/Platform.h>

// Project includes
#include "SystemMemoryMap.h"

// Determine if a C++ compiler is being used.  If so, ensure that standard C is used to process the API information.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//@{
// General-purpose and alternate-function I/Os (GPIO) peripheral module.
//
// Reference: ST_CortexM3_STM32F103_TRM_Rev15.pdf Chapter 9
// @author lbreitenmoser
//@}

//@{
// Enumeration of the available GPIO modules
//@}
typedef enum {
    GPIO_ModuleAddress_GPIOA = GPIOA_BASE,
    GPIO_ModuleAddress_GPIOB = GPIOB_BASE,
    GPIO_ModuleAddress_GPIOC = GPIOC_BASE,
    GPIO_ModuleAddress_GPIOD = GPIOD_BASE,
    GPIO_ModuleAddress_GPIOE = GPIOE_BASE
} GPIO_ModuleAddress;

//@{
// Output Maximum frequency selection
//@}
typedef enum {
    GPIO_Speed_10MHz = 1,
    GPIO_Speed_2MHz,
    GPIO_Speed_50MHz
} GPIO_Speed;

//@{
// Configuration Mode enumeration
//@}
typedef enum {
    // Analog Input
    GPIO_Mode_AIN = 0x0,
    // Floating Input
    GPIO_Mode_IN_FLOATING = 0x04,
    // Input w/ PullDown
    GPIO_Mode_IPD = 0x28,
    // Input w/ PullUp
    GPIO_Mode_IPU  = 0x48,
    // Output OpenDrain
    GPIO_Mode_Out_OD = 0x14,
    // Output PushPull
    GPIO_Mode_Out_PP = 0x10,
    // AlternateFunction OpenDrain
    GPIO_Mode_AF_OD = 0x1C,
    // AlternateFunction PushPull
    GPIO_Mode_AF_PP = 0x18
} GPIO_Mode;

//@{
// GPIO Init structure definition
//@}
typedef struct {
    uint16_t Pin;
    GPIO_Speed Speed;
    GPIO_Mode Mode;
} GPIO_InitStruct;

//@{
// Definition of GPIO pins
//@}
#define GPIO_Pin_0      ((uint16_t)0x0001)
#define GPIO_Pin_1      ((uint16_t)0x0002)
#define GPIO_Pin_2      ((uint16_t)0x0004)
#define GPIO_Pin_3      ((uint16_t)0x0008)
#define GPIO_Pin_4      ((uint16_t)0x0010)
#define GPIO_Pin_5      ((uint16_t)0x0020)
#define GPIO_Pin_6      ((uint16_t)0x0040)
#define GPIO_Pin_7      ((uint16_t)0x0080)
#define GPIO_Pin_8      ((uint16_t)0x0100)
#define GPIO_Pin_9      ((uint16_t)0x0200)
#define GPIO_Pin_10     ((uint16_t)0x0400)
#define GPIO_Pin_11     ((uint16_t)0x0800)
#define GPIO_Pin_12     ((uint16_t)0x1000)
#define GPIO_Pin_13     ((uint16_t)0x2000)
#define GPIO_Pin_14     ((uint16_t)0x4000)
#define GPIO_Pin_15     ((uint16_t)0x8000)
// All pins selected
#define GPIO_Pin_All    ((uint16_t)0xFFFF)

//@{
// Definition of GPIO ports
//@}
typedef enum {
    GPIO_PortSourceA = ((uint8_t)0x00),
    GPIO_PortSourceB = ((uint8_t)0x01),
    GPIO_PortSourceC = ((uint8_t)0x02),
    GPIO_PortSourceD = ((uint8_t)0x03),
    GPIO_PortSourceE = ((uint8_t)0x04),
    GPIO_PortSourceF = ((uint8_t)0x05),
    GPIO_PortSourceG = ((uint8_t)0x06)
} GPIO_PortSource;

//@{
// Definition of pin source
//@}
typedef enum {
    GPIO_PinSource0  = ((uint8_t)0x00),
    GPIO_PinSource1  = ((uint8_t)0x01),
    GPIO_PinSource2  = ((uint8_t)0x02),
    GPIO_PinSource3  = ((uint8_t)0x03),
    GPIO_PinSource4  = ((uint8_t)0x04),
    GPIO_PinSource5  = ((uint8_t)0x05),
    GPIO_PinSource6  = ((uint8_t)0x06),
    GPIO_PinSource7  = ((uint8_t)0x07),
    GPIO_PinSource8  = ((uint8_t)0x08),
    GPIO_PinSource9  = ((uint8_t)0x09),
    GPIO_PinSource10 = ((uint8_t)0x0A),
    GPIO_PinSource11 = ((uint8_t)0x0B),
    GPIO_PinSource12 = ((uint8_t)0x0C),
    GPIO_PinSource13 = ((uint8_t)0x0D),
    GPIO_PinSource14 = ((uint8_t)0x0E),
    GPIO_PinSource15 = ((uint8_t)0x0F)
} GPIO_PinSource;

//@{
// Definition of alternative function mappings
//@}
typedef enum {
    // CAN1 Alternate Function mapping
    GPIO_Remap2_CAN1 = ((uint32_t)0x001D6000),
    // Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST
    GPIO_Remap_SWJ_NoJTRST = ((uint32_t)0x00300100)
} GPIO_Remap;

//@{
// Initializes the GPIOx peripheral according to the specified parameters in the GPIO_InitStruct
// @param       - port: where x can be (A..G) to select the GPIO peripheral.
//              - initStruct: pointer to a GPIO_InitStruct structure that contains the configuration information for the specified GPIO peripheral.
//@}
void GPIO_Init(const GPIO_ModuleAddress module, const GPIO_InitStruct* const pInitStruct);

//@{
// Sets the selected data port bits.
// Note: Should only be used if you like to set multiple bits at once.
// For a set of a single bit considider using Bitband operation where each GPIO pin has an own 32-bit value mapped into system memory (@see SystemMemoryMap.h)
// @param       - port: where x can be (A..G) to select the GPIO peripheral.
//              - GPIO_Pin: specifies the port bits to be written.
//                          This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
//@}
void GPIO_SetBits(const GPIO_ModuleAddress module, const uint16_t GPIO_Pin);

//@{
// Clears the selected data port bits.
// Note: Should only be used if you like to set multiple bits at once.
// For a set of a single bit considider using Bitband operation where each GPIO pin has an own 32-bit value mapped into system memory (@see SystemMemoryMap.h)
// @param       - port: where x can be (A..G) to select the GPIO peripheral.
//              - GPIO_Pin: specifies the port bits to be written.
//                          This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
//@}
void GPIO_ResetBits(const GPIO_ModuleAddress module, const uint16_t GPIO_Pin);

//@{
// Selects the GPIO pin used as EXTI Line.
// @param portSource: selects the GPIO port to be used as source for EXTI lines.
// @param pinSource: specifies the EXTI line to be configured.
//@}
void GPIO_EXTILineConfig(const GPIO_PortSource portSource, const GPIO_PinSource pinSource);

//@{
// Changes the mapping of the specified pin.
// @param   remap: selects the pin to remap.
// @param   doEnable: flag if enabled.
//@}
void GPIO_PinRemapConfig(const GPIO_Remap remap, const bool doEnable);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SYSTEMPERIPHERALS_GPIO_H
