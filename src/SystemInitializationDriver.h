// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch. 
// SW guideline: Technote Coding Guidelines Ver. 1.4

#ifndef SYSTEMINITIALIZATIONDRIVER_H
#define SYSTEMINITIALIZATIONDRIVER_H


// Must be very first include
//#include <Imt.Base.Core.Platform/Platform.h>
#include "types.h"

// Imt.Base includes
//#include <Imt.Base.Dff.Runtime/IdleCallbackIfc.h>

namespace blinky {

//@{
// SystemInitializationDriver is responsible to configure the uC and it's built in peripherals.
// @author mguntli
//@}
class SystemInitializationDriver {

public:
    
    //@{
    // Initialize the CPU clock and 1ms system tick based on CPU clock
    //@}
    static void initCpuClock();

    //@{
    // Initialize and enable the peripheral clock for the modules which are required by the application
    //@}
    static void initPeripheralClocks();

    //@{
    // Initialize the pin configuration (PinMux) required by the application
    //@}
    static void initPinConfig();

    //@{
    // Initialize the interrupts of the processor and modules
    //@}
    static void initInterrupts();
    
    //@{
    // Initialize the Runtime of Imt.Base.Dff (priority based, preemptive run to completion kernel)
    // @param callback: When the runtime has no work to perform, the idle callback is called
    //@}
   // static void initRuntime(IdleCallbackIfc* const pCallback);

    //@{
    // Enable the interrupts of the processor and modules.
    //@}
    static void enableInterrupts(void);
    //Added by Sunil for USART testing 
    static void UART_TransmitData(void);
    
    //For timer initialization 
    static void initTimer(void); 
    
    

private:
    
    //@{
    // Constructor.
    //@}
    explicit SystemInitializationDriver();

    //@{
    // Destructor.
    //@}
    virtual ~SystemInitializationDriver();

    //@{
    // Provide the private copy constructor so the compiler does not generate the default one.
    //@}
 //   SystemInitializationDriver(const SystemInitializationDriver& other);

    //@{
    // Provide the private assignment operator so the compiler does not generate the default one.
    //@}
//    SystemInitializationDriver& operator=(const SystemInitializationDriver& other);

};

} // namespace blinky
using blinky::SystemInitializationDriver;

#endif // #ifndef SYSTEMINITIALIZATIONDRIVER_H

