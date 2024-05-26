
/**
 ******************************************************************************
 * @author: Nark
 * @date:   29/03/2024
 ******************************************************************************
**/

#include "stm32f0xx.h"
#include "stm32f0xx_tim.h"
#include "stm32f0xx_exti.h"
#include "stm32f0xx_usart.h"
#include "system_irq.h"
#include "io_cfg.h"

#include "timer.h"

#include "platform.h"
#include "console.h"
#include "hard_timer.h"

#include "app.h"
#include "task_polling.h"
#include "task_list.h"

void nmi_handler() {
	FATAL("SYSTEM", 0x01);
}

void hardfault_handler() {
	FATAL("SYSTEM", 0x02);
}

void mem_manage_handler() {
	FATAL("SYSTEM", 0x03);
}

void bus_fault_handler() {
	FATAL("SYSTEM", 0x04);
}

void usage_fault_handler() {
	FATAL("SYSTEM", 0x05);
}

void svc_handler() {

}

void pendsv_handler() {

}

void wwdg_irq_handler() {

}

void rtc_irq_handler() {

}

void flash_irq_handler() {

}

void rcc_irq_handler() {

}

void exti0_1_irq_handler() {

}


void exti2_3_irq_handler() {

}

void exti3_irq_handler() {
}

void exti4_15_irq_handler() {

}

void dma1_channel1_irq_handler() {

}

void dma1_channel2_3_irq_handler() {

}

void dma1_channel4_5_irq_handler() {

}

void adc_irq_handler() {

}

void tim1_brk_up_trg_com_irq_handler() {

}

void tim1_cc_irq_handler() {

}

void tim3_irq_handler() {

}

void lptim1_irq_handler() {

}

void tim14_irq_handler() {

}

void tim16_irq_handler() {

}

void tim17_irq_handler() {

}

void i2c1_irq_handler() {

}

void spi1_irq_handler() {

}

void system_tick_handler() {
	timer_tick(1);
	system_tick_delay_counter++;
	task_polling_handler();
}

uint8_t buffer_usart1_receive[3];
uint8_t index_get_char = 0;

uint8_t get_remote_data() {
	return buffer_usart1_receive[2];
}

void usart1_irq_handler() {

}

void usart2_irq_handler() {
	volatile uint8_t get_char = usart2_get_char();
	buffer_usart1_receive[index_get_char] = get_char;
	index_get_char++;
	if (index_get_char > 2) {
		index_get_char = 0;
		// APP_PRINT("Buffer uart receive completed\n");
		// APP_PRINT("Buffer[0] %02X\n", buffer_usart1_receive[0]);
		// APP_PRINT("Buffer[1] %02X\n", buffer_usart1_receive[1]);
		// APP_PRINT("Buffer[2] %02X\n", buffer_usart1_receive[2]);
		task_post_pure_msg(TASK_REMOTE_ID, SG_REMOTE_PUSH);
	}
}
