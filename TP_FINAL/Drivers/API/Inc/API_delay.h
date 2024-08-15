#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx_hal.h"

#include "API_delay_port.h"

/* Type Definitions ----------------------------------------------------------*/

typedef uint32_t tick_t; /**< Type definition for the tick count used for delay timing. */
typedef bool bool_t;	 /**< Type definition for boolean values used in delay operations. */

/**
 * @brief  Structure to manage delays.
 * @note   This structure keeps track of the start time, duration, and running status of a delay.
 */
typedef struct
{
	tick_t startTime; /**< The tick value when the delay started. */
	tick_t duration;  /**< Duration of the delay in ticks (milliseconds). */
	bool_t running;	  /**< Indicates whether the delay is currently running. */
} delay_t;

/* Function Prototypes -------------------------------------------------------*/

/**
 * @brief  Initializes a delay structure with the specified duration.
 * @param  delay: Pointer to the delay structure to be initialized.
 * @param  duration: Duration of the delay in ticks (milliseconds).
 * @retval None
 */
void delayInit(delay_t *delay, tick_t duration);

/**
 * @brief  Checks if the specified delay has elapsed.
 * @param  delay: Pointer to the delay structure to be checked.
 * @retval bool_t: Returns true if the delay has elapsed, false otherwise.
 */
bool_t delayRead(delay_t *delay);

/**
 * @brief  Updates the duration of an existing delay.
 * @param  delay: Pointer to the delay structure to be updated.
 * @param  duration: New duration of the delay in ticks (milliseconds).
 * @retval None
 */
void delayWrite(delay_t *delay, tick_t duration);

/**
 * @brief  Checks if the delay is still running.
 * @param  delay: Pointer to the delay structure to be checked.
 * @retval bool_t: Returns true if the delay is still running, false otherwise.
 */
bool_t delayIsRunning(delay_t *delay);

#endif /* API_INC_API_DELAY_H_ */
