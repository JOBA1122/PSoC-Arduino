/*******************************************************************************
* File Name: PIN4.h  
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

#if !defined(CY_PINS_PIN4_H) /* Pins PIN4_H */
#define CY_PINS_PIN4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PIN4_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PIN4_Write(uint8 value) ;
void    PIN4_SetDriveMode(uint8 mode) ;
uint8   PIN4_ReadDataReg(void) ;
uint8   PIN4_Read(void) ;
uint8   PIN4_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PIN4_DRIVE_MODE_BITS        (3)
#define PIN4_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PIN4_DRIVE_MODE_BITS))

#define PIN4_DM_ALG_HIZ         (0x00u)
#define PIN4_DM_DIG_HIZ         (0x01u)
#define PIN4_DM_RES_UP          (0x02u)
#define PIN4_DM_RES_DWN         (0x03u)
#define PIN4_DM_OD_LO           (0x04u)
#define PIN4_DM_OD_HI           (0x05u)
#define PIN4_DM_STRONG          (0x06u)
#define PIN4_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define PIN4_MASK               PIN4__MASK
#define PIN4_SHIFT              PIN4__SHIFT
#define PIN4_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PIN4_PS                     (* (reg32 *) PIN4__PS)
/* Port Configuration */
#define PIN4_PC                     (* (reg32 *) PIN4__PC)
/* Data Register */
#define PIN4_DR                     (* (reg32 *) PIN4__DR)
/* Input Buffer Disable Override */
#define PIN4_INP_DIS                (* (reg32 *) PIN4__PC2)


#if defined(PIN4__INTSTAT)  /* Interrupt Registers */

    #define PIN4_INTSTAT                (* (reg32 *) PIN4__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define PIN4_DRIVE_MODE_SHIFT       (0x00u)
#define PIN4_DRIVE_MODE_MASK        (0x07u << PIN4_DRIVE_MODE_SHIFT)


#endif /* End Pins PIN4_H */


/* [] END OF FILE */
