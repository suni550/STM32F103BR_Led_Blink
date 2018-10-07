// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1
//
// ActiveParts (AP) and the corresponding Data Flow Framework (DFF) is invented and designed by Jakob Däscher.
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE TERMS OF THE COPYRIGHT NOTICE.
// ===================================================================================================
// COPYRIGHT NOTICE
// ===================================================================================================
// Copyright © 2005-2075, IMT Information Management Technology AG, 9470 Buchs, Switzerland
// All rights reserved.
// This code is proprietary software of IMT Information Management Technology AG (hereinafter: "IMT").
// Proprietary software is computer software licensed under exclusive legal right of IMT.
//
// The licensee is given the irrevocable, perpetual, worldwide, non-exclusive right and license to use,
// execute and reproduce the software in binary form within the licensed products.
//
// Redistribution and use in source forms, without modification, are permitted provided that the following conditions are met:
// (1) Copying of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// (2) Copying of source code is only allowed for regulatory documentation and archiving purposes
// (3) Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//
// IMT provide no reassurances that the source code provided does not infringe
// any patent, copyright, or any other intellectual property rights of third parties.
// IMT disclaim any liability to any recipient for claims brought against
// recipient by any third party for infringement of that parties intellectual property rights.
//
// THIS SOFTWARE IS PROVIDED BY IMT AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
// INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL IMT OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
// OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCURE-MENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
// IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ===================================================================================================

#ifndef PLATFORM_H
#define PLATFORM_H

// Definition for platform specific settings.
// Include this file in every header at very first time.
// For Platform switches use the following symbols:
//
// Platform: WIN32
// The key identifier for a "Desktop" Windows OS is WIN32.
// Define the following Preprocessor Defines on Visual Studio > Project Properties > Preprocessor Defines
// WIN32;_WINDOWS
// Define the following Preprocessor Defines on Visual Studio > Project Properties > Preprocessor Defines if necessary
// _DEBUG;_UNITTEST
//
// Platform: __IAR_SYSTEMS_ICC__
// The IAR platform will automatically define __IAR_SYSTEMS_ICC__.
// IAR can have several target devices with different symbols defined by IAR IDE.
//
// Supported targets on IAR IDE:
// Target: __ICCARM__ IAR ARM C/C++ cross compiler
//
// Platform: WINCE ARM
// The key identifier for WinCE is WINCE. Since we are still on a Windows Machine, _WINDOWS is defined as well.
// Define the following Preprocessor Defines on Visual Studio > Project Properties > Preprocessor Defines
// WINCE;UNDER_CE;_WINDOWS;_WIN32_WCE=$(CEVER);$(ARCHFAM);$(_ARCHFAM_);
// Define the following Preprocessor Defines on Visual Studio > Project Properties > Preprocessor Defines if necessary
// Debug: _DEBUG;DEBUG
// Release: NDEBUG;
//
// Platform: __QNXNTO__
// The QNX Momentix IDE will automatically define __QNXNTO__.
//
// Platform: __CC_ARM
// The Keil uVision IDE will automatically define __CC_ARM.
//
// To provide a new platform extend the Platform.h file.

// Include the application defined configuration file.
// Create an Application specific PlatformConfigApp.h File and copy this to the "\Imt.Base.Core.Platform" folder where this file is located.
// All needed Application Platform specific defines should be located in that file.
#include "PlatformConfigApp.h"

//lint -save
//lint -e* // Disable PC-Lint for this header

//
// Use STL (only with C++ compiler)
//
#if defined (USE_STL) && defined (__cplusplus)
    #if defined WINCE
        // WinCE only supports UNICODE
        #ifndef _UNICODE
            #define _UNICODE
        #endif // _UNICODE
        #ifndef UNICODE
            #define UNICODE
        #endif // UNICODE
    #endif // WINCE

    // Include STL stuff
    #include <limits>

    // RTTI, runtime type information
    #ifdef USE_RTTI
        #include <typeinfo>
    #endif // USE_RTTI

    #include <string>
    #include <sstream>

#endif // USE_STL && __cplusplus


//
// Using WINDOWS (WIN32 or WINCE with SDK) and visual studio
//
#if defined (_WINDOWS) || defined (WINCE)
    // unreferenced formal parameter
    #pragma warning(disable : 4100)

    // header <windef.h> defines macros min/max, which conflict with macros in <limits>
    #define NOMINMAX

    // Enable using type limitations
    #if !defined (__STDC_LIMIT_MACROS)
        #define __STDC_LIMIT_MACROS
    #endif

    // Enable exception handling
    #if !defined (ENABLE_EXCEPTION)
        #define ENABLE_EXCEPTION
    #endif

    #if !defined (WINCE) && !defined (_WIN32_WINNT)
        // >=NTDDI_VISTA
        #define _WIN32_WINNT 0x0600
    #endif

    // Visual C++ doesn't contains C99 headers. Include type definitions.
    #if (_MSC_VER < 1600) // VS2010 contains C99 headers
        #include "WIN32/stdint.h"
    #else
        #include <stdint.h>
    #endif
    #include "WIN32/stdbool.h"
    #include "stdfloat.h"
    #include "stdchar.h"

        // Platform specific includes
    #include <cstddef>
    #include <cstring>
    #include <cstdio>
    #include <climits>
    #include <float.h>
    #include <math.h>

    #if defined(FIND_MEMORY_LEAKS) && !defined (PC_LINT) && !defined (WINCE) && defined (_DEBUG)
        // this line should only be active when a memory leak has been detected
        // and debug output is needed to detect the cause of the memory leak
        #include <afx.h>
        #define new DEBUG_NEW
    #endif

    #define tscanf _stscanf_s
    #define VALUE_FLOAT_UNDEFINED std::numeric_limits<float>::quiet_NaN()
    #define VALUE_INT_MIN std::numeric_limits<int>::min()
    #define VALUE_INT_MAX std::numeric_limits<int>::max()
    #define VALUE_UINT_MAX std::numeric_limits<unsigned int>::max()

//
// Using QNX Momentix
//
#elif defined(__QNXNTO__)
    // TODO: Some definitions may be removed (depending on the Imt.Base.Dff implementation)

    // definition of simple types
    #include <stdint.h>
    #include <stdbool.h>
    #include <stddef.h>

    #include "stdfloat.h"
    #include "stdchar.h"

    // definition of simple c++ types
    #ifdef __cplusplus
        // size_t definition
        #include <cstddef>
        using std::size_t;
    #endif // __cplusplus

    // Platform specific includes
    #include <assert.h>

//
// Using IAR
//
#elif defined (__IAR_SYSTEMS_ICC__)
    // Platform is IAR environment, set _DEBUG depending on the NDEBUG flag
    #ifdef NDEBUG
        #ifdef _DEBUG
            #undef _DEBUG
        #endif
        #else
        #ifndef _DEBUG
            #define _DEBUG
        #endif
    #endif

    // Check target device
    #if !defined (__ICCARM__) // Cross compiler for arm
        #error Target Device not supported!
    #endif // __ICCARM__

    // Enable using type limitations
    #if !defined (__STDC_LIMIT_MACROS)
        #define __STDC_LIMIT_MACROS
    #endif

    // Use the C99 Standard header
    #include <stddef.h>
    #include <stdint.h>
    #include <stdbool.h>
    #include <stdio.h>

    #include "stdfloat.h"
    #include "stdchar.h"

    // Platform specific includes 
#if 0 //SUnil 
    #include <cassert>
    #include <cstddef>
    #include <cstdio>
    #include <climits>
    #include <float.h>
    #include <math.h>
    #include <string.h>
#endif
    #define tscanf sscanf
    #define VALUE_FLOAT_UNDEFINED NAN
    #define VALUE_INT_MIN LONG_MIN // 32bit signed
    #define VALUE_INT_MAX LONG_MAX // 32bit signed
    #define VALUE_UINT_MAX ULONG_MAX // 32bit unsigned

//
// Using uVision (Keil)
//
#elif defined (__CC_ARM)
    #define __ASM            __asm                                      /*!< asm keyword for ARM Compiler          */
    #define __INLINE         __inline                                   /*!< inline keyword for ARM Compiler       */
    #define __STATIC_INLINE  static __inline

    // Enable using type limitations
    #if !defined (__STDC_LIMIT_MACROS)
        #define __STDC_LIMIT_MACROS
    #endif

    // Use the C99 Standard header
    #include <stddef.h>
    #include <stdint.h>
    #include <stdbool.h>
    #include <stdio.h>

    #include "stdfloat.h"
    #include "stdchar.h"

    // Platform specific includes
    #include <cassert>
    #include <cstddef>
    #include <cstdio>
    #include <climits>
    #include <float.h>
    #include <math.h>
    #include <string.h>
    #include <core_cmFunc.h>
    #include <core_cmInstr.h>

    #define VALUE_FLOAT_UNDEFINED NAN
    #define VALUE_INT_MIN LONG_MIN // 32bit signed
    #define VALUE_INT_MAX LONG_MAX // 32bit signed
    #define VALUE_UINT_MAX ULONG_MAX // 32bit unsigned
#else // !(_WINDOWS) && !(WINCE) && !(__IAR_SYSTEMS_ICC__) && !(__QNXNTO__)
    //
    // This platform is currently not supported
    //
    #error Check your preprocessor definitions!
#endif // #if defined !(_WINDOWS) && !(WINCE) && !(__IAR_SYSTEMS_ICC__) && !(__QNXNTO__)

#endif // PLATFORM_H

//lint -restore
