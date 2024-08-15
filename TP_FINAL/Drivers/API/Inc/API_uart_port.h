#ifndef API_INC_API_UART_PORT_H_
#define API_INC_API_UART_PORT_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "stm32f4xx_hal.h" /* HAL include */

/* Constants and Macros ------------------------------------------------------*/

#define TxTIMEOUT 5000
#define RxTIMEOUT 10

#define USARTx USART3
#define USARTx_CLK_ENABLE() __HAL_RCC_USART3_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOD_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOD_CLK_ENABLE()

#define USARTx_FORCE_RESET() __HAL_RCC_USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET() __HAL_RCC_USART3_RELEASE_RESET()

/* Definition for USARTx Pins ------------------------------------------------*/

#define USARTx_TX_PIN GPIO_PIN_8
#define USARTx_TX_GPIO_PORT GPIOD
#define USARTx_TX_AF GPIO_AF7_USART3
#define USARTx_RX_PIN GPIO_PIN_9
#define USARTx_RX_GPIO_PORT GPIOD
#define USARTx_RX_AF GPIO_AF7_USART3

/* External Variables --------------------------------------------------------*/

extern UART_HandleTypeDef UartHandle;

/* Function Prototypes -------------------------------------------------------*/

uint8_t UART_HAL_Init(void);
uint8_t UART_HAL_Tx(const uint8_t *pstring, uint16_t size);
uint8_t UART_HAL_Rx(uint8_t *pstring, uint16_t size);

#endif /* API_INC_API_UART_PORT_H_ */
