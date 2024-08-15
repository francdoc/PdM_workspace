#include "API_uart_port.h"

/**
 * @brief  Initializes the UART peripheral using the HAL library.
 * @note   This function sets up the UART peripheral.
 * @param  None
 * @retval uint8_t: Returns 0 if the initialization is successful, 1 if an error occurs.
 */
uint8_t UART_HAL_Init(void)
{
	HAL_StatusTypeDef res = HAL_UART_Init(&UartHandle);
	if (HAL_OK != res)
	{
		return 1;
	}
	return 0;
}

/**
 * @brief  Transmits data over UART.
 * @note   This function sends data over the UART interface.
 * @param  pstring: Pointer to the data buffer to be transmitted.
 * @param  size: Number of bytes to transmit.
 * @retval uint8_t: Returns 0 if the transmission is successful, 1 if an error occurs.
 */
uint8_t UART_HAL_Tx(const uint8_t *pstring, uint16_t size)
{
	HAL_StatusTypeDef res = HAL_UART_Transmit(&UartHandle, pstring, size, TxTIMEOUT);
	if (HAL_OK != res)
	{
		return 1;
	}
	return 0;
}

/**
 * @brief  Receives data over UART.
 * @note   This function receives data from the UART interface.
 * @param  pstring: Pointer to the buffer where the received data will be stored.
 * @param  size: Number of bytes to receive.
 * @retval uint8_t: Returns 0 if the reception is successful, 1 if an error occurs.
 */
uint8_t UART_HAL_Rx(uint8_t *pstring, uint16_t size)
{
	HAL_StatusTypeDef res = HAL_UART_Receive(&UartHandle, pstring, size, RxTIMEOUT);
	if (HAL_OK != res)
	{
		return 1;
	}
	return 0;
}
