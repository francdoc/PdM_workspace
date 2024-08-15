#include "API_clock_date_port.h"

// Define the global variables
RTC_TimeTypeDef sTime = {0}; // Structure to store time values
RTC_DateTypeDef sDate = {0}; // Structure to store date values

void CLOCK_DATE_HAL_SetInitialTime(void)
{
    // Set initial time values (in BCD format)
    sTime.Hours = 0x01;
    sTime.Minutes = 0x20;
    sTime.Seconds = 0x00;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;
}

uint8_t CLOCK_DATE_HAL_ConfigInitialTime(void)
{
    HAL_StatusTypeDef res = HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD);
    if (HAL_OK != res)
    {
        return 1;
    }
    return 0;
}

void CLOCK_DATE_HAL_SetInitialDate(void)
{
    // Set initial date values (in BCD format)
    sDate.WeekDay = RTC_WEEKDAY_MONDAY;
    sDate.Month = RTC_MONTH_AUGUST;
    sDate.Date = 0x10;
    sDate.Year = 0x24;
}

uint8_t CLOCK_DATE_HAL_ConfigInitialDate(void)
{
    HAL_StatusTypeDef res = HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD);
    if (HAL_OK != res)
    {
        return 1;
    }
    return 0;
}

void CLOCK_DATE_HAL_GetTimeDate(void)
{
    // Get the current time from the RTC
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BCD);

    // Get the current date from the RTC
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BCD);
}
