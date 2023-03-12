/*
 * sensor_HCSR04.c
 *
 */
#include "sensor_HCSR04.h"

volatile Sensor sensor1 = {0, 0, 0, 0, 0,{0,0,0}};
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim1;

/**
  * @brief Function to control the servo rotation
  * @param Direction
  * @retval None
  */
void Look(Direction direction)
{
	switch(direction)
	{
	case Right:
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,400);
		break;
	case Left:
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,1600);
		break;
	case Forward:
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,1000);
		break;
	case Backwards:
		break;
	}
}
/**
  * @brief Function to send trigger signal to HCSR04
  * @param None
  * @retval None
  */
void TriggerHCSR04(void)
{
	HAL_GPIO_WritePin(Trig_GPIO_Port, Trig_Pin, GPIO_PIN_SET);

	__HAL_TIM_SET_COUNTER(&htim2,0);
	while(__HAL_TIM_GET_COUNTER(&htim2)<10);

	HAL_GPIO_WritePin(Trig_GPIO_Port, Trig_Pin, GPIO_PIN_RESET);
	__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1);
}
/**
  * @brief Function to look in all possible directions
  * @param None
  * @retval None
  */
void ScanSurroundings()
{
	Look(Right);
	HAL_Delay(1000);
	TriggerHCSR04();
	HAL_Delay(500);
	sensor1.DistanceAround[Right]=sensor1.Distance;
	Look(Left);
	HAL_Delay(1000);
	TriggerHCSR04();
	HAL_Delay(500);
	sensor1.DistanceAround[Left]=sensor1.Distance;
	Look(Forward);
	HAL_Delay(1000);
	TriggerHCSR04();
	HAL_Delay(500);
	sensor1.DistanceAround[Forward]=sensor1.Distance;
	SerialSend(sensor1.DistanceAround[Right],sensor1.DistanceAround[Left],sensor1.DistanceAround[Forward]);
}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == htim1.Instance)
	{
	    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{
			if (sensor1.RisingEdgeDetected == 0)
			{
				sensor1.Echo_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
				sensor1.RisingEdgeDetected = 1;
				__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
			}
			else if (sensor1.RisingEdgeDetected == 1)
			{
				sensor1.Echo_Val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
				__HAL_TIM_SET_COUNTER(htim, 0);
				if (sensor1.Echo_Val2 > sensor1.Echo_Val1)
				{
					sensor1.Echo_Time = sensor1.Echo_Val2 - sensor1.Echo_Val1;
				}
				else if (sensor1.Echo_Val1 > sensor1.Echo_Val2)
				{
					sensor1.Echo_Time = (0xffff - sensor1.Echo_Val1) + sensor1.Echo_Val2;
				}
				sensor1.Distance = sensor1.Echo_Time * .034/2;
				sensor1.RisingEdgeDetected = 0;

				__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
				__HAL_TIM_DISABLE_IT(&htim1, TIM_IT_CC1);
			}
		}
	}
}
