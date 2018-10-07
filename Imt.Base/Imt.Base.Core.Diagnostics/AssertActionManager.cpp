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

// main include
#include "AssertActionManager.h"
#include "Diagnostics.h"

static void defaultAssertExHandler(const AssertActionManager::AssertEvent::Id actionEvent, const char_t* const pMsg) {
    // declare a volatile variable, so that the compiler will never optimize away our default exception handler
    volatile uint32_t defaultEndlessCounter = 0U;
    for (;;) {
        // the application hasn't registered an action handlers, but an assert has occurred (see call stack)
        defaultEndlessCounter++;
    }
} //lint !e550 Symbol 'defaultEndlessCounter' not accessed [MISRA C++ Rule 0-1-4]

static void defaultAssertDebugHandler(const AssertActionManager::AssertEvent::Id actionEvent, const char_t* const pMsg) {
    // ignore and don't do anything
    ;
}

//lint -esym(956, s_handlers) // Justification: Global static pool to store handlers across the application
static AssertActionManager::AssertActionHandler s_handlers[AssertActionManager::AssertEvent::COUNT] = { &defaultAssertExHandler, &defaultAssertDebugHandler };

void AssertActionManager::initActionManager(void) {
    s_handlers[AssertActionManager::AssertEvent::ASSERT_EX_EVENT] = &defaultAssertExHandler;
    s_handlers[AssertActionManager::AssertEvent::ASSERT_DEBUG_EVENT] = &defaultAssertDebugHandler;
    // extend this initialization list of further events are added
    ASSERT_COMPILER(AssertActionManager::AssertEvent::MAX == static_cast<uint32_t>(AssertActionManager::AssertEvent::ASSERT_DEBUG_EVENT));
}

AssertActionManager::AssertActionHandler AssertActionManager::registerActionHandler(const AssertActionHandler handler, const AssertEvent::Id actionEvent) {
    const AssertActionHandler oldHandler = s_handlers[actionEvent];
    s_handlers[actionEvent] = handler;
    return oldHandler;
}

//lint -esym(714, fireAssert) // Symbol not referenced [MISRA C++ Rule 0-1-3]
void AssertActionManager::fireAssert(const AssertEvent::Id actionEvent, const char_t* const pMsg) {
    (*(s_handlers[actionEvent]))(actionEvent, pMsg);
}
