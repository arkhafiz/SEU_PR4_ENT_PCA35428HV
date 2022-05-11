/*
 * functions.h
 *
 *  Created on: 20 apr 2022
 *      Author: Adelina
 */

#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_

void display_leds_LDR(uint32_t raw_LDR);

void display_leds_NTC(float raw_NTC);

void LEDMode(uint32_t raw_LDR, float raw_NTC, uint32_t raw_po, uint32_t NTC_volt);

void turn_off_leds();

void find_blinking_led(uint32_t raw_pot);

#endif /* INC_FUNCTIONS_H_ */
