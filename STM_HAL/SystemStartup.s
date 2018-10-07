// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

//------------------------------------------------------------------------------
// Reset sequence:
// 1. Fetch initial stack pointer value at 0x00000000 into R13
// 2. Fetch reset vector -> instrcution fetch (address = reset vector)
//
// After Reset the Cortex-M3 processor is in Thread mode, priority is Privileged.
// This assembler module performs:
// - Declare Reset_Handler (weak definition)
// - Set the initial PC == __iar_program_start
//
// __iar_program_start will do the following
// 1. initialize the C++ runtime
// 2. jump to __main (runtime) and then jumps to main (defined in application)
//------------------------------------------------------------------------------

        MODULE  ?systemStartup

        EXTERN  __iar_program_start

THUMB
        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        LDR     R0, =__iar_program_start
        BX      R0
        END