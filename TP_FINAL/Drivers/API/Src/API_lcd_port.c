/* Includes ------------------------------------------------------------------*/
#include "API_lcd_port.h"

/* Public functions ----------------------------------------------------------*/

/**
 * @brief  Sends a byte of data to the LCD via the I2C interface.
 * @note   This function transmits the provided value to the LCD device over the I2C bus. It uses the I2C handle `hi2c1`
 *         and assumes that the LCD is configured to operate with the provided I2C address.
 * @param  valor: The byte of data to be transmitted to the LCD.
 * @retval None
 */
void LCD_HAL_I2C_Write(uint8_t valor)
{
  HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDRESS << LCD_WRITE_CMD, &valor, sizeof(valor), HAL_MAX_DELAY);
}

/**
 *  @brief  Provides a delay for a specified number of milliseconds.
 * @param  delay: The amount of time, in milliseconds, to delay.
 * @retval None
 */
void LCD_HAL_Delay(uint32_t delay)
{
  HAL_Delay(delay);
}

/**
 * @brief  Toggles the state of the specified LED.
 * @param  Led: Specifies the LED to be toggled. This parameter can be one of the LED identifiers defined in the board support package (BSP), such as `LED2`, `LED3`, etc.
 * @retval None
 */
void LCD_HAL_Blink(Led_TypeDef Led)
{
  BSP_LED_Toggle(Led);
}
