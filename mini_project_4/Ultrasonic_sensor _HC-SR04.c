/*
 * Ultrasonic_sensor _HC-SR04.c
 *
 *  Created on: Oct 18, 2022
 *      Author: abdoa
 */
#include "std_types.h"
#include "ICU.h"
#include "Ultrasonic_sensor _HC-SR04.h"
#include "gpio.h"
#include "util/delay.h"

ICU_config config ={rising,F_CPU_8};
uint8 icu_counter=0;
uint16 icu_timer_value=0;

void Ultrasonic_init(){
	ICU_init(&config);
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(Trigger_port_id, Trigger_pin_id, PIN_OUTPUT);

}
void Ultrasonic_Trigger(){
	GPIO_writePin(Trigger_port_id, Trigger_pin_id, LOGIC_HIGH);
	_delay_us(11);
	GPIO_writePin(Trigger_port_id, Trigger_pin_id, LOGIC_LOW);
}
uint16 Ultrasonic_readDistance(){
	Ultrasonic_Trigger();
	icu_counter=0;
	icu_timer_value=0;
	while(icu_counter!=2){}

	uint16 distance = icu_timer_value/58;
/*Sound velocity = 340.00 m/s = 34000 cm/s The distance of Object (in cm) = (340000∗Time)/2 = 17000 * Time
Total distance is divided by 2 because signal travels from HC-SR04 to object and returns to the module HC-SR-04.
Now, here we have selected an internal 8MHz oscillator frequency for ATmega32, with Prescaler F_CPU/8 for timer frequency.
Then time to execute 1 instruction is 1 us.
So, the timer gets incremented after 1 us time elapse.
= 17000 x (TIMER value) x 1 x 10^-6 cm
= 0.017 x (TIMER value) cm
distance (cm)= (TIMER value) / 58.8 cm*/
	return distance;
}
void Ultrasonic_edgeProcessing(){
	icu_counter++;
	if(icu_counter==1){
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(falling);
	}
	else if(icu_counter==2){
		icu_timer_value=ICU_getInputCaptureValue();
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(rising);

	}
}
