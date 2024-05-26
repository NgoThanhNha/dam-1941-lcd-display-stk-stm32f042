
#include "soft_i2c.h"

/* user drivers */
#include "hard_timer.h"
#include "io_cfg.h"

/* software i2c protocol functions */
void i2c_start() {
	ssd1306_clk_digital_write_high();
	ssd1306_data_digital_write_high();
	ssd1306_data_digital_write_low();
	ssd1306_clk_digital_write_low();
}

void i2c_stop() {
	ssd1306_clk_digital_write_low();
	ssd1306_data_digital_write_low();	
	ssd1306_clk_digital_write_high();
	ssd1306_data_digital_write_high();
}

void i2c_write_byte(uint8_t u8data) {
	for(uint8_t i = 0; i < 8; i++) {
        if ((u8data << i) & 0x80){
            ssd1306_data_digital_write_high();
        }
        else {
            ssd1306_data_digital_write_low();
        }
        ssd1306_clk_digital_write_high();
        ssd1306_clk_digital_write_low();
	}
    ssd1306_data_digital_write_high();
	ssd1306_clk_digital_write_high();

	ssd1306_clk_digital_write_low();
}