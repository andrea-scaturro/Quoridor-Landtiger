/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../RIT/RIT.h"
#include <stdio.h>

#include "../TouchPanel/TouchPanel.h"
/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern int timeout;
extern int time;
extern int two_player_one_board;
extern int two_player_two_board;
extern int one_player_one_board;
extern int loading;
extern int timeout_connection;
extern int connection;
extern int menu;
extern int p1Y;
extern int p2Y;
extern void start_game_two_player_two_board(void);

int timeout=0;
int time =20;
int loading=0;
int loading_time=8;  // 8 sec per la connessione
int timeout_connection=0;
int num_point_loading=0;
int count_menu=0;

void TIMER0_IRQHandler (void)
{
	
	if(menu == 0 && loading ==0 && (two_player_one_board==0 && two_player_two_board==0 && one_player_one_board==0) && (p1Y != 12 ) && (p2Y != 210) ){
	
		count_menu++;
		
			GUI_Text(50, 270, (uint8_t *) "PRESS INT0 TO PLAY", Yellow, Black);
		
		if(count_menu%2 ==0){
			
				GUI_Text(50, 270, (uint8_t *) "PRESS INT0 TO PLAY", Black, Black);
			
		}
	
	}
	
	
	if(loading==1   && (two_player_one_board==0 && two_player_two_board==0 && one_player_one_board==0)){
	static int count = 0;
	count++;
		
		
		num_point_loading++;
			
			if(num_point_loading==4){
				GUI_Text(160, 235, (uint8_t *) "   ", Black, Black);
				num_point_loading=0;
			}
			
			if(num_point_loading ==1){
				GUI_Text(75, 235, (uint8_t *) "CONNECTING.", Yellow, Black);
			}
				if(num_point_loading ==2){
				GUI_Text(75, 235, (uint8_t *) "CONNECTING..", Yellow, Black);
			}
					if(num_point_loading ==3){
				GUI_Text(75, 235, (uint8_t *) "CONNECTING...", Yellow, Black);
			}
					
		
		if(count%2 == 0){
			loading_time --;
			
		}
		if (loading_time ==0){
				timeout_connection=1;
		}
		
		if(timeout_connection==1){
		
					disable_timer(0);
					GUI_Text(75, 235, (uint8_t *) "CONNECTING...", Black, Black);
					GUI_Text(60, 220, (uint8_t *) "PLAYER NOT FOUND", Yellow, Black);
					GUI_Text(60, 250, (uint8_t *) "  press Reset", Yellow, Black);
						loading=0;
						
			}
		
	
			
	}
	
	if(two_player_one_board==1 || two_player_two_board==1 || one_player_one_board==1){
	static int clear = 0;
	char time_in_char[5] = "";	
	
	 
	extern int turn;
	
	clear++;
	if(clear%2 == 0){
		
			time --;
			sprintf(time_in_char,"%4d s",time);
			GUI_Text(88, 290,(uint8_t *)"       ", White, Black);
			GUI_Text(92, 290,(uint8_t *)time_in_char, White, Black);			
					
		}
						
		if(time ==0){
			time =20;
			clear=0;	
			timeout=1;
			GUI_Text(88, 290,(uint8_t *)"timeout", White, Red);
			time = 20;	
			if(turn == 1){
				turn=2;
			}
			else{ turn =1; }
		
				
				}
			}
  LPC_TIM0->IR = 1;			/* clear interrupt flag */

			
 return;

}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
