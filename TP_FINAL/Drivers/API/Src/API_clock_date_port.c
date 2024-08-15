#include "API_clock_date_port.h"

// Define the global variables
RTC_TimeTypeDef sTime = {0}; // Stores time values
RTC_DateTypeDef sDate = {0}; // Stores date values

/**
 * @brief Sets initial time values.
 *
 * Configures `sTime` with predefined initial time values in BCD format.
 */
void CLOCK_DATE_HAL_SetInitialTime(void)
{
	// TODO: should be configurable via UART. Must change CLOCK_DATE_HAL_SetInitialTime function signature to allow inputs.
    sTime.Hours = 0x01;
    sTime.Minutes = 0x20;
    sTime.Seconds = 0x00;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;
}

/**
 * @brief Configures RTC with initial time.
 *
 * Sets the RTC time using `sTime`.
 *
 * @return uint8_t Returns 0 if successful, 1 if an error occurs.
 */
uint8_t CLOCK_DATE_HAL_ConfigInitialTime(void)
{
    HAL_StatusTypeDef res = HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD);
    if (HAL_OK != res)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief Sets initial date values.
 *
 * Configures `sDate` with predefined initial date values in BCD format.
 */
void CLOCK_DATE_HAL_SetInitialDate(void)
{
	// TODO: should be configurable via UART. Must change CLOCK_DATE_HAL_SetInitialDate function signature to allow inputs.
    sDate.WeekDay = RTC_WEEKDAY_MONDAY;
    sDate.Month = RTC_MONTH_AUGUST;
    sDate.Date = 0x10;
    sDate.Year = 0x24;
}

/**
 * @brief Configures RTC with initial date.
 *
 * Sets the RTC date using `sDate`.
 *
 * @return uint8_t Returns 0 if successful, 1 if an error occurs.
 */
uint8_t CLOCK_DATE_HAL_ConfigInitialDate(void)
{
    HAL_StatusTypeDef res = HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD);
    if (HAL_OK != res)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief Retrieves current time and date from RTC.
 *
 * Updates `sTime` and `sDate` with the current time and date from the RTC.
 */
void CLOCK_DATE_HAL_GetTimeDate(void)
{
    // Get the current time from the RTC
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BCD);
    // Get the current date from the RTC
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BCD);
}
