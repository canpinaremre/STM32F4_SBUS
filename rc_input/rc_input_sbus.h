/*
 * @Author: canpinaremre
 * Purpose: To read RC SBUS data
 * Language:  C
 */
#include "stm32f4xx_hal.h"

#define SBUS_ERROR_CNT 10

typedef struct{
	uint16_t PWM_US_RC_CH[16];
	uint8_t frame_lost;
	uint8_t failsafe;
	uint8_t arm;
	uint8_t disarm;
	uint8_t error;
	uint8_t sbus_msg_bytes[25];
	uint8_t error_cnt;

}SBUS;

uint8_t RC_READ_SBUS(UART_HandleTypeDef *huart,SBUS *sbus);
