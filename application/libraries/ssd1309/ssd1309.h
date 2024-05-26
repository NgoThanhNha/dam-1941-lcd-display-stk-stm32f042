/**
 ******************************************************************************
 * @author: Nark
 * @date:   29/03/2024
 ******************************************************************************
**/

#ifndef __SSD1309_H__
#define __SSD1309_H__

#include <cstring>
#include <stdlib.h>

#include "Adafruit_GFX.h"

#define SSD1309_WIDTH           128
#define SSD1309_HEIGHT          64
#define frame_buffer_size 		1024

class Adafruit_SSD1309 : public Adafruit_GFX {
public:
    Adafruit_SSD1309();
	~Adafruit_SSD1309();

	//initialized the ssd1306 in the setup function
	virtual bool initialize();

	//update the framebuffer to the screen.
    virtual void update();
	
	//draw one pixel on the screen.
	virtual void drawPixel(int16_t x, int16_t y, uint16_t color);

	//clear the screen
	void clear(bool isUpdateHW=false);

protected:
	//write one byte to the screen.
	void writeData(uint8_t _data);
	void writeCommand(uint8_t _command);

protected:
	unsigned char* render_buffer; //the frame buffer for the adafruit gfx. size=64x8 bytes
};

#endif /* __SSD1309_H__ */