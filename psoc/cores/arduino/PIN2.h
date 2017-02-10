/*******************************************************************************
* File Name: PIN2.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PIN2_H) /* Pins PIN2_H */
#define CY_PINS_PIN2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PIN2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PIN2_Write(uint8 value) ;
void    PIN2_SetDriveMode(uint8 mode) ;
uint8   PIN2_ReadDataReg(void) ;
uint8   PIN2_Read(void) ;
uint8   PIN2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PIN2_DRIVE_MODE_BITS        (3)
#define PIN2_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PIN2_DRIVE_MODE_BITS))

#define PIN2_DM_ALG_HIZ         (0x00u)
#define PIN2_DM_DIG_HIZ         (0x01u)
#define PIN2_DM_RES_UP          (0x02u)
#define PIN2_DM_RES_DWN         (0x03u)
#define PIN2_DM_OD_LO           (0x04u)
#define PIN2_DM_OD_HI           (0x05u)
#define PIN2_DM_STRONG          (0x06u)
#define PIN2_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define PIN2_MASK               PIN2__MASK
#define PIN2_SHIFT              PIN2__SHIFT
#define PIN2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PIN2_PS                     (* (reg32 *) PIN2__PS)
/* Port Configuration */
#define PIN2_PC                     (* (reg32 *) PIN2__PC)
/* Data Register */
#define PIN2_DR                     (* (reg32 *) PIN2__DR)
/* Input Buffer Disable Override */
#define PIN2_INP_DIS                (* (reg32 *) PIN2__PC2)


#if defined(PIN2__INTSTAT)  /* Interrupt Registers */

    #define PIN2_INTSTAT                (* (reg32 *) PIN2__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define PIN2_DRIVE_MODE_SHIFT       (0x00u)
#define PIN2_DRIVE_MODE_MASK        (0x07u << PIN2_DRIVE_MODE_SHIFT)


#endif /* End Pins PIN2_H */


/* [] END OF FILE */
