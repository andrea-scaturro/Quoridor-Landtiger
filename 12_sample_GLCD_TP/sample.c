/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "button_EXINT/button.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"
#include "MyFunction/myfunc.h"
#include "CAN/CAN.h"
//#include "CAN/CAN.h"

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


extern void schermata_iniziale(void);

int main(void)
{


  SystemInit();  												/* System Initialization (i.e., PLL)  */
  LCD_Initialization();
  BUTTON_init();
	TP_Init();
	CAN_Init();
	
	//TouchPanel_Calibrate();
	LCD_Clear(Black);
	schermata_iniziale();
		
	init_timer(0, 0xBEBC20 ); 						/* 500ms * 25MHz = 1.25*10^7 = 0xBEBC20 */

	//init_timer(0, 0x1312D0 ); 						/* 50ms * 25MHz = 1.25*10^6 = 0x1312D0 per debug veloce */ 
	
//	init_timer(1, 0x98968 ); 						/* 25ms * 25MHz = 1/2*1.25*10^6 = 0x1312D0 per debug veloce */ 
	
	//enable_timer(1);
	enable_timer(0);
	init_RIT(0x004C4B40);									/* RIT Initialization 50 msec       	*/
	enable_RIT();
	joystick_init();											/* Joystick Initialization           
	
	LPC_SC->PCON |= 0x1;									*/
	LPC_SC->PCON &= ~(0x2);						
	
  while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
