/*
 * serial.c
 *
 */
#include "serial.h"

char USB_TxBuffer[20];

/**
  * @brief Function to send the prepared data to VCP
  * @param uint8_t,uint8_t,uint8_t
  * @retval None
  */
void SerialSend(uint8_t RightReading, uint8_t LeftReading, uint8_t ForwardReading)
{
	strcpy(USB_TxBuffer,"R:");
	itoa(RightReading,USB_TxBuffer+2,10);
	strcpy(USB_TxBuffer+5," L:");
	itoa(LeftReading,USB_TxBuffer+8,10);
	strcpy(USB_TxBuffer+11," F:");
	itoa(ForwardReading,USB_TxBuffer+14,10);
	strcpy(USB_TxBuffer+17,"\r\n");
	CDC_Transmit_FS((uint8_t *)USB_TxBuffer, 20);

}

