/*******************************************************************************
* File Name: PIN4.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "PIN4.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        PIN4_PC =   (PIN4_PC & \
                                (uint32)(~(uint32)(PIN4_DRIVE_MODE_IND_MASK << (PIN4_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (PIN4_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: PIN4_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void PIN4_Write(uint8 value) 
{
    uint8 drVal = (uint8)(PIN4_DR & (uint8)(~PIN4_MASK));
    drVal = (drVal | ((uint8)(value << PIN4_SHIFT) & PIN4_MASK));
    PIN4_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: PIN4_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  PIN4_DM_STRONG     Strong Drive 
*  PIN4_DM_OD_HI      Open Drain, Drives High 
*  PIN4_DM_OD_LO      Open Drain, Drives Low 
*  PIN4_DM_RES_UP     Resistive Pull Up 
*  PIN4_DM_RES_DWN    Resistive Pull Down 
*  PIN4_DM_RES_UPDWN  Resistive Pull Up/Down 
*  PIN4_DM_DIG_HIZ    High Impedance Digital 
*  PIN4_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void PIN4_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(PIN4__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: PIN4_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro PIN4_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PIN4_Read(void) 
{
    return (uint8)((PIN4_PS & PIN4_MASK) >> PIN4_SHIFT);
}


/*******************************************************************************
* Function Name: PIN4_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 PIN4_ReadDataReg(void) 
{
    return (uint8)((PIN4_DR & PIN4_MASK) >> PIN4_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PIN4_INTSTAT) 

    /*******************************************************************************
    * Function Name: PIN4_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 PIN4_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(PIN4_INTSTAT & PIN4_MASK);
		PIN4_INTSTAT = maskedStatus;
        return maskedStatus >> PIN4_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
