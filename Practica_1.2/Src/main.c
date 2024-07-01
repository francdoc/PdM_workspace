/**
 ******************************************************************************
 * @file    UART/UART_Printf/Src/main.c
 * @author  MCD Application Team
 * @brief   This example shows how to retarget the C library printf function
 *          to the UART.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F4xx_HAL_Examples
 * @{
 */

/** @addtogroup UART_Printf
 * @{
 */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define TIMEoN 200  // millis
#define TIMEoFF 200 // millis

/* Definition for LED States */
// NOTE: I could have used BSP_LED_On and BSP_LED_Off functions instead of doing LED_toggle(led, ON) and LED_toggle(led, OFF) inside LED_blink.
#define ON 1
#define OFF 0

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static uint8_t ledState = 0; // 0 = OFF; 1 = ON

/* UART handler declaration */
UART_HandleTypeDef UartHandle;

Led_TypeDef LED_sequence_1[] = {LED1, LED2, LED3};
Led_TypeDef LED_sequence_2[] = {LED3, LED2, LED1};

const uint8_t MAXlED_1 = sizeof(LED_sequence_1) / sizeof(Led_TypeDef); // Total number of elements in vector.
const uint8_t MAXlED_2 = sizeof(LED_sequence_2) / sizeof(Led_TypeDef); // Total number of elements in vector.

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);

void LED_blink(Led_TypeDef led, uint32_t millisOn, uint32_t millisOff);
void SLEEP_millis(uint32_t millis);
void LED_toggle(Led_TypeDef led, uint8_t state);
int BOARD_setup();

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Delays execution for a specified number of milliseconds.
 * @param  millis: The duration of the delay in milliseconds. This parameter is of type uint32_t.
 * @retval None
 */
void SLEEP_millis(uint32_t millis)
{
  if (millis < 0)
  {
    /* Input Error */
    Error_Handler();
  }
  HAL_Delay(millis);
}

/**
 * @brief  Toggles the state of a specified LED if the desired state is different from the current state.
 * @param  led: The LED to be toggled. This parameter is of type Led_TypeDef.
 * @param  state: The desired state of the LED. This parameter is of type uint8_t, where 1 represents ON and 0 represents OFF.
 * @retval None
 */
void LED_toggle(Led_TypeDef led, uint8_t state)
{
  if (state != 0 && state != 1)
  {
    /* Input Error */
    Error_Handler();
  }
  if (state != ledState)
  {
    BSP_LED_Toggle(led);
    ledState = state;
  }
}

/**
 * @brief  Controls the blinking of a specified LED.
 *         Turns the LED on for a specified duration, then off for another specified duration.
 * @param  led: The LED to be controlled. This parameter is of type Led_TypeDef.
 * @param  millisOn: The duration in milliseconds for which the LED remains on.
 * @param  millisOff: The duration in milliseconds for which the LED remains off.
 * @retval None
 */
void LED_blink(Led_TypeDef led, uint32_t millisOn, uint32_t millisOff)
{
  if (millisOn < 0 || millisOff < 0)
  {
    /* Input Error */
    Error_Handler();
  }
  LED_toggle(led, ON);
  SLEEP_millis(millisOn);
  LED_toggle(led, OFF);
  SLEEP_millis(millisOff);
}

/**
 * @brief  Blinks a sequence of LEDs.
 * @param  sequence: Array of LEDs to be blinked.
 * @param  length: Number of LEDs in the sequence.
 * @param  millisOn: Duration in milliseconds that a LED is ON.
 * @param  millisOff: Duration in milliseconds that a LED is OFF.
 * @retval None
 */
void LED_sequence_blink(Led_TypeDef *sequence, uint8_t length, uint32_t millisOn, uint32_t millisOff)
{
  for (uint8_t index = 0; index < length; index++)
  {
    LED_blink(sequence[index], millisOn, millisOff);
  }
}

/**
 * @brief  Returns the state of user button.
 * @retval uint32_t: 0 if user button is not pressed, 1 if user button is pressed.
 */
uint32_t get_btn_change(void)
{
  return BSP_PB_GetState(BUTTON_USER);
}

/**
 * @brief  Initializes the STM32F4xx board, the HAL, system clock configuration and BSP LEDs.
 * @param  None
 * @retval int  Returns 0 if initialization is OK.
 */
int BOARD_setup()
{
  /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user
         can eventually implement his proper time base source (a general purpose
         timer for example or other time source), keeping in mind that Time base
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */

  HAL_Init();

  /* Configure the system clock to 180 MHz */
  SystemClock_Config();

  /* Initialize BSP Led for LED1, LED2, LED3 */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);

  /* Initialize BSP PB for BUTTON_USER */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

  return 0;
}

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void)
{
  int error = BOARD_setup();

  if (error != 0)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* Infinite loop */
  while (1)
  {
    if (!get_btn_change())
    {
      LED_sequence_blink(LED_sequence_1, MAXlED_1, TIMEoN, TIMEoFF);
    }
    else
    {
      LED_sequence_blink(LED_sequence_2, MAXlED_2, TIMEoN, TIMEoFF);
    }
  }
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 180000000
 *            HCLK(Hz)                       = 180000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 4
 *            APB2 Prescaler                 = 2
 *            HSE Frequency(Hz)              = 8000000
 *            PLL_M                          = 8
 *            PLL_N                          = 360
 *            PLL_P                          = 2
 *            PLL_Q                          = 7
 *            PLL_R                          = 2
 *            VDD(V)                         = 3.3
 *            Main regulator output voltage  = Scale1 mode
 *            Flash Latency(WS)              = 5
 * @param  None
 * @retval None
 */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}
/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void)
{
  /* Turn LED2 on */
  BSP_LED_On(LED2);
  while (1)
  {
  }
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
