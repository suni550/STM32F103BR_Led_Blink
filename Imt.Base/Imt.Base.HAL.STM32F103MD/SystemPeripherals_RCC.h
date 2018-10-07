// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#ifndef SYSTEMPERIPHERALS_RCC_H
#define SYSTEMPERIPHERALS_RCC_H

// Must be very first include
#include <Imt.Base.Core.Platform/Platform.h>

// Determine if a C++ compiler is being used.  If so, ensure that standard C is used to process the API information.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//@{
// Reset and clock control (RCC) peripheral module
//
// Reference: ST_CortexM3_STM32F103_TRM_Rev15.pdf Chapter 8
// @author lbreitenmoser
//@}

//@{
// Enumeration for APB1 peripheral module identifiers
//@}
typedef enum  {
    RCC_APB1Periph_TIM2   = (uint32_t)0x00000001,
    RCC_APB1Periph_TIM3   = (uint32_t)0x00000002,
    RCC_APB1Periph_TIM4   = (uint32_t)0x00000004,
    RCC_APB1Periph_WWDG   = (uint32_t)0x00000800,
    RCC_APB1Periph_SPI2   = (uint32_t)0x00004000,
    RCC_APB1Periph_USART2 = (uint32_t)0x00020000,
    RCC_APB1Periph_USART3 = (uint32_t)0x00040000,
    RCC_APB1Periph_I2C1   = (uint32_t)0x00200000,
    RCC_APB1Periph_I2C2   = (uint32_t)0x00400000,
    RCC_APB1Periph_CAN    = (uint32_t)0x02000000,
    RCC_APB1Periph_BKP    = (uint32_t)0x08000000,
    RCC_APB1Periph_PWR    = (uint32_t)0x10000000
} RCC_APB1Periph;

//@{
// Enumeration for APB2 peripheral module identifiers
//@}
typedef enum {
  RCC_APB2Periph_AFIO   = (uint32_t)0x00000001,
  RCC_APB2Periph_GPIOA  = (uint32_t)0x00000004,
  RCC_APB2Periph_GPIOB  = (uint32_t)0x00000008,
  RCC_APB2Periph_GPIOC  = (uint32_t)0x00000010,
  RCC_APB2Periph_GPIOD  = (uint32_t)0x00000020,
  RCC_APB2Periph_GPIOE  = (uint32_t)0x00000040,
  RCC_APB2Periph_ADC1   = (uint32_t)0x00000200,
  RCC_APB2Periph_ADC2   = (uint32_t)0x00000400,
  RCC_APB2Periph_TIM1   = (uint32_t)0x00000800,
  RCC_APB2Periph_SPI1   = (uint32_t)0x00001000,
  RCC_APB2Periph_TIM8   = (uint32_t)0x00002000,
  RCC_APB2Periph_USART1 = (uint32_t)0x00004000
} RCC_APB2Periph;

//@{
// Enumeration for AHB peripheral module identifiers
//@}
typedef enum {
    RCC_AHBPeriph_DMA1  = ((uint32_t)0x00000001),
    RCC_AHBPeriph_DMA2  = ((uint32_t)0x00000002),
    RCC_AHBPeriph_SRAM  = ((uint32_t)0x00000004),
    RCC_AHBPeriph_FLITF = ((uint32_t)0x00000010),
    RCC_AHBPeriph_CRC   = ((uint32_t)0x00000040),
    RCC_AHBPeriph_FSMC  = ((uint32_t)0x00000100),
    RCC_AHBPeriph_SDIO  = ((uint32_t)0x00000400)
} RCC_AHBPeriph;

//@{
// Enumeration of the available clock source to output on the MCO pin
//@}
typedef enum {
    RCC_McoClkSrc_NoClock     = ((uint32_t)0x00000000),
    RCC_McoClkSrc_SYSCLK      = ((uint32_t)0x04000000),
    RCC_McoClkSrc_HSI         = ((uint32_t)0x05000000),
    RCC_McoClkSrc_HSE         = ((uint32_t)0x06000000),
    RCC_McoClkSrc_PLLCLK_Div2 = ((uint32_t)0x07000000)
} RCC_McoClkSrc;

//@{
// Enumeration of the available SYSCLK divider values
//@}
typedef enum {
    RCC_SysclkDiv_1   = ((uint32_t)0x00000000),
    RCC_SysclkDiv_2   = ((uint32_t)0x00000080),
    RCC_SysclkDiv_4   = ((uint32_t)0x00000090),
    RCC_SysclkDiv_8   = ((uint32_t)0x000000A0),
    RCC_SysclkDiv_16  = ((uint32_t)0x000000B0),
    RCC_SysclkDiv_64  = ((uint32_t)0x000000C0),
    RCC_SysclkDiv_128 = ((uint32_t)0x000000D0),
    RCC_SysclkDiv_256 = ((uint32_t)0x000000E0),
    RCC_SysclkDiv_512 = ((uint32_t)0x000000F0)
} RCC_SysclkDiv;

//@{
// Enumeration of the available HCLK divider values
//@}
typedef enum {
    RCC_HclkDiv_1  = ((uint32_t)0x00000000),
    RCC_HclkDiv_2  = ((uint32_t)0x00000400),
    RCC_HclkDiv_4  = ((uint32_t)0x00000500),
    RCC_HclkDiv_8  = ((uint32_t)0x00000600),
    RCC_HclkDiv_16 = ((uint32_t)0x00000700)
} RCC_HclkDiv;

//@{
// Enumeration of the available PLL clock sources
//@}
typedef enum {
    RCC_PllClkSrc_HSI_Div2 = ((uint32_t)0x00000000),
    RCC_PllClkSrc_HSE_Div1 = ((uint32_t)0x00010000),
    RCC_PllClkSrc_HSE_Div2 = ((uint32_t)0x00030000)
} RCC_PllClkSrc;

//@{
// Enumeration of the available PLL multiplication factors
//@}
typedef enum {
    RCC_PLLMul_2  = ((uint32_t)0x00000000),
    RCC_PLLMul_3  = ((uint32_t)0x00040000),
    RCC_PLLMul_4  = ((uint32_t)0x00080000),
    RCC_PLLMul_5  = ((uint32_t)0x000C0000),
    RCC_PLLMul_6  = ((uint32_t)0x00100000),
    RCC_PLLMul_7  = ((uint32_t)0x00140000),
    RCC_PLLMul_8  = ((uint32_t)0x00180000),
    RCC_PLLMul_9  = ((uint32_t)0x001C0000),
    RCC_PLLMul_10 = ((uint32_t)0x00200000),
    RCC_PLLMul_11 = ((uint32_t)0x00240000),
    RCC_PLLMul_12 = ((uint32_t)0x00280000),
    RCC_PLLMul_13 = ((uint32_t)0x002C0000),
    RCC_PLLMul_14 = ((uint32_t)0x00300000),
    RCC_PLLMul_15 = ((uint32_t)0x00340000),
    RCC_PLLMul_16 = ((uint32_t)0x00380000)
} RCC_PllMul;

//@{
// Enumeration of the available SYSCLK sources
//@}
typedef enum {
    RCC_SYSCLKSource_HSI    = ((uint32_t)0x00000000),
    RCC_SYSCLKSource_HSE    = ((uint32_t)0x00000001),
    RCC_SYSCLKSource_PLLCLK = ((uint32_t)0x00000002)
} RCC_SysclkSrc;

typedef struct {
    uint32_t SYSCLK_Frequency;
    uint32_t HCLK_Frequency;
    uint32_t PCLK1_Frequency;
    uint32_t PCLK2_Frequency;
    uint32_t ADCCLK_Frequency;
} RCC_Clocks;

//@{
// Enables or disables the Low Speed APB (APB1) peripheral clock
// @param  module: specifies the APB1 peripheral to gates its clock.
// @param  enabled: true = ENABLE, false = DISABLE
//@}
void RCC_EnableAPB1PeripheralClock(const RCC_APB1Periph module, const bool enabled);

//@{
// Enables or disables the High Speed APB (APB2) peripheral clock
// @param  module: specifies the APB2 peripheral to gates its clock.
// @param  enabled: true = ENABLE, false = DISABLE
//@}
void RCC_EnableAPB2PeripheralClock(const RCC_APB2Periph module, const bool enabled);

//@{
// Forces or releases High Speed APB (APB1) peripheral reset.
// @param  module: Specifies the APB1 peripheral to reset.
// @param  doReset: true = forces reset, false = release reset
//@}
void RCC_ResetAPB1Peripheral(const RCC_APB1Periph module, const bool doReset);

//@{
// Forces or releases High Speed APB (APB2) peripheral reset.
// @param  module: Specifies the APB2 peripheral to reset.
// @param  doReset: true = forces reset, false = release reset
//@}
void RCC_ResetAPB2Peripheral(const RCC_APB2Periph module, const bool doReset);

//@{
// Enables or disables the AHB peripheral clock
// @param  module: specifies the AHB peripheral to gates its clock.
// @param  enabled: true = ENABLE, false = DISABLE
//@}
void RCC_EnableAHBPeriphClock(const RCC_AHBPeriph module, const bool enabled);

//@{
// Returns the frequencies of different on chip clocks.
// @param  RCC_Clocks: pointer to a RCC_ClocksTypeDef structure which will hold
//                     the clocks frequencies.
// @note   The result of this function could be not correct when using
//         fractional value for HSE crystal.
//@}
RCC_Clocks RCC_GetClocksFreq(void);

//@{
// Checks if the controller was reseted because of a window watchdog reset.
// @return bool: true when a window watchdog reset was occurred.
//               else false
//@}
bool RCC_IsWindowWatchdogReset(void);

//@{
// Clears the RCC reset flags.
// @note: The reset flags are: PINRST, PORRST, SFTRST,
//        IWDGRST, WWDGRST, LPWRRST
//@}
void RCC_ClearResetFlags(void);

//@{
// Set the clock source to output on the MCO pin.
// @param mcoClockSource: the selected clock source on the MCO pin.
//@}
void RCC_SetMcoClockSource(const RCC_McoClkSrc mcoClockSource);

//@{
// Configures the AHB clock (HCLK).
// @param sysclkDiv: Defines the AHB clock divider.
//                   This clock is derived from the system clock(SYSCLK)
//@}
void RCC_HCLKConfig(const RCC_SysclkDiv sysclkDiv);

//@{
// Configures the High Speed APB1 clock (PCLK1).
// @param hclkDiv: Defines the APB1 clock divider.
//                 This clock is derived from the AHB clock(HCLK).
//@}
void RCC_PCLK1Config(const RCC_HclkDiv hclkDiv);

//@{
// Configures the High Speed APB2 clock (PCLK1).
// @param hclkDiv: Defines the APB2 clock divider.
//                 This clock is derived from the AHB clock(HCLK).
//@}
void RCC_PCLK2Config(const RCC_HclkDiv hclkDiv);

//@{
// Configures the PLL clock source and multiplication factor.
// @note This function must be used only when the PLL is disabled.
// @param pllClkSrc: Specifies the PLL entry clock source.
// @param pllMul: Specifies the PLL multiplication factor..
//@}
void RCC_PllConfig(const RCC_PllClkSrc pllClkSrc, const RCC_PllMul pllMul);

//@{
// Enables or disables the PLL.
// @note The PLL can not be disabled if it is used as system clock.
// @param enable: true = ENABLE, false = DISABLE
//@}
void RCC_SetPllState(const bool enable);

//@{
// Returns if the PLL clock is ready (= PLL is locked).
// @return bool: true PLL clock is ready, else false
//@}
bool RCC_IsPllReady(void);

//@{
// Configures the system clock (SYSCLK).
// @param sysclkSrc: Specifies the clock source used as system clock.
//@}
void RCC_SYSCLKConfig(const RCC_SysclkSrc sysclkSrc);

//@{
// Returns the clock source used as system clock (SYSCLK).
// @return RCC_SysclkSrc: The clock source used as system clock.
//@}
RCC_SysclkSrc RCC_GetSYSCLKSource(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SYSTEMPERIPHERALS_RCC_H
