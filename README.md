# STM32F4_SBUS
SBUS Reading using HAL Library of STM32F4

Use DMA with UART and use UART inverter for SBUS signal. Because SBUS is a inverted UART signal.

Example:

	SBUS sbus;
	sbus.arm = 0;
	sbus.disarm = 0;

	if (RC_READ_SBUS(&huart1,&sbus)) {

			sendString("CH1:", &huart2);
			
			sendInt(sbus.PWM_US_RC_CH[0], &huart2);
			
			sendString("CH2:", &huart2);
			
			sendInt(sbus.PWM_US_RC_CH[1], &huart2);
			
			sendString("CH3:", &huart2);
			
			sendInt(sbus.PWM_US_RC_CH[2], &huart2);
			
			sendString("CH4:", &huart2);
			
			sendInt(sbus.PWM_US_RC_CH[3], &huart2);
			
			sendString("CH5:", &huart2);
			
			sendInt(sbus.PWM_US_RC_CH[4], &huart2);
			
			sendString("CH6:", &huart2);
			
			sendInt(sbus.PWM_US_RC_CH[5], &huart2);
			
			sendString("CH7:", &huart2);
			
			sendInt(sbus.PWM_US_RC_CH[6], &huart2);
			
			sendString("CH8:", &huart2);
			
			sendInt(sbus.PWM_US_RC_CH[7], &huart2);
			
			sendString("CH9:", &huart2);
			
			sendInt(sbus.PWM_US_RC_CH[8], &huart2);
			
			sendString("CH10:", &huart2);
			
			sendInt(sbus.PWM_US_RC_CH[9], &huart2);

			if (sbus.failsafe) {
				sendString("failsafe\r\n", &huart2);
			}
			if (sbus.frame_lost) {
				sendString("frame_lost\r\n", &huart2);
			}

		}
		if (sbus.error) {
			sendString("Connection Error!!\r\n", &huart2);
		}
