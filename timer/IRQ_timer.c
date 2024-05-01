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
#include "../RIT/RIT.h"
#include <stdio.h>

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern int k;
extern int x1p,x2p;
int x1=230, y1=158, x2=234, y2=162;
int angle = 0;
int score = 0;
char str[10];
int record = 100;
int direction = 0; 
int wait = 1000;

void down_SX(){	
	
	direction = 0;
	disable_timer(1);
	reset_timer(1);
	
	if (x1 > 8 && y2 < 274){
		
		if (angle == 0){
			for(k=0;k<5;k++) {
				LCD_DrawLine(x1, y1+k, x2, y1+k, Black);
				LCD_DrawLine(x1-5, y1+5+k, x2-5, y1+5+k, Green);
			}
			x1 = x1-5; x2 = x2-5; y1 = y1+5; y2 = y2+5;
		}
		
		if (angle == 1){
			for(k=0;k<5;k++) {
				LCD_DrawLine(x1, y1+k, x2, y1+k, Black);
				LCD_DrawLine(x1-5, y1+4+k, x2-5, y1+4+k, Green);
			}
			x1 = x1-5; x2 = x2-5; y1 = y1+4; y2 = y2+4;
		}
		
		if (angle == 2){
			for(k=0;k<5;k++) {
				LCD_DrawLine(x1, y1+k, x2, y1+k, Black);
				LCD_DrawLine(x1-5, y1+3+k, x2-5, y1+3+k, Green);
			}
			x1 = x1-5; x2 = x2-5; y1 = y1+3; y2 = y2+3;
		}		
	}	
	
	if (x1 <= 8){
		init_timer(1, 0x848);
		enable_timer(1);
		direction = 1;
	}
	
	if (y2 >= 274)
		checkPaddle();
	
}


void down_DX(){
	
	direction = 1;
	disable_timer(1);
	reset_timer(1);
	
	if (x2 < 230 && y2 < 274){

		if (angle == 0){
			for(k=0;k<5;k++) {
				LCD_DrawLine(x1, y1+k, x2, y1+k, Black);
				LCD_DrawLine(x1+5, y1+5+k, x2+5, y1+5+k, Green);
			}
			x1 = x1+5; x2 = x2+5; y1 = y1+5; y2 = y2+5;
		}
		
		if (angle == 1){
			for(k=0;k<5;k++) {
				LCD_DrawLine(x1, y1+k, x2, y1+k, Black);
				LCD_DrawLine(x1+5, y1+4+k, x2+5, y1+4+k, Green);
			}
			x1 = x1+5; x2 = x2+5; y1 = y1+4; y2 = y2+4;
		}
		
		if (angle == 2){
			for(k=0;k<5;k++) {
				LCD_DrawLine(x1, y1+k, x2, y1+k, Black);
				LCD_DrawLine(x1+5, y1+3+k, x2+5, y1+3+k, Green);
			}
			x1 = x1+5; x2 = x2+5; y1 = y1+3; y2 = y2+3;
		}		
	}	
	
	if (x2 >= 230){
		init_timer(1, 0x848);
		enable_timer(1);
		direction = 0;
	}
	
	if (y2 >= 274)
		checkPaddle();
	
}

void up_SX(){
	
	direction = 2;
	disable_timer(1);
	reset_timer(1);
	
	if (x1 > 8 && y1 > 8){

		if (angle == 0){
			for(k=0;k<5;k++) {
				LCD_DrawLine(x1, y2-k, x2, y2-k, Black);
				LCD_DrawLine(x1-5, y2-5-k, x2-5, y2-5-k, Green);
			}
			x1 = x1-5; x2 = x2-5; y1 = y1-5; y2 = y2-5;
		}
		
		if (angle == 1){
			for(k=0;k<5;k++) {
				LCD_DrawLine(x1, y1+k, x2, y1+k, Black);
				LCD_DrawLine(x1-5, y2-4-k, x2-5, y2-4-k, Green);
			}
			x1 = x1-5; x2 = x2-5; y1 = y1-4; y2 = y2-4;
		}
		
		if (angle == 2){
			for(k=0;k<5;k++) {
				LCD_DrawLine(x1, y1+k, x2, y1+k, Black);
				LCD_DrawLine(x1-5, y2-3-k, x2-5, y2-3-k, Green);
			}
			x1 = x1-5; x2 = x2-5; y1 = y1-3; y2 = y2-3;
		}		
	}	
	
	if (x1 <= 8){
		init_timer(1, 0x848);
		enable_timer(1);
		direction = 3;
	}
	
	if (y1 <=8){
		init_timer(1, 0x848);
		enable_timer(1);
		direction = 0;
	}	
}

void up_DX(){
 	
	direction = 3;
	disable_timer(1);
	reset_timer(1);
	
	if (x2 < 230 && y1 > 8){

		if (angle == 0){
			for(k=0;k<5;k++) {
				LCD_DrawLine(x1, y2-k, x2, y2-k, Black);
				LCD_DrawLine(x1+5, y2-5-k, x2+5, y2-5-k, Green);
			}
			x1 = x1+5; x2 = x2+5; y1 = y1-5; y2 = y2-5;
		}
		
		if (angle == 1){
			for(k=0;k<5;k++) {
				LCD_DrawLine(x1, y1+k, x2, y1+k, Black);
				LCD_DrawLine(x1+5, y2-4-k, x2+5, y2-4-k, Green);
			}
			x1 = x1+5; x2 = x2+5; y1 = y1-4; y2 = y2-4;
		}
		
		if (angle == 2){
			for(k=0;k<5;k++) {
				LCD_DrawLine(x1, y1+k, x2, y1+k, Black);
				LCD_DrawLine(x1+5, y2-3-k, x2+5, y2-3-k, Green);
			}
			x1 = x1+5; x2 = x2+5; y1 = y1-3; y2 = y2-3;
		}		
	}	
	
	if (x2 >= 230){
		init_timer(1, 0x848);
		enable_timer(1);
		direction = 2;
	}
	
	if (y1 <=8){
		init_timer(1, 0x848);
		enable_timer(1);
		direction = 1;
	}	
}
	
void checkPaddle(){
	
	if (x2 < x1p || x1 > x2p)
		youLose();
	
	if (x2 >= x1p && x2 <= x1p+17){
		continueGame();
		if (angle < 2)
			angle++;
		direction = 2;	
	}
	
	if (x2 > x1p+17 && x2 < x2p-13){
		continueGame();
		if (angle > 0)
			angle --;
		if (direction == 0)
			direction = 2;
		else 
			direction = 3;
	}
		
	if (x2 >= x2p-13 && x1 <= x2p){
		continueGame();
		if (angle < 2)
			angle++;
		direction = 3;	
	}	
}

void continueGame(){
	
	init_timer(1, 0x424);
	enable_timer(1);
	
	if(score < 100) 
		score += 5;
	else 
		score +=10;
	
	sprintf(str,"%d",score);
	GUI_Text(8, 160, (uint8_t *) str, White, Black);
	
	if(score > record) 
		record = score;
	
	sprintf(str,"%d",record);
	GUI_Text(200, 8, (uint8_t *) str, White, Black);
	
}

void youLose(){
	
	disable_timer(0);
	GUI_Text(70, 170, (uint8_t *) " Hai Perso! ", White, Black);
	
}

void TIMER0_IRQHandler (void) {
	
	switch(direction){
		case 0: 
			down_SX();
			break;
		case 1:
			down_DX();
			break;
		case 2:
			up_SX();
			break;
		case 3:
			up_DX();
			break;
		default:
			break;
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
uint16_t SinTable[45] =
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};
void TIMER1_IRQHandler (void)
{
	static int ticks=0;
	
	LPC_DAC->DACR = SinTable[ticks]<<6;
	ticks++;
	if(ticks==45) ticks=0;

  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
