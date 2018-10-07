#include "SystemInitializationDriver.h"
#include "LedBlink.h"


int main(void) {
  
    SystemInitializationDriver::initCpuClock();
    SystemInitializationDriver::initPeripheralClocks();
    SystemInitializationDriver::initPinConfig();
    SystemInitializationDriver::initInterrupts();
    SystemInitializationDriver::enableInterrupts();
    
    while(1) {
     // LedBlinkHandler::ledBlink();
      
    }
    
    return 0;
  
}