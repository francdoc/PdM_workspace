#include "API_delay_port.h"

/**
 * @brief  Retrieves the current system tick value in milliseconds.
 * @note   This function returns the value of the system tick counter maintained by the HAL,
 *         which increments every millisecond. It is typically used for implementing delays or measuring time intervals.
 * @param  None
 * @retval uint32_t: The current tick value in milliseconds.
 */
uint32_t DELAY_HAL_GetTick(void)
{
    return HAL_GetTick();
}
