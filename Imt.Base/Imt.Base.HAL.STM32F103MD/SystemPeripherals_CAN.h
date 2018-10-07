// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#ifndef SYSTEMPERIPHERALS_CAN_H
#define SYSTEMPERIPHERALS_CAN_H

// Must be very first include
#include <Imt.Base.Core.Platform/Platform.h>

// Determine if a C++ compiler is being used.  If so, ensure that standard C is used to process the API information.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//@{
// The Basic Extended CAN peripheral (CAN) peripheral module.
// It can receive and transmit standard frames with 11-bit identifiers as well as extended frames with 29-bit identifiers.
// It has three transmit mailboxes, two receive FIFOs with 3 stages and 14 scalable filter banks.
//
// Reference: ST_CortexM3_STM32F103_TRM_Rev15.pdf Chapter 24
// Reference: ST_CortexM3_STM32F103_Datasheet_Rev16.pdf Chapter 2.3.19
// @author lbreitenmoser
//@}

//@{
// CAN baud rate Prescaler
//@}
typedef enum {
    // Prescale by 1
    CAN_BRP_1 = ((uint8_t)0x01),
    // Prescale by 10
    CAN_BRP_10 = ((uint8_t)0x0A)
} CAN_BRP;

//@{
// CAN Mode
//@}
typedef enum {
    // Normal mode
    CAN_Mode_Normal = ((uint8_t)0x00)
} CAN_Mode;

//@{
// CAN resynchronization jump width
//@}
typedef enum {
    // 1 time quantum
    CAN_SJW_1tq = ((uint8_t)0x00)
} CAN_SJW;

//@{
// CAN time quantum in bit segment 1
//@}
typedef enum {
    // 5 time quantum
    CAN_BS1_5tq = ((uint8_t)0x04)
} CAN_BS1;

//@{
// CAN time quantum in bit segment 2
//@}
typedef enum {
    // 2 time quantum
    CAN_BS2_2tq = ((uint8_t)0x01)
} CAN_BS2;

//@{
// CAN init structure definition
//@}
typedef struct {
    // Specifies the length of a time quantum.
    CAN_BRP Prescaler;

    // Specifies the CAN operating mode.
    CAN_Mode Mode;

    // Specifies the maximum number of time quanta the CAN hardware is allowed to lengthen or shorten a bit to perform resynchronization.
    CAN_SJW SJW;

    // Specifies the number of time quanta in Bit Segment 1.
    CAN_BS1 BS1;

    // Specifies the number of time quanta in Bit Segment 2.
    CAN_BS2 BS2;

    // Enable or disable the time triggered communication mode.
    // This parameter can be set either to true (= enabled) or false (= disabled).
    bool TTCM;

    // Enable or disable the automatic bus-off management.
    // This parameter can be set either to true (= enabled) or false (= disabled).
    bool ABOM;

    // Enable or disable the automatic wake-up mode.
    // This parameter can be set either to true (= enabled) or false (= disabled).
    bool AWUM;

    // Enable or disable the no-automatic retransmission mode.
    // This parameter can be set either to true (= enabled) or false (= disabled).
    bool NART;

    // Enable or disable the Receive FIFO Locked mode.
    // This parameter can be set either to true (= enabled) or false (= disabled).
    bool RFLM;

    // Enable or disable the transmit FIFO priority.
    // This parameter can be set either to true (= enabled, Priority driven by the request order (chronologically))  or false (= disabled, Priority driven by the identifier of the message).
    bool TXFP;
} CAN_InitStruct;

//@{
// CAN filter number
//@}
typedef enum {
    CAN_FilterNr0 = ((uint8_t)0x00),
    CAN_FilterNr1 = ((uint8_t)0x01),
    CAN_FilterNr2 = ((uint8_t)0x02),
    CAN_FilterNr3 = ((uint8_t)0x03)
} CAN_FilterNumber;

//@{
// CAN filter mode
//@}
typedef enum {
    // identifier/mask mode
    CAN_FilterMode_IdMask = ((uint8_t)0x00)
} CAN_FilterMode;

//@{
// CAN filter FIFO assignment
//@}
typedef enum {
    // Filter FIFO 0 assignment for filter x
    CAN_Filter_FIFO0 = ((uint8_t)0x00)
} CAN_FilterFIFOAssignment;

//@{
// CAN filter scale
//@}
typedef enum {
    // One 32-bit filter
    CAN_FilterScale_32bit = ((uint8_t)0x01)
} CAN_FilterScale;

//@{
// CAN 32-Bit mapping
//@}
typedef struct CAN_Filter32BitMapping {
    // must be zero
    uint32_t zero : 1;
    // 0 = Remote & 1 = Remote frame expected
    uint32_t RTR : 1;
    // 0 = STD, 1 = Extended
    uint32_t IDE : 1;
    // EXID[17:0]
    uint32_t EXID : 18;
    // STID [0:10] / EXTID[18:28]
    uint32_t STID : 11;
} CAN_Filter32BitMapping;

//@{
// CAN CAN filter init structure definition
//@}
typedef struct {
    // Specifies the filter which will be initialized.
    CAN_FilterNumber FilterNumber;

    // Specifies the filter mode to be initialized.
    CAN_FilterMode FilterMode;

    // Specifies the filter scale.
    CAN_FilterScale FilterScale;

    // Specifies the FIFO (0 or 1) which will be assigned to the filter.
    CAN_FilterFIFOAssignment FilterFIFOAssignment;

    // Enable or disable the filter.
    // This parameter can be set either to true (=enable) or false (=disable).
    bool FilterActivation;

    // Specifies the filter identification number
    union {
        uint32_t value;
        CAN_Filter32BitMapping CAN_FilterId;
    } FilterBankRegister1;

    // Specifies the filter mask number or identification number
    union {
        uint32_t value;
        CAN_Filter32BitMapping CAN_Mask;
    } FilterBankRegister2;

} CAN_FilterInitStruct;

//@{
// CAN identifier type
//@}
typedef enum {
    // 11bit identifier
    CAN_Identifier_Standard = 0x00000000,
    // 29bit extended identifier
    CAN_Identifier_Extended = 0x00000004
} CAN_Identifier;

//@{
// CAN used mailbox for transmission
//@}
typedef enum {
    // Mailbox 0 used for transmission
    CAN_TxMailbox0       = ((uint8_t)0x00),
    // Mailbox 1 used for transmission
    CAN_TxMailbox1       = ((uint8_t)0x01),
    // Mailbox 2 used for transmission
    CAN_TxMailbox2       = ((uint8_t)0x02),
    // No empty mailbox available for transmission
    CAN_TxNoEmptyMailbox = ((uint8_t)0x04)
} CAN_TxMailbox;

//@{
// CAN Tx message structure definition
//@}
typedef struct {
    // Specifies the CAN identifier.
    // This parameter can be either a standard identifier with a value between 0 to 0x7FF or an extended identifier with a value between 0 to 0x1FFFFFFF.
    uint32_t Id;

    // Specifies the type of identifier for the message that will be transmitted.
    CAN_Identifier IDE;

    // Specifies the length of the frame that will be transmitted. This parameter can be a value between 0 to 8
    uint8_t DLC;

    // Contains the data to be transmitted. It ranges from 0 to 0xFF.
    uint8_t Data[8];
} CanTxMsg;

//@{
// CAN Rx FIFO number
//@}
typedef enum {
    // CAN FIFO 0 used to receive
    CAN_FIFO0 = ((uint8_t)0x00)
} CAN_RxFifoNr;

//@{
// CAN Rx message structure definition
//@}
typedef struct {
    // Specifies the CAN identifier.
    // This parameter can be either a standard identifier with a value between 0 to 0x7FF or an extended identifier with a value between 0 to 0x1FFFFFFF.
    uint32_t Id;

    // Specifies the type of identifier for the message that has been received.
    // This parameter can be a value of @see CAN_Identifier
    CAN_Identifier IDE;

    //  Specifies the length of the frame that will be received.
    // This parameter can be a value between 0 to 8
    uint8_t DLC;

    // Contains the data to be received. It ranges from 0 to 0xFF.
    uint8_t Data[8];

    // Specifies the index of the filter the message stored in the mailbox passes through.
    // This parameter can be a value between 0 to 0xFF
    uint8_t FMI;
} CanRxMsg;

//@{
// Enumeration for CAN interrupt config identifiers
//@}
typedef enum  {
    // FIFO 0 message pending Interrupt
    CAN_ITCONFIG_FMP0 = ((uint32_t)0x00000002),
    // FIFO 0 full Interrupt
    CAN_IT_FF0 = ((uint32_t)0x00000004),
    // FIFO 0 overrun Interrupt
    CAN_IT_FOV0 = ((uint32_t)0x00000008)
} CAN_InterruptConfig;

//@ {
// Deinitializes the CAN peripheral registers to their default reset values.
//@ }
void CAN_DeInit(void);

//@ {
// Initializes the CAN peripheral according to the specified parameters in the canInitStruct.
// @param  canInitStruct: pointer to a CAN_InitStruct structure that contains the configuration information for the CAN peripheral.
// @return true indicates initialization succeed - false indicates initialization failed
//@ }
bool CAN_Init(const CAN_InitStruct* const canInitStruct);

//@ {
// @brief Initializes the CAN peripheral according to the specified parameters in the filterInitStruct.
// filterInitStruct: pointer to a CAN_FilterInitStruct structure that contains the configuration information.
//@ }
void CAN_FilterInit(const CAN_FilterInitStruct* const filterInitStruct);

//@ {
// @brief  Initiates the transmission of a message.
// @param  txMessage: pointer to a structure which contains CAN Id, CAN DLC and CAN data.
// @return The number of the mailbox that is used for transmission or CAN_TxNoEmptyMailbox if there is no empty mailbox.
//@ }
CAN_TxMailbox CAN_Transmit(const CanTxMsg* const txMessage);

//@ {
// @brief  Cancels a transmit request.
// @param  mailboxNr: The number of the mailbox of which the transmit request should be canceled
//@ }
void CAN_CancelTransmit(const CAN_TxMailbox mailboxNr);

//@ {
// @brief  Receives a message.
// @param  rxFifoNr:   Receive FIFO number.
// @param  RxMessage:  pointer to a structure receive message which contains CAN Id, CAN DLC, CAN data and FMI number.
//@ }
void CAN_Receive(const CAN_RxFifoNr rxFifoNr, CanRxMsg* const rxMessage);

//@ {
// @brief  Enables or disables the specified CANx interrupts.
// @param  interruptConfig: specifies the CAN interrupt sources to be enabled or disabled.
// @param  doEnable:        true = interrupt will be enabled - false = interrupt will be disabled
//@ }
void CAN_EnableInterrupt(const CAN_InterruptConfig interruptConfig, const bool doEnable);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // #ifndef SYSTEMPERIPHERALS_CAN_H
