// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1
//
// ActiveParts (AP) and the corresponding Data Flow Framework (DFF) is invented and designed by Jakob Däscher.
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE TERMS OF THE COPYRIGHT NOTICE.
// ===================================================================================================
// COPYRIGHT NOTICE
// ===================================================================================================
// Copyright © 2005-2075, IMT Information Management Technology AG, 9470 Buchs, Switzerland
// All rights reserved./OUT:"D:\Work_Git\Imt.Base.Dff-cpp\Imt.Base.Dff\Unittest\Imt.Base.HAL.AM3354.lib" /NOLOGO
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

#ifndef ASSERTACTIONMANAGER_H
#define ASSERTACTIONMANAGER_H

// Imt.Base includes
#include <Imt.Base.Core.Platform/Platform.h>

namespace imt {
namespace base {
namespace core {
namespace diagnostics {

//@{
// The AssertActionManager defines some events called AssertActionEvents for which functions can be registered.
// When the corresponding event occurs the registered function will be called.
// The AssertActionManager will be used from the assertion macros in Diagnostics.h and DiagnosticsConfigApp.h
// The later is application dependent.
// @author hug
//@}
//lint -esym(758, imt::base::core::diagnostics::AssertActionManager) // global class not referenced [MISRA C++ Rule 0-1-5] // Justification: pure static methods grouped inside a class
class AssertActionManager {

public:

    //@{
    // Defines different assert action events.
    //@}
    struct AssertEvent {
        static const uint32_t MIN = 0U;
        enum Id {
            // Something unexpected happened (it's not safe to continue program execution!)
            ASSERT_EX_EVENT = MIN,    // <- start with MIN
            // Inform developer that something happened (it's ok to continue, not included in release build)
            ASSERT_DEBUG_EVENT        // <- MAX : if new values are added here, replace MAX value
        };
        static const uint32_t MAX = static_cast<uint32_t>(ASSERT_DEBUG_EVENT);
        static const uint32_t COUNT = MAX + 1U;
    };

    //@{
    // Define the prototype of a function which can handle an action event.
    // Such a function can be registered for a particular AssertActionEvent.
    // When such a AssertActionEvent occurs the function will be called
    // @param actionEvent The event that has occurred. A function may handles multiple events.
    // @param pMsg Optional message
    //@}
    typedef void(*AssertActionHandler)(const AssertEvent::Id actionEvent, const char_t* const pMsg);

    //@{
    // Initialize the AssertActionManager.
    //@}
    static void initActionManager(void);

    //@{
    // Register a new handler for a specific event.
    // @param handler Handler to be registered. Must not be NULL
    // @param actionEvent Event for which the handler will be registered
    // @return The former AssertActionHandler
    // @see LogEvent
    //@}
    static AssertActionHandler registerActionHandler(const AssertActionHandler handler, const AssertEvent::Id actionEvent);

    //@{
    // Fire the assertion
    // @param AssertActionEvent actionEvent
    // @param pMsg Optional message which contains further information for the event
    // @return none
    //@}
    static void fireAssert(const AssertEvent::Id actionEvent, const char_t* const pMsg);

private:
    //@{
    // Private constructor
    //@}
    AssertActionManager(void);

    //@{
    // Private copy constructor
    //@}
    AssertActionManager(const AssertActionManager& other);

    //@{
    // Private assignment operator
    //@}
    AssertActionManager& operator=(const AssertActionManager& other);

    //@{
    // Private destructor
    //@}
    ~AssertActionManager(void);
};

} // namespace diagnostics
} // namespace core
} // namespace base
} // namespace imt
using imt::base::core::diagnostics::AssertActionManager;

#endif // #ifndef ASSERTACTIONMANAGER_H
