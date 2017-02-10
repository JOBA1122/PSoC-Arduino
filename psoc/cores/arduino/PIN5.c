/*******************************************************************************
* File Name: PIN5.c  
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
#include "PIN5.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        PIN5_PC =   (PIN5_PC & \
                                (uint32)(~(uint32)(PIN5_DRIVE_MODE_IND_MASK << (PIN5_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (PIN5_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: PIN5_Write
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
void PIN5_Write(uint8 value) 
{
    uint8 drVal = (uint8)(PIN5_DR & (uint8)(~PIN5_MASK));
    drVal = (drVal | ((uint8)(value << PIN5_SHIFT) & PIN5_MASK));
    PIN5_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: PIN5_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  PIN5_DM_STRONG     Strong Drive 
*  PIN5_DM_OD_HI      Open Drain, Drives High 
*  PIN5_DM_OD_LO      Open Drain, Drives Low 
*  PIN5_DM_RES_UP     Resistive Pull Up 
*  PIN5_DM_RES_DWN    Resistive Pull Down 
*  PIN5_DM_RES_UPDWN  Resistive Pull Up/Down 
*  PIN5_DM_DIG_HIZ    High Impedance Digital 
*  PIN5_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void PIN5_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(PIN5__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: PIN5_Read
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
*  Macro PIN5_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PIN5_Read(void) 
{
    return (uint8)((PIN5_PS & PIN5_MASK) >> PIN5_SHIFT);
}


/*******************************************************************************
* Function Name: PIN5_ReadDataReg
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
uint8 PIN5_ReadDataReg(void) 
{
    return (uint8)((PIN5_DR & PIN5_MASK) >> PIN5_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PIN5_INTSTAT) 

    /*******************************************************************************
    * Function Name: PIN5_ClearInterrupt
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
    uint8 PIN5_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(PIN5_INTSTAT & PIN5_MASK);
		PIN5_INTSTAT = maskedStatus;
        return maskedStatus >> PIN5_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
