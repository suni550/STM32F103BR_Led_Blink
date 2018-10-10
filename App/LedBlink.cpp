// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch. 
// Dev. System:  Microsoft Visual 2008
// SW guideline: SOP-Coding Guidelines Ver. 1.1
// $Author:  $
// $Revision:  $
// $Modtime:  $
// $Archive:  $

//#include "SystemInitializationDriver.h"
//#include "E:\STM32F103BR\STM32F103BR_Led_Blink\STM_HAL/SystemPeripherals_RCC.h"
//#include "SystemPeripherals_RCC.h"
//#include "SystemPeripherals_GPIO.h"
// Imt.Base

#include "LedBlink.h"


void LedBlinkHandler::ledBlink() {
    if(R_LED_STAT) {
        W_LED_STAT = 0;
        LedBlinkHandler::Delay(850000);
    }
    else {
        W_LED_STAT = 1;
       LedBlinkHandler::Delay(500000);
    }
}

void LedBlinkHandler::Delay(uint32_t counter) {
    while(counter > 0) {
      counter--;
    }
}

extern "C" void EXTI15_10_IRQHandler(void){
    if(R_USER_BUTTON_B1 == 0x0u) {
      LedBlinkHandler::ledBlink();
      int a,b, result;
      a= 4; b= 6;
      result = a+b;
      printf("results = %d\n");
     //   unsigned char data = 0xDD;
          unsigned char txData = 0x04;
    }
    // Notify runtime about application ISR entry
    EXTI_ClearITPendingBit(EXTI_Line13);
}