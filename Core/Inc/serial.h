/*
 * serial.h
 *
 */

#ifndef INC_SERIAL_H_
#define INC_SERIAL_H_

#include <stdlib.h>
#include <string.h>
#include "usb_device.h"
#include "usbd_cdc_if.h"

void SerialSend(uint8_t,uint8_t,uint8_t);

#endif /* INC_SERIAL_H_ */
