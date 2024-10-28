/*
 * fsm_setting.c
 *
 *  Created on: 27 Oct 2024
 *      Author: PC
 */

#include "fsm_setting.h"

int mode = 0, en0 = 1, en1 = 0, en2 = 1, en3 = 0;

void turn_Led7SEG(){
	HAL_GPIO_WritePin(EN0_GPIO_Port,EN0_Pin, en0);
	HAL_GPIO_WritePin(EN1_GPIO_Port,EN1_Pin, en1);
	HAL_GPIO_WritePin(EN2_GPIO_Port,EN2_Pin, en2);
	HAL_GPIO_WritePin(EN3_GPIO_Port,EN3_Pin, en3);
}

void setup_Led7SEG(){
	if(timer_flag[2] == 1){
		switch(en0){
		case 0:
			en0 = 1;
			en1 = 0;
			break;
		case 1:
			en0 = 0;
			en1 = 1;
			break;
		}

		if(mode == 0){
			en2 = en0;
			en3 = en1;
		}else{
			en2 = 0;
			en3 = 1;
		}
		random = -random;
		setTimer(2, 50);
	}
}

void fsm_setting(){
	turn_Led7SEG();
}

