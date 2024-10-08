/* Includes ------------------------------------------------------------------*/
#include "API_uart.h"

/* Private variable ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void Error_Handler(void);

/* Public functions ----------------------------------------------------------*/

/**
 * @brief  Initialize UART with specific settings.
 * @param  None.
 * @retval bool_t: returns true if initialization is successful, otherwise false.
 */

bool_t uartInit(void)
{
  UartHandle.Instance = USARTx;
  UartHandle.Init.BaudRate = 9600;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits = UART_STOPBITS_1;
  UartHandle.Init.Parity = UART_PARITY_ODD;
  UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode = UART_MODE_TX_RX;
  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

  if (OK != UART_HAL_Init())
  {
    /* Initialization Error */
    return false;
  }

  uartSendString((uint8_t *)"UART init OK -> baud rate configured = 9600 | stopbits = 1 | parity = odd.\r\n");

  return true;
}

/**
 * @brief  Send a sring via UART.
 * @param  uint8_t * pstring: pointer to the string.
 * @retval None.
 */
void uartSendString(uint8_t *pstring)
{
  if (NULL != pstring && MAXbUFFER > strlen((char *)pstring))
  {
    if (OK != UART_HAL_Tx(pstring, strlen((char *)pstring)))
    {
      Error_Handler();
    }
  }
  else
    Error_Handler();
}

/**
 * @brief  Send a specific number of characters from a string via UART.
 * @param  uint8_t * pstring: pointer to the string.
 * @param  uint16_t size: number of characters to send.
 * @retval None.
 */
void uartSendStringSize(uint8_t *pstring, uint16_t size)
{
  if (NULL != pstring && MAXbUFFER > size && 0 < size)
  {
    if (OK != UART_HAL_Tx(pstring, size))
    {
      Error_Handler();
    }
  }
  else
    Error_Handler();
}

/**
 * @brief  Receive a specific number of characters via UART.
 * @param  uint8_t * pstring: pointer to the buffer where received characters will be stored.
 * @param  uint16_t size: number of characters to receive.
 * @retval None.
 */
void uartReceiveStringSize(uint8_t *pstring, uint16_t size)
{
  if (NULL != pstring && MAXbUFFER > size && 0 < size)
  {
    if (OK != UART_HAL_Rx(pstring, size))
    {
      Error_Handler();
    }
  }
  else
    Error_Handler();
}

/* Private API code ----------------------------------------------------------*/

/**
 * @brief  Handles errors by entering an infinite loop.
 * @param  None.
 * @retval None.
 */
static void Error_Handler(void)
{
  while (1)
  {
  }
}
