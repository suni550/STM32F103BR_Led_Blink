// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#include "SystemPeripherals_I2C.h"

// Imt.Base includes
#include <Imt.Base.Core.Diagnostics/Diagnostics.h>

// Project includes
#include "SystemPeripherals_RCC.h"

//@{
// I2C module register structure
//@}
typedef struct {
    volatile uint16_t CR1;
    uint16_t  RESERVED0;
    volatile uint16_t CR2;
    uint16_t  RESERVED1;
    volatile uint16_t OAR1;
    uint16_t  RESERVED2;
    volatile uint16_t OAR2;
    uint16_t  RESERVED3;
    volatile uint16_t DR;
    uint16_t  RESERVED4;
    volatile uint16_t SR1;
    uint16_t  RESERVED5;
    volatile uint16_t SR2;
    uint16_t  RESERVED6;
    volatile uint16_t CCR;
    uint16_t  RESERVED7;
    volatile uint16_t TRISE;
    uint16_t  RESERVED8;
} I2C_ModuleRegisters;

// I2C FLAG mask
#define FLAG_Mask               ((uint32_t)0x00FFFFFF)

// I2C ADD0 mask
#define OAR1_ADD0_Set           ((uint16_t)0x0001)
#define OAR1_ADD0_Reset         ((uint16_t)0xFFFE)

// I2C SPE mask
#define CR1_PE_Set              ((uint16_t)0x0001)
#define CR1_PE_Reset            ((uint16_t)0xFFFE)

// I2C START mask
#define CR1_START_Set           ((uint16_t)0x0100)

// I2C STOP mask
#define CR1_STOP_Set            ((uint16_t)0x0200)

// I2C ACK mask
#define CR1_ACK_Set             ((uint16_t)0x0400)
#define CR1_ACK_Reset           ((uint16_t)0xFBFF)

// I2C SWRST mask
#define CR1_SWRST_Set           ((uint16_t)0x8000)
#define CR1_SWRST_Reset         ((uint16_t)0x7FFF)

// I2C F/S mask
#define CCR_FS_Set              ((uint16_t)0x8000)
// I2C FREQ mask
#define CR2_FREQ_Reset          ((uint16_t)0xFFC0)
// I2C CCR mask
#define CCR_CCR_Set             ((uint16_t)0x0FFF)
// I2C registers Masks
#define CR1_CLEAR_Mask          ((uint16_t)0xFBF5)

#define I2C_Mode_I2C            ((uint16_t)0x0000)
#define I2C_Ack_Enable          ((uint16_t)0x0400)
#define I2C_AcknowledgedAddress_7bit    ((uint16_t)0x4000)

void I2C_Init(const I2C_ModuleAddress port, const I2C_InitStruct* const initStructure) {
    // parameter check
    if (initStructure == NULL) {
        ASSERT_DEBUG(false);
        return;
    }
    ASSERT_DEBUG(initStructure->ClockSpeedHz <= 400000);
    I2C_ModuleRegisters* const pI2C = (I2C_ModuleRegisters*)port;
    RCC_Clocks rcc_clocks;

    //---------------------------- I2Cx CR2 Configuration ------------------------
    // Get the I2Cx CR2 value
    uint16_t tmpreg = pI2C->CR2;
    // Clear frequency FREQ[5:0] bits
    tmpreg &= CR2_FREQ_Reset;
    // Get pclk1 frequency value
    rcc_clocks = RCC_GetClocksFreq();
    const uint32_t pclk1 = rcc_clocks.PCLK1_Frequency;
    // Set frequency bits depending on pclk1 value
    const uint16_t freqrange = (uint16_t)(pclk1 / 1000000);
    tmpreg |= freqrange;
    // Write to I2Cx CR2
    pI2C->CR2 = tmpreg;

    //---------------------------- I2Cx CCR Configuration ------------------------
    // Disable the selected I2C peripheral to configure TRISE
    pI2C->CR1 &= CR1_PE_Reset;

    // Reset tmpreg value
    // Clear F/S, DUTY and CCR[11:0] bits
    tmpreg = 0;

    if (initStructure->ClockSpeedHz <= 100000) {
        // Configure speed in standard mode
        // Standard mode speed calculate
        uint16_t result = (uint16_t)(pclk1 / (initStructure->ClockSpeedHz << 1));
        // Test if CCR value is under 0x4
        if (result < 0x04) {
            // Set minimum allowed value
            result = 0x04;
        }
        // Set speed value for standard mode
        tmpreg |= result;
        // Set Maximum Rise Time for standard mode
        pI2C->TRISE = freqrange + 1;
    }
    else {
        uint16_t result;
        // Configure speed in fast mode
        //(I2C_InitStruct->I2C_ClockSpeed <= 400000)
        if (initStructure->FastModeDutyCycle == I2C_DutyCycle_2) {
            // Fast mode speed calculate: Tlow/Thigh = 2
            result = (uint16_t)(pclk1 / (initStructure->ClockSpeedHz * 3));
        }
        else {
            //I2C_InitStruct->I2C_DutyCycle == I2C_DutyCycle_16_9
            // Fast mode speed calculate: Tlow/Thigh = 16/9
            result = (uint16_t)(pclk1 / (initStructure->ClockSpeedHz * 25));
            // Set DUTY bit
            result |= (uint16_t)I2C_DutyCycle_16_9;
        }
        // Test if CCR value is under 0x1
        if ((result & CCR_CCR_Set) == 0) {
            // Set minimum allowed value
            result |= (uint16_t)0x0001;
        }
        // Set speed value and set F/S bit for fast mode
        tmpreg |= result | CCR_FS_Set;
        // Set Maximum Rise Time for fast mode
        pI2C->TRISE = (uint16_t)(((freqrange * 300) / 1000) + 1);
    }
    // Write to I2Cx CCR
    pI2C->CCR = tmpreg;

    // Enable the selected I2C peripheral
    pI2C->CR1 |= CR1_PE_Set;

    //---------------------------- I2Cx CR1 Configuration ------------------------
    // Get the I2Cx CR1 value
    tmpreg = pI2C->CR1;
    // Clear ACK, SMBTYPE and  SMBUS bits
    tmpreg &= CR1_CLEAR_Mask;
    // Configure I2Cx: mode and acknowledgement
    // Set SMBTYPE and SMBUS bits according to I2C_Mode value
    // Set ACK bit according to I2C_Ack value
    tmpreg |= I2C_Mode_I2C;
    if (initStructure->Acknowledge_Enabled) {
        tmpreg |= I2C_Ack_Enable;
    }
    // Write to I2Cx CR1
    pI2C->CR1 = tmpreg;

    //---------------------------- I2Cx OAR1 Configuration -----------------------
    // Set I2Cx Own Address1 and acknowledged address
    pI2C->OAR1 = (I2C_AcknowledgedAddress_7bit | initStructure->OwnAddress1);
}

void I2C_Send7bitAddress(const I2C_ModuleAddress port, const uint8_t address, const bool writeEnabled) {
    I2C_ModuleRegisters* const pI2C = (I2C_ModuleRegisters*)port;

    // shift to correct position
    uint8_t value = (uint8_t)(address << 1);
    // Test on the direction to set/reset the read/write bit
    if (!writeEnabled) {
        // Set the address bit0 for read
        value |= OAR1_ADD0_Set;
    }
    else {
        // Reset the address bit0 for write
        value &= OAR1_ADD0_Reset;
    }
    // Send the address
    pI2C->DR = value;
}

void I2C_SendData(const I2C_ModuleAddress port, const uint8_t data) {
    I2C_ModuleRegisters* const pI2C = (I2C_ModuleRegisters*)port;
    // Write in the DR register the data to be sent
    pI2C->DR = data;
}

uint8_t I2C_ReceiveData(const I2C_ModuleAddress port) {
    const I2C_ModuleRegisters* const pI2C = (I2C_ModuleRegisters*)port;
    // Return the data in the DR register
    return (uint8_t)pI2C->DR;
}

void I2C_GenerateSTART(const I2C_ModuleAddress port) {
    I2C_ModuleRegisters* const pI2C = (I2C_ModuleRegisters*)port;
    // Generate a START condition
    pI2C->CR1 |= CR1_START_Set;
}

void I2C_GenerateSTOP(const I2C_ModuleAddress port) {
    I2C_ModuleRegisters* const pI2C = (I2C_ModuleRegisters*)port;
    // Generate a STOP condition
    pI2C->CR1 |= CR1_STOP_Set;
}

void I2C_AcknowledgeConfig(const I2C_ModuleAddress port, const bool ackEnabled) {
    I2C_ModuleRegisters* const pI2C = (I2C_ModuleRegisters*)port;
    // Check the parameters
    if (ackEnabled) {
        // Enable the acknowledgement
        pI2C->CR1 |= CR1_ACK_Set;
    }
    else {
        // Disable the acknowledgement
        pI2C->CR1 &= CR1_ACK_Reset;
    }
}

void I2C_SetSoftwareReset(const I2C_ModuleAddress port, const bool newState) {
    I2C_ModuleRegisters* const pI2C = (I2C_ModuleRegisters*)port;
    if(newState) {
        // Enter reset state
        pI2C->CR1 |= CR1_SWRST_Set;
    }
    else {
        // Leave reset state
        pI2C->CR1 &= CR1_SWRST_Reset;
    }
}

void I2C_PeripheralEnable(const I2C_ModuleAddress port, const bool peripheralEnabled) {
    I2C_ModuleRegisters* const pI2C = (I2C_ModuleRegisters*)port;
    if (peripheralEnabled) {
        // Enable the selected I2C peripheral
        pI2C->CR1 |= CR1_PE_Set;
    }
    else {
        // Disable the selected I2C peripheral
        pI2C->CR1 &= CR1_PE_Reset;
    }
}

void I2C_EnableInterrupt(const I2C_ModuleAddress port, const I2C_InterruptConfig interruptConfig, const bool enabled) {
    I2C_ModuleRegisters* const pI2C = (I2C_ModuleRegisters*)port;
    if (enabled) {
        // Enable the selected I2C interrupts
        pI2C->CR2 |= (uint16_t)interruptConfig;
    }
    else {
        // Disable the selected I2C interrupts
        pI2C->CR2 &= (uint16_t)(~interruptConfig);
    }
}

bool I2C_IsInterruptErrorPending(const I2C_ModuleAddress port, const I2C_InterruptErrorBit interruptBit) {
    const I2C_ModuleRegisters* const pI2C = (I2C_ModuleRegisters*)port;

    // Read the I2Cx status register
    const uint32_t flag1 = pI2C->SR1;
    uint32_t flag2 = pI2C->SR2;
    flag2 = flag2 << 16;

    // Get the I2C status value
    const uint32_t i2cstatus = (flag1 | flag2) & FLAG_Mask;

    // Get bit[23:0] of the flag
    const uint32_t bitsToCheck = ((uint32_t)interruptBit) & FLAG_Mask;

    // Check the status of the specified I2C flag
    bool bitIsSet;
    if ((i2cstatus & bitsToCheck) != 0) {
        // I2C_IT is set
        bitIsSet = true;
    }
    else {
        // I2C_IT is reset
        bitIsSet = false;
    }
    return bitIsSet;
}

void I2C_ClearInterruptErrorPending(const I2C_ModuleAddress port, const I2C_InterruptErrorBit interruptBit) {
    I2C_ModuleRegisters* const pI2C = (I2C_ModuleRegisters*)port;
    const uint32_t bitsToClear = (uint32_t)interruptBit;
    // Get the I2C flag position
    const uint32_t flagpos = bitsToClear & FLAG_Mask;
    // Get the I2C flag index
    const uint32_t flagindex = bitsToClear >> 28;
    // all values defined in I2C_InterruptErrorBit can be cleared by writing 0 to SR1
    ASSERT_DEBUG(flagindex == 1);
    // Clear the flag by writing 0
    pI2C->SR1 = (uint16_t)~flagpos;
}

bool I2C_IsStartGenerationPending(const I2C_ModuleAddress port) {
    const I2C_ModuleRegisters* const pI2C = (I2C_ModuleRegisters*)port;
    // CR1 bit START is cleared by hardware when start is sent
    // -> if set a start generation was requested but the start
    //    generation is still pending
    return ((pI2C->CR1 & CR1_START_Set) == CR1_START_Set);
}

uint16_t I2C_GetSR1(const I2C_ModuleAddress port) {
    const I2C_ModuleRegisters* const pI2C = (I2C_ModuleRegisters*)port;
    return pI2C->SR1;
}

uint16_t I2C_GetSR2(const I2C_ModuleAddress port) {
    const I2C_ModuleRegisters* const pI2C = (I2C_ModuleRegisters*)port;
    return pI2C->SR2;
}

