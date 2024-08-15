#include "API_uart_port.h"

uint8_t UART_HAL_Init(void)
{
	HAL_StatusTypeDef res = HAL_UART_Init(&UartHandle);
	if (HAL_OK != res)
	{
		return 1;
	}
	return 0;
}

uint8_t UART_HAL_Tx(const uint8_t *pstring, uint16_t size)
{
	HAL_StatusTypeDef res = HAL_UART_Transmit(&UartHandle, pstring, size, TxTIMEOUT);
	if (HAL_OK != res)
	{
		return 1;
	}
	return 0;
}

uint8_t UART_HAL_Rx(uint8_t *pstring, uint16_t size)
{
	HAL_StatusTypeDef res = HAL_UART_Receive(&UartHandle, pstring, size, RxTIMEOUT);
	if (HAL_OK != res)
	{
		return 1;
	}
	return 0;
}
