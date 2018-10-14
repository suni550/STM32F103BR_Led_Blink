// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch. 
// Dev. System:  Microsoft Visual 2008
// SW guideline: SOP-Coding Guidelines Ver. 1.1
// $Author:  $
// $Revision:  $
// $Modtime:  $
// $Archive:  $



#include <SystemPeripherals_USART.h>
#include "UsartApp.h"

static uint8_t rxData[20],rxIndex = 0;





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


    