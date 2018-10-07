// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#include "SystemPeripherals_NVIC.h"

// Project includes
#include "SystemMemoryMap.h"
#include "Core_CortexM3.h"

typedef struct {
    // Offset: 0x000  Interrupt Set Enable Register
    volatile uint32_t ISER[8];
    uint32_t RESERVED0[24];
    // Offset: 0x080  Interrupt Clear Enable Register
    volatile uint32_t ICER[8];
    uint32_t RSERVED1[24];
    // Offset: 0x100  Interrupt Set Pending Register
    volatile uint32_t ISPR[8];
    uint32_t RESERVED2[24];
    // Offset: 0x180  Interrupt Clear Pending Register
    volatile uint32_t ICPR[8];
    uint32_t RESERVED3[24];
    // Offset: 0x200  Interrupt Active bit Register
    volatile uint32_t IABR[8];
    uint32_t RESERVED4[56];
    // Offset: 0x300  Interrupt Priority Register (8Bit wide)
    volatile uint8_t  IP[240];
    uint32_t RESERVED5[644];
    //Offset: 0xE00  Software Trigger Interrupt Register
    volatile  uint32_t STIR;
}  NVIC_ModuleRegisters;
// NVIC configuration struct
#define NVIC ((NVIC_ModuleRegisters*)NVIC_BASE)

// STM32F103 has 4 priority bits
#define NVIC_PRIO_BITS 4

void NVIC_SetPriorityGrouping(const uint32_t priorityGroup) {
    // only values 0..7 are used
    const uint32_t priorityGroupTmp = (priorityGroup & (uint32_t)0x07);

    // read old register configuration
    uint32_t reg_value  = SCB->AIRCR;
    // clear bits to change
    reg_value &= ~(SCB_AIRCR_VECTKEY_Mask | SCB_AIRCR_PRIGROUP_Mask);
    // Insert write key and priority group
    reg_value  = (reg_value | ((uint32_t)0x5FA << SCB_AIRCR_VECTKEY_Pos) | (priorityGroupTmp << 8));
    SCB->AIRCR = reg_value;
}

void NVIC_SetPriority(const IRQ_NumberType irqNumber, const IRQ_PriorityType irqPriority) {
    if((int32_t)irqNumber < 0) {
        // set Priority for Cortex-M System Interrupts
        SCB->SHPR[((uint32_t)(irqNumber) & 0xF)-4] = (((uint8_t)irqPriority << (8 - NVIC_PRIO_BITS)) & 0xFF);
    }
    else {
        // set Priority for device specific Interrupts
        NVIC->IP[(uint32_t)(irqNumber)] = (((uint8_t)irqPriority << (8 - NVIC_PRIO_BITS)) & 0xFF);
    }
}

void NVIC_EnableIRQ(const IRQ_NumberType irqNumber) {
    // enable interrupt
    NVIC->ISER[((uint32_t)(irqNumber) >> 5)] = (1 << ((uint32_t)(irqNumber) & 0x1F));
}
