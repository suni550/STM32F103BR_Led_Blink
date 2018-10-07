// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#ifndef SYSTEMPERIPHERALS_EXTI_H
#define SYSTEMPERIPHERALS_EXTI_H

// Must be very first include
#include <Imt.Base.Core.Platform/Platform.h>

// Determine if a C++ compiler is being used.  If so, ensure that standard C is used to process the API information.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//@{
// External interrupt/event controller (EXTI)
// The external interrupt/event controller consists of up to 20 edge detectors in connectivity line devices, or 19 edge detectors in other devices for generating event/interrupt requests.
// Each input line can be independently configured to select the type (event or interrupt) and the corresponding trigger event (rising or falling or both).
// Each line can also masked independently.
//
// Reference: ST_CortexM3_STM32F103_TRM_Rev15.pdf Chapter 13
// @author lbreitenmoser
//@}

//@{
// Enumeration of the available EXTI modes
//@}
typedef enum {
    EXTI_Mode_Interrupt = 0x00,
    EXTI_Mode_Event = 0x04
} EXTI_Mode;

//@{
// Enumeration of the available EXTI triggers
//@}
typedef enum {
    EXTI_Trigger_Rising = 0x08,
    EXTI_Trigger_Falling = 0x0C,
    EXTI_Trigger_Rising_Falling = 0x10
} EXTI_Trigger;

//@{
// Enumeration of the available EXTI lines
//@}
typedef enum {
    // External interrupt line 0
    EXTI_Line0  = 0x00001,
    // External interrupt line 1
    EXTI_Line1  = 0x00002,
    // External interrupt line 2
    EXTI_Line2  = 0x00004,
    // External interrupt line 3
    EXTI_Line3  = 0x00008,
    // External interrupt line 4
    EXTI_Line4  = 0x00010,
    // External interrupt line 5
    EXTI_Line5  = 0x00020,
    // External interrupt line 6
    EXTI_Line6  = 0x00040,
    // External interrupt line 7
    EXTI_Line7  = 0x00080,
    // External interrupt line 8
    EXTI_Line8  = 0x00100,
    // External interrupt line 9
    EXTI_Line9  = 0x00200,
    // External interrupt line 10
    EXTI_Line10 = 0x00400,
    // External interrupt line 11
    EXTI_Line11 = 0x00800,
    // External interrupt line 12
    EXTI_Line12 = 0x01000,
    // External interrupt line 13
    EXTI_Line13 = 0x02000,
    // External interrupt line 14
    EXTI_Line14 = 0x04000,
    // External interrupt line 15
    EXTI_Line15 = 0x08000,
    // External interrupt line 16 Connected to the PVD Output
    EXTI_Line16 = 0x10000,
    // External interrupt line 17 Connected to the RTC Alarm event
    EXTI_Line17 = 0x20000,
    // External interrupt line 18 Connected to the USB Device/USB OTG FS Wakeup from suspend event
    EXTI_Line18 = 0x40000,
    // External interrupt line 19 Connected to the Ethernet Wakeup event
    EXTI_Line19 = 0x80000
} EXTI_Line;

typedef struct {
    // Specifies the EXTI lines to be enabled or disabled.
    EXTI_Line Line;

    // Specifies the mode for the EXTI lines.
    EXTI_Mode Mode;

    // Specifies the trigger signal active edge for the EXTI lines.
    EXTI_Trigger Trigger;

    // Specifies the if the EXTI is enabled (=true) or disabled (=false).
    bool EXTI_Enabled;
} EXTI_InitStruct;

//@{
// Initialize the external interrupt with the given configuration
// @param EXTI_InitTypeDef * EXTI_InitStruct
// @return void
//@}
void EXTI_Init(const EXTI_InitStruct* const extiInitStruct);

//@{
// Clear the external interrupt pending bit
// @param uint32_t EXTI_Line
// @return void
//@}
void EXTI_ClearITPendingBit(const EXTI_Line line);

//@{
// Check is the external interrupt pending bit is set
// @param uint32_t EXTI_Line
// @return bool true: selected trigger request occurred, false: No trigger request occurred
//@}
bool EXTI_IsITPending(const EXTI_Line line);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SYSTEMPERIPHERALS_EXTI_H
