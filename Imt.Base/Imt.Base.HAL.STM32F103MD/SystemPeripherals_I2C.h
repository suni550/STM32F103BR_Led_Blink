// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#ifndef SYSTEMPERIPHERALS_I2C_H
#define SYSTEMPERIPHERALS_I2C_H

// Must be very first include
#include <Imt.Base.Core.Platform/Platform.h>

// Project includes
#include "SystemMemoryMap.h"

// Determine if a C++ compiler is being used.  If so, ensure that standard C is used to process the API information.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//@{
// Inter-Integrated Circuit (I2C) peripheral module.
//
// Reference: ST_CortexM3_STM32F103_TRM_Rev15.pdf Chapter 26
// @author mguntli
//@}

//@{
// Enumeration of the available I2C modules
//@}
typedef enum {
    I2C_ModuleAddress_I2C1 = I2C1_BASE,
    I2C_ModuleAddress_I2C2 = I2C2_BASE
} I2C_ModuleAddress;

//@{
// Enumeration for I2C interrupt error bit identifiers.
// BERR, ARLO, AF, OVR, PECERR, TIMEOUT and SMBALERT are logically ORed on the same interrupt channel (it_error).
//@}
typedef enum {
    I2C_ITERR_SMBALERT = (uint32_t)0x10008000,
    I2C_ITERR_TIMEOUT  = (uint32_t)0x10004000,
    I2C_ITERR_PECERR   = (uint32_t)0x10001000,
    I2C_ITERR_OVR      = (uint32_t)0x10000800,
    I2C_ITERR_AF       = (uint32_t)0x10000400,
    I2C_ITERR_ARLO     = (uint32_t)0x10000200,
    I2C_ITERR_BERR     = (uint32_t)0x10000100
} I2C_InterruptErrorBit;

//@{
// Enumeration for I2C event identifiers of SR1 register.
//@}
typedef enum {
    I2C_SR1_FLAG_SMBALERT   = ((uint16_t)0x8000),
    I2C_SR1_FLAG_TIMEOUT    = ((uint16_t)0x4000),
    I2C_SR1_FLAG_PECERR     = ((uint16_t)0x1000),
    I2C_SR1_FLAG_OVR        = ((uint16_t)0x0800),
    I2C_SR1_FLAG_AF         = ((uint16_t)0x0400),
    I2C_SR1_FLAG_ARLO       = ((uint16_t)0x0200),
    I2C_SR1_FLAG_BERR       = ((uint16_t)0x0100),
    I2C_SR1_FLAG_TXE        = ((uint16_t)0x0080),
    I2C_SR1_FLAG_RXNE       = ((uint16_t)0x0040),
    I2C_SR1_FLAG_STOPF      = ((uint16_t)0x0010),
    I2C_SR1_FLAG_ADD10      = ((uint16_t)0x0008),
    I2C_SR1_FLAG_BTF        = ((uint16_t)0x0004),
    I2C_SR1_FLAG_ADDR       = ((uint16_t)0x0002),
    I2C_SR1_FLAG_SB         = ((uint16_t)0x0001)
} I2C_SR1_Flag;

//@{
// Enumeration for I2C event identifiers of SR2 register.
//@}
typedef enum {
    I2C_SR2_FLAG_DUALF      = ((uint16_t)0x0080),
    I2C_SR2_FLAG_SMBHOST    = ((uint16_t)0x0040),
    I2C_SR2_FLAG_SMBDEFAULT = ((uint16_t)0x0020),
    I2C_SR2_FLAG_GENCALL    = ((uint16_t)0x0010),
    I2C_SR2_FLAG_TRA        = ((uint16_t)0x0004),
    I2C_SR2_FLAG_BUSY       = ((uint16_t)0x0002),
    I2C_SR2_FLAG_MSL        = ((uint16_t)0x0001)
} I2C_SR2_Flag;

//@{
// Enumeration for I2C interrupt config identifiers
//@}
typedef enum  {
    I2C_ITCONFIG_BUF = (uint16_t)0x0400,  // buffer interrupt mask
    I2C_ITCONFIG_EVT = (uint16_t)0x0200,  // event interrupt mask
    I2C_ITCONFIG_ERR = (uint16_t)0x0100   // error interrupt mask
} I2C_InterruptConfig;

//@{
// I2C duty cycle in fast mode
// @see ST_CortexM3_STM32F103_TRM_Rev15.pdf 26.6.8
//@}
typedef enum {
    // Fm mode tlow/thigh = 16/9
    I2C_DutyCycle_16_9 = (uint16_t)0x4000,
    // Fm mode tlow/thigh = 2
    I2C_DutyCycle_2    = (uint16_t)0xBFFF
} I2C_DutyCycle;

//@{
// I2C Init structure definition
//@}
typedef struct {
    // own 7-bit I2C address
    uint16_t OwnAddress1;
    // acknowledge enabled / disabled
    bool Acknowledge_Enabled;
    // I2C clock speed in Hz
    uint32_t ClockSpeedHz;
    // if ClockSpeedHz >=100000, then this parameter is used
    I2C_DutyCycle FastModeDutyCycle;
} I2C_InitStruct;


//@{
// Initializes the I2C peripheral according to the specified parameters in the initStructure.
// @param port: Select the I2C peripheral.
// @param initStructure: pointer to a I2C_InitStruct structure that contains the configuration information for the specified I2C peripheral.
//@}
void I2C_Init(const I2C_ModuleAddress port, const I2C_InitStruct* const initStructure);

//@{
// Transmits the address byte to select the slave device.
// @param port: Select the I2C peripheral.
// @param address: specifies the slave address which will be transmitted
// @param writeEnabled: specifies whether the I2C device will be a transmitter or a Receiver.
//@}
void I2C_Send7bitAddress(const I2C_ModuleAddress port, const uint8_t address, const bool writeEnabled);

//@{
// Sends a data byte through the port.
// @param port: Select the I2C peripheral.
// @param data: byte to be transmitted.
//@}
void I2C_SendData(const I2C_ModuleAddress port, const uint8_t data);

//@{
// Returns the most recent received data by the port.
// @param port: select the I2C peripheral.
// @return uint8_t: the value of the received data
//@}
uint8_t I2C_ReceiveData(const I2C_ModuleAddress port);

//@{
// Generates port communication START condition.
// @param port: select the I2C peripheral.
//@}
void I2C_GenerateSTART(const I2C_ModuleAddress port);

//@{
// Generates port communication STOP condition.
// @param port: select the I2C peripheral.
//@}
void I2C_GenerateSTOP(const I2C_ModuleAddress port);

//@{
// Enables or disables the specified I2C acknowledge feature.
// @param port: select the I2C peripheral.
// @param bool ackEnabled: new state of the I2C Acknowledgment.
//@}
void I2C_AcknowledgeConfig(const I2C_ModuleAddress port, const bool ackEnabled);

//@{
// Set's the specified I2C into the desired reset state.
// @param port: Select the I2C peripheral.
// @param bool newState: if true the module goes into reset state
//                       if false the module leaves the reset state
//@}
void I2C_SetSoftwareReset(const I2C_ModuleAddress port, const bool newState);

//@{
// Enables or disables the specified I2C peripheral.
// @param port: Select the I2C peripheral.
// @param bool peripheralEnabled: new state of the port peripheral.
//@}
void I2C_PeripheralEnable(const I2C_ModuleAddress port, const bool peripheralEnabled);

//@{
// Enables or disables the specified I2C interrupts.
// @param port: Select the I2C peripheral.
// @param interruptConfig: specifies the I2C interrupts sources to be enabled or disabled.
// @param bool enabled: new state of the specified I2C interrupts.
//@}
void I2C_EnableInterrupt(const I2C_ModuleAddress port, const I2C_InterruptConfig interruptConfig, const bool enabled);

//@{
// Checks whether the specified I2C interrupt error has occurred or not.
// @param port: Select the I2C peripheral.
// @param interruptBit: specifies the interrupt error bit to check.
// @return bool: true if pending else false
//@}
bool I2C_IsInterruptErrorPending(const I2C_ModuleAddress port, const I2C_InterruptErrorBit interruptBit);

//@{
// Clears the port’s interrupt error pending bits.
// @param port: Select the I2C peripheral.
// @param interruptBit: specifies the interrupt error pending bit to clear.
//@}
void I2C_ClearInterruptErrorPending(const I2C_ModuleAddress port, const I2C_InterruptErrorBit interruptBit);

//@{
// Checks if the I2C start generation is still pending.
// @param port: Select the I2C peripheral.
// @return bool: true if start generation is still pending else false
//@}
bool I2C_IsStartGenerationPending(const I2C_ModuleAddress port);

//@{
// Returns SR1 value of the port.
// @param port: Select the I2C peripheral.
// @return uint32_t: last event
//@}
uint16_t I2C_GetSR1(const I2C_ModuleAddress port);

//@{
// Returns SR2 value of the port.
// @param port: Select the I2C peripheral.
// @return uint32_t: last event
//@}
uint16_t I2C_GetSR2(const I2C_ModuleAddress port);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // #ifndef SYSTEMPERIPHERALS_I2C_H
