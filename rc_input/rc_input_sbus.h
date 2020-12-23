/*
 * @Author: canpinaremre
 * Purpose: To read RC SBUS data
 * Language:  C
 */
#include "stm32f4xx_hal.h"

#define SBUS_MAX_CHANNEL_CNT 6
#define SBUS_IN_MIN_PWM 172
#define SBUS_IN_MAX_PWM 1811
#define SBUS_OUT_MIN_PWM 1000
#define SBUS_OUT_MAX_PWM 2000
#define SBUS_ERROR_CNT 10

/* Define if you want to use ARM/DISARM with sticks*/
#define SBUS_ARM_DISARM_STICKS

#ifdef SBUS_ARM_DISARM_STICKS
#define SBUS_DISARM_CNT 10
#define SBUS_ARM_CNT 10
#define SBUS_ARM_DISARM_TOLARANCE 30
#define SBUS_THROTTLE_CHANNEL 0
#define SBUS_YAW_CHANNEL 3
#endif


typedef struct{
	uint16_t PWM_US_RC_CH[16];
	uint8_t frame_lost;
	uint8_t failsafe;
	uint8_t arm;
	uint8_t disarm;
	uint8_t error;
	uint8_t sbus_msg_bytes[25];
	uint8_t error_cnt;
#ifdef SBUS_ARM_DISARM_STICKS
	uint8_t arm_cnt;
	uint8_t disarm_cnt;
#endif

}SBUS;

uint8_t RC_READ_SBUS(UART_HandleTypeDef *huart,SBUS *sbus);
uint16_t MAP(uint16_t au32_IN, uint16_t au32_INmin, uint16_t au32_INmax, uint16_t au32_OUTmin, uint16_t au32_OUTmax);
