// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

// Must be very first include
#include <Imt.Base.Core.Platform/Platform.h>

// ----------------------------------------------------------------------------------
// Default implementations of Cortex-M3 interrupt handlers.
// Note: Since IAR 7.20 it is required to overwrite the file vector_table_M.s in order to initialize the vector table
// __weak = any function with the same name will override these definitions.
// __stackless = makes a function callable without a working stack
// ----------------------------------------------------------------------------------

// Enable the IAR extensions for this source file
#pragma language=extended

//@{
// An overflow of a descending stack placed at the start of RAM (see LinkerConfig.icf) causes the Hard Fault exception on an ARM Cortex-M3.
// This is exactly what we want, because the exception handler provides the last line of defense to perform damage control.
// However, we must be very careful how to write the exception handler, because the stack pointer (SP) is out of bounds at this point.
// Any attempt to use the stack will fail and cause another Hard Fault exception.
// The non-standard extended keyword you can use here is __stackless, which means exactly that the IAR compiler should not use the stack in the designated function.
// The IAR version can also use the IAR intrinsic functions __get_SP() and __set_SP() to get and set the stack pointer, respectively, instead of inline assembly:
//@}
// symbol created by the IAR linker
extern int CSTACK$$Base;
__stackless __weak void HardFault_Handler(void) {
    // Default Handler for HardFault Interrupt
    unsigned old_sp = __get_SP();

    // stack overflow?
    if (old_sp < (unsigned)&CSTACK$$Base) {
        // Stack overflow detected, endless loop
        // Note: If required the stack pointer could be re-initialized to the beginning, so we can at least do the logging: __set_SP((unsigned)&CSTACK$$Limit);
        while(true) {
            ;
        }
    }
    else {
        // Other reason for hard fault, endless loop
        while(true) {
            ;
        }
    }
}

__stackless __weak void MemManage_Handler(void) {
    // Default Handler for Mem-Manage Interrupt, endless loop
    while(true) {
        ;
    }
}

__stackless __weak void BusFault_Handler(void) {
    // Default Handler for Bus-Fault Interrupt, endless loop
    while(true) {
        ;
    }
}

__stackless __weak void UsageFault_Handler(void) {
    // Default Handler for Usage-Fault Interrupt, endless loop
    while(true) {
        ;
    }
}

__weak void NMI_Handler(void) {
    // Default Handler for Non-Maskable Interrupt, endless loop
    while (true) {
        ;
    }
}

__weak void SVC_Handler(void) {
    // Default Handler for SVC_Handler, endless loop
    while(true) {
        ;
    }
}

__weak void DebugMon_Handler(void) {
    // Default Handler for DebugMon_Handler, endless loop
    while(true) {
        ;
    }
}

__weak void PendSV_Handler(void) {
    // Default Handler for PendSV_Handler, endless loop
    while(true) {
        ;
    }
}

__weak void SysTick_Handler(void) {
    // Default Handler for SysTick_Handler, endless loop
    while(true) {
        ;
    }
}
