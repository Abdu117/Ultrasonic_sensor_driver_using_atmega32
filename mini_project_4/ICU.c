/*
 * ICU.c
 *
 *  Created on: Oct 18, 2022
 *      Author: abdoa
 */
#include <avr/interrupt.h>
#include "std_types.h"
#include "ICU.h"
#include "avr/io.h"
#include "gpio.h"
static volatile void(*fun_ptr)(void)= NULL_PTR;

ISR(TIMER1_CAPT_vect){
	if(fun_ptr!=NULL_PTR)
	{
		fun_ptr();
	}
}

void ICU_init(ICU_config *config){
	TCCR1A=(1<<FOC1A)|(1<<FOC1B);
	TCCR1B = (TCCR1B & 0xF8) | (config->clock_select);
	TCCR1B = (TCCR1B & 0xBF) | ((config->input_edge)<<6);
	GPIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_INPUT);
	TCNT1 = 0;
	ICR1 = 0;
	TIMSK=(1<<TICIE1);
}

void ICU_setCallBack(void(*a_ptr)(void))
{fun_ptr=a_ptr;	}

void ICU_setEdgeDetectionType(const input_edge edgeType){
	TCCR1B = (TCCR1B & 0xBF) | ((edgeType)<<6);
}

uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;
}

void ICU_clearTimerValue(void)
{
	TCNT1 = 0;
}

void ICU_DeInit(void)
{
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	TIMSK &= ~(1<<TICIE1);
}
