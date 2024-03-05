#include <string.h>
#include <stdio.h>
#include "lpc17xx.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../RIT/RIT.h"
#include "../timer/timer.h"
#include "myfunc.h"


 struct Move{

	uint32_t playerId:8;
	uint32_t playerMove:4;
	uint32_t vertical:4;
	uint32_t x:8;
	uint32_t y:8;

};

// array in cui verranno salvate le mosse dei due player
extern struct Move moves[100];       
extern int count_moves;



 struct Wall {
    uint16_t wallx;
    uint16_t wally;
		uint16_t direction;
};

extern struct Wall wall;


extern uint16_t length;

extern int two_player_one_board;
extern int two_player_two_board;
extern int one_player_one_board;

extern int menu_sel;
extern int menu;
extern int num;

extern int turn;

extern int board[7][7];
extern int wallO_board[7][7]; 
extern int wallV_board[7][7]; 

extern int key1;
extern int timeout;
extern int time;

extern	int startX ;
extern  int startY ;
extern  int squareSize;
extern  int spacing;
		
extern  int rows;
extern  int cols;


extern uint16_t p1X ;
extern uint16_t p1Y ;
		
extern	uint16_t p2X ;  
extern	uint16_t p2Y;   
		
extern	uint16_t check_p1X ;
extern	uint16_t check_p1Y ;
		
extern	uint16_t check_p2X ;  
extern	uint16_t check_p2Y;   
		
		
extern int right;
extern int left;
extern int up;
extern int down;

		
extern	uint16_t p1W;
extern	uint16_t p2W;

extern int offset;
extern int offsetWall;

extern int visited[7][7];
	
int c=0;
	
struct Wall wall;



extern void CleanSquare(int x, int y, int width, int height, int color);
extern void DrawSquare(int x, int y, int size, int color);
extern void DrawRectangle(int x, int y, int width, int height, int color);
extern void DrawMatrix(int startX, int startY, int squareSize, int spacing, int rows, int cols, int color);
extern void DrawWall(struct Wall wall ,uint16_t color  );
extern void quoridor(void);
extern void schermata_iniziale(void);
extern void start_menu(void);
extern void start_menu_one_board(void);
extern void selected_menu_up(void);
extern void selected_menu_down(void);
extern int hasPath(int path_x, int path_y);
extern int hasPath_2(int path_x, int path_y); 
extern void pressedINT0(void);
extern void pressedKey1(void);
extern void pressedKey2(void);




void start_game_NPC(){


		int i=0;
		int j=0;

	// posizioni player
		uint16_t p1X = 111;
		uint16_t p1Y = 210;
		
		uint16_t p2X = 111;  //4 in +
		uint16_t p2Y = 12;   // 3 in +         

	// inizializzo
		for( i=0; i<7; i++){
				for( j=0;j<7; j++){		
					board[i][j]=0;
				}
		}
		
		// setta lo sfondo	
		LCD_Clear(Black);
		
    // Disegna la matrice
    DrawMatrix(startX, startY, squareSize, spacing, rows, cols, Blue);
			
		DrawRectangle(5,260,70,55 ,Blue);
		DrawRectangle(85,260,70,55, Blue);
		DrawRectangle(165,260,70,55, Blue);
		// limite 210
	
	GUI_Text(15, 265, (uint8_t *) "P1 wall", White, Black);
	GUI_Text(175, 265, (uint8_t *) "P2 wall", White, Black);
	
	CleanSquare(p1X,p1Y,20,20, Red);
	CleanSquare(p2X,p2Y,20, 20,White);
	
	
	enable_timer(0);
}







 //------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//-------------------------------- 1 PLAYER 1 BOARD FUNCTION ----------------------------------------

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//-------------------------------MOVE WALL FUNCTION------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



void move_upWall_NPC(){
	
				if(wall.direction ==0){
					if(wall.wally -offsetWall <=210 && wall.wally-offsetWall >= 10 ){   // check bordi 
						if( wallO_board[(wall.wallx-9) / offsetWall ][(wall.wally-38) / offsetWall -1] ==0 && wallO_board[(wall.wallx-9) / offsetWall +1][(wall.wally-38) / offsetWall -1] ==0  ){     // check se c e un altro muro sopra
						DrawWall(wall,Black);
						wall.wally-=offsetWall;
						DrawWall(wall,Yellow);
						if(wallO_board[3][3]==1 && wallO_board[4][3]==1){
						
							struct Wall w;
							w.direction=0;
							w.wallx=108;
							w.wally=137;
							
							DrawWall(w,Yellow);
						}
					}
				}
			}
				if(wall.direction ==1 ){
					if(wall.wally -offsetWall <=180 && wall.wally-offsetWall >= 6 ){
						 if( wallV_board[(wall.wallx-39) / offsetWall ][(wall.wally-8) / offsetWall -1] ==0   ){     // check se c e un altro muro sopra
						DrawWall(wall,Black);																												
						wall.wally-=offsetWall;
						DrawWall(wall,Yellow);
							 if(wallO_board[3][3]==1 && wallO_board[4][3]==1){
						
							struct Wall w;
							w.direction=0;
							w.wallx=108;
							w.wally=137;
							
							DrawWall(w,Yellow);
						}
				
				}
					}
				}
			

}

void move_downWall_NPC(){
	
			if(wall.direction ==0){
						if( wallO_board[(wall.wallx-9) / offsetWall ][(wall.wally-38) / offsetWall +1] ==0 && wallO_board[(wall.wallx-9) / offsetWall +1][(wall.wally-38) / offsetWall +1] ==0  ){  
						if(wall.wally +offsetWall <=210 && wall.wally+offsetWall >= 10 ){
						DrawWall(wall,Black);
						wall.wally+=offsetWall;
						DrawWall(wall,Yellow);	
							if(wallO_board[3][3]==1 && wallO_board[4][3]==1){
						
							struct Wall w;
							w.direction=0;
							w.wallx=108;
							w.wally=137;
							
							DrawWall(w,Yellow);
						}
						}
					}
					}
				if(wall.direction ==1){
					if(wall.wally +offsetWall <=180 && wall.wally+offsetWall >= 10 ){
						 if( wallV_board[(wall.wallx-39) / offsetWall ][(wall.wally-8) / offsetWall +2] ==0   ){   
						
						DrawWall(wall,Black);
						wall.wally+=offsetWall;
						DrawWall(wall,Yellow);	
							 if(wallO_board[3][3]==1 && wallO_board[4][3]==1){
						
							struct Wall w;
							w.direction=0;
							w.wallx=108;
							w.wally=137;
							
							DrawWall(w,Yellow);
						}
						}			
				}
				}
}
						

void move_rightWall_NPC(){
	
						if(wall.direction ==0){
						if(wall.wallx +offsetWall <=220 && wall.wallx+offsetWall >= 8 ){
						if( wallO_board[(wall.wallx-9) / offsetWall +2][(wall.wally-38) / offsetWall] ==0  ){  
						DrawWall(wall,Black);	
						wall.wallx+=offsetWall;
						DrawWall(wall,Yellow);	
						if(wallO_board[3][3]==1 && wallO_board[4][3]==1){
						
							struct Wall w;
							w.direction=0;
							w.wallx=108;
							w.wally=137;
							
							DrawWall(w,Yellow);
						}							
						}
					}
				}	
						if(wall.direction ==1){
						if(wall.wallx +offsetWall <=220 && wall.wallx+offsetWall >= 8 ){
						if( wallV_board[(wall.wallx-39) / offsetWall +1][(wall.wally-8) / offsetWall] ==0 && wallV_board[(wall.wallx-39) / offsetWall +1][(wall.wally-8) / offsetWall +1] ==0  ){  
						DrawWall(wall,Black);	
						wall.wallx+=offsetWall;
						DrawWall(wall,Yellow);		
						if(wallO_board[3][3]==1 && wallO_board[4][3]==1){
						
							struct Wall w;
							w.direction=0;
							w.wallx=108;
							w.wally=137;
							
							DrawWall(w,Yellow);
						}
						}
					}
					
				}
}

void move_leftWall_NPC(){
	
						if(wall.direction == 0){
						if(wall.wallx -offsetWall <=200 && wall.wallx-offsetWall >= 8 ){
							if( wallO_board[(wall.wallx-9) / offsetWall -1][(wall.wally-38) / offsetWall] ==0  ){ 
						DrawWall(wall,Black);	
						wall.wallx-=offsetWall;
						DrawWall(wall,Yellow);	
						if(wallO_board[3][3]==1 && wallO_board[4][3]==1){
						
							struct Wall w;
							w.direction=0;
							w.wallx=108;
							w.wally=137;
							
							DrawWall(w,Yellow);
						}
						}
					}
				}
						if(wall.direction == 1){
						if(wall.wallx -offsetWall <=200 && wall.wallx-offsetWall >= 8 ){
								if( wallV_board[(wall.wallx-39) / offsetWall -1][(wall.wally-8) / offsetWall] ==0 && wallV_board[(wall.wallx-39) / offsetWall -1][(wall.wally-8) / offsetWall -1] ==0  ){  
						DrawWall(wall,Black);	
						wall.wallx-=offsetWall;
						DrawWall(wall,Yellow);	
						if(wallO_board[3][3]==1 && wallO_board[4][3]==1){
						
							struct Wall w;
							w.direction=0;
							w.wallx=108;
							w.wally=137;
							
							DrawWall(w,Yellow);
						}
						}
					}
				}		
}




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//-------------------------------MOVE PLAYER FUNCTION----------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


void move_up_NPC(){
	
	
	if(key1==0){
	if(turn ==1 ){
					// (pix -12)/ 33 = i                                &&  p1Y < check_p1Y+33 &&  p1Y > check_p1Y-33
		 
					
					if(p1Y -offset <=210 && p1Y-offset >= 10 && p1Y > check_p1Y-33 &&  p1X > check_p1X-33 &&  p1X< check_p1X+33 ){ // check token che non esce dai bordi
						if(wallO_board[(p1X-12)/offset][(p1Y-12)/offset -1] == 0){   
						board[(p1X-12)/offset][(p1Y-12)/offset]=0;
						CleanSquare(p1X,p1Y,20,20,Black);			
						if( board[(p1X-12)/offset][(p1Y - offset -12)/offset] ==1 ){ // check salto token
							
								p1Y-=offset; // salto token
						
						}
						p1Y-=offset;
						CleanSquare(p1X,p1Y,20,20,Red);	
						board[(p1X-12)/offset][(p1Y-12)/offset]=1;	
					}
				}
				}
	
	else if(turn ==2 ){
						
											//NPC Play
				}
	}
	else {   // move wall
		move_upWall_NPC();
	
	}
}

void move_down_NPC(){

	if(key1==0){
	
	if(turn ==1 ){
						
						if(p1Y +offset <=210 && p1Y+offset >= 10 && p1Y < check_p1Y+33 &&  p1X > check_p1X-33 &&  p1X< check_p1X+33){  
						if(wallO_board[(p1X-12)/offset][(p1Y-12)/offset] == 0){ 
						board[(p1X-12)/offset][(p1Y-12)/offset]=0;	
						CleanSquare(p1X,p1Y,20,20,Black);
						if( board[(p1X-12)/offset][(p1Y + offset -12)/offset] ==1 ){  
							p1Y+=offset;
						}
						p1Y+=offset;
						CleanSquare(p1X,p1Y,20,20,Red);
						board[(p1X-12)/offset][(p1Y-12)/offset]=1;	
						
						}
					}
					}
	else if(turn ==2 ){
						
										//NPC Play
				}
	}
	
	else {
		move_downWall_NPC();
	}

}

void move_left_NPC(){

	if(key1==0){
	if(turn ==1 ){
		
					
						if(p1X -offset <=210 && p1X-offset >= 10 && p1X > check_p1X-33  &&  p1Y < check_p1Y+33 &&  p1Y > check_p1Y-33 ){
							if(wallV_board[(p1X-12)/offset-1][(p1Y-12)/offset] == 0){ 
							board[(p1X-12)/offset][(p1Y-12)/offset]=0;
							CleanSquare(p1X,p1Y,20,20,Black);		
							if(board[(p1X-offset-12)/offset][(p1Y-12)/offset]==1	){
								p1X-=offset;
							}
							p1X-=offset;
							CleanSquare(p1X,p1Y,20,20,Red);	
							board[(p1X-12)/offset][(p1Y-12)/offset]=1;	
						
						}
					}
					}
	else if(turn ==2 ){
			
					//NPC Play
				}
			}
	else{
		move_leftWall_NPC();
	}
}






void move_right_NPC(){
	
	if(key1==0){
	if(turn ==1 ){	
						
		if(p1X +offset <=210 && p1X+offset >= 10 &&  p1X< check_p1X+33   &&  p1Y < check_p1Y+33 &&  p1Y > check_p1Y-33 ){ // da mettere i check sulla Y !!!!!!!! 
						if(wallV_board[(p1X-12)/offset][(p1Y-12)/offset] == 0){ 
						board[(p1X-12)/offset][(p1Y-12)/offset]=0;
						CleanSquare(p1X,p1Y,20,20,Black);	
					
						if(board[(p1X+offset-12)/offset][(p1Y-12)/offset]==1	){		
							p1X+=offset;
						}
						p1X+= offset;
						CleanSquare(p1X,p1Y,20,20,Red);	
						board[(p1X-12)/offset][(p1Y-12)/offset]=1;	
						}
					}
		}
		else if(turn ==2 ){
							
		//NPC Play
		}
	}
	else{
		move_rightWall_NPC();
	}

}



void possible_moves_p1_NPC(){
	
	
		switch(check_p1X){
	
			case 12: 			
					CleanSquare(check_p1X+ offset,check_p1Y ,20,20,Blue2);
					CleanSquare(check_p1X ,check_p1Y + offset ,20,20,Blue2);
					CleanSquare(check_p1X,check_p1Y-offset ,20,20,Blue2);
			break;
			
			case 210:
					
					CleanSquare(check_p1X-offset,check_p1Y ,20,20,Blue2);
					CleanSquare(check_p1X ,check_p1Y + offset ,20,20,Blue2);
					CleanSquare(check_p1X,check_p1Y-offset ,20,20,Blue2);
			default:
				
					CleanSquare(check_p1X+ offset,check_p1Y ,20,20,Blue2);		
					CleanSquare(check_p1X - offset,check_p1Y ,20,20,Blue2);
					
		}
		
		
		switch(check_p1Y){
		
			case 210:
				
				CleanSquare(check_p1X+ offset,check_p1Y ,20,20,Blue2);
				CleanSquare(check_p1X - offset,check_p1Y ,20,20,Blue2);
				CleanSquare(check_p1X,check_p1Y-offset ,20,20,Blue2);
		break;
			default:
				
				CleanSquare(check_p1X,check_p1Y+offset ,20,20,Blue2);
				CleanSquare(check_p1X,check_p1Y- offset ,20,20,Blue2);	
			break;
		}	
		
		
			if(wallV_board[(check_p1X-12)/offset][(check_p1Y-12)/offset] == 1 && board[(check_p1X +offset -12)/offset][(check_p1Y-12)/offset] ==0){
				
				CleanSquare(check_p1X+ offset,check_p1Y ,20,20,Black);		
			
			} 
			if(wallV_board[(check_p1X-12)/offset-1][(check_p1Y-12)/offset] == 1 && board[(check_p1X -offset -12)/offset][(check_p1Y-12)/offset] ==0){
				
				CleanSquare(check_p1X- offset,check_p1Y ,20,20,Black);		
			
			} 
			if(wallO_board[(check_p1X-12)/offset][(check_p1Y-12)/offset -1] == 1 && board[(check_p1X  -12)/offset][(check_p1Y-12)/offset -1] ==0 ){ 
				CleanSquare(check_p1X,check_p1Y -offset,20,20,Black);
			
			}

			 if(wallO_board[(check_p1X-12)/offset][(check_p1Y-12)/offset] == 1 && board[(check_p1X -12)/offset][(check_p1Y-12)/offset +1] ==0)   {
			 
			 	CleanSquare(check_p1X,check_p1Y +offset,20,20,Black);
			 }
			 
			 
		
			 
			

}






void delete_possible_moves_p1_NPC(){

										if(board[(check_p1X-12)/offset-1][(check_p1Y-12)/offset] ==0 ){
							
												CleanSquare(check_p1X-offset,check_p1Y,20,20,Black);	
										}
										if(board[(check_p1X-12)/offset+1][(check_p1Y-12)/offset] ==0 ){
							
												CleanSquare(check_p1X+offset,check_p1Y,20,20,Black);	
										}
										if(board[(check_p1X-12)/offset][(check_p1Y-12)/offset-1] ==0 ){
							
												CleanSquare(check_p1X,check_p1Y -offset,20,20,Black);	
										}
										
										if(board[(check_p1X-12)/offset][(check_p1Y-12)/offset+1] ==0 && check_p1Y !=210){
							
												CleanSquare(check_p1X,check_p1Y +offset,20,20,Black);	
										}
									
}



void check_gameOver_NPC(){        

	if(p1Y==12 || p2Y==210){
	
		CleanSquare(p1X,p1Y,20,20,Black);
		CleanSquare(p2X,p2Y,20,20,Black);
		disable_RIT();
		disable_timer(0);
		
	} 	

if( p1Y==12 ){
	one_player_one_board=0;
	
	CleanSquare(p1X,p1Y,20,20,Black);
	CleanSquare(p2X,p2Y,20,20,Black);
	
  
		disable_RIT();
		disable_timer(0);
		
		
		
		delete_possible_moves_p1_NPC();
		LCD_Clear(Black);
		CleanSquare(p1X,p1Y,20,20,Black);
		CleanSquare(p2X,p2Y,20,20,Black);
		GUI_Text(80, 130, (uint8_t *) "Player1 Win", Red, Black);
		GUI_Text(25, 230, (uint8_t *) "Press RESET to play again", White, Black);
		
		return;
	}
	if( p2Y==210 ){
		one_player_one_board=0;
		CleanSquare(p1X,p1Y,20,20,Black);
		CleanSquare(p2X,p2Y,20,20,Black);
		
		disable_RIT();
		disable_timer(0);
		LCD_Clear(Black);
		CleanSquare(p1X,p1Y,20,20,Black);
		CleanSquare(p2X,p2Y,20,20,Black);
	
		
		GUI_Text(80, 130, (uint8_t *) "Player2 Win", White, Black);
		GUI_Text(25, 230, (uint8_t *) "Press RESET to play again", White, Black);
		return;
		
	}
	
	
}



void sel_NPC(){
if(key1 == 0){
								
                  if(turn == 1){
									
									delete_possible_moves_p1_NPC();
									
									check_p1X=p1X;
									check_p1Y=p1Y;
										
									board[(p1X-12)/offset][(p1Y-12)/offset]=1;
										
											
											if(count_moves <100){
										// salvo la mossa 
									if(right !=0 && (left ==0 && up ==0 && down ==0)){
										moves[count_moves].playerId=0;
										moves[count_moves].playerMove=0;
										moves[count_moves].vertical=0;
										moves[count_moves].x=p1X;
										moves[count_moves].y=p1Y;
										count_moves++;
									}
									
									if(left !=0 && (right ==0 && up ==0 && down ==0)){
										moves[count_moves].playerId=0;
										moves[count_moves].playerMove=0;
										moves[count_moves].vertical=0;
										moves[count_moves].x=p1X;
										moves[count_moves].y=p1Y;
										count_moves++;
									}
									
									
									if(up !=0 && (left ==0 && right ==0 && down ==0)){
										moves[count_moves].playerId=0;
										moves[count_moves].playerMove=0;
										moves[count_moves].vertical=1;
										moves[count_moves].x=p1X;
										moves[count_moves].y=p1Y;
										count_moves++;
									}
									
									if(down !=0 && (left ==0 && up ==0 && right ==0)){
										moves[count_moves].playerId=0;
										moves[count_moves].playerMove=0;
										moves[count_moves].vertical=1;
										moves[count_moves].x=p1X;
										moves[count_moves].y=p1Y;
										count_moves++;
									}
								}
									
									
									
									
									turn=2;
								}
								else if(turn == 2){ 
									
									
									board[(p2X-12)/offset][(p2Y-12)/offset]=1;	
									
									
										if(count_moves <100){
									
										// salvo la mossa 
									if(right !=0 && (left ==0 && up ==0 && down ==0)){
										moves[count_moves].playerId=1;
										moves[count_moves].playerMove=0;
										moves[count_moves].vertical=0;
										moves[count_moves].x=p2X;
										moves[count_moves].y=p2Y;
										count_moves++;
									}
									
									if(left !=0 && (right ==0 && up ==0 && down ==0)){
										moves[count_moves].playerId=1;
										moves[count_moves].playerMove=0;
										moves[count_moves].vertical=0;
										moves[count_moves].x=p2X;
										moves[count_moves].y=p2Y;
										count_moves++;
									}
									
									
									if(up !=0 && (left ==0 && right ==0 && down ==0)){
										moves[count_moves].playerId=1;
										moves[count_moves].playerMove=0;
										moves[count_moves].vertical=1;
										moves[count_moves].x=p2X;
										moves[count_moves].y=p2Y;
										count_moves++;
									}
									
									if(down !=0 && (left ==0 && up ==0 && right ==0)){
										moves[count_moves].playerId=1;
										moves[count_moves].playerMove=0;
										moves[count_moves].vertical=1;
										moves[count_moves].x=p2X;
										moves[count_moves].y=p2Y;
										count_moves++;
									}
								}
									
									turn =1;
								}
							}
							else if (key1== 1){
								if(turn == 1){
									
									if(check_p1X!=p1X || check_p1Y != p1Y){
											board[(p1X-12)/offset][(p1Y-12)/offset]=0;
											CleanSquare(p1X,p1Y,20,20,Black);
											p1X=check_p1X;
											p1Y= check_p1Y;
										CleanSquare(p1X,p1Y,20,20,Red);
									}
									
									if(wall.direction==0 ){
										wallO_board[(wall.wallx-9)/offset][(wall.wally-38)/offset]=1;
										wallO_board[(wall.wallx-9)/offset +1][((wall.wally-38)/offset )]=1;
										
									}
									
									if(wall.direction==1 ){
								
										wallV_board[(wall.wallx-39)/offset][(wall.wally-8)/offset]=1;
										wallV_board[(wall.wallx-39)/offset][((wall.wally-8)/offset )+1]=1;
									}
									delete_possible_moves_p1_NPC();
									
									if(hasPath(p1X,p1Y)==0 || hasPath_2(p2X,p2Y)==0){
								
										GUI_Text(40, 235, (uint8_t *) "You can't trap player", Red, Black);
										
										if(wall.direction==0){
													
										wallO_board[(wall.wallx-9)/offset][(wall.wally-38)/offset]=0;
										wallO_board[(wall.wallx-9)/offset +1][((wall.wally-38)/offset )]=0;
										
								
										}
										if(wall.direction==1){
											wallV_board[(wall.wallx-39)/offset][(wall.wally-8)/offset]=0;
											wallV_board[(wall.wallx-39)/offset][((wall.wally-8)/offset )+1]=0;
										}
										DrawWall(wall,Black);
										key1=0;
										return;
								}
									
									
										if(count_moves <100){
										// salvo la mossa 
									if(right !=0 && (left ==0 && up ==0 && down ==0)){
										moves[count_moves].playerId=0;
										moves[count_moves].playerMove=1;
										moves[count_moves].vertical=0;
										moves[count_moves].x=wall.wallx;
										moves[count_moves].y=wall.wally;
										count_moves++;
									}
									
									if(left !=0 && (right ==0 && up ==0 && down ==0)){
										moves[count_moves].playerId=0;
										moves[count_moves].playerMove=1;
										moves[count_moves].vertical=0;
										moves[count_moves].x=wall.wallx;
										moves[count_moves].y=wall.wally;
										count_moves++;
									}
									
									
									if(up !=0 && (left ==0 && right ==0 && down ==0)){
										moves[count_moves].playerId=0;
										moves[count_moves].playerMove=1;
										moves[count_moves].vertical=1;
										moves[count_moves].x=wall.wallx;
										moves[count_moves].y=wall.wally;
										count_moves++;
									}
									
									if(down !=0 && (left ==0 && up ==0 && right ==0)){
										moves[count_moves].playerId=0;
										moves[count_moves].playerMove=1;
										moves[count_moves].vertical=1;
										moves[count_moves].x=wall.wallx;
										moves[count_moves].y=wall.wally;
										count_moves++;
									}
								}
									
									
									p1W--;
									turn=2;
								
								
								
								}
								else if(turn == 2){ 
									
									if(wall.direction==0 ){
										wallO_board[(wall.wallx-9)/offset][(wall.wally-38)/offset]=1;
										wallO_board[(wall.wallx-9)/offset +1][((wall.wally-38)/offset )]=1;						
									}
									
									if(wall.direction==1 ){
										wallV_board[(wall.wallx-39)/offset][(wall.wally-8)/offset]=1;
										wallV_board[(wall.wallx-39)/offset][((wall.wally-8)/offset )+1]=1;
									}
									
									
									if(hasPath(p1X,p1Y)==0 || hasPath_2(p2X,p2Y)==0){
								
										GUI_Text(40, 235, (uint8_t *) "You can't trap player", Red, Black);
										DrawWall(wall,Black);
										if(wall.direction==0){
													
										wallO_board[(wall.wallx-9)/offset][(wall.wally-38)/offset]=0;
										wallO_board[(wall.wallx-9)/offset +1][((wall.wally-38)/offset )]=0;
								
										}
										if(wall.direction==1){
											wallV_board[(wall.wallx-39)/offset][(wall.wally-8)/offset]=0;
											wallV_board[(wall.wallx-39)/offset][((wall.wally-8)/offset )+1]=0;
										}
										key1=0;
										return;
								}
									
								//  ssss
									
									if(count_moves <100){
									
										// salvo la mossa 
									if(right !=0 && (left ==0 && up ==0 && down ==0)){
										moves[count_moves].playerId=1;
										moves[count_moves].playerMove=1;
										moves[count_moves].vertical=0;
										moves[count_moves].x=wall.wallx;
										moves[count_moves].y=wall.wally;
										count_moves++;
									}
									
									if(left !=0 && (right ==0 && up ==0 && down ==0)){
										moves[count_moves].playerId=1;
										moves[count_moves].playerMove=1;
										moves[count_moves].vertical=0;
										moves[count_moves].x=wall.wallx;
										moves[count_moves].y=wall.wally;
										count_moves++;
									}
									
									
									if(up !=0 && (left ==0 && right ==0 && down ==0)){
										moves[count_moves].playerId=1;
										moves[count_moves].playerMove=1;
										moves[count_moves].vertical=1;
										moves[count_moves].x=wall.wallx;
										moves[count_moves].y=wall.wally;
										count_moves++;
									}
									
									if(down !=0 && (left ==0 && up ==0 && right ==0)){
										moves[count_moves].playerId=1;
										moves[count_moves].playerMove=1;
										moves[count_moves].vertical=1;
										moves[count_moves].x=wall.wallx;
										moves[count_moves].y=wall.wally;
										count_moves++;
									}
								}
									
									p2W--;
									turn =1;
								}
								key1=0;
							}
							time=20;
							timeout=0;
							
	check_gameOver_NPC();
}



void NPC(){

if( (p1Y > 78 && p2Y <144) || c%2!=0 ){
	
int	n1= wallO_board[(p2X-12)/33 +1][(p2Y-12)/33 ] +wallO_board[(p2X-12)/33 +2][(p2Y-12)/33 ] +wallO_board[(p2X-12)/33 +3][(p2Y-12)/33 ];
int	n2= wallO_board[(p2X-12)/33][(p2Y-12)/33 -1] + wallO_board[(p2X-12)/33 -2][(p2Y-12)/33 ] +wallO_board[(p2X-12)/33 -3][(p2Y-12)/33 ] ;

  if( wallO_board[(p2X-12)/33][(p2Y-12)/33 ] ==0 && p2Y < 210  ){    //down
		
				board[(p2X-12)/offset][(p2Y-12)/offset]=0;
				CleanSquare(p2X,p2Y,20,20,Black);
		
				if(board[(p2X-12)/offset][(p2Y-12+offset)/offset]==1	){		
							p2Y+=offset;
				}
				p2Y+=33;
				CleanSquare(p2X,p2Y,20,20,White);
				sel_NPC();
		}
    
		
		else if(  wallV_board[(p2X-12)/33 ][(p2Y-12)/33]== 0 && (n1<=n2) && p2X < 210){    //right
			board[(p2X-12)/offset][(p2Y-12)/offset]=0;
			CleanSquare(p2X,p2Y,20,20,Black);
			
			if(board[(p2X+offset-12)/offset][(p2Y-12)/offset]==1	){		
							p2X+=offset;
			}
			
			p2X+=33;	
			CleanSquare(p2X,p2Y,20,20,White);
			sel_NPC();
		}
		
		else if( wallV_board[(p2X-12)/33 -1][(p2Y-12)/33]== 0 && (n1>=n2) && p2X > 12 ){    //left
				board[(p2X-12)/offset][(p2Y-12)/offset]=0;
			CleanSquare(p2X,p2Y,20,20,Black);
			
			if(board[(p2X-offset-12)/offset][(p2Y-12)/offset]==1	){		
							p2X-=offset;
			}
			
			p2X-=33;
			CleanSquare(p2X,p2Y,20,20,White);
			sel_NPC();
		}
		
		
		else if(  wallO_board[(p2X-12)/33][(p2Y-12)/33 -1] ==0 && p2Y > 12){    //up			
			board[(p2X-12)/offset][(p2Y-12)/offset]=0;
			CleanSquare(p2X,p2Y,20,20,Black);
			
			if(board[(p2X-12)/offset][(p2Y-12-offset)/offset]==1	){		
							p2Y-=offset;
				}
			
			p2Y-=33;
			CleanSquare(p2X,p2Y,20,20,White);
			sel_NPC();
		}
		
	}

else{
	
		struct Wall wall_NPC;
			key1=1;
			c++;
			if( wallO_board[(p1X-12)/33][(p1Y-12)/33 -1] ==0  ){        // up P1
					wallO_board[(p1X-12)/33][(p1Y-12)/33 -1]=1;
					
				if(wallO_board[(p1X-12)/33 +1 ][(p1Y-12)/33 -1] ==0){    // up-right 
					wall_NPC.direction=0;
					wall_NPC.wallx=p1X-3;
					wall_NPC.wally=p1Y-7;
					wallO_board[(p1X-12)/33 +1 ][(p1Y-12)/33 -1]=1;
					DrawWall(wall_NPC,Yellow);
				
				}
				else if(wallO_board[(p1X-12)/33 -1][(p1Y-12)/33 -1] ==0){    //up-left
					wall_NPC.direction=0;
					wall_NPC.wallx=p1X-3-offset;
					wall_NPC.wally=p1Y-7;
					wallO_board[(p1X-12)/33 -1][(p1Y-12)/33 -1]=1;
					DrawWall(wall_NPC,Yellow);
				}
				sel_NPC();
			}

}


}



void handler_RIT_NPC(){

	char w1[5] = "";	
	char w2[5] = "";	
	char turn_in_char[5] = "";
	sprintf(w1,"%d",p1W);
	sprintf(w2,"%d",p2W);
	
	GUI_Text(42, 290, (uint8_t *)w1, White, Black);
	GUI_Text(202, 285, (uint8_t *)w2, White, Black);
  
  sprintf(turn_in_char," P%d",turn);
	GUI_Text(92, 265,(uint8_t *)turn_in_char, White, Black);	 

	
				
	if(( timeout ==1 ) && 	((check_p1X != p1X )|| (check_p1Y != p1Y) ) ){
		
	if(board[(check_p1X-12)/offset-1][(check_p1Y-12)/offset] ==0 ){
							
												CleanSquare(check_p1X-offset,check_p1Y,20,20,Black);	
										}
										if(board[(check_p1X-12)/offset+1][(check_p1Y-12)/offset] ==0 ){
							
												CleanSquare(check_p1X+offset,check_p1Y,20,20,Black);	
										}
										if(board[(check_p1X-12)/offset][(check_p1Y-12)/offset-1] ==0 ){
							
												CleanSquare(check_p1X,check_p1Y -offset,20,20,Black);	
										}
										
										if(board[(check_p1X-12)/offset][(check_p1Y-12)/offset+1] ==0 && check_p1Y !=210){
							
												CleanSquare(check_p1X,check_p1Y +offset,20,20,Black);	
										}
					
		CleanSquare(p1X,p1Y,20,20,Black);	
		board[(p1X-12)/offset][(p1Y-12)/offset]=0;
		p1X = check_p1X;
		p1Y = check_p1Y;
		CleanSquare(p1X,p1Y,20,20,Red);	
		
		if(key1==1){
					
			DrawWall(wall, Black);
			key1=0;
		}
		
		timeout=0;
	
	}
	
	

		if((key1 ==1 && timeout ==1 )){
						
			DrawWall(wall, Black);
			key1=0;
			timeout=0;
	
	}
	if(timeout==1){
		
		if(turn == 1){
				if(board[(check_p2X-12)/offset-1][(check_p2Y-12)/offset] ==0 ){
							
												CleanSquare(check_p2X-offset,check_p2Y,20,20,Black);	
										}
										if(board[(check_p2X-12)/offset+1][(check_p2Y-12)/offset] ==0 ){
							
												CleanSquare(check_p2X+offset,check_p2Y,20,20,Black);	
										}
										if(board[(check_p2X-12)/offset][(check_p2Y-12)/offset-1] ==0 ){
							
												CleanSquare(check_p2X,check_p2Y -offset,20,20,Black);	
										}								
										if(board[(check_p2X-12)/offset][(check_p2Y-12)/offset+1] ==0  && check_p1Y !=12 ){
							
												CleanSquare(check_p2X,check_p2Y +offset,20,20,Black);	
										}
		}

		delete_possible_moves_p1_NPC();
		timeout=0;
	}
		CleanSquare(p1X,p1Y ,20,20,Red);
		CleanSquare(p2X,p2Y ,20,20,White);
	
	if(turn ==1){
		
 		possible_moves_p1_NPC();
	}
	
	if(turn ==2){
	
		NPC();
	}
	
	
		CleanSquare(p1X,p1Y ,20,20,Red);
		CleanSquare(p2X,p2Y ,20,20,White);
	
}



















