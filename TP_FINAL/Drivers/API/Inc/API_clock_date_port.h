#ifndef API_INC_API_CLOCK_DATE_PORT_H_
#define API_INC_API_CLOCK_DATE_PORT_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h" /* <- BSP include */

// Declarations of global variables
extern RTC_TimeTypeDef sTime;
extern RTC_DateTypeDef sDate;
extern RTC_HandleTypeDef hrtc;

void CLOCK_DATE_HAL_SetInitialTime(void);
uint8_t CLOCK_DATE_HAL_ConfigInitialTime(void);
void CLOCK_DATE_HAL_SetInitialDate(void);
uint8_t CLOCK_DATE_HAL_ConfigInitialDate(void);
void CLOCK_DATE_HAL_GetTimeDate(void);

#endif /* API_INC_API_CLOCK_DATE_PORT_H_ */
