/*********************************************************************************************************
--------------File Info---------------------------------------------------------------------------------
 File name:           IRQ_RIT.c
 Last modified Date:  2014-09-25
 Last Version:        V1.00
 Descriptions:        functions to manage T0 and T1 interrupts
 Correlated files:    RIT.h
--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../GLCD/GLCD.h" 
#include "../button_EXINT/button.h" 
#include "../MyFunction/myfunc.h"
#include <string.h>
/******************************************************************************
 Function name:    RIT_IRQHandler

 Descriptions:    REPETITIVE INTERRUPT TIMER handler

 parameters:      None
 Returned value:    None

******************************************************************************/

extern int select;
extern int left;
extern int right;
extern int up;
extern int down;

extern int num;

extern int two_player_one_board;
extern int two_player_two_board;
extern int one_player_one_board;
extern int menu;

volatile int down_0 = 0;
volatile int down_1 = 0;
volatile int down_2 = 0;
	
 int select=0;
 int left=0;
 int right=0;
 int up=0;
 int down=0;

 int num=0;
extern void HANDLER(void);
extern void handler_RIT_NPC(void);
extern void sel(void);
extern void sel_NPC(void);
extern void move_left(void);
extern void move_right(void);
extern void move_up(void);
extern void move_down(void);


extern void handler_CAN(void);
extern void sel_CAN(void);
extern void move_left_CAN(void);
extern void move_right_CAN(void);
extern void move_up_CAN(void);
extern void move_down_CAN(void);

extern void move_left_NPC(void);
extern void move_right_NPC(void);
extern void move_up_NPC(void);
extern void move_down_NPC(void);
extern void selected_menu_down(void);
extern void selected_menu_up(void);

extern int num;
extern int menu_sel;

extern void start_game_NPC(void);
extern void start_game_two_player_one_board(void);
extern void start_game_two_player_two_board(void);
extern void start_menu_one_board(void);
extern void start_connection(void);

extern void pressedINT0(void);
extern void pressedKey1(void);
extern void pressedKey2(void);

void RIT_IRQHandler (void)
{          
		
	
	  /* button management */
		
		if(down_0!=0){  
			down_0 ++;  
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){

			switch(down_0){
			case 2:
						pressedINT0();		// INT0
			
				break;
			default:
				break;
		}
	}
	else {	/* button released */
		down_0=0;			
		NVIC_EnableIRQ(EINT0_IRQn);							 /* enable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
	}
	}
	if(down_1!=0){  
			down_1 ++;  
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){

			switch(down_1){
			case 2:
					pressedKey1();//key1
				break;
			default:			
				break;
		}
	}
	else {	/* button released */
		down_1=0;			
		NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 1 pin selection */
	}
	}
	if(down_2!=0){  
			down_2 ++;  
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){
			switch(down_2){
			case 2:
			pressedKey2();       //key2
				break;
			default:
				break;
		}
	}
	else {	/* button released */
		down_2=0;			
		NVIC_EnableIRQ(EINT2_IRQn); 							 /* enable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 2 pin selection */
	}
	}
	
	
	
	//joystick
	
	
	
	if(two_player_one_board==1){
	
			HANDLER();
	}
	
	else if(two_player_two_board==1){
	
			handler_CAN();
	}
	else if( one_player_one_board==1 ){
	
		handler_RIT_NPC();
	}
	
	
  if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){  
		
    /* Joytick Select pressed p1.25*/
    select++;
    switch(select){
      case 1:
				
			
			if(two_player_one_board==1){
				sel();
				
		   }
			else if(two_player_two_board==1){
				sel_CAN();
				
		   }
		  else if( one_player_one_board==1){
				sel_NPC();
			}
		
							
			menu_sel++; 
			
			if(menu_sel == 3){
			menu=0;
			if(num % 2 == 0){
				
				start_game_two_player_one_board();
				two_player_one_board=1;
			}
			else{
				start_game_NPC();
				one_player_one_board=1;
			}
		}
			
			if(menu_sel == 2){
			
			if(num % 2 == 0){
				start_menu_one_board();
			}
			else{
				menu=0;
				menu_sel=5;
				start_connection();
			}
		}
		
	
		
							
      break;
      default:
        break;
    }    
    
  }
  else{
       select=0;
  }
  
  
    if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){  
    /* Joytick Left pressed p1.27*/
  left++;
    switch(left){
      case 1:
				
			if(two_player_one_board==1){
					move_left();
			}
			if(two_player_two_board==1){
					move_left_CAN();
			}
			if( one_player_one_board==1){
			
					move_left_NPC();
			}
			
      break;      
      default:
        break;
    }    
    
    }
      else{
  left=0;
  }
      
    if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){  
    /* Joytick Right pressed p1.28*/
      right++;
      switch(right){
      case 1:
				
			if(two_player_one_board==1){
				move_right();
			}
			if(two_player_two_board==1){
				move_right_CAN();
			}
			if( one_player_one_board==1){
			
					move_right_NPC();
			}
       
      break;
      default:
        break;
    }      
    }  else{
    right=0;
    }
    
    
    if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){  
    /* Joytick Down pressed p1.26*/    
      down++;
      switch(down){
      case 1:
				if(two_player_one_board==1){
						move_down();
				}
				if(two_player_two_board==1){
						move_down_CAN();
				}
				
					if(menu==1){
							num++;
							selected_menu_down();
					}
					if( one_player_one_board==1){
			
					move_down_NPC();
			}
    
      break;
      default:
        break;
    }    
    
    }  else{
    down=0;
    }
      
    if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){  
    /* Joytick Up pressed p1.29*/
    up++;
      switch(up){
      case 1:
				if(two_player_one_board==1){
							move_up();
				}
				
						if(two_player_two_board==1){
							move_up_CAN();
				}
				
				
					if(menu==1){
								num++;
								selected_menu_up();
							}
					if( one_player_one_board==1){
			
					move_up_NPC();
			}
      break;
      default:
        break;
    }    
    
    }
    else{
    up=0;
    }
	

  LPC_RIT->RICTRL |= 0x1;  /* clear interrupt flag */
  
  return;
}



/******************************************************************************


**                            End Of File
******************************************************************************/


