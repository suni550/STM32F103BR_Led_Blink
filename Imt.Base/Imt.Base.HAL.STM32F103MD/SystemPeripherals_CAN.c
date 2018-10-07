// (c) IMT - Information Management Technology AG, CH-9470 Buchs, www.imt.ch.
// SW guideline: Technote Coding Guidelines Ver. 1.5.1

#include "SystemPeripherals_CAN.h"

// Imt.Base includes
#include <Imt.Base.Core.Diagnostics/Diagnostics.h>

// Project includes
#include "SystemPeripherals_RCC.h"
#include "SystemMemoryMap.h"

//@{
// CAN TxMailBox
//@}
typedef struct {
    uint32_t TIR;
    uint32_t TDTR;
    uint32_t TDLR;
    uint32_t TDHR;
} CAN_TxMailBox;

//@{
// CAN FIFOMailBox
//@}
typedef struct {
    uint32_t RIR;
    uint32_t RDTR;
    uint32_t RDLR;
    uint32_t RDHR;
} CAN_FIFOMailBox;

//@{
// CAN FilterRegister
//@}
typedef struct {
    uint32_t FR1;
    uint32_t FR2;
} CAN_FilterRegister;

//@{
// CAN module register structure
//@}
//lint -save
//lint -e754 // local structure member not referenced (offset required for correct register access)
typedef struct {
    volatile uint32_t MCR;
    volatile uint32_t MSR;
    volatile uint32_t TSR;
    volatile uint32_t RF0R;
    volatile uint32_t RF1R;
    volatile uint32_t IER;
    volatile uint32_t ESR;
    volatile uint32_t BTR;
    uint32_t RESERVED0[88];
    volatile CAN_TxMailBox sTxMailBox[3];
    volatile CAN_FIFOMailBox sFIFOMailBox[2];
    uint32_t RESERVED1[12];
    volatile uint32_t FMR;
    volatile uint32_t FM1R;
    uint32_t  RESERVED2;
    volatile uint32_t FS1R;
    uint32_t  RESERVED3;
    volatile uint32_t FFA1R;
    uint32_t  RESERVED4;
    volatile uint32_t FA1R;
    uint32_t  RESERVED5[8];
    volatile CAN_FilterRegister sFilterRegister[14];
} CAN_ModuleRegisters;
//lint -restore

//@{
// CAN remote transmission request
//@}
typedef enum {
    // Data frame
    CAN_RTR_Data = ((uint32_t)0x00000000)
} CAN_RTR;

//@{
// Bit definition for CAN_MCR register
//@}
// Initialization Request
#define  CAN_MCR_INRQ       ((uint16_t)0x0001)
// Sleep Mode Request
#define  CAN_MCR_SLEEP      ((uint16_t)0x0002)
// Transmit FIFO Priority
#define  CAN_MCR_TXFP       ((uint16_t)0x0004)
// Receive FIFO Locked Mode
#define  CAN_MCR_RFLM       ((uint16_t)0x0008)
// No Automatic Retransmission
#define  CAN_MCR_NART       ((uint16_t)0x0010)
// Automatic Wakeup Mode
#define  CAN_MCR_AWUM       ((uint16_t)0x0020)
// Automatic Bus-Off Management
#define  CAN_MCR_ABOM       ((uint16_t)0x0040)
// Time Triggered Communication Mode
#define  CAN_MCR_TTCM       ((uint16_t)0x0080)

//@{
// Bit definition for CAN_MSR register
//@}
// Initialization Acknowledge
#define  CAN_MSR_INAK       ((uint16_t)0x0001)

//@{
// Bit definition for CAN_RF0R register
//@}
// Release FIFO 0 Output Mailbox
#define  CAN_RF0R_RFOM0     ((uint8_t)0x20)

//@{
// Bit definition for CAN_TSR register
//@}
// Transmit Mailbox 0 Empty
#define  CAN_TSR_TME0       ((uint32_t)0x04000000)
// Transmit Mailbox 1 Empty
#define  CAN_TSR_TME1       ((uint32_t)0x08000000)
// Transmit Mailbox 2 Empty
#define  CAN_TSR_TME2       ((uint32_t)0x10000000)
// Abort Request for Mailbox 0
#define  CAN_TSR_ABRQ0      ((uint32_t)0x00000080)
// Abort Request for Mailbox 1
#define  CAN_TSR_ABRQ1      ((uint32_t)0x00008000)
// Abort Request for Mailbox 2
#define  CAN_TSR_ABRQ2      ((uint32_t)0x00800000)

//@{
// CAN Mailbox Transmit Request
//@}
// Transmit mailbox request
#define TMIDxR_TXRQ         ((uint32_t)0x00000001)

//@{
// CAN Filter Master Register bits
//@}
// Filter init mode
#define FMR_FINIT           ((uint32_t)0x00000001)

//@{
// Time out for INAK bit
//@}
#define INAK_TIMEOUT        ((uint32_t)0x0000FFFF)

void CAN_DeInit(void) {
    // Enable CAN1 reset state
    RCC_ResetAPB1Peripheral(RCC_APB1Periph_CAN, true);
    // Release CAN1 from reset state
    RCC_ResetAPB1Peripheral(RCC_APB1Periph_CAN, false);
}

bool CAN_Init(const CAN_InitStruct* const canInitStruct) {
    if (canInitStruct == NULL) {
        ASSERT_DEBUG(false);
        return false;
    }

    bool InitStatus = false;
    uint32_t wait_ack = 0x00000000;
    CAN_ModuleRegisters* const pCAN = (CAN_ModuleRegisters*)CAN_BASE;

    // Exit from sleep mode
    pCAN->MCR &= (~(uint32_t)CAN_MCR_SLEEP);

    // Request initialization
    pCAN->MCR |= CAN_MCR_INRQ ;

    // Wait the acknowledge
    while (((pCAN->MSR & CAN_MSR_INAK) != CAN_MSR_INAK) && (wait_ack != INAK_TIMEOUT)) {
        wait_ack++;
    }

    // Check acknowledge
    if ((pCAN->MSR & CAN_MSR_INAK) != CAN_MSR_INAK) {
        InitStatus = false;
    }
    else {
        // Set the time triggered communication mode
        if (canInitStruct->TTCM) {
            pCAN->MCR |= CAN_MCR_TTCM;
        }
        else {
            pCAN->MCR &= ~(uint32_t)CAN_MCR_TTCM;
        }

        // Set the automatic bus-off management
        if (canInitStruct->ABOM) {
            pCAN->MCR |= CAN_MCR_ABOM;
        }
        else {
            pCAN->MCR &= ~(uint32_t)CAN_MCR_ABOM;
        }

        // Set the automatic wake-up mode
        if (canInitStruct->AWUM) {
            pCAN->MCR |= CAN_MCR_AWUM;
        }
        else {
            pCAN->MCR &= ~(uint32_t)CAN_MCR_AWUM;
        }

        // Set the no automatic retransmission
        if (canInitStruct->NART) {
            pCAN->MCR |= CAN_MCR_NART;
        }
        else {
            pCAN->MCR &= ~(uint32_t)CAN_MCR_NART;
        }

        // Set the receive FIFO locked mode
        if (canInitStruct->RFLM) {
            pCAN->MCR |= CAN_MCR_RFLM;
        }
        else {
            pCAN->MCR &= ~(uint32_t)CAN_MCR_RFLM;
        }

        // Set the transmit FIFO priority
        if (canInitStruct->TXFP) {
            pCAN->MCR |= CAN_MCR_TXFP;
        }
        else {
            pCAN->MCR &= ~(uint32_t)CAN_MCR_TXFP;
        }

        // Set the bit timing register
        pCAN->BTR = (uint32_t)((uint32_t)canInitStruct->Mode << 30) | \
            ((uint32_t)canInitStruct->SJW << 24) | \
            ((uint32_t)canInitStruct->BS1 << 16) | \
            ((uint32_t)canInitStruct->BS2 << 20) | \
            ((uint32_t)canInitStruct->Prescaler - 1);

        // Request leave initialization
        pCAN->MCR &= ~(uint32_t)CAN_MCR_INRQ;

        // Wait the acknowledge
        wait_ack = 0;

        while (((pCAN->MSR & CAN_MSR_INAK) == CAN_MSR_INAK) && (wait_ack != INAK_TIMEOUT)) {
            wait_ack++;
        }

        // ...and check acknowledged
        if ((pCAN->MSR & CAN_MSR_INAK) == CAN_MSR_INAK) {
            InitStatus = false;
        }
        else {
            InitStatus = true;
        }
    }

    // At this step, return the status of initialization
    return InitStatus;
}

void CAN_FilterInit(const CAN_FilterInitStruct* const filterInitStruct) {
    if (filterInitStruct == NULL) {
        ASSERT_DEBUG(false);
        return;
    }

    const uint32_t filter_number_bit_pos = ((uint32_t)1) << (uint8_t)filterInitStruct->FilterNumber;
    CAN_ModuleRegisters* const pCAN = (CAN_ModuleRegisters*)CAN_BASE;

    // Initialization mode for the filter
    pCAN->FMR |= FMR_FINIT;

    // Filter Deactivation
    pCAN->FA1R &= ~(uint32_t)filter_number_bit_pos;

    // Filter Scale

    if (filterInitStruct->FilterScale == CAN_FilterScale_32bit) {
        // 32-bit scale for the filter
        pCAN->FS1R |= filter_number_bit_pos;
        // 32-bit identifier
        pCAN->sFilterRegister[filterInitStruct->FilterNumber].FR1 = filterInitStruct->FilterBankRegister1.value;

        // 32-bit mask
        pCAN->sFilterRegister[filterInitStruct->FilterNumber].FR2 = filterInitStruct->FilterBankRegister2.value;
    }

    // Filter Mode
    if (filterInitStruct->FilterMode == CAN_FilterMode_IdMask) {
        /*Id/Mask mode for the filter*/
        pCAN->FM1R &= ~(uint32_t)filter_number_bit_pos;
    }

    // Filter FIFO assignment
    if (filterInitStruct->FilterFIFOAssignment == CAN_Filter_FIFO0) {
        // FIFO 0 assignation for the filter
        pCAN->FFA1R &= ~(uint32_t)filter_number_bit_pos;
    }

    // Filter activation
    if (filterInitStruct->FilterActivation) {
        pCAN->FA1R |= filter_number_bit_pos;
    }

    // Leave the initialization mode for the filter
    pCAN->FMR &= ~FMR_FINIT;
}

CAN_TxMailbox CAN_Transmit(const CanTxMsg* const txMessage) {
    if (txMessage == NULL) {
        ASSERT_DEBUG(false);
        return CAN_TxNoEmptyMailbox;
    }

    CAN_ModuleRegisters* const pCAN = (CAN_ModuleRegisters*)CAN_BASE;
    CAN_TxMailbox transmit_mailbox = CAN_TxMailbox0;

    // Select one empty transmit mailbox
    if ((pCAN->TSR & CAN_TSR_TME0) == CAN_TSR_TME0) {
        transmit_mailbox = CAN_TxMailbox0;
    }
    else if ((pCAN->TSR & CAN_TSR_TME1) == CAN_TSR_TME1) {
        transmit_mailbox = CAN_TxMailbox1;
    }
    else if ((pCAN->TSR & CAN_TSR_TME2) == CAN_TSR_TME2) {
        transmit_mailbox = CAN_TxMailbox2;
    }
    else {
        transmit_mailbox = CAN_TxNoEmptyMailbox;
    }

    if (transmit_mailbox != CAN_TxNoEmptyMailbox) {
        // Set up the Id
        pCAN->sTxMailBox[transmit_mailbox].TIR &= TMIDxR_TXRQ;
        if (txMessage->IDE == CAN_Identifier_Standard) {
            pCAN->sTxMailBox[transmit_mailbox].TIR |= ((txMessage->Id << 21));
        }
        else {
            pCAN->sTxMailBox[transmit_mailbox].TIR |= ((txMessage->Id << 3) | (uint32_t)txMessage->IDE);
        }

        // Set up the DLC
        const uint8_t dlc = txMessage->DLC & (uint8_t)0x0000000F;
        pCAN->sTxMailBox[transmit_mailbox].TDTR &= (uint32_t)0xFFFFFFF0;
        pCAN->sTxMailBox[transmit_mailbox].TDTR |= dlc;

        // Set up the data field
        pCAN->sTxMailBox[transmit_mailbox].TDLR =
            (((uint32_t)txMessage->Data[3] << 24) |
            ((uint32_t)txMessage->Data[2] << 16) |
            ((uint32_t)txMessage->Data[1] << 8) |
            ((uint32_t)txMessage->Data[0]));
        pCAN->sTxMailBox[transmit_mailbox].TDHR =
            (((uint32_t)txMessage->Data[7] << 24) |
            ((uint32_t)txMessage->Data[6] << 16) |
            ((uint32_t)txMessage->Data[5] << 8) |
            ((uint32_t)txMessage->Data[4]));

        // Request transmission
        pCAN->sTxMailBox[transmit_mailbox].TIR |= TMIDxR_TXRQ;
    }
    return transmit_mailbox;
}

void CAN_CancelTransmit(const CAN_TxMailbox mailboxNr) {
    CAN_ModuleRegisters* const pCAN = (CAN_ModuleRegisters*)CAN_BASE;

    // abort transmission
    switch (mailboxNr) {
    case (CAN_TxMailbox0):
        pCAN->TSR |= CAN_TSR_ABRQ0;
        break;
    case (CAN_TxMailbox1):
        pCAN->TSR |= CAN_TSR_ABRQ1;
        break;
    case (CAN_TxMailbox2):
        pCAN->TSR |= CAN_TSR_ABRQ2;
        break;
    case (CAN_TxNoEmptyMailbox):
        // do nothing
        break;
    default:
        // do nothing
        break;
    }
}

void CAN_Receive(const CAN_RxFifoNr rxFifoNr, CanRxMsg* const rxMessage) {
    if (rxMessage == NULL) {
        ASSERT_DEBUG(false);
        return;
    }

    CAN_ModuleRegisters* const pCAN = (CAN_ModuleRegisters*)CAN_BASE;

    // Get the Id
    rxMessage->IDE = (CAN_Identifier)((uint8_t)0x04 & pCAN->sFIFOMailBox[rxFifoNr].RIR);

    if (rxMessage->IDE == CAN_Identifier_Standard) {
        // 11-bit standard identifier
        rxMessage->Id = (uint32_t)0x000007FF & (pCAN->sFIFOMailBox[rxFifoNr].RIR >> 21);
    }
    else {
        // 29-bit extended identifier
        rxMessage->Id = (uint32_t)0x1FFFFFFF & (pCAN->sFIFOMailBox[rxFifoNr].RIR >> 3);
    }

    const uint8_t rtr = (uint8_t)0x02 & pCAN->sFIFOMailBox[rxFifoNr].RIR;
    // Remote transmission is currently not supported by this driver
    // --> check the filter configuration
    ASSERT_DEBUG(rtr == (uint8_t)CAN_RTR_Data);

    // Get the DLC
    rxMessage->DLC = (uint8_t)0x0F & pCAN->sFIFOMailBox[rxFifoNr].RDTR;
    // Get the FMI
    rxMessage->FMI = (uint8_t)0xFF & (pCAN->sFIFOMailBox[rxFifoNr].RDTR >> 8);
    // Get the data field
    rxMessage->Data[0] = (uint8_t)0xFF & pCAN->sFIFOMailBox[rxFifoNr].RDLR;
    rxMessage->Data[1] = (uint8_t)0xFF & (pCAN->sFIFOMailBox[rxFifoNr].RDLR >> 8);
    rxMessage->Data[2] = (uint8_t)0xFF & (pCAN->sFIFOMailBox[rxFifoNr].RDLR >> 16);
    rxMessage->Data[3] = (uint8_t)0xFF & (pCAN->sFIFOMailBox[rxFifoNr].RDLR >> 24);
    rxMessage->Data[4] = (uint8_t)0xFF & pCAN->sFIFOMailBox[rxFifoNr].RDHR;
    rxMessage->Data[5] = (uint8_t)0xFF & (pCAN->sFIFOMailBox[rxFifoNr].RDHR >> 8);
    rxMessage->Data[6] = (uint8_t)0xFF & (pCAN->sFIFOMailBox[rxFifoNr].RDHR >> 16);
    rxMessage->Data[7] = (uint8_t)0xFF & (pCAN->sFIFOMailBox[rxFifoNr].RDHR >> 24);

    // Release FIFO0
    if (rxFifoNr == CAN_FIFO0) {
        pCAN->RF0R |= CAN_RF0R_RFOM0;
    }
    else {
        // Receiving on FIFO1 is currently not supported
        // --> check the filter configuration
        ASSERT_DEBUG(false);
    }
}

void CAN_EnableInterrupt(const CAN_InterruptConfig interruptConfig, const bool doEnable) {
    CAN_ModuleRegisters* const pCAN = (CAN_ModuleRegisters*)CAN_BASE;
    if (doEnable) {
        pCAN->IER |= (uint32_t)interruptConfig;
    }
    else {
        pCAN->IER &= ~(uint32_t)interruptConfig;
    }
}
