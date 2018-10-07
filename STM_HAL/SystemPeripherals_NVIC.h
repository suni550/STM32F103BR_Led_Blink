// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#ifndef SYSTEMPERIPHERALS_NVIC_H
#define SYSTEMPERIPHERALS_NVIC_H

// Must be very first include
#include <Imt.Base.Core.Platform/Platform.h>

// Determine if a C++ compiler is being used.  If so, ensure that standard C is used to process the API information.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//@{
// Nested vectored interrupt controller (NVIC) peripheral module.
//
// Reference: ST_CortexM3_STM32F103_TRM_Rev15.pdf Chapter 10
// Reference: ST_CortexM3_STM32F103_Datasheet_Rev16.pdf for peripheral availability
// @author mguntli
//@}

//@{
// STM32F103 Interrupt Number Definition
//@}
typedef enum {
    //******  Cortex-M3 Processor Exceptions Numbers **************************************************
    // 2 Non Maskable Interrupt
    NonMaskableInt_IRQn         = -14,
    // 4 Cortex-M3 Memory Management Interrupt
    MemoryManagement_IRQn       = -12,
    // 5 Cortex-M3 Bus Fault Interrupt
    BusFault_IRQn               = -11,
    // 6 Cortex-M3 Usage Fault Interrupt
    UsageFault_IRQn             = -10,
    // 11 Cortex-M3 SV Call Interrupt
    SVCall_IRQn                 = -5,
    // 12 Cortex-M3 Debug Monitor Interrupt
    DebugMonitor_IRQn           = -4,
    // 14 Cortex-M3 Pend SV Interrupt
    PendSV_IRQn                 = -2,
    // 15 Cortex-M3 System Tick Interrupt
    SysTick_IRQn                = -1,

    //******  STM32 specific Interrupt Numbers *********************************************************
    // Window WatchDog Interrupt
    WWDG_IRQn                   = 0,
    // PVD through EXTI Line detection Interrupt
    PVD_IRQn                    = 1,
    // Tamper Interrupt
    TAMPER_IRQn                 = 2,
    // RTC global Interrupt
    RTC_IRQn                    = 3,
    // FLASH global Interrupt
    FLASH_IRQn                  = 4,
    // RCC global Interrupt
    RCC_IRQn                    = 5,
    // EXTI Line0 Interrupt
    EXTI0_IRQn                  = 6,
    // EXTI Line1 Interrupt
    EXTI1_IRQn                  = 7,
    // EXTI Line2 Interrupt
    EXTI2_IRQn                  = 8,
    // EXTI Line3 Interrupt
    EXTI3_IRQn                  = 9,
    // EXTI Line4 Interrupt
    EXTI4_IRQn                  = 10,
    // DMA1 Channel 1 global Interrupt
    DMA1_Channel1_IRQn          = 11,
    // DMA1 Channel 2 global Interrupt
    DMA1_Channel2_IRQn          = 12,
    // DMA1 Channel 3 global Interrupt
    DMA1_Channel3_IRQn          = 13,
    // DMA1 Channel 4 global Interrupt
    DMA1_Channel4_IRQn          = 14,
    // DMA1 Channel 5 global Interrupt
    DMA1_Channel5_IRQn          = 15,
    // DMA1 Channel 6 global Interrupt
    DMA1_Channel6_IRQn          = 16,
    // DMA1 Channel 7 global Interrupt
    DMA1_Channel7_IRQn          = 17,
    // ADC1 and ADC2 global Interrupt
    ADC1_2_IRQn                 = 18,
    // USB Device High Priority or CAN TX Interrupts
    USB_HP_CAN_TX_IRQn          = 19,
    // USB Device Low Priority or CAN RX0 Interrupts
    USB_LP_CAN_RX0_IRQn         = 20,
    // CAN RX1 Interrupt
    CAN_RX1_IRQn                = 21,
    // CAN SCE Interrupt
    CAN_SCE_IRQn                = 22,
    // External Line[9:5] Interrupts
    EXTI9_5_IRQn                = 23,
    // TIM1 Break Interrupt
    TIM1_BRK_IRQn               = 24,
    // TIM1 Update Interrupt
    TIM1_UP_IRQn                = 25,
    // TIM1 Trigger and Commutation Interrupt
    TIM1_TRG_COM_IRQn           = 26,
    // TIM1 Capture Compare Interrupt
    TIM1_CC_IRQn                = 27,
    // TIM2 global Interrupt
    TIM2_IRQn                   = 28,
    // TIM3 global Interrupt
    TIM3_IRQn                   = 29,
    // TIM4 global Interrupt
    TIM4_IRQn                   = 30,
    // I2C1 Event Interrupt
    I2C1_EV_IRQn                = 31,
    // I2C1 Error Interrupt
    I2C1_ER_IRQn                = 32,
    // I2C2 Event Interrupt
    I2C2_EV_IRQn                = 33,
    // I2C2 Error Interrupt
    I2C2_ER_IRQn                = 34,
    // SPI1 global Interrupt
    SPI1_IRQn                   = 35,
    // SPI2 global Interrupt
    SPI2_IRQn                   = 36,
    // USART1 global Interrupt
    USART1_IRQn                 = 37,
    // USART2 global Interrupt
    USART2_IRQn                 = 38,
    // USART3 global Interrupt
    USART3_IRQn                 = 39,
    // External Line[15:10] Interrupts
    EXTI15_10_IRQn              = 40,
    // RTC Alarm through EXTI Line Interrupt
    RTCAlarm_IRQn               = 41,
    // USB Device WakeUp from suspend through EXTI Line Interrupt
    USBWakeup_IRQn              = 42
    // end of interrupts for medium density STM32F103x8 & STM32F103xB
} IRQ_NumberType;

//@{
// STM32F103 has 4 priority bits (=0xF = 16 priorities)
// Note: highest priority has lowest value
//@}
typedef enum  {
    IRQ_Priority0             = 0,
    IRQ_Priority1             = 1,
    IRQ_Priority2             = 2,
    IRQ_Priority3             = 3,
    IRQ_Priority4             = 4,
    IRQ_Priority5             = 5,
    IRQ_Priority6             = 6,
    IRQ_Priority7             = 7,
    IRQ_Priority8             = 8,
    IRQ_Priority9             = 9,
    IRQ_Priority10            = 10,
    IRQ_Priority11            = 11,
    IRQ_Priority12            = 12,
    IRQ_Priority13            = 13,
    IRQ_Priority14            = 14,
    IRQ_Priority15            = 15
} IRQ_PriorityType;

//@{
// Set Priority Grouping.
// The function sets the priority grouping field using the required unlock sequence.
// The parameter PriorityGroup is assigned to the field SCB->AIRCR [10:8] PRIGROUP field.
// Only values from 0..7 are used.
// In case of a conflict between priority grouping and available priority bits, the smallest possible priority group is set.
// @param PriorityGroup Priority grouping field.
//@}
void NVIC_SetPriorityGrouping(const uint32_t priorityGroup);

//@{
// The function sets the priority of an interrupt.
// @param IRQ_NumberType irqNumber
// @param IRQ_PriorityType irqPriority
//@}
void NVIC_SetPriority(const IRQ_NumberType irqNumber, const IRQ_PriorityType irqPriority);

//@{
// Enable External Interrupt.
// The function enables a device-specific interrupt in the NVIC interrupt controller.
// @param IRQ_NumberType irqNumber External interrupt number. Value cannot be negative.
void NVIC_EnableIRQ(const IRQ_NumberType irqNumber);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SYSTEMPERIPHERALS_NVIC_H
