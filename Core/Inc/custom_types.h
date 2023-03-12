/*
 * custom_types.h
 *
 */

#ifndef INC_CUSTOM_TYPES_H_
#define INC_CUSTOM_TYPES_H_

typedef struct Sensor {
	uint32_t Echo_Val1;
	uint32_t Echo_Val2;
	uint32_t Echo_Time;
	uint8_t RisingEdgeDetected;
	uint8_t Distance;
	uint8_t DistanceAround[3];
}Sensor;

typedef enum Direction {
	Right,
	Left,
	Forward,
	Backwards
}Direction;

#endif /* INC_CUSTOM_TYPES_H_ */
