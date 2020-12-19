/*
 * @Author: canpinaremre
 * Purpose: To read RC SBUS data
 * Language:  C
 */


#include <lib/rc_input/rc_input_sbus.h>


uint8_t RC_READ_SBUS(UART_HandleTypeDef *huart,uint16_t *PWM_US_RC_CH,uint8_t *frame_lost,uint8_t *failsafe) {


		HAL_UART_Receive_DMA(huart, sbus_msg_bytes, 25);

		if (sbus_msg_bytes[0] != 0x0F) {
			//Error out of sync

			return 0;

		}

//		digital_channel_1 = 0;
//		digital_channel_2 = 0;
		*frame_lost = 0;
		*failsafe = 0;
		PWM_US_RC_CH[0] = (((uint16_t) sbus_msg_bytes[1])
				| ((uint16_t) sbus_msg_bytes[2] << 8)) & 0x07FF;
		PWM_US_RC_CH[1] = (((uint16_t) sbus_msg_bytes[2] >> 3)
				| ((uint16_t) sbus_msg_bytes[3] << 5)) & 0x07FF;
		PWM_US_RC_CH[2] = (((uint16_t) sbus_msg_bytes[3] >> 6)
				| ((uint16_t) sbus_msg_bytes[4] << 2)
				| ((uint16_t) sbus_msg_bytes[5] << 10)) & 0x07FF;
		PWM_US_RC_CH[3] = (((uint16_t) sbus_msg_bytes[5] >> 1)
				| ((uint16_t) sbus_msg_bytes[6] << 7)) & 0x07FF;
		PWM_US_RC_CH[4] = (((uint16_t) sbus_msg_bytes[6] >> 4)
				| ((uint16_t) sbus_msg_bytes[7] << 4)) & 0x07FF;
		PWM_US_RC_CH[5] = (((uint16_t) sbus_msg_bytes[7] >> 7)
				| ((uint16_t) sbus_msg_bytes[8] << 1)
				| ((uint16_t) sbus_msg_bytes[9] << 9)) & 0x07FF;
		PWM_US_RC_CH[6] = (((uint16_t) sbus_msg_bytes[9] >> 2)
				| ((uint16_t) sbus_msg_bytes[10] << 6)) & 0x07FF;
		PWM_US_RC_CH[7] = (((uint16_t) sbus_msg_bytes[10] >> 5)
				| ((uint16_t) sbus_msg_bytes[11] << 3)) & 0x07FF;
		PWM_US_RC_CH[8] = (((uint16_t) sbus_msg_bytes[12])
				| ((uint16_t) sbus_msg_bytes[13] << 8)) & 0x07FF;
		PWM_US_RC_CH[9] = (((uint16_t) sbus_msg_bytes[13] >> 3)
				| ((uint16_t) sbus_msg_bytes[14] << 5)) & 0x07FF;
		PWM_US_RC_CH[10] = (((uint16_t) sbus_msg_bytes[14] >> 6)
				| ((uint16_t) sbus_msg_bytes[15] << 2)
				| ((uint16_t) sbus_msg_bytes[16] << 10)) & 0x07FF;
		PWM_US_RC_CH[11] = (((uint16_t) sbus_msg_bytes[16] >> 1)
				| ((uint16_t) sbus_msg_bytes[17] << 7)) & 0x07FF;
		PWM_US_RC_CH[12] = (((uint16_t) sbus_msg_bytes[17] >> 4)
				| ((uint16_t) sbus_msg_bytes[18] << 4)) & 0x07FF;
		PWM_US_RC_CH[13] = (((uint16_t) sbus_msg_bytes[18] >> 7)
				| ((uint16_t) sbus_msg_bytes[19] << 1)
				| ((uint16_t) sbus_msg_bytes[20] << 9)) & 0x07FF;
		PWM_US_RC_CH[14] = (((uint16_t) sbus_msg_bytes[20] >> 2)
				| ((uint16_t) sbus_msg_bytes[21] << 6)) & 0x07FF;
		PWM_US_RC_CH[15] = (((uint16_t) sbus_msg_bytes[21] >> 5)
				| ((uint16_t) sbus_msg_bytes[22] << 3)) & 0x07FF;

//		if (sbus_msg_bytes[23] & (1 << 0)) {
//			digital_channel_1 = 1;
//		}
//
//		if (sbus_msg_bytes[23] & (1 << 1)) {
//			digital_channel_2 = 1;
//		}

		if (sbus_msg_bytes[23] & (1 << 2)) {
			*frame_lost = 1;
		}

		if (sbus_msg_bytes[23] & (1 << 3)) {
			*failsafe = 1;
		}

		return 1;

	}
