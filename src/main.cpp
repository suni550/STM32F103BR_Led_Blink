#include "SystemInitializationDriver.h"
#include "LedBlink.h"


int main(void) {
  
  //Processor, Clock and Ping Config
    SystemInitializationDriver::initCpuClock();
    SystemInitializationDriver::initPeripheralClocks();
    SystemInitializationDriver::initPinConfig();
    //Initialize peripherals 
     SystemInitializationDriver::initTimer();
    //Initialize the external interrupts
    SystemInitializationDriver::initInterrupts();
      // Enable the interrupts just before the scheduler starts
    SystemInitializationDriver::enableInterrupts();
    
    while(1) {
     // LedBlinkHandler::ledBlink();
      SystemInitializationDriver::UART_TransmitData();
    }
    
    return 0;
  
}