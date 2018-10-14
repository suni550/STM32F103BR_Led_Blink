// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch. 
// Dev. System:  Microsoft Visual 2008
// SW guideline: SOP-Coding Guidelines Ver. 1.1
// $Author:  $
// $Revision:  $
// $Modtime:  $
// $Archive:  $

#include "SystemInitializationDriver.h"
#include "SystemPeripherals_SysTick.h"
#include "SystemPeripherals_RCC.h"
#include "SystemPeripherals_GPIO.h"
#include "SystemPeripherals_NVIC.h"
#include "SystemPeripherals_EXTI.h"
#include "SystemPeripherals_USART.h"
#include "SystemPeripherals_TIM.h"
// Imt.Base
#if 0
//#include "ApplicationHardwareConfig.h"
#include <Imt.Base.Dff.Runtime/RuntimeCore.h>
#include <Imt.Base.Dff.Runtime/RuntimeTimer.h>
#include <LowLevelIOInterface.h>
#endif

 void SystemInitializationDriver::initCpuClock() {
  // after reset the clock is set to internal 8MHz (HSI)
  // PLL frequency = 1/2 HSI frequency = 4MHz
  // PLLMUL after reset = 0 = PLL input clock x 2 = 8MHz
  // Default setting is fine for our application, since we would like to clock the CPU as low as possible
   const unsigned long CPU_CLOCK = 8000000U;
  
  // CPU clock = 8MHz, 1ms = 8000 ticks
    const uint32_t counterValue1Ms = CPU_CLOCK / 1000U; 
    SysTick_ConfigureCounterValue(counterValue1Ms);
}

void SystemInitializationDriver::initPeripheralClocks() {
  // initialize peripheral clocks based on application use case
    RCC_EnableAPB2PeripheralClock(RCC_APB2Periph_GPIOA, true);
    RCC_EnableAPB2PeripheralClock(RCC_APB2Periph_GPIOC, true); 
    RCC_EnableAPB1PeripheralClock(RCC_APB1Periph_USART2, true); 
    RCC_EnableAPB1PeripheralClock(RCC_APB1Periph_TIM2, true);
    RCC_EnableAPB2PeripheralClock(RCC_APB2Periph_AFIO,true);
}

void SystemInitializationDriver::initPinConfig() {
    GPIO_InitStruct  GPIO_config,GPIO_config2,GPIO_config3,GPIO_config4;
    USART_InitStruct USART_config; 
   
    /* GPIO Port A Pin5 Configuration Output for LED; LD2 on the board*/
    GPIO_config.Pin = GPIO_Pin_5; 
    GPIO_config.Mode = GPIO_Mode_Out_PP;   //GPIO_Mode_Out_OD;// 
    GPIO_config.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIO_ModuleAddress_GPIOA, &GPIO_config);
    
    /*GPIO Port C pin 13 Configuration for GPIO EXTI IN */
    GPIO_config4.Pin = GPIO_Pin_13; 
    GPIO_config4.Mode =  GPIO_Mode_IN_FLOATING;//GPIO_Mode_IPU;   //GPIO_Mode_IPD;
    GPIO_config4.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIO_ModuleAddress_GPIOC, &GPIO_config4);
    
    /* GPIO Port A Pin2 Configuration USART Tx */
    GPIO_config2.Pin = GPIO_Pin_2; 
    GPIO_config2.Mode = GPIO_Mode_AF_PP;//GPIO_Mode_AF_OD;   
    GPIO_config2.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIO_ModuleAddress_GPIOA, &GPIO_config2);
  
    /* GPIO Port A Pin3 Configuration USART Rx */
    GPIO_config3.Pin = GPIO_Pin_3; 
    GPIO_config3.Mode =  GPIO_Mode_AF_OD;//GPIO_Mode_AF_PP; 
    GPIO_config3.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIO_ModuleAddress_GPIOA, &GPIO_config3);
       
   /*USART Configuration */
    USART_Enable(USART_ModuleAddress_USART2,true); 
    USART_config.BaudRate = 115200; //9600;
    USART_config.DataBits =  USART_DataBits_8b; 
    USART_config.StopBits = USART_StopBits_1; 
    USART_config.Parity = USART_Parity_No; 
    USART_config.Mode = USART_Mode_RxTx ;
    USART_config.HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART_ModuleAddress_USART2, &USART_config);
    
    /* Port C pin 13 EXTI configuration*/  
    EXTI_InitStruct extiInitStruct;
    extiInitStruct.Line = EXTI_Line13;
    extiInitStruct.Mode = EXTI_Mode_Interrupt;
    extiInitStruct.Trigger = EXTI_Trigger_Falling;// EXTI_Trigger_Rising;
    extiInitStruct.EXTI_Enabled = true;
    EXTI_Init(&extiInitStruct);
   // NVIC_SetPriority(EXTI15_10_IRQn,IRQ_Priority5);
    GPIO_EXTILineConfig(GPIO_PortSourceC, GPIO_PinSource13);
}

void SystemInitializationDriver::initInterrupts() {

    // Assign all priority bits for preemption-priority and none to sub-priority
    NVIC_SetPriorityGrouping(0U);
    // Initialize system tick interrupt as highest interrupt
   // NVIC_SetPriority(SysTick_IRQn, IRQ_Priority0);
    
    /* Port C pin 13 EXTI configuration*/  
    NVIC_SetPriority(EXTI15_10_IRQn,IRQ_Priority5);
    
    //GPIO_Pin_2 USART2 Tx
    NVIC_SetPriority(USART2_IRQn, IRQ_Priority4);
   // USART_EnableInterrupt(USART_ModuleAddress_USART2,USART_Irq_CR1_TXE,true);
    
    //GPIO_Pin_3 USART2 Rx
    NVIC_SetPriority(USART2_IRQn, IRQ_Priority4);
    USART_EnableInterrupt(USART_ModuleAddress_USART2,USART_Irq_CR1_RXNE,true);
    
    //Timer interrupt
    NVIC_SetPriority(TIM2_IRQn,IRQ_Priority3);
    TIM_EnableInterrupt(TIM_ModuleAddress_TIM2, TIM_Irq_UpdateInterrupt, true);
}


#if 0
void SystemInitializationDriver::initRuntime(IdleCallbackIfc* const pCallback) {

    RuntimeCore::init(pCallback);
    // Initialize timer modules
    RuntimeTimer::initTimerModule();

}
#endif

void SystemInitializationDriver::enableInterrupts(void) {

    // SysTick is used by DFF-runtime to process the 1ms tick count
 //   SysTick_EnableInterrupt(true);  
    //GPIO EXTI 
    NVIC_EnableIRQ(EXTI15_10_IRQn);
    //USART IRQ  
    NVIC_EnableIRQ(USART2_IRQn);  
    //Timer interrupt
    NVIC_EnableIRQ(TIM2_IRQn);
  //  TIM_EnableInterrupt(TIM_ModuleAddress_TIM2, TIM_Irq_UpdateInterrupt, true);

 }

void  SystemInitializationDriver::initTimer(void) {

  // APB1 Timer Clock is 16 MHz
    TIM_TimeBaseInitStruct config;
   
    // master timer counting microseconds
    config.CounterMode = TIM_CounterModeUp;
    config.Period =  2000;
    
    //80000/prescaler value * period= time in sec 
    config.Prescaler = 20000; // scale timer to 10kHz, so that it has an increment of 100 microsecond
    TIM_TimeBaseInit(TIM_ModuleAddress_TIM2, &config);
   // TIM_SetMasterMode(TIM_ModuleAddress_TIM2, TIM_MasterMode_Update);

   //Enable timer; Enabled before using the Timer in LedHeartbeatAppHandler.cpp
    TIM_Enable(TIM_ModuleAddress_TIM2, true); 
}


void SystemInitializationDriver::UART_TransmitData(void){

   const unsigned char msg[] = "USART is Working\n\r"; 
  
   for (int i = 0; msg[i] != '\0'; ++i) {
      while(!USART_IsTransmitDataRegisterEmpty(USART_ModuleAddress_USART2)){};
      USART_SendData(USART_ModuleAddress_USART2, msg[i]);
   }
  // while (!USART_IsReadDataRegisterNotEmpty(USART_ModuleAddress_USART2)){};
     
   {
     //cnt++;
   //  uint16_t rxbyte = USART_ReceiveData (USART_ModuleAddress_USART2);
   }

 }

