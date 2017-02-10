/*******************************************************************************
* File Name: PIN7.h  
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

#if !defined(CY_PINS_PIN7_H) /* Pins PIN7_H */
#define CY_PINS_PIN7_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PIN7_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PIN7_Write(uint8 value) ;
void    PIN7_SetDriveMode(uint8 mode) ;
uint8   PIN7_ReadDataReg(void) ;
uint8   PIN7_Read(void) ;
uint8   PIN7_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PIN7_DRIVE_MODE_BITS        (3)
#define PIN7_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PIN7_DRIVE_MODE_BITS))

#define PIN7_DM_ALG_HIZ         (0x00u)
#define PIN7_DM_DIG_HIZ         (0x01u)
#define PIN7_DM_RES_UP          (0x02u)
#define PIN7_DM_RES_DWN         (0x03u)
#define PIN7_DM_OD_LO           (0x04u)
#define PIN7_DM_OD_HI           (0x05u)
#define PIN7_DM_STRONG          (0x06u)
#define PIN7_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define PIN7_MASK               PIN7__MASK
#define PIN7_SHIFT              PIN7__SHIFT
#define PIN7_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PIN7_PS                     (* (reg32 *) PIN7__PS)
/* Port Configuration */
#define PIN7_PC                     (* (reg32 *) PIN7__PC)
/* Data Register */
#define PIN7_DR                     (* (reg32 *) PIN7__DR)
/* Input Buffer Disable Override */
#define PIN7_INP_DIS                (* (reg32 *) PIN7__PC2)


#if defined(PIN7__INTSTAT)  /* Interrupt Registers */

    #define PIN7_INTSTAT                (* (reg32 *) PIN7__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define PIN7_DRIVE_MODE_SHIFT       (0x00u)
#define PIN7_DRIVE_MODE_MASK        (0x07u << PIN7_DRIVE_MODE_SHIFT)


#endif /* End Pins PIN7_H */


/* [] END OF FILE */
