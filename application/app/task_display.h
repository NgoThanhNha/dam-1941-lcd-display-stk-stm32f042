/**
 ******************************************************************************
 * @author: Nark
 * @date:   02/04/2024
 ******************************************************************************
**/

#ifndef __TASK_DISPLAY_H_
#define __TASK_DISPLAY_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "message.h"

#include "screen_manager.h"
#include "ssd1309.h"

extern scr_mng_t app_screen;
extern Adafruit_SSD1309 view_render;

extern void task_display_handler(stk_msg_t* msg);
extern void view_render_init();

#ifdef __cplusplus
}
#endif

#endif /* __TASK_DISPLAY_H_ */