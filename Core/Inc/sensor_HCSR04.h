/*
 * sensor_HCSR04.h
 *
 */

#ifndef INC_SENSOR_HCSR04_H_
#define INC_SENSOR_HCSR04_H_

#define Trig_Pin GPIO_PIN_8
#define Trig_GPIO_Port GPIOE

#include "stm32f4xx_hal.h"
#include "custom_types.h"
#include "serial.h"
void Look(Direction);
void TriggerHCSR04(void);
void ScanSurroundings();


#endif /* INC_SENSOR_HCSR04_H_ */
