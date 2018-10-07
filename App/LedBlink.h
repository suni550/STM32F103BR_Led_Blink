// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch. 
// SW guideline: Technote Coding Guidelines Ver. 1.4

#ifndef LEDBLINK_H
#define LEDBLINK_H


#include "types.h"
#include "ApplicationHardwareConfig.h"
#include "SystemPeripherals_EXTI.h"

//namespace blinky {
  
  class LedBlinkHandler {
  public:  
    static void ledBlink(void); 
    static void Delay(uint32_t counter) ;

  private:
    //@{
    // Constructor.
    //@}
//    explicit LedBlinkHandler();

    //@{
    // Destructor.
    //@}
  //  virtual ~LedBlinkHandler();
    
  };
//}
//using blinky::LedBlinkHandler;



#endif // #ifndef LEDBLINK_H

