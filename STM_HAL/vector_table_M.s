/**************************************************
 *
 * Part one of the system initialization code, contains low-level
 * initialization, plain thumb variant.
 *
 * Copyright 2008 IAR Systems. All rights reserved.
 *
 * $Revision: 65537 $
 *
 * Note: Since IAR 7.20 it is required to overwrite the file vector_table_M.s in order to initialize the vector table
 **************************************************/

; Reference: ST_CortexM3_STM32F103_Datasheet_Rev16.pdf for peripheral availability
; Reference: ST_CortexM3_STM32F103_TRM_Rev15.pdf Table 63 Vector table for other STM32F10xxx devices
;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol __iar_program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY, which
; is where to find the SP start value.
; If vector table is not located at address 0, the user has to initialize the  NVIC vector
; table register (VTOR) before using interrupts.
;
; Cortex-M version
;

        MODULE  ?vector_table

        AAPCS INTERWORK, VFP_COMPATIBLE, RWPI_COMPATIBLE
        PRESERVE8


        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  Reset_Handler
        PUBLIC  __vector_table

        DATA

__iar_init$$done:               ; The vector table is not needed
                                ; until after copy initialization is done

__vector_table
        /* General Cortex-M3 interrupts */
        DCD     sfe(CSTACK)
        DCD     Reset_Handler

        DCD     NMI_Handler
        DCD     HardFault_Handler
        DCD     MemManage_Handler
        DCD     BusFault_Handler
        DCD     UsageFault_Handler
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     SVC_Handler
        DCD     DebugMon_Handler
        DCD     0
        DCD     PendSV_Handler
        DCD     SysTick_Handler

        /* external interrupts for STM32F103x8 / STM32F103xB (IRQs) */
        DCD     WWDG_IRQHandler                 /* Window watchdog interrupt */
        DCD     PVD_IRQHandler                  /* PVD through EXTI Line detection interrupt */
        DCD     TAMPER_IRQHandler               /* Tamper interrupt */
        DCD     RTC_IRQHandler                  /* RTC global interrupt */
        DCD     FLASH_IRQHandler                /* Flash global interrupt */
        DCD     RCC_IRQHandler                  /* RCC global interrupt */
        DCD     EXTI0_IRQHandler                /* EXTI Line0 interrupt */
        DCD     EXTI1_IRQHandler                /* EXTI Line1 interrupt */
        DCD     EXTI2_IRQHandler                /* EXTI Line2 interrupt */
        DCD     EXTI3_IRQHandler                /* EXTI Line3 interrupt */
        DCD     EXTI4_IRQHandler                /* EXTI Line4 interrupt */
        DCD     DMA1_Channel1_IRQHandler        /* DMA1 Channel1 global interrupt */
        DCD     DMA1_Channel2_IRQHandler        /* DMA1 Channel2 global interrupt */
        DCD     DMA1_Channel3_IRQHandler        /* DMA1 Channel3 global interrupt */
        DCD     DMA1_Channel4_IRQHandler        /* DMA1 Channel4 global interrupt */
        DCD     DMA1_Channel5_IRQHandler        /* DMA1 Channel5 global interrupt */
        DCD     DMA1_Channel6_IRQHandler        /* DMA1 Channel6 global interrupt */
        DCD     DMA1_Channel7_IRQHandler        /* DMA1 Channel7 global interrupt */
        DCD     ADC1_2_IRQHandler               /* ADC1 and ADC2 global interrupt */
        DCD     USB_HP_CAN_TX_IRQHandler        /* USB High Priority or CAN TX interrupts */
        DCD     USB_LP_CAN_RX0_IRQHandler       /* USB Low Priority or CAN RX0 interrupts */
        DCD     CAN_RX1_IRQHandler              /* CAN RX1 interrupt */
        DCD     CAN_SCE_IRQHandler              /* CAN SCE interrupt */
        DCD     EXTI9_5_IRQHandler              /* EXTI Line[9:5] interrupts */
        DCD     TIM1_BRK_IRQHandler             /* TIM1 Break interrupt */
        DCD     TIM1_UP_IRQHandler              /* TIM1 Update interrupt */
        DCD     TIM1_TRG_COM_IRQHandler         /* TIM1 Trigger and Commutation interrupts */
        DCD     TIM1_CC_IRQHandler              /* TIM1 Capture Compare interrupt */
        DCD     TIM2_IRQHandler                 /* TIM2 global interrupt */
        DCD     TIM3_IRQHandler                 /* TIM3 global interrupt */
        DCD     TIM4_IRQHandler                 /* TIM4 global interrupt */
        DCD     I2C1_EV_IRQHandler              /* I2C1 event interrupt */
        DCD     I2C1_ER_IRQHandler              /* I2C1 error interrupt */
        DCD     I2C2_EV_IRQHandler              /* I2C2 event interrupt */
        DCD     I2C2_ER_IRQHandler              /* I2C2 error interrupt */
        DCD     SPI1_IRQHandler                 /* SPI1 global interrupt */
        DCD     SPI2_IRQHandler                 /* SPI2 global interrupt */
        DCD     USART1_IRQHandler               /* USART1 global interrupt */
        DCD     USART2_IRQHandler               /* USART2 global interrupt */
        DCD     USART3_IRQHandler               /* USART3 global interrupt */
        DCD     EXTI15_10_IRQHandler            /* EXTI Line[15:10] interrupts */
        DCD     RTCAlarm_IRQHandler             /* RTC alarm through EXTI line interrupt */
        DCD     USBWakeup_IRQHandler            /* USB wakeup from suspend through EXTI line interrupt */
        /* end of peripherals for medium density STM32F103x8 & STM32F103xB */

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default weak STM32F103 IRQ handlers with endless loops.
;; Weak = any function with the same name will override these definitions.
;;

        PUBWEAK NMI_Handler
        PUBWEAK HardFault_Handler
        PUBWEAK MemManage_Handler
        PUBWEAK BusFault_Handler
        PUBWEAK UsageFault_Handler
        PUBWEAK SVC_Handler
        PUBWEAK DebugMon_Handler
        PUBWEAK PendSV_Handler
        PUBWEAK SysTick_Handler
        PUBWEAK WWDG_IRQHandler
        PUBWEAK PVD_IRQHandler
        PUBWEAK TAMPER_IRQHandler
        PUBWEAK RTC_IRQHandler
        PUBWEAK FLASH_IRQHandler
        PUBWEAK RCC_IRQHandler
        PUBWEAK EXTI0_IRQHandler
        PUBWEAK EXTI1_IRQHandler
        PUBWEAK EXTI2_IRQHandler
        PUBWEAK EXTI3_IRQHandler
        PUBWEAK EXTI4_IRQHandler
        PUBWEAK DMA1_Channel1_IRQHandler
        PUBWEAK DMA1_Channel2_IRQHandler
        PUBWEAK DMA1_Channel3_IRQHandler
        PUBWEAK DMA1_Channel4_IRQHandler
        PUBWEAK DMA1_Channel5_IRQHandler
        PUBWEAK DMA1_Channel6_IRQHandler
        PUBWEAK DMA1_Channel7_IRQHandler
        PUBWEAK ADC1_2_IRQHandler
        PUBWEAK USB_HP_CAN_TX_IRQHandler
        PUBWEAK USB_LP_CAN_RX0_IRQHandler
        PUBWEAK CAN_RX1_IRQHandler
        PUBWEAK CAN_SCE_IRQHandler
        PUBWEAK EXTI9_5_IRQHandler
        PUBWEAK TIM1_BRK_IRQHandler
        PUBWEAK TIM1_UP_IRQHandler
        PUBWEAK TIM1_TRG_COM_IRQHandler
        PUBWEAK TIM1_CC_IRQHandler
        PUBWEAK TIM2_IRQHandler
        PUBWEAK TIM3_IRQHandler
        PUBWEAK TIM4_IRQHandler
        PUBWEAK I2C1_EV_IRQHandler
        PUBWEAK I2C1_ER_IRQHandler
        PUBWEAK I2C2_EV_IRQHandler
        PUBWEAK I2C2_ER_IRQHandler
        PUBWEAK SPI1_IRQHandler
        PUBWEAK SPI2_IRQHandler
        PUBWEAK USART1_IRQHandler
        PUBWEAK USART2_IRQHandler
        PUBWEAK USART3_IRQHandler
        PUBWEAK EXTI15_10_IRQHandler
        PUBWEAK RTCAlarm_IRQHandler
        PUBWEAK USBWakeup_IRQHandler

        SECTION .text:CODE:REORDER:NOROOT(1)
        THUMB

NMI_Handler
HardFault_Handler
MemManage_Handler
BusFault_Handler
UsageFault_Handler
SVC_Handler
DebugMon_Handler
PendSV_Handler
SysTick_Handler
WWDG_IRQHandler
PVD_IRQHandler
TAMPER_IRQHandler
RTC_IRQHandler
FLASH_IRQHandler
RCC_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_IRQHandler
EXTI3_IRQHandler
EXTI4_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_IRQHandler
DMA1_Channel3_IRQHandler
DMA1_Channel4_IRQHandler
DMA1_Channel5_IRQHandler
DMA1_Channel6_IRQHandler
DMA1_Channel7_IRQHandler
ADC1_2_IRQHandler
USB_HP_CAN_TX_IRQHandler
USB_LP_CAN_RX0_IRQHandler
CAN_RX1_IRQHandler
CAN_SCE_IRQHandler
EXTI9_5_IRQHandler
TIM1_BRK_IRQHandler
TIM1_UP_IRQHandler
TIM1_TRG_COM_IRQHandler
TIM1_CC_IRQHandler
TIM2_IRQHandler
TIM3_IRQHandler
TIM4_IRQHandler
I2C1_EV_IRQHandler
I2C1_ER_IRQHandler
I2C2_EV_IRQHandler
I2C2_ER_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
USART3_IRQHandler
EXTI15_10_IRQHandler
RTCAlarm_IRQHandler
USBWakeup_IRQHandler
Default_Handler
__default_handler
        CALL_GRAPH_ROOT __default_handler, "interrupt"
        NOCALL __default_handler
        ; if you reach this code, you have enabled an interrupt but not declared the correct interrupt handler (override existing weak definitions)
        B __default_handler

        END
