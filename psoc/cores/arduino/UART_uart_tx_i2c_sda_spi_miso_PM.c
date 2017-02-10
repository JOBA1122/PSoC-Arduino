/*******************************************************************************
* File Name: UART_uart_tx_i2c_sda_spi_miso.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "UART_uart_tx_i2c_sda_spi_miso.h"

static UART_uart_tx_i2c_sda_spi_miso_BACKUP_STRUCT  UART_uart_tx_i2c_sda_spi_miso_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: UART_uart_tx_i2c_sda_spi_miso_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet UART_uart_tx_i2c_sda_spi_miso_SUT.c usage_UART_uart_tx_i2c_sda_spi_miso_Sleep_Wakeup
*******************************************************************************/
void UART_uart_tx_i2c_sda_spi_miso_Sleep(void)
{
    #if defined(UART_uart_tx_i2c_sda_spi_miso__PC)
        UART_uart_tx_i2c_sda_spi_miso_backup.pcState = UART_uart_tx_i2c_sda_spi_miso_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            UART_uart_tx_i2c_sda_spi_miso_backup.usbState = UART_uart_tx_i2c_sda_spi_miso_CR1_REG;
            UART_uart_tx_i2c_sda_spi_miso_USB_POWER_REG |= UART_uart_tx_i2c_sda_spi_miso_USBIO_ENTER_SLEEP;
            UART_uart_tx_i2c_sda_spi_miso_CR1_REG &= UART_uart_tx_i2c_sda_spi_miso_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(UART_uart_tx_i2c_sda_spi_miso__SIO)
        UART_uart_tx_i2c_sda_spi_miso_backup.sioState = UART_uart_tx_i2c_sda_spi_miso_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        UART_uart_tx_i2c_sda_spi_miso_SIO_REG &= (uint32)(~UART_uart_tx_i2c_sda_spi_miso_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: UART_uart_tx_i2c_sda_spi_miso_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to UART_uart_tx_i2c_sda_spi_miso_Sleep() for an example usage.
*******************************************************************************/
void UART_uart_tx_i2c_sda_spi_miso_Wakeup(void)
{
    #if defined(UART_uart_tx_i2c_sda_spi_miso__PC)
        UART_uart_tx_i2c_sda_spi_miso_PC = UART_uart_tx_i2c_sda_spi_miso_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            UART_uart_tx_i2c_sda_spi_miso_USB_POWER_REG &= UART_uart_tx_i2c_sda_spi_miso_USBIO_EXIT_SLEEP_PH1;
            UART_uart_tx_i2c_sda_spi_miso_CR1_REG = UART_uart_tx_i2c_sda_spi_miso_backup.usbState;
            UART_uart_tx_i2c_sda_spi_miso_USB_POWER_REG &= UART_uart_tx_i2c_sda_spi_miso_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(UART_uart_tx_i2c_sda_spi_miso__SIO)
        UART_uart_tx_i2c_sda_spi_miso_SIO_REG = UART_uart_tx_i2c_sda_spi_miso_backup.sioState;
    #endif
}


/* [] END OF FILE */
