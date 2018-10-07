// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#ifndef CORE_CORTEXM3_H
#define CORE_CORTEXM3_H

// Must be very first include
#include <Imt.Base.Core.Platform/Platform.h>

// Project includes
#include "SystemMemoryMap.h"

//------------------------------------------------------------------------------
// System Control Block (SCB) register structure
// Reference: Cortex-M3 Devices Generic User Guide DUI0552A Table 4-12
//------------------------------------------------------------------------------
typedef struct {
    // Offset: 0x00 CPU ID Base Register
    volatile uint32_t CPUID;
    // Offset: 0x04 Interrupt Control State Register
    volatile uint32_t ICSR;
    // Offset: 0x08 Vector Table Offset Register
    volatile uint32_t VTOR;
    // Offset: 0x0C Application Interrupt / Reset Control Register
    volatile uint32_t AIRCR;
    // Offset: 0x10 System Control Register
    volatile uint32_t SCR;
    // Offset: 0x14 Configuration Control Register
    volatile uint32_t CCR;
    // Offset: 0x18 System Handlers Priority Registers (4-7, 8-11, 12-15)
    volatile uint8_t  SHPR[12];
    // Offset: 0x24 System Handler Control and State Register
    volatile uint32_t SHCRS;
    // Offset: 0x28 Configurable Fault Status Register
    volatile uint32_t CFSR;
    // Offset: 0x2C Hard Fault Status Register
    volatile uint32_t HFSR;
    // Offset: 0x30 Debug Fault Status Register
    volatile uint32_t DFSR;
    // Offset: 0x34 Mem Manage Address Register
    volatile uint32_t MMAR;
    // Offset: 0x38 Bus Fault Address Register
    volatile uint32_t BFAR;
    // Offset: 0x3C Auxiliary Fault Status Register
    volatile uint32_t AFSR;
} SCB_Type;
// SCB configuration struct
#define SCB ((SCB_Type*)SCB_BASE)

//------------------------------------------------------------------------------
// Bit definition for SCB_ICSR register
//------------------------------------------------------------------------------
// Active ISR number field
#define  SCB_ICSR_VECTACTIVE                 ((uint32_t)0x000001FF)
// All active exceptions minus the IPSR_current_exception yields the empty set
#define  SCB_ICSR_RETTOBASE                  ((uint32_t)0x00000800)
// Pending ISR number field
#define  SCB_ICSR_VECTPENDING                ((uint32_t)0x003FF000)
// Interrupt pending flag
#define  SCB_ICSR_ISRPENDING                 ((uint32_t)0x00400000)
// Clear pending SysTick bit
#define  SCB_ICSR_PENDSTCLR                  ((uint32_t)0x02000000)
// Set pending SysTick bit
#define  SCB_ICSR_PENDSTSET                  ((uint32_t)0x04000000)
// Clear pending pendSV bit
#define  SCB_ICSR_PENDSVCLR                  ((uint32_t)0x08000000)
// Set pending pendSV bit
#define  SCB_ICSR_PENDSVSET                  ((uint32_t)0x10000000)
// Set pending NMI bit
#define  SCB_ICSR_NMIPENDSET                 ((uint32_t)0x80000000)

//------------------------------------------------------------------------------
// Bit definition for SCB_SCR register
//------------------------------------------------------------------------------
// Sleep deep bit
#define  SCB_SCR_SLEEPDEEP                   ((uint8_t)0x04)

//------------------------------------------------------------------------------
// SCB Application Interrupt and Reset Control Register Definitions
//------------------------------------------------------------------------------
// SCB AIRCR: VECTKEY Position
#define SCB_AIRCR_VECTKEY_Pos              16
// SCB AIRCR: VECTKEY Mask
#define SCB_AIRCR_VECTKEY_Mask             (0xFFFFUL << SCB_AIRCR_VECTKEY_Pos)
// SCB AIRCR: PRIGROUP Position
#define SCB_AIRCR_PRIGROUP_Pos             8
// SCB AIRCR: PRIGROUP Mask
#define SCB_AIRCR_PRIGROUP_Mask            (7UL << SCB_AIRCR_PRIGROUP_Pos)

#endif // CORE_CORTEXM3_H
