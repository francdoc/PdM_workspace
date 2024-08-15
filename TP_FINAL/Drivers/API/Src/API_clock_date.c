#ifndef API_SRC_API_CLOCK_DATE_C_
#define API_SRC_API_CLOCK_DATE_C_

#include "API_clock_date.h"

/**
 * @brief  Error handler for the clock and date functions.
 *         This function enters an infinite loop, indicating a critical error.
 * @param  None
 * @retval None
 */
void Clock_Error_Handler(void)
{
    while (1)
    {
        // Stay in an infinite loop to indicate an error
    }
}

/**
 * @brief  Initializes the RTC clock with a predefined time and date.
 * @param  None
 * @retval None
 */
void ClockInit(void)
{
    CLOCK_DATE_HAL_SetInitialTime();

    // Set the RTC time, check for errors
    if (OK != CLOCK_DATE_HAL_ConfigInitialTime())
    {
        Clock_Error_Handler();
    }

    CLOCK_DATE_HAL_SetInitialDate();

    // Set the RTC date, check for errors
    if (OK != CLOCK_DATE_HAL_ConfigInitialDate())
    {
        Clock_Error_Handler();
    }
}

/**
 * @brief  Updates the global time and date variables with the current RTC time and date.
 * @param  None
 * @retval None
 */
void ClockUpdateTimeDate(void)
{
    CLOCK_DATE_HAL_GetTimeDate();
}

#endif /* API_SRC_API_CLOCK_DATE_C_ */
