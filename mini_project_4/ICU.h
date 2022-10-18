/*
 * ICU.h
 *
 *  Created on: Oct 18, 2022
 *      Author: abdoa
 */

#ifndef ICU_H_
#define ICU_H_
#include "std_types.h"
typedef enum{
	falling,rising
}input_edge;

typedef enum {
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}clock_select;

typedef struct{
	input_edge input_edge;
	clock_select clock_select;
}ICU_config;
void ICU_init(ICU_config *config);
void ICU_setCallBack(void(*a_ptr)(void));
void ICU_setEdgeDetectionType(const input_edge edgeType);
uint16 ICU_getInputCaptureValue(void);
void ICU_clearTimerValue(void);
void ICU_DeInit(void);

#endif /* ICU_H_ */
