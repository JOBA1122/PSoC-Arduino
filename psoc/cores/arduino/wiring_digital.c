/*
  wiring_digital.c - digital input and output functions
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  Modified 28 September 2010 by Mark Sproul

  $Id: wiring.c 248 2007-02-03 15:36:30Z mellis $
*/

#define ARDUINO_MAIN
//#include "wiring_private.h"
#include "wiring_digital.h"
//#include "pins_arduino.h"



uint32_t flag0=0,flag1=0,flag2=0,flag3=0,flag4=0,flag5=0,flag6=0;
uint32_t flag7=0;

void pinMode(uint32_t pin, uint32_t mode)
{
 
    switch(pin)
    {
     case 0:
     {   
      switch(mode)
      {
       case 1://ENTRADA
       {
        Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
        flag0=1;
         break;
       }
                    
       case 2://SALIDA
       {
        Control_PIN1_Write((Control_PIN1_Read() OR  (1<<pin)));
        flag0=0;
         break;
       }
                    
       case 3://ENTRADA CON PULLUP
       {
        Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
        PIN0_SetDriveMode(PIN0_DM_RES_UP);
        break;    
       }
                    
       case 4://ENTRADA CON PULDOWN
       {
        Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
        PIN0_SetDriveMode(PIN0_DM_RES_DWN);
        break;    
       }
      }
            
     break;    
     }
        
     case 1:
     {   
      switch(mode)
       {
       case 1://ENTRADA
       {
         Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
         flag1=1;
         break;
       }
                    
       case 2://SALIDA
       {
         Control_PIN1_Write((Control_PIN1_Read() OR  (1<<pin)));
         flag1=0;
         break;
       }
                    
       case 3://ENTRADA CON PULLUP
       {
         Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
         PIN1_SetDriveMode(PIN1_DM_RES_UP);
         break;    
       }
                    
       case 4://ENTRADA CON PULDOWN
       {
         Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
         PIN1_SetDriveMode(PIN1_DM_RES_DWN);
         break;    
       }
      }
            
      break;    
     }
        
     case 2:
     {   
      switch(mode)
      {
       case 1://ENTRADA
       {
         Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
         flag2=1;
         break;
        }
                    
        case 2://SALIDA
        {
         Control_PIN1_Write((Control_PIN1_Read() OR  (1<<pin)));
         flag2=0;
         break;
        }
                    
        case 3://ENTRADA CON PULLUP
        {
         Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
         PIN2_SetDriveMode(PIN2_DM_RES_UP);
         break;    
         }
                    
        case 4://ENTRADA CON PULDOWN
        {
         Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
         PIN2_SetDriveMode(PIN2_DM_RES_DWN);
         break;    
         }
       }
            
        break;    
     }
        
     case 3:
     {   
      switch(mode)
      {
       case 1://ENTRADA
       {
         Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
         flag3=1;
         break;
       }
                    
       case 2://SALIDA
       {
         Control_PIN1_Write((Control_PIN1_Read() OR  (1<<pin)));
         flag3=0;
         break;
       }
                    
       case 3://ENTRADA CON PULLUP
       {
         Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
         PIN3_SetDriveMode(PIN3_DM_RES_UP);
         break;    
        }
                    
       case 4://ENTRADA CON PULDOWN
       {
         Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
         PIN3_SetDriveMode(PIN3_DM_RES_DWN);
         break;    
        }
       }
            
      break;    
     }
        
     case 4:
     {   
      switch(mode)
      {
       case 1://ENTRADA
       {
        Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
        flag4=1;
        break;
       }
                    
       case 2://SALIDA
       {
        Control_PIN1_Write((Control_PIN1_Read() OR  (1<<pin)));
        flag4=0;
        break;
        }
                    
       case 3://ENTRADA CON PULLUP
       {
        Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
        PIN4_SetDriveMode(PIN4_DM_RES_UP);
        break;    
       }
                    
       case 4://ENTRADA CON PULDOWN
       {
         Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
         PIN4_SetDriveMode(PIN4_DM_RES_DWN);
         break;    
        }
       }
            
      break;    
     }
        
     case 5:
     {   
      switch(mode)
      {
       case 1://ENTRADA
       {
        Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
        flag5=1;
        break;
        }
                    
       case 2://SALIDA
       {
        Control_PIN1_Write((Control_PIN1_Read() OR  (1<<pin)));
        flag5=0;
        break;
        }
                    
       case 3://ENTRADA CON PULLUP
       {
        Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
        PIN5_SetDriveMode(PIN5_DM_RES_UP);
        break;    
       }
                    
       case 4://ENTRADA CON PULDOWN
       {
        Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
        PIN5_SetDriveMode(PIN5_DM_RES_DWN);
        break;    
        }
       }
            
      break;    
     }
        
     case 6:
     {   
      switch(mode)
      {
       case 1://ENTRADA
       {
        Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
        flag6=1;
        break;
       }
                    
       case 2://SALIDA
       {
        Control_PIN1_Write((Control_PIN1_Read() OR  (1<<pin)));
        flag6=0;
        break;
       }
                    
       case 3://ENTRADA CON PULLUP
       {
        Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
        PIN6_SetDriveMode(PIN6_DM_RES_UP);
        break;    
       }
                    
       case 4://ENTRADA CON PULDOWN
       {
        Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
        PIN6_SetDriveMode(PIN6_DM_RES_DWN);
        break;    
        }
       }
            
      break;    
     }
        
     case 7:
     {   
      switch(mode)
      {
       case 1://ENTRADA
       {
         Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
         flag7=1;
         break;
       }
                    
       case 2://SALIDA
       {                       
         Control_PIN1_Write((Control_PIN1_Read() OR  (1<<pin)));
         flag7=0;
         break;
        }
        case 3://ENTRADA CON PULLUP
       {
         Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
         PIN7_SetDriveMode(PIN0_DM_RES_UP);
         break;    
        }
                    
        case 4://ENTRADA CON PULDOWN
        {
         Control_PIN1_Write((Control_PIN1_Read() AND  ~(1<<pin)));
         PIN7_SetDriveMode(PIN0_DM_RES_DWN);
         break;    
        }  
       }
            
      break;    
     }
        
	}
 }
 


// Forcing this inline keeps the callers from having to push their own stuff
// on the stack. It is a good performance win and only takes 1 more byte per
// user than calling. (It will take more bytes on the 168.)
//
// But shouldn't this be moved into pinMode? Seems silly to check and do on
// each digitalread or write.
//
// Mark Sproul:
// - Removed inline. Save 170 bytes on atmega1280
// - changed to a switch statment; added 32 bytes but much easier to read and maintain.
// - Added more #ifdefs, now compiles for atmega645
//
//static inline void turnOffPWM(uint8_t timer) __attribute__ ((always_inline));
//static inline void turnOffPWM(uint8_t timer)
// static void turnOffPWM(uint8_t timer)
// {
	// switch (timer)
	// {
		// #if defined(TCCR1A) && defined(COM1A1)
		// case TIMER1A:   cbi(TCCR1A, COM1A1);    break;
		// #endif
		// #if defined(TCCR1A) && defined(COM1B1)
		// case TIMER1B:   cbi(TCCR1A, COM1B1);    break;
		// #endif
		// #if defined(TCCR1A) && defined(COM1C1)
		// case TIMER1C:   cbi(TCCR1A, COM1C1);    break;
		// #endif
		
		// #if defined(TCCR2) && defined(COM21)
		// case  TIMER2:   cbi(TCCR2, COM21);      break;
		// #endif
		
		// #if defined(TCCR0A) && defined(COM0A1)
		// case  TIMER0A:  cbi(TCCR0A, COM0A1);    break;
		// #endif
		
		// #if defined(TIMER0B) && defined(COM0B1)
		// case  TIMER0B:  cbi(TCCR0A, COM0B1);    break;
		// #endif
		// #if defined(TCCR2A) && defined(COM2A1)
		// case  TIMER2A:  cbi(TCCR2A, COM2A1);    break;
		// #endif
		// #if defined(TCCR2A) && defined(COM2B1)
		// case  TIMER2B:  cbi(TCCR2A, COM2B1);    break;
		// #endif
		
		// #if defined(TCCR3A) && defined(COM3A1)
		// case  TIMER3A:  cbi(TCCR3A, COM3A1);    break;
		// #endif
		// #if defined(TCCR3A) && defined(COM3B1)
		// case  TIMER3B:  cbi(TCCR3A, COM3B1);    break;
		// #endif
		// #if defined(TCCR3A) && defined(COM3C1)
		// case  TIMER3C:  cbi(TCCR3A, COM3C1);    break;
		// #endif

		// #if defined(TCCR4A) && defined(COM4A1)
		// case  TIMER4A:  cbi(TCCR4A, COM4A1);    break;
		// #endif					
		// #if defined(TCCR4A) && defined(COM4B1)
		// case  TIMER4B:  cbi(TCCR4A, COM4B1);    break;
		// #endif
		// #if defined(TCCR4A) && defined(COM4C1)
		// case  TIMER4C:  cbi(TCCR4A, COM4C1);    break;
		// #endif			
		// #if defined(TCCR4C) && defined(COM4D1)
		// case TIMER4D:	cbi(TCCR4C, COM4D1);	break;
		// #endif			
			
		// #if defined(TCCR5A)
		// case  TIMER5A:  cbi(TCCR5A, COM5A1);    break;
		// case  TIMER5B:  cbi(TCCR5A, COM5B1);    break;
		// case  TIMER5C:  cbi(TCCR5A, COM5C1);    break;
		// #endif
	// }
// }

void digitalWrite(uint32_t pin, uint32_t value)
{
   switch(pin)
    {
        case 0:
        {   
            if ((flag0==1) && (value==1))//enable pullup
            PIN0_SetDriveMode(PIN0_DM_RES_UP);
            
            else if((flag0==1) && (value==0))//disable pullup
            PIN0_SetDriveMode(PIN0_DM_DIG_HIZ);
            
            else
            PIN0_Write(value);
            break;
        }
        
        case 1:
        {   
            if ((flag1==1) && (value==1))//enable pullup
            PIN1_SetDriveMode(PIN1_DM_RES_UP);
            
            else if((flag1==1) && (value==0))//disable pullup
            PIN1_SetDriveMode(PIN1_DM_DIG_HIZ);
            
            else
            PIN1_Write(value);
            break;
        }
        
        case 2:
        {   
            if ((flag2==1) && (value==1))//enable pullup
            PIN2_SetDriveMode(PIN2_DM_RES_UP);
            
            else if((flag2==1) && (value==0))//disable pullup
            PIN2_SetDriveMode(PIN2_DM_DIG_HIZ);
            
            else
            PIN2_Write(value);
            break;
        }
        
        case 3:
        {   
            if ((flag3==1) && (value==1))//enable pullup
            PIN3_SetDriveMode(PIN3_DM_RES_UP);
            
            else if((flag3==1) && (value==0))//disable pullup
            PIN3_SetDriveMode(PIN3_DM_DIG_HIZ);
            
            else
            PIN3_Write(value);
            break;
        }
        
        case 4:
        {   
            if ((flag4==1) && (value==1))//enable pullup
            PIN4_SetDriveMode(PIN4_DM_RES_UP);
            
            else if((flag4==1) && (value==0))//disable pullup
            PIN4_SetDriveMode(PIN4_DM_DIG_HIZ);
            
            else
            PIN4_Write(value);
            break;
        }
        
        case 5:
        {   
            if ((flag5==1) && (value==1))//enable pullup
            PIN5_SetDriveMode(PIN5_DM_RES_UP);
            
            else if((flag2==1) && (value==0))//disable pullup
            PIN5_SetDriveMode(PIN5_DM_DIG_HIZ);
            
            else
            PIN5_Write(value);
            break;
        }
        
        case 6:
        {   
            if ((flag6==1) && (value==1))//enable pullup
            PIN6_SetDriveMode(PIN6_DM_RES_UP);
            
            else if((flag6==1) && (value==0))//disable pullup
            PIN6_SetDriveMode(PIN6_DM_DIG_HIZ);
            
            else
            PIN6_Write(value);
            break;
        }
        
        case 7:
        {   
            if ((flag7==1) && (value==1))//enable pullup
            PIN7_SetDriveMode(PIN0_DM_RES_UP);
            
            else if((flag7==1) && (value==0))//disable pullup
            PIN7_SetDriveMode(PIN0_DM_DIG_HIZ);
            
            else
            PIN7_Write(value);
            break;
        }

            
    }
}

int digitalRead(uint32_t pin)
{  int value=0;
    switch (pin)
    {
        case 0:
        {
            value=PIN0_Read();
            break;
        }
        
        case 1:
        {
            value=PIN1_Read();
            break;
        }
     
        case 2:
        {
            value=PIN2_Read();
            break;
        }
        
        case 3:
        {
            value=PIN3_Read();
            break;
        }
        
        case 4:
        {
            value=PIN4_Read();
            break;
        }
     
        case 5:
        {
            value=PIN5_Read();
            break;
        }
             
        case 6:
        {
            value=PIN6_Read();
            break;
        }
        
        case 7:
        {
            value=PIN7_Read();
            break;
        }
        
             
        
        
    }
    return value;
}
