/**
 ******************************************************************************
 * @author: Nark
 * @date:   29/03/2024
 ******************************************************************************
**/

#include "ssd1309.h"

/* system drivers */
#include "stm32f0xx.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"

/* user drivers */
#include "hard_timer.h"
#include "io_cfg.h"
#include "soft_i2c.h"

using namespace std;

static unsigned char frame_buffer[frame_buffer_size];

Adafruit_SSD1309::Adafruit_SSD1309():
	Adafruit_GFX(SSD1309_WIDTH, SSD1309_HEIGHT)
{
	render_buffer = 0;
}
Adafruit_SSD1309::~Adafruit_SSD1309()
{

}

void Adafruit_SSD1309::writeCommand(uint8_t _command) {
    i2c_start();
    i2c_write_byte(0x78);
    i2c_write_byte(0x00);
    i2c_write_byte(_command);
    i2c_stop();
}

void Adafruit_SSD1309::writeData(uint8_t _data) {
	i2c_start();
	i2c_write_byte(0x78);
	i2c_write_byte(0x40);
	i2c_write_byte(_data);
	i2c_stop();
}

bool Adafruit_SSD1309::initialize() {
    render_buffer = frame_buffer;
    memset(render_buffer, 0, frame_buffer_size);

	writeCommand(0xAE);//display off
	writeCommand(0x00);//Set Memory Addressing Mode
	writeCommand(0x10);//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	writeCommand(0x40);//Set Page Start Address for Page Addressing Mode,0-7
	writeCommand(0xB0);//Set COM Output Scan Direction
	writeCommand(0x81);//---set low column address
	writeCommand(0xCF);//---set high column address
	writeCommand(0xA1);//--set start line address
	writeCommand(0xA6);//--set contrast control register
	writeCommand(0xA8);
	writeCommand(0x3F);//--set segment re-map 0 to 127
	writeCommand(0xC8);//--set normal display
	writeCommand(0xD3);//--set multiplex ratio(1 to 64)
	writeCommand(0x00);//
	writeCommand(0xD5);//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	writeCommand(0x80);//-set display offset
	writeCommand(0xD9);//-not offset
	writeCommand(0xF1);//--set display clock divide ratio/oscillator frequency
	writeCommand(0xDA);//--set divide ratio
	writeCommand(0x12);//--set pre-charge period
	writeCommand(0xDB);//
	writeCommand(0x40);//--set com pins hardware configuration
	writeCommand(0x8D);//--set vcomh
	writeCommand(0x14);//0x20,0.77xVcc
	writeCommand(0xAF);//--set DC-DC enable

    //Turn on the OLED display
    writeCommand(0xAF);

    delay_ms(10);

    return true;
}

void Adafruit_SSD1309::drawPixel(int16_t x, int16_t y, uint16_t color) {
	unsigned char row;
	unsigned char offset;
	unsigned char  preData;//previous data.
	unsigned char val;
	int16_t  index;

	if ((x < 0) || (x >= SSD1309_WIDTH) || (y < 0) || (y >= SSD1309_HEIGHT) || (render_buffer == 0))	return;

	//get the previous data;
	row = y / 8;
	offset = y % 8;
	index = row * SSD1309_WIDTH + x;
	preData = render_buffer[index];

	//set pixel;
	val = 1<<offset;
	if (color != 0) {
		render_buffer[index] = preData | val;
	}
    else {
		render_buffer[index] = preData & (~val);
	}
}

void Adafruit_SSD1309::update() {
    unsigned int i = 0;
    unsigned int m, n;
    for (m = 0;m < 8; m++) {
        writeCommand(0xb0+m);	//page0-page1
        writeCommand(0x00);		//low column start address
        writeCommand(0x10);		//high column start address

        i2c_start();
        i2c_write_byte(0x78);
        i2c_write_byte(0x40);
        for (n = 0; n < 128; n++) {
            i2c_write_byte(render_buffer[i++]);
        }
        i2c_stop();
    }
}

void Adafruit_SSD1309::clear(bool isUpdateHW) {
    memset(render_buffer, 0, frame_buffer_size);
    if(isUpdateHW) update();
}