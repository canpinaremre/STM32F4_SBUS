/*
 * @Author: canpinaremre
 * Purpose: To read RC SBUS data
 * Language:  C
 */

#include "stm32f4xx_hal.h"
#include "main.h"

uint8_t sbus_msg_bytes[25];

uint8_t RC_READ_SBUS(UART_HandleTypeDef *huart,uint16_t *PWM_US_RC_CH,uint8_t *frame_lost,uint8_t *failsafe);
