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

#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

// core includes
#include <Imt.Base.Core.Platform/Platform.h>
#include "AssertActionManager.h"

//// ASSERT_EX declaration ----------------------------------------------------------------------------------

//@{
// "Assert and throw exception" (ASSERT_EX). Even so we do not have exception support use this
// macro to test conditions for which it is not secure to continue safely when the condition
// evaluates to false. The registered handler is responsible to react appropriately.
// There is a second version of this macro with a postfix of 1. It takes additionally a second parameter.
// This parameter is for future extensions in the debugging environment. It takes a c-string
// which will be used to indicate the reason of the failure.
// @param condition When this condition evaluates to false the handler will be called
// @param  message The message to specify the error that has occurred
//@}
inline void ASSERT_EX1(const bool condition, const char_t* const pMsg) {
    if (!(condition)) {
        AssertActionManager::fireAssert(AssertActionManager::AssertEvent::ASSERT_EX_EVENT, pMsg);
    }
};

inline void ASSERT_EX(const bool condition) {
    ASSERT_EX1(condition, "");
};

//// ASSERT_DEBUG declaration -------------------------------------------------------------------------------

//@{
// "Assert for debugging only" (ASSERT_DEBUG). Use this sort of assertion only while debugging.
// This flavor of asserts will be compiled only for a debug build on the the developer machine
// and on the target as well.
//@}
inline void ASSERT_DEBUG1(const bool condition, const char_t* const pMsg) {
    if (!(condition)) {
        AssertActionManager::fireAssert(AssertActionManager::AssertEvent::ASSERT_DEBUG_EVENT, pMsg);
    }
};

inline void ASSERT_DEBUG(const bool condition) {
    ASSERT_DEBUG1(condition, "");
};

//// ASSERT_COMPILER declaration ----------------------------------------------------------------------------
//lint -save
//lint -e431 -e970 -e1960 -e1963 // Justification: legacy code to force the compiler to check conditions

//@{
// Check at compile time if a condition is true.
// Usage: ASSERT_COMPILER(sizeof(int) == 4)
// Implementation:    Tries to define an array type inside a block scope.
//                    In case the condition fails the    array will have a negative size.
//                    This should every compiler detect and trigger a compile time error
// @param condition        This assertion fails if the condition evaluates to false
// @param  uniqueName    This must be a unique name which does not contain any special characters
//                        and does not start with a digit.
//@}
// Interface
//lint -esym(758, STATIC_ASSERTION_FAILURE*) // not referenced [MISRA C++ Rule 0-1-5]
template <bool> struct STATIC_ASSERTION_FAILURE;

// Partial specialization only for true
template <> struct STATIC_ASSERTION_FAILURE<true>{};

//lint -esym(758, static_assert_test*) // not referenced [MISRA C++ Rule 0-1-5]
//lint -esym(1795, static_assert_test*) // was defined but not instantiated [MISRA C++ Rule 14-7-1]
template<int> struct static_assert_test{};

#define ASSERT_JOIN( X, Y ) DO_ASSERT_JOIN( X, Y )

#define DO_ASSERT_JOIN( X, Y ) X##Y

#define ASSERT_COMPILER( B )                                                                           \
    /*lint -esym(749,*static_assert_test*)*/                                                           \
    /*lint -esym(753,*untagged*)*/                                                                     \
    /*lint -esym(758,*untagged*)*/                                                                     \
    enum {                                                                                             \
        ASSERT_JOIN(static_assert_test, __LINE__) = sizeof( STATIC_ASSERTION_FAILURE< ( B ) > )        \
    }

//lint -restore

// Include the application defined configuration file.
#include "DiagnosticsConfigApp.h"

#endif // #ifndef DIAGNOSTICS_H
