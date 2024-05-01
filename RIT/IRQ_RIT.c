/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../GLCD/GLCD.h"
#include "../timer/timer.h"
#include "../adc/adc.h"
/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
volatile int k;
extern uint8_t buttonPressed;
extern int x1, x2, y1, y2;
extern int angle, score;
extern int x1p,x2p;
extern int direction;

void RIT_IRQHandler (void)
{	
	static uint8_t pause = 0;	
	static int down = 0;
	down++;

	ADC_start_conversion();	
	
	if(buttonPressed == 1 && (LPC_GPIO2->FIOPIN & (1<<11)) == 0){
		reset_RIT();
		switch(down){
			case 1:
				if(pause == 0) {
					GUI_Text(30, 100, (uint8_t *)  "Premi Key1 per giocare!", Black, Black);
					enable_timer(0);
				}
				else if(pause == 1){
					enable_timer(0);
					enable_timer(1);
					pause = 0;
					GUI_Text(95, 170, (uint8_t *) " Pausa ", Black, Black);
					GUI_Text(15, 190, (uint8_t *) " Premi Int0 per riniziare.", Black, Black);
			}	
			break;
		default:
			break;
		}
	}
	
	else if(buttonPressed == 2 && (LPC_GPIO2->FIOPIN & (1<<12)) == 0){
		reset_RIT();
		switch(down){
			case 1:	
			if(pause == 0 && y2 < 274 && y1 != 158) {
				disable_timer(0);
				disable_timer(1);
				pause = 1;
				GUI_Text(95, 170, (uint8_t *) " Pausa ", White, Black);
				GUI_Text(15, 190, (uint8_t *) " Premi Int0 per riniziare.", White, Black);
			}		
			break;
		default:
			break;
		}
	}	

	else if(buttonPressed == 0 && (LPC_GPIO2->FIOPIN & (1<<10)) == 0){
		reset_RIT();
		switch(down){
			case 1:
				if(pause == 1 || y2 >= 274) {	
					reset_timer(0);
					reset_timer(1);
					score = 0;
					GAME_Restart();
					direction = 0;
					pause = 0;
					x1=230,y1=158,x2=234,y2=162;
					x1p=95,x2p=144;
					angle = 0;
				}
				break;
			default:
				break;
		}
	}	
	
	else {	
		down=0;
		reset_RIT();
		NVIC_EnableIRQ(EINT0_IRQn);
		LPC_PINCON->PINSEL4    |= (1 << 20);
		NVIC_EnableIRQ(EINT1_IRQn);
		LPC_PINCON->PINSEL4    |= (1 << 22);
		NVIC_EnableIRQ(EINT2_IRQn);
		LPC_PINCON->PINSEL4    |= (1 << 24);
	}	
	
  LPC_RIT->RICTRL |= 0x1;	
}
	

/******************************************************************************
**                            End Of File
******************************************************************************/
