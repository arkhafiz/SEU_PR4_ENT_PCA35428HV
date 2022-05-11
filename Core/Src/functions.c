/*
 * functions.c
 *
 *  Created on: Apr 19, 2022
 *      Author: arkhafiz
 *
 *  1.a. Read the button input, to know which information display on the leds
 *
 *  1.b. Display with leds the level of LDR and NTC
 *
 *  1.c Display the level of the alarm with the potenziometro
 *
 *  1.d Set the alarm level and manage the buzzer
 *
 *  QUESTION: The leds are only the first row in the picture?
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "main.h"

//PINS
//Botton Left = BL
//Botton Right = BR
//LDR = ADC1_IN0
//NTC = ADC1_IN1
//Potenciometro= ADC1_IN4
//Buzzer = BU
//Leds: D1-D8

//Managing the display of the leds with the counter value
int counter=0;
int button_left_pressed=0;
int button_left_state=0;
int button_right_state=0;
int button_right_pressed=0;

//Which situation we are
//int display_LDR=0;


//Blink state, 1 if it's blinking, 0 if it doesnt
int blink_state=0;

//State of the buzzer
int buzzer_state=0;

//Tick
uint32_t last_tick=0;


void LEDMode(uint32_t raw_LDR, float raw_NTC, uint32_t raw_pot, uint32_t NTC_volt){

    //Bottom left
	button_left_state=HAL_GPIO_ReadPin(BL_GPIO_Port, BL_Pin);

	//Bottom right
	button_right_state=HAL_GPIO_ReadPin(BR_GPIO_Port, BR_Pin);

    //Consider the time in the memory
	uint32_t tick = HAL_GetTick();

    //Managing the left button
    //TOUCH THE LEFT BUTTON
	if(button_left_state==0) {
		button_left_pressed=1;
        counter++;
        printf("Button Left Pressed %d\n", button_left_pressed);
        printf("Counter %d\n", counter);
	}


    //TOUCHING EVERY DISPAIR TIME ==> LDR LEDS
    if(counter==1 && button_left_pressed==1){

		turn_off_leds();

		int raw = raw_LDR;

		if(0 <= raw && raw <= 511){
			HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
		}
		else if(512 <= raw && raw <= 1023){
			HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);

		}
		else if(1024 <= raw && raw <= 1535){
			HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_SET);
		}
		else if(1536 <= raw && raw <= 2047){
			HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_SET);
		}
		else if(2048 <= raw && raw <= 2559){
			HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_SET);
		}
		else if(2560 <= raw && raw <= 3071){
			HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_SET);
		}
		else if(3072 <= raw && raw <= 3583){
			HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,GPIO_PIN_SET);
		}
		else if(3584 <= raw && raw <= 4095){
			HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D8_GPIO_Port,D8_Pin,GPIO_PIN_SET);
		}

    }

    //TOUCHING EVERY PAIR TIME ==> NTC LEDS
    if(counter==2 && button_left_pressed==1){

		turn_off_leds();


	    if(25.000000 <= raw_NTC && raw_NTC <= 25.624000){
	        HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
	    }
	    else if(25.625000 <= raw_NTC && raw_NTC <= 26.249000){
	        HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);

	    }
	    else if(26.250000 <= raw_NTC && raw_NTC <= 26.874000){
	        HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_SET);
	    }
	    else if(26.875000 <= raw_NTC && raw_NTC <= 27.499000){
	        HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_SET);
	    }
	    else if(27.500000 <= raw_NTC && raw_NTC <= 28.124000){
	        HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_SET);
	    }
	    else if(28.125000 <= raw_NTC && raw_NTC <= 28.749000){
	        HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_SET);
	    }
	    else if(28.750000 <= raw_NTC && raw_NTC <= 29.374000){
	        HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,GPIO_PIN_SET);
	    }
	    else if(29.375000 <= raw_NTC && raw_NTC <= 30.000000){
	        HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,GPIO_PIN_SET);
	        HAL_GPIO_WritePin(D8_GPIO_Port,D8_Pin,GPIO_PIN_SET);
	    }

    }

    if(counter==3 && button_left_pressed==1){
    	counter=1;

		turn_off_leds();

		int raw = raw_LDR;

		if(0 <= raw && raw <= 511){
			HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
		}
		else if(512 <= raw && raw <= 1023){
			HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);

		}
		else if(1024 <= raw && raw <= 1535){
			HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_SET);
		}
		else if(1536 <= raw && raw <= 2047){
			HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_SET);
		}
		else if(2048 <= raw && raw <= 2559){
			HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_SET);
		}
		else if(2560 <= raw && raw <= 3071){
			HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_SET);
		}
		else if(3072 <= raw && raw <= 3583){
			HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,GPIO_PIN_SET);
		}
		else if(3584 <= raw && raw <= 4095){
			HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D8_GPIO_Port,D8_Pin,GPIO_PIN_SET);
		}
    }

    //Display alarm level
    if(tick-last_tick>200) {
        find_blinking_led(raw_pot);
		last_tick=tick;
	}


    //Alarm control
    if(counter==1){
        if(raw_LDR > raw_pot){
            //Buzzer on
            HAL_GPIO_WritePin(BU_GPIO_Port,BU_Pin,GPIO_PIN_SET);
            buzzer_state=1;
        }
        else{
            //Buffer off
            HAL_GPIO_WritePin(BU_GPIO_Port,BU_Pin,GPIO_PIN_RESET);
            buzzer_state=0;
        }
    }
    else if(counter==2){
		if(NTC_volt > raw_pot){
			//Buzzer on
			HAL_GPIO_WritePin(BU_GPIO_Port,BU_Pin,GPIO_PIN_SET);
			buzzer_state=1;
		}
		else{
			printf("Buffer off");
			//Buffer off
			HAL_GPIO_WritePin(BU_GPIO_Port,BU_Pin,GPIO_PIN_RESET);
			buzzer_state=0;
		}
    }
    else if(counter==3){
        if(raw_LDR > raw_pot){
            printf("Buzzer on");
            //Buzzer on
            HAL_GPIO_WritePin(BU_GPIO_Port,BU_Pin,GPIO_PIN_SET);
            buzzer_state=1;
        }
        else{
        	printf("Buffer off");
            //Buffer off
            HAL_GPIO_WritePin(BU_GPIO_Port,BU_Pin,GPIO_PIN_RESET);
            buzzer_state=0;
        }
    }

    //Controlling the right button
    if(button_right_state==0){
        button_right_pressed=1;
    }

    //----Managing the buzzer with the button
    if(buzzer_state==1 && button_right_pressed==1){
    	printf("Reset the buzzer");
        HAL_GPIO_WritePin(BU_GPIO_Port,BU_Pin,GPIO_PIN_RESET);
        buzzer_state=0;
        //Wait 10 seconds to setup
        HAL_Delay(10000);
    }
}

void turn_off_leds(){
    HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(D8_GPIO_Port,D8_Pin,GPIO_PIN_RESET);
}


void find_blinking_led(uint32_t raw_pot){

    if(0 <= raw_pot && raw_pot <= 511){
        //Make it blinking
        if(blink_state==0){
            HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_SET);
            blink_state=1;
        }
        else{
            HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_RESET);
            blink_state=0;
        }
    }
    else if(512 <= raw_pot && raw_pot <= 1023){
        if(blink_state==0){
            HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_SET);
            blink_state=1;
        }
        else{
        HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_RESET);
            blink_state=0;
        }
    }
    else if(1024 <= raw_pot && raw_pot <= 1535){
        if(blink_state==0){
            HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_SET);
            blink_state=1;
        }
        else{
            HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_RESET);
            blink_state=0;
        }
    }
    else if(1536 <= raw_pot && raw_pot <= 2047){
        if(blink_state==0){
            HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_SET);
            blink_state=1;
        }
        else{
            HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_RESET);
            blink_state=0;
        }
    }
    else if(2048 <= raw_pot && raw_pot <= 2559){
        if(blink_state==0){
            HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_SET);
            blink_state=1;
        }
        else{
            HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_RESET);
            blink_state=0;
        }
    }
    else if(2560 <= raw_pot && raw_pot <= 3071){
        if(blink_state==0){
            HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_SET);
            blink_state=1;
        }
        else{
            HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_RESET);
            blink_state=0;
        }
    }
    else if(3072 <= raw_pot && raw_pot <= 3583){
        if(blink_state==0){
            HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,GPIO_PIN_SET);
            blink_state=1;
        }
        else{
            HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,GPIO_PIN_RESET);
            blink_state=0;
        }
    }
    else if(3584 <= raw_pot && raw_pot <= 4095){
        if(blink_state==0){
            HAL_GPIO_WritePin(D8_GPIO_Port,D8_Pin,GPIO_PIN_SET);
            blink_state=1;
        }
        else{
            HAL_GPIO_WritePin(D8_GPIO_Port,D8_Pin,GPIO_PIN_RESET);
            blink_state=0;
        }
    }
}


