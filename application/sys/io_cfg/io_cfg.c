/**
 ******************************************************************************
 * @author: Nark
 * @date:   29/03/2024
 ******************************************************************************
**/

#include "io_cfg.h"

#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_misc.h"

#include "xprintf.h"

/* ssd1306 ports */
void ssd1306_clk_init() {
    GPIO_InitTypeDef    GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(SSD1306_CLK_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = SSD1306_CLK_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(SSD1306_CLK_IO_PORT, &GPIO_InitStructure);
}

void ssd1306_data_init() {
    GPIO_InitTypeDef    GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(SSD1306_DATA_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = SSD1306_DATA_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(SSD1306_DATA_IO_PORT, &GPIO_InitStructure);
}

void ssd1306_clk_digital_write_low() {
	GPIO_ResetBits(SSD1306_CLK_IO_PORT, SSD1306_CLK_IO_PIN);
}

void ssd1306_clk_digital_write_high() {
	GPIO_SetBits(SSD1306_CLK_IO_PORT, SSD1306_CLK_IO_PIN);
}

void ssd1306_data_digital_write_low() {
	GPIO_ResetBits(SSD1306_DATA_IO_PORT, SSD1306_DATA_IO_PIN);
}

void ssd1306_data_digital_write_high() {
	GPIO_SetBits(SSD1306_DATA_IO_PORT, SSD1306_DATA_IO_PIN);
}

void button_pwr_init() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(BUTTON_PWR_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = BUTTON_PWR_IO_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(BUTTON_PWR_IO_PORT, &GPIO_InitStructure);
}

void button_mode_init() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(BUTTON_MODE_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = BUTTON_MODE_IO_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(BUTTON_MODE_IO_PORT, &GPIO_InitStructure);
}

void button_up_init() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(BUTTON_UP_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = BUTTON_UP_IO_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(BUTTON_UP_IO_PORT, &GPIO_InitStructure);
}

void button_down_init() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(BUTTON_DOWN_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = BUTTON_DOWN_IO_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(BUTTON_DOWN_IO_PORT, &GPIO_InitStructure);
}

uint8_t button_pwr_read() {
	return (GPIO_ReadInputDataBit(BUTTON_PWR_IO_PORT, BUTTON_PWR_IO_PIN));
}

uint8_t button_mode_read() {
	return (GPIO_ReadInputDataBit(BUTTON_MODE_IO_PORT, BUTTON_MODE_IO_PIN));
}

uint8_t button_up_read() {
	return (GPIO_ReadInputDataBit(BUTTON_UP_IO_PORT, BUTTON_UP_IO_PIN));
}

uint8_t button_down_read() {
	return (GPIO_ReadInputDataBit(BUTTON_DOWN_IO_PORT, BUTTON_DOWN_IO_PIN));
}

void led_life_init() {
	GPIO_InitTypeDef    GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(LED_LIFE_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = LED_LIFE_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(LED_LIFE_IO_PORT, &GPIO_InitStructure);
}

void led_life_on() {
	GPIO_ResetBits(LED_LIFE_IO_PORT, LED_LIFE_IO_PIN);
}

void led_life_off() {
	GPIO_SetBits(LED_LIFE_IO_PORT, LED_LIFE_IO_PIN);
}

void relay_init() {
	GPIO_InitTypeDef    GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(RELAY_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = RELAY_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(RELAY_IO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(RELAY_IO_PORT, RELAY_IO_PIN);
}

void relay_on() {
	GPIO_ResetBits(RELAY_IO_PORT, RELAY_IO_PIN);
}

void relay_off() {
	GPIO_SetBits(RELAY_IO_PORT, RELAY_IO_PIN);
}

void usart2_init(uint32_t baud_speed) {
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHBPeriphClockCmd(CONSOLE_GPIO_CLOCK, ENABLE);
	GPIO_PinAFConfig(CONSOLE_GPIO_PORT, GPIO_PinSource2, GPIO_AF_1);
	GPIO_PinAFConfig(CONSOLE_GPIO_PORT, GPIO_PinSource3, GPIO_AF_1);

	GPIO_InitStructure.GPIO_Pin = CONSOLE_TX_PIN | CONSOLE_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(CONSOLE_GPIO_PORT, &GPIO_InitStructure);

	RCC_APB1PeriphClockCmd(CONSOLE_CLOCK, ENABLE);
	USART_InitStructure.USART_BaudRate = baud_speed;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);

	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ClearITPendingBit(USART2, USART_IT_RXNE | USART_IT_TXE);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART2, ENABLE);

	NVIC_SetPriority(USART2_IRQn, 0);
	NVIC_EnableIRQ(USART2_IRQn);
}

void usart2_put_char(uint8_t _char) {

	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);

	/* put transnission data */
	USART_SendData(USART2, (uint8_t)_char);

	/* wait transmission completed */
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);

}

uint8_t usart2_get_char() {
	volatile uint8_t c;

	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET) {
		c = (uint8_t)USART_ReceiveData(USART2);
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}

	return c;
}

void io_init() {
	/* ssd1306 io init */
    ssd1306_clk_init();
    ssd1306_data_init();

	/* button io init */
	button_pwr_init();
	button_mode_init();
	button_up_init();
	button_down_init();

	/* relay init */
	relay_init();

	/* led life init */
	led_life_init();
}


