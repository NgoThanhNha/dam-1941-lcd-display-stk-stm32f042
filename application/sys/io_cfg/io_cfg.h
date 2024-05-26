/**
 ******************************************************************************
 * @author: Nark
 * @date:   29/03/2024
 ******************************************************************************
**/

#ifndef __IO_CFG_H__
#define __IO_CFG_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

/*-----------------------------------------------------------------*/
/*                         ssd1306 pin map                         */
/*-----------------------------------------------------------------*/
#define SSD1306_CLK_IO_PORT             (GPIOA)
#define SSD1306_CLK_IO_PIN              (GPIO_Pin_9)
#define SSD1306_CLK_IO_CLOCK            (RCC_AHBPeriph_GPIOA)

#define SSD1306_DATA_IO_PORT            (GPIOA)
#define SSD1306_DATA_IO_PIN             (GPIO_Pin_10)
#define SSD1306_DATA_IO_CLOCK           (RCC_AHBPeriph_GPIOA)

/*-----------------------------------------------------------------*/
/*                         buttons pin map                         */
/*-----------------------------------------------------------------*/
#define BUTTON_PWR_IO_PIN				(GPIO_Pin_4)
#define BUTTON_PWR_IO_PORT				(GPIOA)
#define BUTTON_PWR_IO_CLOCK			    (RCC_AHBPeriph_GPIOA)

#define BUTTON_MODE_IO_PIN				(GPIO_Pin_7)
#define BUTTON_MODE_IO_PORT				(GPIOA)
#define BUTTON_MODE_IO_CLOCK			(RCC_AHBPeriph_GPIOA)

#define BUTTON_DOWN_IO_PIN				(GPIO_Pin_6)
#define BUTTON_DOWN_IO_PORT				(GPIOA)
#define BUTTON_DOWN_IO_CLOCK			(RCC_AHBPeriph_GPIOA)

#define BUTTON_UP_IO_PIN				(GPIO_Pin_5)
#define BUTTON_UP_IO_PORT				(GPIOA)
#define BUTTON_UP_IO_CLOCK			    (RCC_AHBPeriph_GPIOA)

/*-----------------------------------------------------------------*/
/*                        led life pin map                         */ 
/*-----------------------------------------------------------------*/
#define LED_LIFE_IO_PORT                (GPIOA)
#define LED_LIFE_IO_PIN                 (GPIO_Pin_0)
#define LED_LIFE_IO_CLOCK               (RCC_AHBPeriph_GPIOA)

/*-----------------------------------------------------------------*/
/*                         relay pin map                           */
/*-----------------------------------------------------------------*/
#define RELAY_IO_PIN				    (GPIO_Pin_1)
#define RELAY_IO_PORT				    (GPIOA)
#define RELAY_IO_CLOCK			        (RCC_AHBPeriph_GPIOA)

/*-----------------------------------------------------------------*/
/*                         usart1 pin map                          */
/*-----------------------------------------------------------------*/
#define CONSOLE_GPIO_PORT                (GPIOA)
#define CONSOLE_GPIO_CLOCK               (RCC_AHBPeriph_GPIOA)
#define CONSOLE_CLOCK                    (RCC_APB1Periph_USART2)
#define CONSOLE_TX_PIN                   (GPIO_Pin_2)
#define CONSOLE_RX_PIN                   (GPIO_Pin_3)

/*-----------------------------------------------------------------*/
/*                       ssd1306 io functions                      */
/*-----------------------------------------------------------------*/
extern void ssd1306_clk_init();
extern void ssd1306_data_init();
extern void ssd1306_clk_digital_write_low();
extern void ssd1306_clk_digital_write_high();
extern void ssd1306_data_digital_write_low();
extern void ssd1306_data_digital_write_high();

/* button functions */
extern uint8_t button_pwr_read();
extern uint8_t button_mode_read();
extern uint8_t button_up_read();
extern uint8_t button_down_read();

/* led life functions */
extern void led_life_on();
extern void led_life_off();

/* relay functions */
extern void relay_on();
extern void relay_off();

/* usart1 functions */
extern void usart2_init(uint32_t usart1_speed);
extern void usart2_put_char(uint8_t _char);
extern uint8_t usart2_get_char();

/* io initialize */
extern void io_init();

#ifdef __cplusplus
}
#endif

#endif /* __IO_CFG_H__ */