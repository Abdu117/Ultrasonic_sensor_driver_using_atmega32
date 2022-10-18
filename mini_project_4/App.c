/*
 * App.c
 *
 *  Created on: Oct 18, 2022
 *      Author: abdoa
 */
#include "std_types.h"
#include "Ultrasonic_sensor _HC-SR04.h"
#include "LCD.h"
#include "avr/io.h"
int main(){
	LCD_init();
	Ultrasonic_init();
	uint16 distance;
	LCD_displayString("Distance= ");
	SREG|=(1<<7);
	while(1){
		LCD_moveCursor(0, 10);
		distance = Ultrasonic_readDistance();
		if(distance>99){
		LCD_intgerToString(distance);
		LCD_displayString("cm");
		}
		else{
			LCD_intgerToString(distance);
			LCD_displayCharacter(' ');
			LCD_displayString("cm");
		}

	}


}
