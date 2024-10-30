/*
 * fsm_manual.c
 *
 *  Created on: 27 Oct 2024
 *      Author: PC
 */

#include "fsm_manual.h"

int temp, test_1 = 0;

int case2(int mode,int a,
		GPIO_TypeDef* D0_PORT, uint16_t D0_PIN, GPIO_TypeDef* D1_PORT, uint16_t D1_PIN,
		GPIO_TypeDef* D2_PORT, uint16_t D2_PIN, GPIO_TypeDef* D3_PORT, uint16_t D3_PIN,
		GPIO_TypeDef* D4_PORT, uint16_t D4_PIN, GPIO_TypeDef* D5_PORT, uint16_t D5_PIN){
	setup_Led7SEG();

	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
	HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);

	HAL_GPIO_WritePin(D0_PORT, D0_PIN, en0);
	HAL_GPIO_WritePin(D1_PORT, D1_PIN, en0);
	HAL_GPIO_WritePin(D2_PORT, D2_PIN, 0);
	HAL_GPIO_WritePin(D3_PORT, D3_PIN, 0);
	HAL_GPIO_WritePin(D4_PORT, D4_PIN, 0);
	HAL_GPIO_WritePin(D5_PORT, D5_PIN, 0);
	display7SEG_1(mode + 1);

	if(button_flag[1] == 1){
	  button_flag[1] = 0;
	  a++;
	}
	if(button_flag[2] == 1){
	  button_flag[2] = 0;
	  switch(mode){
	  case 1:
		  prev_max_Red = a;
		  break;
	  case 2:
		  prev_max_Yellow = a;
		  break;
	  case 3:
		  prev_max_Green = a;
		  break;
	  }
	}
	if(button_flag[3] == 1){
	  button_flag[3] = 0;
	  a--;
	}
	if(a > 99) a = 0;
	if(a < 0) a = 99;
	if(random == 1)
	  display7SEG(a / 10);
	else
	  display7SEG(a % 10);
	return a;
}


void fsm_manual(){
	if(button_flag[0] == 1){
		button_flag[0] = 0;
		mode++;
		test_1 = 1;
		if(mode == 4) {
			if(prev_max_Red == prev_max_Green + prev_max_Yellow){
				max_Red = prev_max_Red;
				max_Green = prev_max_Green;
				max_Yellow = prev_max_Yellow;
			}else if(prev_max_Red > prev_max_Yellow){
				prev_max_Green = prev_max_Red - prev_max_Yellow;
				max_Red = prev_max_Red;
				max_Green = prev_max_Green;
				max_Yellow = prev_max_Yellow;
			}
			Reset();
			mode = 0;
		}
	}
	if(timer_flag[3] == 1){
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		setTimer(3, 25);
	}
	switch(mode){
	case 0:
	  if(timer_flag[0] == 1){
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
		  dem--;
		  case1();
		  if(dem == 0){
			  dem = 2;
		  }
		  setTimer(0, 50);
	  }
	  break;
	case 1:
		if(test_1 == 1){
			temp = max_Red;
			test_1 = 0;
		}
		temp = case2(mode, temp,
			  LED_RED_1_GPIO_Port, LED_RED_1_Pin,LED_RED_2_GPIO_Port, LED_RED_2_Pin,
			  LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin,LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin,
			  LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin,LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin
		);
		break;
	case 2:
		if(test_1 == 1){
			temp = max_Yellow;
			test_1 = 0;
		}
		temp = case2(mode, temp,
			  LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin,LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin,
			  LED_RED_1_GPIO_Port, LED_RED_1_Pin,LED_RED_2_GPIO_Port, LED_RED_2_Pin,
			  LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin,LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin
		);
		break;
	case 3:
		if(test_1 == 1){
			temp = max_Green;
			test_1 = 0;
		}
		temp = case2(mode, temp,
			  LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin,LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin,
			  LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin,LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin,
			  LED_RED_1_GPIO_Port, LED_RED_1_Pin,LED_RED_2_GPIO_Port, LED_RED_2_Pin
		);
		break;
	}
}
