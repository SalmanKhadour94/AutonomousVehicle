/*
 * motors.h
 *
 */

#ifndef INC_MOTORS_H_
#define INC_MOTORS_H_

#define MotorB1_Pin GPIO_PIN_5
#define MotorB1_GPIO_Port GPIOA
#define MotorB2_Pin GPIO_PIN_7
#define MotorB2_GPIO_Port GPIOA
#define MotorA2_Pin GPIO_PIN_4
#define MotorA2_GPIO_Port GPIOC
#define MotorA1_Pin GPIO_PIN_5
#define MotorA1_GPIO_Port GPIOC

#include "stm32f4xx_hal.h"
#include "custom_types.h"

void Go(Direction);
void Stop(void);


#endif /* INC_MOTORS_H_ */
