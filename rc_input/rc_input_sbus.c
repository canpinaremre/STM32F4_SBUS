/*
 * @Author: canpinaremre
 * Purpose: To read RC SBUS data
 * Language:  C
 */
#include <lib/rc_input/rc_input_sbus.h>

uint8_t RC_READ_SBUS(UART_HandleTypeDef *huart,SBUS *sbus) {

	HAL_UART_Receive_DMA(huart, sbus->sbus_msg_bytes, 25);

	if (sbus->sbus_msg_bytes[0] != 0x0F) {
		//Error out of sync
		sbus->error_cnt++;
		if (sbus->error_cnt > SBUS_ERROR_CNT) {
			sbus->error = 1;
		}
		return 0;
	}

	sbus->error = 0;
	sbus->error_cnt = 0;
	sbus->frame_lost = 0;
	sbus->failsafe = 0;


		sbus->PWM_US_RC_CH[0] = (((uint16_t) sbus->sbus_msg_bytes[1])
				| ((uint16_t) sbus->sbus_msg_bytes[2] << 8)) & 0x07FF;
		sbus->PWM_US_RC_CH[1] = (((uint16_t) sbus->sbus_msg_bytes[2] >> 3)
				| ((uint16_t) sbus->sbus_msg_bytes[3] << 5)) & 0x07FF;
		sbus->PWM_US_RC_CH[2] = (((uint16_t) sbus->sbus_msg_bytes[3] >> 6)
				| ((uint16_t) sbus->sbus_msg_bytes[4] << 2)
				| ((uint16_t) sbus->sbus_msg_bytes[5] << 10)) & 0x07FF;
		sbus->PWM_US_RC_CH[3] = (((uint16_t) sbus->sbus_msg_bytes[5] >> 1)
				| ((uint16_t) sbus->sbus_msg_bytes[6] << 7)) & 0x07FF;
		sbus->PWM_US_RC_CH[4] = (((uint16_t) sbus->sbus_msg_bytes[6] >> 4)
				| ((uint16_t) sbus->sbus_msg_bytes[7] << 4)) & 0x07FF;
		sbus->PWM_US_RC_CH[5] = (((uint16_t) sbus->sbus_msg_bytes[7] >> 7)
				| ((uint16_t) sbus->sbus_msg_bytes[8] << 1)
				| ((uint16_t) sbus->sbus_msg_bytes[9] << 9)) & 0x07FF;
		sbus->PWM_US_RC_CH[6] = (((uint16_t) sbus->sbus_msg_bytes[9] >> 2)
				| ((uint16_t) sbus->sbus_msg_bytes[10] << 6)) & 0x07FF;
		sbus->PWM_US_RC_CH[7] = (((uint16_t) sbus->sbus_msg_bytes[10] >> 5)
				| ((uint16_t) sbus->sbus_msg_bytes[11] << 3)) & 0x07FF;
		sbus->PWM_US_RC_CH[8] = (((uint16_t) sbus->sbus_msg_bytes[12])
				| ((uint16_t) sbus->sbus_msg_bytes[13] << 8)) & 0x07FF;
		sbus->PWM_US_RC_CH[9] = (((uint16_t) sbus->sbus_msg_bytes[13] >> 3)
				| ((uint16_t) sbus->sbus_msg_bytes[14] << 5)) & 0x07FF;
		sbus->PWM_US_RC_CH[10] = (((uint16_t) sbus->sbus_msg_bytes[14] >> 6)
				| ((uint16_t) sbus->sbus_msg_bytes[15] << 2)
				| ((uint16_t) sbus->sbus_msg_bytes[16] << 10)) & 0x07FF;
		sbus->PWM_US_RC_CH[11] = (((uint16_t) sbus->sbus_msg_bytes[16] >> 1)
				| ((uint16_t) sbus->sbus_msg_bytes[17] << 7)) & 0x07FF;
		sbus->PWM_US_RC_CH[12] = (((uint16_t) sbus->sbus_msg_bytes[17] >> 4)
				| ((uint16_t) sbus->sbus_msg_bytes[18] << 4)) & 0x07FF;
		sbus->PWM_US_RC_CH[13] = (((uint16_t) sbus->sbus_msg_bytes[18] >> 7)
				| ((uint16_t) sbus->sbus_msg_bytes[19] << 1)
				| ((uint16_t) sbus->sbus_msg_bytes[20] << 9)) & 0x07FF;
		sbus->PWM_US_RC_CH[14] = (((uint16_t) sbus->sbus_msg_bytes[20] >> 2)
				| ((uint16_t) sbus->sbus_msg_bytes[21] << 6)) & 0x07FF;
		sbus->PWM_US_RC_CH[15] = (((uint16_t) sbus->sbus_msg_bytes[21] >> 5)
				| ((uint16_t) sbus->sbus_msg_bytes[22] << 3)) & 0x07FF;

	for (uint8_t i = 0; i <= SBUS_MAX_CHANNEL_CNT; i++) {
		sbus->PWM_US_RC_CH[i] = MAP(sbus->PWM_US_RC_CH[i], SBUS_IN_MIN_PWM,
				SBUS_IN_MAX_PWM, SBUS_OUT_MIN_PWM, SBUS_OUT_MAX_PWM);
	}

	if (sbus->sbus_msg_bytes[23] & (1 << 2)) {
		sbus->frame_lost = 1;
	}

	if (sbus->sbus_msg_bytes[23] & (1 << 3)) {
		sbus->failsafe = 1;
	}

#ifdef SBUS_ARM_DISARM_STICKS
	if (sbus->PWM_US_RC_CH[SBUS_THROTTLE_CHANNEL]
			<= (1000 + SBUS_ARM_DISARM_TOLARANCE)) {
		if (sbus->PWM_US_RC_CH[SBUS_YAW_CHANNEL]
				<= (1000 + SBUS_ARM_DISARM_TOLARANCE)) {
			sbus->disarm_cnt++;
			if (sbus->disarm_cnt >= SBUS_DISARM_CNT) {
				sbus->disarm = 1;
			}
		} else {
			sbus->disarm_cnt = 0;
			sbus->disarm = 0;
		}
		if (sbus->PWM_US_RC_CH[SBUS_YAW_CHANNEL]
				>= (2000 - SBUS_ARM_DISARM_TOLARANCE)) {
			sbus->arm_cnt++;
			if (sbus->arm_cnt >= SBUS_ARM_CNT) {
				sbus->arm = 1;
			}
		} else {
			sbus->arm_cnt = 0;
			sbus->arm = 0;
		}

	} else {
		sbus->disarm_cnt = 0;
		sbus->arm_cnt = 0;
		sbus->arm = 0;
		sbus->disarm = 0;
	}
#endif

	return 1;
}

uint16_t MAP(uint16_t au32_IN, uint16_t au32_INmin, uint16_t au32_INmax,
		uint16_t au32_OUTmin, uint16_t au32_OUTmax) {
	return ((((au32_IN - au32_INmin) * (au32_OUTmax - au32_OUTmin))
			/ (au32_INmax - au32_INmin)) + au32_OUTmin);
}
