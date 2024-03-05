
#include <string.h>
#include <stdio.h>
#include "lpc17xx.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../RIT/RIT.h"
#include "../timer/timer.h"
#include "myfunc.h"
#include "../CAN/CAN.h"

 struct Move{

	uint32_t playerId:8;
	uint32_t playerMove:4;
	uint32_t vertical:4;
	uint32_t x:8;
	uint32_t y:8;

};

// array in cui verranno salvate le mosse dei due player
extern struct Move moves[100];
struct Move moves[100];
extern int count_moves;
int count_moves=0;


 struct Wall {
    uint16_t wallx;
    uint16_t wally;
		uint16_t direction;
};



extern uint16_t length;

extern int two_player_one_board;
extern int two_player_two_board;
extern int one_player_one_board;


extern int menu;
extern int num;
extern int menu_sel;
extern int turn;
int turn =1;

extern CAN_msg       CAN_TxMsg;    
extern CAN_msg       CAN_RxMsg;  


int menu_sel=0;
int menu =0;
uint16_t length= 60;

extern int board[7][7];
int board[7][7];
extern int wallO_board[7][7]; 
extern int wallV_board[7][7]; 
extern int visited[7][7];

extern int timeout;
extern int time;


extern	int startX ;
extern  int startY ;
extern  int squareSize;
extern  int spacing;
		
extern  int rows;
extern  int cols;
		
		
extern	uint16_t p1W;
extern	uint16_t p2W;


		
extern uint16_t p1X ;
extern uint16_t p1Y ;
		
extern	uint16_t p2X ;  
extern	uint16_t p2Y;   
		
extern	uint16_t check_p1X ;
extern	uint16_t check_p1Y ;
		
extern	uint16_t check_p2X ;  
extern	uint16_t check_p2Y;   

extern int offset;
extern int offsetWall;
		int offset=33;
		int offsetWall=33;
		
		//player
		
		uint16_t p1X = 111;
		uint16_t p1Y = 210;
		
		uint16_t p2X = 111;  
		uint16_t p2Y = 12;   
		
		uint16_t check_p1X = 111;
		uint16_t check_p1Y = 210;
		
		uint16_t check_p2X = 111;  
		uint16_t check_p2Y = 12;   



//  dimensioni griglia
		int startX = 8;
    int startY = 8;
    int squareSize = 27;
    int spacing = 6;

    // Numero di righe e colonne della matrice
    int rows = 7;
    int cols = 7;
		
		
		uint16_t p1W = 8;
		uint16_t p2W = 8;
		int count =0;
		
		
extern struct Move moves[100];   
extern int key1;
extern int i;
extern int j;

		
		int key1=0;
		int i=0;
		int j=0;
		
extern struct Wall newWall2;
struct Wall newWall2;

		
		uint16_t wall_length = 60;
		
		int wallO_board[7][7];
		int wallV_board[7][7];
		
		int visited[7][7];

		extern char turn_in_char[5];
		
		char turn_in_char[5] = "";	
	

//---------------------------------------------------GLCD FUNCTION-----------------------------------------




void DrawSquare(int x, int y, int size, int color) {
    LCD_DrawLine(x, y, x + size, y, color);              // Linea superiore
    LCD_DrawLine(x, y, x, y + size, color);              // Linea sinistra
    LCD_DrawLine(x, y + size, x + size, y + size, color); // Linea inferiore
    LCD_DrawLine(x + size, y, x + size, y + size, color); // Linea destra
}



void DrawRectangle(int x, int y, int width, int height, int color) {
    LCD_DrawLine(x, y, x + width, y, color);                    // Linea superiore
    LCD_DrawLine(x, y, x, y + height, color);                   // Linea sinistra
    LCD_DrawLine(x, y + height, x + width, y + height, color);  // Linea inferiore
    LCD_DrawLine(x + width, y, x + width, y + height, color);   // Linea destra
}


void DrawMatrix(int startX, int startY, int squareSize, int spacing, int rows, int cols, int color) {
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            int x = startX + j * (squareSize + spacing);
            int y = startY + i * (squareSize + spacing);
            DrawSquare(x, y, squareSize, color);
        }
    }
}
		
// disegna quadrati con riempimento
void CleanSquare (int X_start, int Y_start, int width, int height, int color)
{
	uint16_t i, j;
	
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			LCD_SetPoint(X_start + i, Y_start + j, color);
		}
	}
	
}


void DrawWall(struct Wall wall ,uint16_t color  ){

	if(wall.direction==0){
	LCD_DrawLine(wall.wallx,wall.wally,wall.wallx+length,wall.wally,color);
	}
	if(wall.direction==1){
	LCD_DrawLine(wall.wallx,wall.wally,wall.wallx,wall.wally+length,color);
	}
}



 


void quoridor(){
uint16_t color = Yellow;
	
	
	// Q
	
    LCD_DrawLine(40, 115, 40, 95, color);
    LCD_DrawLine(40, 115, 60, 115, color);
    LCD_DrawLine(40, 95, 60, 95, color);
    LCD_DrawLine(60, 95, 60, 115, color);
    LCD_DrawLine(50, 105, 63, 115, color);

    // U
    LCD_DrawLine(65, 115, 65, 95, color);
    LCD_DrawLine(80, 95, 80, 115, color);
    LCD_DrawLine(65, 115, 80, 115, color);

    // O
    LCD_DrawLine(85, 115, 85, 95, color);
    LCD_DrawLine(85, 95, 100, 95, color);
    LCD_DrawLine(100, 95, 100, 115, color);
    LCD_DrawLine(85, 115, 100, 115, color);

    // R
    LCD_DrawLine(110, 115, 110, 95, color);
    LCD_DrawLine(110, 95, 125, 95, color);
    LCD_DrawLine(125, 95, 125, 105, color);
    LCD_DrawLine(125, 105, 110, 115, color);
    LCD_DrawLine(110, 105, 125, 115, color);

    // I
    LCD_DrawLine(130, 115, 140, 115, color);
    LCD_DrawLine(135, 95, 135, 115, color);
    LCD_DrawLine(130, 95, 140, 95, color);

    // D
    LCD_DrawLine(145, 115, 145, 95, Blue);
    LCD_DrawLine(145, 95, 160, 95, Blue);
    LCD_DrawLine(160, 95, 160, 115, Blue);
    LCD_DrawLine(145, 115, 160, 115, Blue);
    LCD_DrawLine(160, 100, 160, 110, Blue);

    // O
    LCD_DrawLine(165, 115, 165, 95, color);
    LCD_DrawLine(165, 95, 180, 95, color);
    LCD_DrawLine(180, 95, 180, 115, color);
    LCD_DrawLine(165, 115, 180, 115, color);

    // R
    LCD_DrawLine(185, 115, 185, 95, color);
    LCD_DrawLine(185, 95, 200, 95, color);
    LCD_DrawLine(200, 95, 200, 105, color);
    LCD_DrawLine(200, 105, 185, 115, color);
    LCD_DrawLine(185, 105, 200, 115, color);


}

void schermata_iniziale(){

	// funzione per disegnare la schermata iniziale 

		quoridor();
		
		GUI_Text(105, 130, (uint8_t *) "v2.0", Blue, Black);
		
	
		LCD_DrawLine(10, 10, 230, 10, Blue); //lato superiore
		LCD_DrawLine(10, 10, 10,230, Blue); // lato sinistro
	
		LCD_DrawLine(10, 230, 230, 230, Blue); //lato inferiore
		LCD_DrawLine(230, 10, 230,230, Blue); // lato destro
	
	
		
	
}

void start_menu(){

	// funzione per disegnare la schermata iniziale 
		LCD_Clear(Black);
		quoridor();
		
		GUI_Text(105, 130, (uint8_t *) "v2.0", Blue, Black);
		
	
		LCD_DrawLine(10, 10, 230, 10, Blue); //lato superiore
		LCD_DrawLine(10, 10, 10,300, Blue); // lato sinistro
	
		LCD_DrawLine(10, 300, 230, 300, Blue); //lato inferiore
		LCD_DrawLine(230, 10, 230,300, Blue); // lato destro
	
	
		GUI_Text(75, 210, (uint8_t *) "SINGLE BOARD", Yellow, Black);
		GUI_Text(75, 260, (uint8_t *) " TWO BOARD", Yellow, Black);
	
		
		DrawRectangle(65,200, 120, 30, Yellow);
	
	//	DrawRectangle(65,250, 120, 30, Yellow);

}


void start_menu_one_board(){
		
	
		GUI_Text(75, 210, (uint8_t *) "SINGLE BOARD", Black, Black);
		GUI_Text(75, 260, (uint8_t *) " TWO BOARD", Black, Black);
	
		GUI_Text(75, 210, (uint8_t *) "   HUMAN", Yellow, Black);
		GUI_Text(75, 260, (uint8_t *) "    NPC   ", Yellow, Black);
	
		
		DrawRectangle(65,200, 120, 30, Yellow);

}

void selected_menu_up(){

	DrawRectangle(65,250, 120, 30, Black);
	DrawRectangle(65,200, 120, 30, Yellow);
}

void selected_menu_down(){
	DrawRectangle(65,200, 120, 30, Black);
	DrawRectangle(65,250, 120, 30, Yellow);
}



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//----------------------------------- RIT FUNCTIONS  ----------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




int hasPath(int path_x, int path_y) {
    
    if(count <50 ){
      if( visited[(path_x-12)/33][(path_y-12)/33 -1] ==0  && wallO_board[(path_x-12)/33][(path_y-12)/33 -1] ==0  && path_y >12){    //up			
			
			visited[(path_x-12)/33][(path_y-12)/33 -1] =1;
			path_y-=33;
			
		}
		else if( visited[(path_x-12)/33 -1][(path_y-12)/33] ==0  && wallV_board[(path_x-12)/33 -1][(path_y-12)/33]== 0 && path_x > 12 ){    //left
			
			visited[(path_x-12)/33 -1][(path_y-12)/33] =1;
			path_x-=33;
		}
		else if( visited[(path_x-12)/33 +1][(path_y-12)/33] ==0  && wallV_board[(path_x-12)/33 ][(path_y-12)/33]== 0  && path_x < 210 ){    //right
			
			visited[(path_x-12)/33 +1][(path_y-12)/33] =1;
			path_x+=33;	
		}
		else if( visited[(path_x-12)/33][(path_y-12)/33 +1] ==0  && wallO_board[(path_x-12)/33][(path_y-12)/33 ] ==0   && path_y < 210){    //down
		
			 visited[(path_x-12)/33][(path_y-12)/33 +1] =1;
			path_y+=33;
		}
		
		if(path_y==12){
			count=0;	
			
			for(i =0; i<7; i++){
				for(j=0;j<7;j++){
					visited[i][j]=0;
				}	
			}
			return 1;
		}
		else{
			count ++;
			hasPath(path_x,path_y);
		}
	}
	else{
		count=0;
		for(i =0; i<7; i++){
				for(j=0;j<7;j++){
					visited[i][j]=0;
				}	
			}
		 return 0;
	}

}
	

int hasPath_2(int path_x, int path_y) {
    
      if(count <50 ){
			
        if( visited[(path_x-12)/33][(path_y-12)/33 +1] ==0  && wallO_board[(path_x-12)/33][(path_y-12)/33 ] ==0 && path_y < 210  ){    //down
				visited[(path_x-12)/33][(path_y-12)/33 +1] =1;
				path_y+=33;
		}
    
		
		else if( visited[(path_x-12)/33 +1][(path_y-12)/33 ] ==0  && wallV_board[(path_x-12)/33 ][(path_y-12)/33]== 0  && path_x < 210){    //right
		visited[(path_x-12)/33 +1][(path_y-12)/33] =1;
			path_x+=33;	
		}
		
		else if( visited[(path_x-12)/33 -1][(path_y-12)/33] ==0  && wallV_board[(path_x-12)/33 -1][(path_y-12)/33]== 0  && path_x > 12 ){    //left
			visited[(path_x-12)/33 -1][(path_y-12)/33] =1;
			path_x-=33;
		}
		
		
		else if( visited[(path_x-12)/33][(path_y-12)/33 -1] ==0  && wallO_board[(path_x-12)/33][(path_y-12)/33 -1] ==0 && path_y > 12){    //up			
   visited[(path_x-12)/33][(path_y-12)/33 -1] =1;
		path_y-=33;
		}
		
		if(path_y==210){
			count=0;	
			return 1;
		}
		else{
			count ++;
			hasPath_2(path_x,path_y);
		}
	}
	else{
		count=0;
		 return 0;
	}
	
	

}


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//----------------------------------- BUTTON FUNCTIONS  ----------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



extern void place_wall_two_player(void);
extern struct Wall RotateWall (struct Wall wall );
extern void start_game_NPC(void);
extern void start_game_two_player_one_board(void);
extern void rotate_wall_two_player(void);

void pressedINT0(){
	
	
		if(menu_sel == 0){
			start_menu();
			menu=1;
			menu_sel++;
		}
	
		
}



void pressedKey1(){
	
	
	place_wall_two_player();
	


}


void pressedKey2(){
	
	rotate_wall_two_player();

}



// handshake CAN 


void send_handshake(){

          CAN_TxMsg.data[0] = 0xff ;          
          CAN_TxMsg.len = 1;
          CAN_TxMsg.id = 2;
          CAN_TxMsg.format = STANDARD_FORMAT;
          CAN_TxMsg.type = DATA_FRAME;
          CAN_wrMsg (1, &CAN_TxMsg);               /* transmit message */


}
void send_response(){

          CAN_TxMsg.data[0] = 0xf1 ;          
          CAN_TxMsg.len = 1;
          CAN_TxMsg.id = 2;
          CAN_TxMsg.format = STANDARD_FORMAT;
          CAN_TxMsg.type = DATA_FRAME;
          CAN_wrMsg (1, &CAN_TxMsg);               /* transmit message */
					// start game
}
















