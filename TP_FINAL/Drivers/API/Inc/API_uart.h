#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

/* Includes ------------------------------------------------------------------*/
#include "API_uart_port.h"

/* Exported types ------------------------------------------------------------*/
#ifndef BOOL_TYPE_DEFINITIOON_
#define BOOL_TYPE_DEFINITIOON_

typedef bool bool_t;

#define OK 0
#define ERROR 1

#endif // BOOL_TYPE_DEFINITIOON_

/* Exported constants --------------------------------------------------------*/
#define MAXbUFFER 256

/* Exported functions ------------------------------------------------------- */
bool_t uartInit(void);
void uartSendString(uint8_t *pstring);
void uartSendStringSize(uint8_t *pstring, uint16_t size);
void uartReceiveStringSize(uint8_t *pstring, uint16_t size);
int uartReceiveStringAndParseDate(uint8_t *pstring, uint16_t size, RTC_TimeTypeDef *sTime, RTC_DateTypeDef *sDate);
#endif /* API_INC_API_UART_H_ */
