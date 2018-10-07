// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.4

#ifndef APPLICATIONHARDWARECONFIG_H
#define APPLICATIONHARDWARECONFIG_H

// Must be very first include
#include <Imt.Base.Core.Platform/Platform.h>

// Imt.Base includes
#include <Imt.Base.HAL.STM32F103MD/SystemMemoryMap.h>

//@{
// Mapping of application relevant peripherals
// @author mguntli
//@}

//------------------------------------------------------------------------------
// Mapping of hardware schematics pin-name to chip pin-address
//------------------------------------------------------------------------------
//lint -esym(526, STAT)
//#ifdef _UNITTEST
  //  extern uint32_t STAT; //lint !e956 -esym(843, STAT) -esym(528, STAT) // Justification: led as variable only for unit tests
//#else
    // Digital Outputs, which are bit banded (atomic) in the peripheral memory area
    #define W_LED_STAT             GPIOA_5_WRITE_ADDR
    #define R_LED_STAT             GPIOA_5_READ_ADDR 
    #define R_USER_BUTTON_B1   GPIOC_13_READ_ADDR
//#endif // _UNITTEST

#endif // #ifndef APPLICATIONHARDWARECONFIG_H
