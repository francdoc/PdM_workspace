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

/* Private typedef -----------------------------------------------------------*/
typedef enum {
  BUTTON_UP,
  BUTTON_FALLING,
  BUTTON_DOWN,
  BUTTON_RAISING,
} debounceState_t;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define BUTTONled LED1

/* Private variables ---------------------------------------------------------*/
uint32_t DELAYsys = 5;       // Super loop delay in milliseconds.
uint32_t DELAYdebounce = 40; // Debounce delay time in milliseconds.

delay_t delaySys;
delay_t delayDebounce;

debounceState_t currentButtonState;

/* UART handler declaration */
UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);

void buttonPressed();
void buttonReleased();

void debounceFSM_init();
void debounceFSM_update();

uint32_t getBtnState();

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  When called this function turns ON LED to indicate that the button is being pressed.
 * @retval None.
 */
void buttonPressed() {
	BSP_LED_On(BUTTONled);
}

/**
 * @brief  When called this function turns OFF LED to indicate that the button was released.
 * @retval None.
 */
void buttonReleased() {
	BSP_LED_Off(BUTTONled);
}

/**
 * @brief  Returns the state of user button.
 * @retval uint32_t: 0 if user button is not pressed, 1 if user button is
 * pressed.
 */
uint32_t getBtnState(void) {
	return BSP_PB_GetState(BUTTON_USER);
}

/**
 * @brief  Initializes FSM with initial state BUTTON_UP.
 * @retval None.
 */
void debounceFSM_init() {
	currentButtonState = BUTTON_UP;
    delayInit(&delayDebounce, DELAYdebounce);
}

/**
 * @brief  Updates the state of the button debounce finite state machine (FSM).
 *
 * This function must be called repeatedly to manage the transitions and states
 * of the button debounce FSM. It handles four states: BUTTON_UP, BUTTON_FALLING,
 * BUTTON_DOWN, and BUTTON_RAISING, ensuring that button presses and releases
 * are debounced properly.
 *
 * The debounceFSM_update function uses a delay mechanism to confirm state transitions.
 * When a button press or release is detected, it waits for a specified debounce time
 * to confirm the action, thus avoiding false triggers due to noise or quick transitions.
 *
 * @retval None
 */
void debounceFSM_update() {
  switch (currentButtonState) {
  case BUTTON_UP:
    if (getBtnState()) {
      currentButtonState = BUTTON_FALLING;
    }
    break;
  case BUTTON_FALLING:
    if (delayRead(&delayDebounce)) {
      if (getBtnState()) {
        buttonPressed();
        currentButtonState = BUTTON_DOWN;
      } else {
        currentButtonState = BUTTON_UP;
      }
    }
    break;
  case BUTTON_DOWN:
    if (!getBtnState()) {
      currentButtonState = BUTTON_RAISING;
    }
    break;
  case BUTTON_RAISING:
    if (delayRead(&delayDebounce)) {
      if (!getBtnState()) {
        buttonReleased();
        currentButtonState = BUTTON_UP;
      } else {
        currentButtonState = BUTTON_DOWN;
      }
    }
    break;
  default:
    Error_Handler();
  }
}

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void) {
  /* STM32F4xx HAL library initialization:
     - Configure the Flash prefetch
     - Systick timer is configured by default as source of time base, but user
           can eventually implement his proper time base source (a general
     purpose timer for example or other time source), keeping in mind that Time
     base duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
           handled in milliseconds basis.
     - Set NVIC Group Priority to 4
     - Low Level Initialization
   */
  HAL_Init();

  /* Configure the system clock to 180 MHz */
  SystemClock_Config();

  /* Initialize BSP PB for BUTTON_USER */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

  /* Initialize BSP LEDs */
  BSP_LED_Init(BUTTONled);
  BSP_LED_Init(LED2);

  debounceFSM_init();

  delayInit(&delaySys, DELAYsys);

  /* Infinite loop */
  while (1) {
    if (delayRead(&delaySys)) {
      debounceFSM_update();
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
  static void SystemClock_Config(void) {
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    /* Enable Power Control clock */
    __HAL_RCC_PWR_CLK_ENABLE();

    /* The voltage scaling allows optimizing the power consumption when the
     device is clocked below the maximum system frequency, to update the voltage
     scaling value regarding system frequency refer to product datasheet.  */
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
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
      /* Initialization Error */
      Error_Handler();
    }

    if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
      /* Initialization Error */
      Error_Handler();
    }

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                                   RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
      /* Initialization Error */
      Error_Handler();
    }
  }
  /**
   * @brief  This function is executed in case of error occurrence.
   * @param  None
   * @retval None
   */
  static void Error_Handler(void) {
    /* Turn LED2 on */
    BSP_LED_On(LED2);
    while (1) {
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
  void assert_failed(uint8_t * file, uint32_t line) {
    /* User can add his own implementation to report the file name and line
     number, ex: printf("Wrong parameters value: file %s on line %d\r\n", file,
     line) */

    /* Infinite loop */
    while (1) {
    }
  }
#endif

  /**
   * @}
   */

  /**
   * @}
   */

  /************************ (C) COPYRIGHT STMicroelectronics *****END OF
   * FILE****/
