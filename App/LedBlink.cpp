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
#include <SystemPeripherals_USART.h>
#include "SystemPeripherals_TIM.h"

static uint8_t rxData[20],rxIndex = 0;

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
      //unsigned char txData = 0x04;
    }
    // Notify runtime about application ISR entry
    EXTI_ClearITPendingBit(EXTI_Line13);
}

extern "C" void USART2_IRQHandler(void) {
    uint8_t data;
   // RuntimeInterrupts::applicationIsrEntry();
   /*
    while(!USART_IsTransmitDataRegisterEmpty(USART_ModuleAddress_USART2)){};
     USART_SendData(USART_ModuleAddress_USART2, 0x55); */
    if(USART_IsReadDataRegisterNotEmpty(USART_ModuleAddress_USART2)) {
        data = USART_ReceiveData(USART_ModuleAddress_USART2);
        
            rxData[rxIndex++]= data;
        if(rxIndex==20) { 
          rxIndex = 0; 
          
        }
    }
   // RuntimeInterrupts::applicationIsrExit();
}

extern "C" void TIM2_IRQHandler(void) {
  TIM_ClearPendingInterrupt(TIM_ModuleAddress_TIM2,TIM_IrqFlag_UpdateInterrupt);
  if(R_LED_STAT) {
        W_LED_STAT = 0;
      //  LedBlinkHandler::Delay(850000);
    }
    else {
        W_LED_STAT = 1;
      // LedBlinkHandler::Delay(500000);
    }
 } 
 
    