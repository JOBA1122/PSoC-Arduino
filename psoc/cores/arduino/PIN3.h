/*******************************************************************************
* File Name: PIN3.h  
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

#if !defined(CY_PINS_PIN3_H) /* Pins PIN3_H */
#define CY_PINS_PIN3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PIN3_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PIN3_Write(uint8 value) ;
void    PIN3_SetDriveMode(uint8 mode) ;
uint8   PIN3_ReadDataReg(void) ;
uint8   PIN3_Read(void) ;
uint8   PIN3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PIN3_DRIVE_MODE_BITS        (3)
#define PIN3_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PIN3_DRIVE_MODE_BITS))

#define PIN3_DM_ALG_HIZ         (0x00u)
#define PIN3_DM_DIG_HIZ         (0x01u)
#define PIN3_DM_RES_UP          (0x02u)
#define PIN3_DM_RES_DWN         (0x03u)
#define PIN3_DM_OD_LO           (0x04u)
#define PIN3_DM_OD_HI           (0x05u)
#define PIN3_DM_STRONG          (0x06u)
#define PIN3_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define PIN3_MASK               PIN3__MASK
#define PIN3_SHIFT              PIN3__SHIFT
#define PIN3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PIN3_PS                     (* (reg32 *) PIN3__PS)
/* Port Configuration */
#define PIN3_PC                     (* (reg32 *) PIN3__PC)
/* Data Register */
#define PIN3_DR                     (* (reg32 *) PIN3__DR)
/* Input Buffer Disable Override */
#define PIN3_INP_DIS                (* (reg32 *) PIN3__PC2)


#if defined(PIN3__INTSTAT)  /* Interrupt Registers */

    #define PIN3_INTSTAT                (* (reg32 *) PIN3__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define PIN3_DRIVE_MODE_SHIFT       (0x00u)
#define PIN3_DRIVE_MODE_MASK        (0x07u << PIN3_DRIVE_MODE_SHIFT)


#endif /* End Pins PIN3_H */


/* [] END OF FILE */
