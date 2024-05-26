/**
 ******************************************************************************
 * @author: Nark
 * @date:   02/04/2024
 ******************************************************************************
**/

#include "task_display.h"

#include "stk.h"
#include "message.h"

#include "console.h"
#include "screen_manager.h"

#include "ssd1309.h"

#include "io_cfg.h"
#include "app.h"
#include "task_list.h"

scr_mng_t app_screen;
Adafruit_SSD1309 view_render;

void task_display_handler(stk_msg_t* msg) {
    screen_mng_dispatch(msg);
}

void view_render_init() {
    view_render.initialize();
}