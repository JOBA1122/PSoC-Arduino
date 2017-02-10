/***************************************************************************//**
* \file UART_I2C_INT.c
* \version 3.20
*
* \brief
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in I2C mode.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_PVT.h"
#include "UART_I2C_PVT.h"
#include "cyapicallbacks.h"


/*******************************************************************************
* Function Name: UART_I2C_ISR
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the SCB I2C mode.
*
*******************************************************************************/
CY_ISR(UART_I2C_ISR)
{
    uint32 diffCount;
    uint32 endTransfer;

#ifdef UART_I2C_ISR_ENTRY_CALLBACK
    UART_I2C_ISR_EntryCallback();
#endif /* UART_I2C_ISR_ENTRY_CALLBACK */

#if (UART_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
    uint32 response;

    response = UART_I2C_ACK_ADDR;
#endif /* (UART_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */

    endTransfer = 0u; /* Continue active transfer */

    /* Calls customer routine if registered */
    if(NULL != UART_customIntrHandler)
    {
        UART_customIntrHandler();
    }

    if(UART_CHECK_INTR_I2C_EC_MASKED(UART_INTR_I2C_EC_WAKE_UP))
    {
        /* Mask-off after wakeup */
        UART_SetI2CExtClkInterruptMode(UART_NO_INTR_SOURCES);
    }

    /* Master and Slave error tracking:
    * Add the master state check to track only the master errors when the master is active or
    * track slave errors when the slave is active or idle.
    * A special MMS case: in the address phase with misplaced Start: the master sets the LOST_ARB and
    * slave BUS_ERR. The valid event is LOST_ARB comes from the master.
    */
    if(UART_CHECK_I2C_FSM_MASTER)
    {
        if(UART_I2C_MASTER)
        {
            /* INTR_MASTER_I2C_BUS_ERROR:
            * A misplaced Start or Stop condition occurred on the bus: complete the transaction.
            * The interrupt is cleared in I2C_FSM_EXIT_IDLE.
            */
            if(UART_CHECK_INTR_MASTER_MASKED(UART_INTR_MASTER_I2C_BUS_ERROR))
            {
                UART_mstrStatus |= (uint16) (UART_I2C_MSTAT_ERR_XFER |
                                                         UART_I2C_MSTAT_ERR_BUS_ERROR);

                endTransfer = UART_I2C_CMPLT_ANY_TRANSFER;
            }

            /* INTR_MASTER_I2C_ARB_LOST:
            * The MultiMaster lost arbitrage during transaction.
            * A Misplaced Start or Stop condition is treated as lost arbitration when the master drives the SDA.
            * The interrupt source is cleared in I2C_FSM_EXIT_IDLE.
            */
            if(UART_CHECK_INTR_MASTER_MASKED(UART_INTR_MASTER_I2C_ARB_LOST))
            {
                UART_mstrStatus |= (uint16) (UART_I2C_MSTAT_ERR_XFER |
                                                         UART_I2C_MSTAT_ERR_ARB_LOST);

                endTransfer = UART_I2C_CMPLT_ANY_TRANSFER;
            }

            if(UART_I2C_MULTI_MASTER_SLAVE)
            {
                /* I2C_MASTER_CMD_M_START_ON_IDLE:
                * MultiMaster-Slave does not generate start, because Slave was addressed.
                * Pass control to slave.
                */
                if(UART_CHECK_I2C_MASTER_CMD(UART_I2C_MASTER_CMD_M_START_ON_IDLE))
                {
                    UART_mstrStatus |= (uint16) (UART_I2C_MSTAT_ERR_XFER |
                                                             UART_I2C_MSTAT_ERR_ABORT_XFER);

                    endTransfer = UART_I2C_CMPLT_ANY_TRANSFER;
                }
            }
            

            /* The error handling common part:
            * Sets a completion flag of the master transaction and passes control to:
            *  - I2C_FSM_EXIT_IDLE - to complete transaction in case of: ARB_LOST or BUS_ERR.
            *  - I2C_FSM_IDLE      - to take chance for the slave to process incoming transaction.
            */
            if(0u != endTransfer)
            {
                /* Set completion flags for master */
                UART_mstrStatus |= (uint16) UART_GET_I2C_MSTAT_CMPLT;

                if(UART_I2C_MULTI_MASTER_SLAVE)
                {
                    if(UART_CHECK_I2C_FSM_ADDR)
                    {
                        /* Start generation is set after another master starts accessing Slave.
                        * Clean-up master and turn to slave. Set state to IDLE.
                        */
                        if(UART_CHECK_I2C_MASTER_CMD(UART_I2C_MASTER_CMD_M_START_ON_IDLE))
                        {
                            UART_I2C_MASTER_CLEAR_START;

                            endTransfer = UART_I2C_CMPLT_ANY_TRANSFER; /* Pass control to Slave */
                        }
                        /* Valid arbitration lost on the address phase happens only when: master LOST_ARB is set and
                        * slave BUS_ERR is cleared. Only in that case set the state to IDLE without SCB IP re-enable.
                        */
                        else if((!UART_CHECK_INTR_SLAVE_MASKED(UART_INTR_SLAVE_I2C_BUS_ERROR))
                               && UART_CHECK_INTR_MASTER_MASKED(UART_INTR_MASTER_I2C_ARB_LOST))
                        {
                            endTransfer = UART_I2C_CMPLT_ANY_TRANSFER; /* Pass control to Slave */
                        }
                        else
                        {
                            endTransfer = 0u; /* Causes I2C_FSM_EXIT_IDLE to be set below */
                        }

                        if(0u != endTransfer) /* Clean-up master to proceed with slave */
                        {
                            UART_CLEAR_TX_FIFO; /* Shifter keeps address, clear it */

                            UART_DISABLE_MASTER_AUTO_DATA_ACK; /* In case of reading disable autoACK */

                            /* Clean-up master interrupt sources */
                            UART_ClearMasterInterruptSource(UART_INTR_MASTER_ALL);

                            /* Disable data processing interrupts: they have to be cleared before */
                            UART_SetRxInterruptMode(UART_NO_INTR_SOURCES);
                            UART_SetTxInterruptMode(UART_NO_INTR_SOURCES);

                            UART_state = UART_I2C_FSM_IDLE;
                        }
                        else
                        {
                            /* Set I2C_FSM_EXIT_IDLE for BUS_ERR and ARB_LOST (that is really bus error) */
                            UART_state = UART_I2C_FSM_EXIT_IDLE;
                        }
                    }
                    else
                    {
                        /* Set I2C_FSM_EXIT_IDLE if any other state than address */
                        UART_state = UART_I2C_FSM_EXIT_IDLE;
                    }
                }
                else
                {
                    /* In case of LOST*/
                    UART_state = UART_I2C_FSM_EXIT_IDLE;
                }
                
            }
        }
        
    }
    else /* (UART_CHECK_I2C_FSM_SLAVE) */
    {
        if(UART_I2C_SLAVE)
        {
            /* INTR_SLAVE_I2C_BUS_ERROR or UART_INTR_SLAVE_I2C_ARB_LOST:
            * A Misplaced Start or Stop condition occurred on the bus: set a flag
            * to notify an error condition.
            */
            if(UART_CHECK_INTR_SLAVE_MASKED(UART_INTR_SLAVE_I2C_BUS_ERROR |
                                                        UART_INTR_SLAVE_I2C_ARB_LOST))
            {
                if(UART_CHECK_I2C_FSM_RD)
                {
                    /* TX direction: master reads from slave */
                    UART_slStatus &= (uint8) ~UART_I2C_SSTAT_RD_BUSY;
                    UART_slStatus |= (uint8) (UART_I2C_SSTAT_RD_ERR |
                                                          UART_I2C_SSTAT_RD_CMPLT);
                }
                else
                {
                    /* RX direction: master writes into slave */
                    UART_slStatus &= (uint8) ~UART_I2C_SSTAT_WR_BUSY;
                    UART_slStatus |= (uint8) (UART_I2C_SSTAT_WR_ERR |
                                                          UART_I2C_SSTAT_WR_CMPLT);
                }

                UART_state = UART_I2C_FSM_EXIT_IDLE;
            }
        }
        
    }

    /* States description:
    * Any Master operation starts from: the ADDR_RD/WR state as the master generates traffic on the bus.
    * Any Slave operation starts from: the IDLE state as the slave always waits for actions from the master.
    */

    /* FSM Master */
    if(UART_CHECK_I2C_FSM_MASTER)
    {
        if(UART_I2C_MASTER)
        {
            /* INTR_MASTER_I2C_STOP:
            * A Stop condition was generated by the master: the end of the transaction.
            * Set completion flags to notify the API.
            */
            if(UART_CHECK_INTR_MASTER_MASKED(UART_INTR_MASTER_I2C_STOP))
            {
                UART_ClearMasterInterruptSource(UART_INTR_MASTER_I2C_STOP);

                UART_mstrStatus |= (uint16) UART_GET_I2C_MSTAT_CMPLT;
                UART_state       = UART_I2C_FSM_IDLE;
            }
            else
            {
                if(UART_CHECK_I2C_FSM_ADDR) /* Address stage */
                {
                    /* INTR_MASTER_I2C_NACK:
                    * The master sent an address but it was NACKed by the slave. Complete transaction.
                    */
                    if(UART_CHECK_INTR_MASTER_MASKED(UART_INTR_MASTER_I2C_NACK))
                    {
                        UART_ClearMasterInterruptSource(UART_INTR_MASTER_I2C_NACK);

                        UART_mstrStatus |= (uint16) (UART_I2C_MSTAT_ERR_XFER |
                                                                 UART_I2C_MSTAT_ERR_ADDR_NAK);

                        endTransfer = UART_I2C_CMPLT_ANY_TRANSFER;
                    }
                    /* INTR_TX_UNDERFLOW. The master sent an address:
                    *  - TX direction: the clock is stretched after the ACK phase, because the TX FIFO is
                    *    EMPTY. The TX EMPTY cleans all the TX interrupt sources.
                    *  - RX direction: the 1st byte is received, but there is no ACK permission,
                    *    the clock is stretched after 1 byte is received.
                    */
                    else
                    {
                        if(UART_CHECK_I2C_FSM_RD) /* Reading */
                        {
                            UART_state = UART_I2C_FSM_MSTR_RD_DATA;
                        }
                        else /* Writing */
                        {
                            UART_state = UART_I2C_FSM_MSTR_WR_DATA;
                            if(0u != UART_mstrWrBufSize)
                            {
                                /* Enable INTR.TX_EMPTY if there is data to transmit */
                                UART_SetTxInterruptMode(UART_INTR_TX_EMPTY);
                            }
                        }
                    }
                }

                if(UART_CHECK_I2C_FSM_DATA) /* Data phase */
                {
                    if(UART_CHECK_I2C_FSM_RD) /* Reading */
                    {
                        /* INTR_RX_FULL:
                        * RX direction: the master received 8 bytes.
                        * Get data from RX FIFO and decide whether to ACK or  NACK the following bytes.
                        */
                        if(UART_CHECK_INTR_RX_MASKED(UART_INTR_RX_FULL))
                        {
                            /* Calculate difference */
                            diffCount =  UART_mstrRdBufSize -
                                        (UART_mstrRdBufIndex + UART_GET_RX_FIFO_ENTRIES);

                            /* Proceed transaction or end it when RX FIFO becomes FULL again */
                            if(diffCount > UART_I2C_FIFO_SIZE)
                            {
                                diffCount = UART_I2C_FIFO_SIZE;
                            }
                            else
                            {
                                if(0u == diffCount)
                                {
                                    UART_DISABLE_MASTER_AUTO_DATA_ACK;

                                    diffCount   = UART_I2C_FIFO_SIZE;
                                    endTransfer = UART_I2C_CMPLT_ANY_TRANSFER;
                                }
                            }

                            for(; (0u != diffCount); diffCount--)
                            {
                                UART_mstrRdBufPtr[UART_mstrRdBufIndex] = (uint8)
                                                                                        UART_RX_FIFO_RD_REG;
                                UART_mstrRdBufIndex++;
                            }
                        }
                        /* INTR_RX_NOT_EMPTY:
                        * RX direction: the master received one data byte, ACK or NACK it.
                        * The last byte is stored and NACKed by the master. The NACK and Stop is
                        * generated by one command generate Stop.
                        */
                        else if(UART_CHECK_INTR_RX_MASKED(UART_INTR_RX_NOT_EMPTY))
                        {
                            /* Put data in component buffer */
                            UART_mstrRdBufPtr[UART_mstrRdBufIndex] = (uint8) UART_RX_FIFO_RD_REG;
                            UART_mstrRdBufIndex++;

                            if(UART_mstrRdBufIndex < UART_mstrRdBufSize)
                            {
                                UART_I2C_MASTER_GENERATE_ACK;
                            }
                            else
                            {
                               endTransfer = UART_I2C_CMPLT_ANY_TRANSFER;
                            }
                        }
                        else
                        {
                            /* Do nothing */
                        }

                        UART_ClearRxInterruptSource(UART_INTR_RX_ALL);
                    }
                    else /* Writing */
                    {
                        /* INTR_MASTER_I2C_NACK :
                        * The master writes data to the slave and NACK was received: not all the bytes were
                        * written to the slave from the TX FIFO. Revert the index if there is data in
                        * the TX FIFO and pass control to a complete transfer.
                        */
                        if(UART_CHECK_INTR_MASTER_MASKED(UART_INTR_MASTER_I2C_NACK))
                        {
                            UART_ClearMasterInterruptSource(UART_INTR_MASTER_I2C_NACK);

                            /* Rollback write buffer index: NACKed byte remains in shifter */
                            UART_mstrWrBufIndexTmp -= (UART_GET_TX_FIFO_ENTRIES +
                                                                   UART_GET_TX_FIFO_SR_VALID);

                            /* Update number of transferred bytes */
                            UART_mstrWrBufIndex = UART_mstrWrBufIndexTmp;

                            UART_mstrStatus |= (uint16) (UART_I2C_MSTAT_ERR_XFER |
                                                                     UART_I2C_MSTAT_ERR_SHORT_XFER);

                            UART_CLEAR_TX_FIFO;

                            endTransfer = UART_I2C_CMPLT_ANY_TRANSFER;
                        }
                        /* INTR_TX_EMPTY :
                        * TX direction: the TX FIFO is EMPTY, the data from the buffer needs to be put there.
                        * When there is no data in the component buffer, the underflow interrupt is
                        * enabled to catch when all the data has been transferred.
                        */
                        else if(UART_CHECK_INTR_TX_MASKED(UART_INTR_TX_EMPTY))
                        {
                            while(UART_I2C_FIFO_SIZE != UART_GET_TX_FIFO_ENTRIES)
                            {
                                /* The temporary mstrWrBufIndexTmp is used because slave could NACK the byte and index
                                * roll-back required in this case. The mstrWrBufIndex is updated at the end of transfer.
                                */
                                if(UART_mstrWrBufIndexTmp < UART_mstrWrBufSize)
                                {
                                #if(!UART_CY_SCBIP_V0)
                                   /* Clear INTR_TX.UNDERFLOW before putting the last byte into TX FIFO. This ensures
                                    * a proper trigger at the end of transaction when INTR_TX.UNDERFLOW single trigger
                                    * event. Ticket ID# 156735.
                                    */
                                    if(UART_mstrWrBufIndexTmp == (UART_mstrWrBufSize - 1u))
                                    {
                                        UART_ClearTxInterruptSource(UART_INTR_TX_UNDERFLOW);
                                        UART_SetTxInterruptMode(UART_INTR_TX_UNDERFLOW);
                                    }
                                 #endif /* (!UART_CY_SCBIP_V0) */

                                    /* Put data into TX FIFO */
                                    UART_TX_FIFO_WR_REG = (uint32) UART_mstrWrBufPtr[UART_mstrWrBufIndexTmp];
                                    UART_mstrWrBufIndexTmp++;
                                }
                                else
                                {
                                    break; /* No more data to put */
                                }
                            }

                        #if(UART_CY_SCBIP_V0)
                            if(UART_mstrWrBufIndexTmp == UART_mstrWrBufSize)
                            {
                                UART_SetTxInterruptMode(UART_INTR_TX_UNDERFLOW);
                            }

                            UART_ClearTxInterruptSource(UART_INTR_TX_ALL);
                        #else
                            UART_ClearTxInterruptSource(UART_INTR_TX_EMPTY);
                        #endif /* (UART_CY_SCBIP_V0) */
                        }
                        /* INTR_TX_UNDERFLOW:
                        * TX direction: all data from the TX FIFO was transferred to the slave.
                        * The transaction needs to be completed.
                        */
                        else if(UART_CHECK_INTR_TX_MASKED(UART_INTR_TX_UNDERFLOW))
                        {
                            /* Update number of transferred bytes */
                            UART_mstrWrBufIndex = UART_mstrWrBufIndexTmp;

                            endTransfer = UART_I2C_CMPLT_ANY_TRANSFER;
                        }
                        else
                        {
                            /* Do nothing */
                        }
                    }
                }

                if(0u != endTransfer) /* Complete transfer */
                {
                    /* Clean-up master after reading: only in case of NACK */
                    UART_DISABLE_MASTER_AUTO_DATA_ACK;

                    /* Disable data processing interrupts: they have to be cleared before */
                    UART_SetRxInterruptMode(UART_NO_INTR_SOURCES);
                    UART_SetTxInterruptMode(UART_NO_INTR_SOURCES);

                    if(UART_CHECK_I2C_MODE_NO_STOP(UART_mstrControl))
                    {
                        /* On-going transaction is suspended: the ReStart is generated by the API request */
                        UART_mstrStatus |= (uint16) (UART_I2C_MSTAT_XFER_HALT |
                                                                 UART_GET_I2C_MSTAT_CMPLT);

                        UART_state = UART_I2C_FSM_MSTR_HALT;
                    }
                    else
                    {
                        /* Complete transaction: exclude the data processing state and generate Stop.
                        * The completion status will be set after Stop generation.
                        * A special case is read: because NACK and Stop are generated by the command below.
                        * Lost arbitration can occur during NACK generation when
                        * the other master is still reading from the slave.
                        */
                        UART_I2C_MASTER_GENERATE_STOP;
                    }
                }
            }

        } /* (UART_I2C_MASTER) */
        

    } /* (UART_CHECK_I2C_FSM_MASTER) */


    /* FSM Slave */
    else if(UART_CHECK_I2C_FSM_SLAVE)
    {
        if(UART_I2C_SLAVE)
        {
            /* INTR_SLAVE_NACK:
            * The master completes reading the slave: the appropriate flags have to be set.
            * The TX FIFO is cleared after an overflow condition is set.
            */
            if(UART_CHECK_INTR_SLAVE_MASKED(UART_INTR_SLAVE_I2C_NACK))
            {
                UART_ClearSlaveInterruptSource(UART_INTR_SLAVE_I2C_NACK);

                /* All entries that remain in TX FIFO are: FIFO Size + 1 (SHIFTER) */
                diffCount = (UART_GET_TX_FIFO_ENTRIES + UART_GET_TX_FIFO_SR_VALID);

                if(UART_slOverFlowCount > diffCount) /* Overflow */
                {
                    UART_slStatus |= (uint8) UART_I2C_SSTAT_RD_OVFL;
                }
                else /* No Overflow */
                {
                    /* Roll-back temporary index */
                    UART_slRdBufIndexTmp -= (diffCount - UART_slOverFlowCount);
                }

                /* Update slave of transferred bytes */
                UART_slRdBufIndex = UART_slRdBufIndexTmp;

                /* Clean-up TX FIFO */
                UART_SetTxInterruptMode(UART_NO_INTR_SOURCES);
                UART_slOverFlowCount = 0u;
                UART_CLEAR_TX_FIFO;

                /* Complete master reading */
                UART_slStatus &= (uint8) ~UART_I2C_SSTAT_RD_BUSY;
                UART_slStatus |= (uint8)  UART_I2C_SSTAT_RD_CMPLT;
                UART_state     =  UART_I2C_FSM_IDLE;
            }


            /* INTR_SLAVE_I2C_WRITE_STOP:
            * The master completes writing to the slave: the appropriate flags have to be set.
            * The RX FIFO contains 1-8 bytes from the previous transaction which needs to be read.
            * There is a possibility that RX FIFO contains an address, it needs to leave it there.
            */
            if(UART_CHECK_INTR_SLAVE_MASKED(UART_INTR_SLAVE_I2C_WRITE_STOP))
            {
                UART_ClearSlaveInterruptSource(UART_INTR_SLAVE_I2C_WRITE_STOP);

                /* Read bytes from RX FIFO when auto data ACK receive logic is enabled. Otherwise all data bytes
                * were already read from the RX FIFO except for address byte which has to stay here to be handled by
                * I2C_ADDR_MATCH.
                */
                if (0u != (UART_I2C_CTRL_REG & UART_I2C_CTRL_S_READY_DATA_ACK))
                {
                    while(0u != UART_GET_RX_FIFO_ENTRIES)
                    {
                        if(UART_CHECK_I2C_ACCEPT_ADDRESS)
                        {
                            if((1u == UART_GET_RX_FIFO_ENTRIES) &&
                               (UART_CHECK_INTR_SLAVE_MASKED(UART_INTR_SLAVE_I2C_ADDR_MATCH)))
                            {
                                break; /* Leave address in RX FIFO */
                            }
                        }
                        

                        /* Put data in component buffer */
                        UART_slWrBufPtr[UART_slWrBufIndex] = (uint8) UART_RX_FIFO_RD_REG;
                        UART_slWrBufIndex++;
                    }

                    UART_DISABLE_SLAVE_AUTO_DATA;
                }

                if(UART_CHECK_INTR_RX(UART_INTR_RX_OVERFLOW))
                {
                    UART_slStatus |= (uint8) UART_I2C_SSTAT_WR_OVFL;
                }

                /* Clears RX interrupt sources triggered on data receiving */
                UART_SetRxInterruptMode(UART_NO_INTR_SOURCES);
                UART_ClearRxInterruptSource(UART_INTR_RX_ALL);

                /* Complete master writing */
                UART_slStatus &= (uint8) ~UART_I2C_SSTAT_WR_BUSY;
                UART_slStatus |= (uint8)  UART_I2C_SSTAT_WR_CMPLT;
                UART_state     =  UART_I2C_FSM_IDLE;
            }


            /* INTR_SLAVE_I2C_ADDR_MATCH or INTR_SLAVE_I2C_GENERAL:
            * The address match or general call address event starts the slave operation:
            * after leaving the TX or RX direction has to be chosen.
            * The wakeup interrupt must be cleared only after an address match is set.
            */
        #if (UART_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
            if (UART_CHECK_INTR_SLAVE_MASKED(UART_INTR_SLAVE_I2C_ADDR_MATCH |
                                                         UART_INTR_SLAVE_I2C_GENERAL))
        #else
            if (UART_CHECK_INTR_SLAVE_MASKED(UART_INTR_SLAVE_I2C_ADDR_MATCH))
        #endif /* (UART_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */
            {
                /* Clear externally clocked address match interrupt source when internally clocked is set */
                UART_ClearI2CExtClkInterruptSource(UART_INTR_I2C_EC_WAKE_UP);

                if (UART_I2C_CUSTOM_ADDRESS_HANDLER)
                {
                    if (NULL != UART_customAddressHandler)
                    {
                        /* Call custom address handler */
                        response = UART_customAddressHandler();
                    }
                    else
                    {
                        /* Read address from the RX FIFO. If there is no address underflow triggers but
                        * component does not use that source. */
                        (void) UART_RX_FIFO_RD_REG;
                        response = UART_I2C_ACK_ADDR;
                    }

                    /* Clears RX sources after address was received in the RX FIFO */
                    UART_ClearRxInterruptSource(UART_INTR_RX_ALL);
                }
                

            #if (UART_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
                if (response == UART_I2C_NAK_ADDR)
                {
                #if (!UART_CY_SCBIP_V0)
                    /* Disable write stop interrupt source as it triggers after address was NACKed. Ticket ID#156094 */
                    UART_DISABLE_INTR_SLAVE(UART_INTR_SLAVE_I2C_WRITE_STOP);
                #endif /* (!UART_CY_SCBIP_V0) */

                    /* Clear address match and stop history */
                    UART_ClearSlaveInterruptSource(UART_INTR_SLAVE_ALL);

                    /* ACK the address byte */
                    UART_I2C_SLAVE_GENERATE_NACK;
                }
                else
            #endif /* (UART_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */
                {
                    if(UART_CHECK_I2C_STATUS(UART_I2C_STATUS_S_READ))
                    /* TX direction: master reads from slave */
                    {
                        UART_SetTxInterruptMode(UART_INTR_TX_EMPTY);

                        /* Set temporary index to address buffer clear from API */
                        UART_slRdBufIndexTmp = UART_slRdBufIndex;

                        /* Start master reading */
                        UART_slStatus |= (uint8) UART_I2C_SSTAT_RD_BUSY;
                        UART_state     = UART_I2C_FSM_SL_RD;
                    }
                    else
                    /* RX direction: master writes into slave */
                    {
                        /* Calculate available buffer size */
                        diffCount = (UART_slWrBufSize - UART_slWrBufIndex);

                    #if (UART_CY_SCBIP_V0)
                        if(diffCount < UART_I2C_FIFO_SIZE)
                        /* Receive data: byte-by-byte */
                        {
                            UART_SetRxInterruptMode(UART_INTR_RX_NOT_EMPTY);
                        }
                        else
                        /* Receive data: into RX FIFO */
                        {
                            if(diffCount == UART_I2C_FIFO_SIZE)
                            {
                                /* NACK when RX FIFO become FULL */
                                UART_ENABLE_SLAVE_AUTO_DATA;
                            }
                            else
                            {
                                /* Stretch clock when RX FIFO becomes FULL */
                                UART_ENABLE_SLAVE_AUTO_DATA_ACK;
                                UART_SetRxInterruptMode(UART_INTR_RX_FULL);
                            }
                        }

                    #else
                        if(UART_CHECK_I2C_ACCEPT_ADDRESS)
                        {
                            /* Enable RX.NOT_EMPTY interrupt source to receive byte by byte.
                            * The byte by byte receive is always chosen for the case when an address is accepted
                            * in RX FIFO. Ticket ID#175559.
                            */
                            UART_SetRxInterruptMode(UART_INTR_RX_NOT_EMPTY);
                        }
                        else
                        {
                            if(diffCount < UART_I2C_FIFO_SIZE)
                            /* Receive data: byte-by-byte */
                            {
                                UART_SetRxInterruptMode(UART_INTR_RX_NOT_EMPTY);
                            }
                            else
                            /* Receive data: into RX FIFO */
                            {
                                if(diffCount == UART_I2C_FIFO_SIZE)
                                {
                                    /* NACK when RX FIFO become FULL */
                                    UART_ENABLE_SLAVE_AUTO_DATA;
                                }
                                else
                                {
                                    /* Stretch clock when RX FIFO becomes FULL */
                                    UART_ENABLE_SLAVE_AUTO_DATA_ACK;
                                    UART_SetRxInterruptMode(UART_INTR_RX_FULL);
                                }
                            }
                        }
                        
                    #endif /* (UART_CY_SCBIP_V0) */

                        /* Start master reading */
                        UART_slStatus |= (uint8) UART_I2C_SSTAT_WR_BUSY;
                        UART_state     = UART_I2C_FSM_SL_WR;
                    }

                    /* Clear address match and stop history */
                    UART_ClearSlaveInterruptSource(UART_INTR_SLAVE_ALL);

                #if (!UART_CY_SCBIP_V0)
                    /* Enable write stop interrupt source as it triggers after address was NACKed. Ticket ID#156094 */
                    UART_ENABLE_INTR_SLAVE(UART_INTR_SLAVE_I2C_WRITE_STOP);
                #endif /* (!UART_CY_SCBIP_V0) */

                    /* ACK the address byte */
                    UART_I2C_SLAVE_GENERATE_ACK;
                }
            }

            /* UART_INTR_RX_FULL:
            * Get data from the RX FIFO and decide whether to ACK or NACK the following bytes
            */
            if(UART_CHECK_INTR_RX_MASKED(UART_INTR_RX_FULL))
            {
                /* Calculate available buffer size to take into account that RX FIFO is FULL */
                diffCount =  UART_slWrBufSize -
                            (UART_slWrBufIndex + UART_I2C_FIFO_SIZE);

                if(diffCount > UART_I2C_FIFO_SIZE) /* Proceed transaction */
                {
                    diffCount   = UART_I2C_FIFO_SIZE;
                    endTransfer = 0u;  /* Continue active transfer */
                }
                else /* End when FIFO becomes FULL again */
                {
                    endTransfer = UART_I2C_CMPLT_ANY_TRANSFER;
                }

                for(; (0u != diffCount); diffCount--)
                {
                    /* Put data in component buffer */
                    UART_slWrBufPtr[UART_slWrBufIndex] = (uint8) UART_RX_FIFO_RD_REG;
                    UART_slWrBufIndex++;
                }

                if(0u != endTransfer) /* End transfer sending NACK */
                {
                    UART_ENABLE_SLAVE_AUTO_DATA_NACK;

                    /* INTR_RX_FULL triggers earlier than INTR_SLAVE_I2C_STOP:
                    * disable all RX interrupt sources.
                    */
                    UART_SetRxInterruptMode(UART_NO_INTR_SOURCES);
                }

                UART_ClearRxInterruptSource(UART_INTR_RX_FULL);
            }
            /* UART_INTR_RX_NOT_EMPTY:
            * The buffer size is less than 8: it requires processing in byte-by-byte mode.
            */
            else if(UART_CHECK_INTR_RX_MASKED(UART_INTR_RX_NOT_EMPTY))
            {
                diffCount = UART_RX_FIFO_RD_REG;

                if(UART_slWrBufIndex < UART_slWrBufSize)
                {
                    UART_I2C_SLAVE_GENERATE_ACK;

                    /* Put data into component buffer */
                    UART_slWrBufPtr[UART_slWrBufIndex] = (uint8) diffCount;
                    UART_slWrBufIndex++;
                }
                else /* Overflow: there is no space in write buffer */
                {
                    UART_I2C_SLAVE_GENERATE_NACK;

                    UART_slStatus |= (uint8) UART_I2C_SSTAT_WR_OVFL;
                }

                UART_ClearRxInterruptSource(UART_INTR_RX_NOT_EMPTY);
            }
            else
            {
                /* Does nothing */
            }


            /* UART_INTR_TX_EMPTY:
            * The master reads the slave: provide data to read or 0xFF in the case of the end of the buffer
            * The overflow condition must be captured, but not set until the end of transaction.
            * There is a possibility of a false overflow due to TX FIFO utilization.
            */
            if(UART_CHECK_INTR_TX_MASKED(UART_INTR_TX_EMPTY))
            {
                while(UART_I2C_FIFO_SIZE != UART_GET_TX_FIFO_ENTRIES)
                {
                    /* Temporary slRdBufIndexTmp is used because the master can NACK the byte and
                    * index roll-back is required in this case. The slRdBufIndex is updated at the end
                    * of the read transfer.
                    */
                    if(UART_slRdBufIndexTmp < UART_slRdBufSize)
                    /* Data from buffer */
                    {
                        UART_TX_FIFO_WR_REG = (uint32) UART_slRdBufPtr[UART_slRdBufIndexTmp];
                        UART_slRdBufIndexTmp++;
                    }
                    else
                    /* Probably Overflow */
                    {
                        UART_TX_FIFO_WR_REG = UART_I2C_SLAVE_OVFL_RETURN;

                        if(UART_slOverFlowCount <= UART_I2C_TX_OVERFLOW_COUNT)
                        {
                            /* Get counter in range of overflow. */
                            UART_slOverFlowCount++;
                        }
                    }
                }

                UART_ClearTxInterruptSource(UART_INTR_TX_EMPTY);
            }

        }  /* (UART_I2C_SLAVE) */
        
    }


    /* FSM EXIT:
    * Slave:  INTR_SLAVE_I2C_BUS_ERROR, INTR_SLAVE_I2C_ARB_LOST
    * Master: INTR_MASTER_I2C_BUS_ERROR, INTR_MASTER_I2C_ARB_LOST.
    */
    else
    {
        UART_CTRL_REG &= (uint32) ~UART_CTRL_ENABLED; /* Disable scb IP */

        UART_state = UART_I2C_FSM_IDLE;

        UART_DISABLE_SLAVE_AUTO_DATA;
        UART_DISABLE_MASTER_AUTO_DATA;

    #if(UART_CY_SCBIP_V0)
        UART_SetRxInterruptMode(UART_NO_INTR_SOURCES);
        UART_SetTxInterruptMode(UART_NO_INTR_SOURCES);

        /* Clear interrupt sources as they are not automatically cleared after SCB is disabled */
        UART_ClearTxInterruptSource(UART_INTR_RX_ALL);
        UART_ClearRxInterruptSource(UART_INTR_TX_ALL);
        UART_ClearSlaveInterruptSource(UART_INTR_SLAVE_ALL);
        UART_ClearMasterInterruptSource(UART_INTR_MASTER_ALL);
    #endif /* (UART_CY_SCBIP_V0) */

        UART_CTRL_REG |= (uint32) UART_CTRL_ENABLED;  /* Enable scb IP */
    }

#ifdef UART_I2C_ISR_EXIT_CALLBACK
    UART_I2C_ISR_ExitCallback();
#endif /* UART_I2C_ISR_EXIT_CALLBACK */

}


/* [] END OF FILE */
