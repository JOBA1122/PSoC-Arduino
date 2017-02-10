/*******************************************************************************
* File Name: PIN6.c  
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
#include "PIN6.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        PIN6_PC =   (PIN6_PC & \
                                (uint32)(~(uint32)(PIN6_DRIVE_MODE_IND_MASK << (PIN6_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (PIN6_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: PIN6_Write
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
void PIN6_Write(uint8 value) 
{
    uint8 drVal = (uint8)(PIN6_DR & (uint8)(~PIN6_MASK));
    drVal = (drVal | ((uint8)(value << PIN6_SHIFT) & PIN6_MASK));
    PIN6_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: PIN6_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  PIN6_DM_STRONG     Strong Drive 
*  PIN6_DM_OD_HI      Open Drain, Drives High 
*  PIN6_DM_OD_LO      Open Drain, Drives Low 
*  PIN6_DM_RES_UP     Resistive Pull Up 
*  PIN6_DM_RES_DWN    Resistive Pull Down 
*  PIN6_DM_RES_UPDWN  Resistive Pull Up/Down 
*  PIN6_DM_DIG_HIZ    High Impedance Digital 
*  PIN6_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void PIN6_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(PIN6__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: PIN6_Read
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
*  Macro PIN6_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PIN6_Read(void) 
{
    return (uint8)((PIN6_PS & PIN6_MASK) >> PIN6_SHIFT);
}


/*******************************************************************************
* Function Name: PIN6_ReadDataReg
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
uint8 PIN6_ReadDataReg(void) 
{
    return (uint8)((PIN6_DR & PIN6_MASK) >> PIN6_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PIN6_INTSTAT) 

    /*******************************************************************************
    * Function Name: PIN6_ClearInterrupt
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
    uint8 PIN6_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(PIN6_INTSTAT & PIN6_MASK);
		PIN6_INTSTAT = maskedStatus;
        return maskedStatus >> PIN6_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
