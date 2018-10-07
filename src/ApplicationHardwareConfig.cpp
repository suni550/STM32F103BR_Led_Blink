// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.4

// Main include
#include "ApplicationHardwareConfig.h"

#ifdef _UNITTEST
    // Digital Outputs
    static uint32_t W_STAT = 0U; //lint !e401 !e956 -esym(843, STAT) -esym(528, STAT) // Justification: led as variable only for unit tests
    static uint32_t R_STAT = 0U;
    static uint32 R_USER_BUTTON_B1 = 0U;
#endif // _UNITTEST
