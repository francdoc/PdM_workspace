#ifndef API_INC_API_DELAY_PORT_H_
#define API_INC_API_DELAY_PORT_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"

/**
 * @brief  Retrieves the current tick value in milliseconds.
 * @note   This function provides the system tick value, which is typically used for timing operations.
 *         The tick value is incremented every millisecond by the HAL.
 * @param  None
 * @retval uint32_t: The current tick value in milliseconds.
 */
uint32_t DELAY_HAL_GetTick();

#endif /* API_INC_API_DELAY_PORT_H_ */
