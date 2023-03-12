/*
 * motors.c
 *
 */

#include "motors.h"

extern TIM_HandleTypeDef htim4;

/**
  * @brief Function to control DC motors
  * @param Direction
  * @retval None
  */
void Go(Direction direction)
{
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1,1050);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2,1050);
	switch(direction)
	{
	case Right:
		HAL_GPIO_WritePin(MotorA1_GPIO_Port, MotorA1_Pin, RESET);
		HAL_GPIO_WritePin(MotorB1_GPIO_Port, MotorB1_Pin, RESET);
		HAL_GPIO_WritePin(MotorB2_GPIO_Port, MotorB2_Pin, RESET);
		HAL_GPIO_WritePin(MotorA2_GPIO_Port, MotorA2_Pin, SET);
		HAL_Delay(1200);
		Stop();
		break;
	case Left:
		HAL_GPIO_WritePin(MotorA1_GPIO_Port, MotorA1_Pin, RESET);
		HAL_GPIO_WritePin(MotorA2_GPIO_Port, MotorA2_Pin, RESET);
		HAL_GPIO_WritePin(MotorB1_GPIO_Port, MotorB1_Pin, RESET);
		HAL_GPIO_WritePin(MotorB2_GPIO_Port, MotorB2_Pin, SET);
		HAL_Delay(1200);
		Stop();
		break;
	case Forward:
		HAL_GPIO_WritePin(MotorA1_GPIO_Port, MotorA1_Pin, RESET);
		HAL_GPIO_WritePin(MotorB1_GPIO_Port, MotorB1_Pin, RESET);
		HAL_GPIO_WritePin(MotorA2_GPIO_Port, MotorA2_Pin, SET);
		HAL_GPIO_WritePin(MotorB2_GPIO_Port, MotorB2_Pin, SET);
		break;
	case Backwards:
		HAL_GPIO_WritePin(MotorA2_GPIO_Port, MotorA2_Pin, RESET);
		HAL_GPIO_WritePin(MotorB2_GPIO_Port, MotorB2_Pin, RESET);
		HAL_GPIO_WritePin(MotorB1_GPIO_Port, MotorB1_Pin, SET);
		HAL_GPIO_WritePin(MotorA1_GPIO_Port, MotorA1_Pin, SET);
		break;
	}
}
/**
  * @brief Function to hard stop the DC motors
  * @param None
  * @retval None
  */
void Stop(void)
{
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1,0);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2,0);
}
