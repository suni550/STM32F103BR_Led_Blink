// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch. 
// Dev. System:  Microsoft Visual 2008
// SW guideline: SOP-Coding Guidelines Ver. 1.1
// $Author:  $
// $Revision:  $
// $Modtime:  $
// $Archive:  $
#include "SystemPeripherals_TIM.h"
#include "TimerApp.h"




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
 
    