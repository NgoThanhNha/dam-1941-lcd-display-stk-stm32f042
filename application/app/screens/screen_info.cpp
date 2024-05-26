/**
 ******************************************************************************
 * @author: Nark
 * @date:   06/04/2024
 ******************************************************************************
**/

#include "screen_info.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "console.h"
#include "screen_manager.h"
#include "hard_timer.h"

#include "app.h"
#include "task_list.h"
#include "task_display.h"

#include "screen_idle.h"
#include "screen_input_mode.h"
#include "screen_volume.h"
#include "screen_filter_type.h"
 
static void view_screen_info_update();
static int8_t info_logo_pos_x = 15;
static int8_t info_logo_pos_y = 5;
static int8_t text_info_pos_x;
static int8_t text_info_pos_y;
uint32_t polling_dac_text_animation = POLLING_INFO_ANIMATION_DISABLE;

void screen_info_handler(stk_msg_t* msg) {
    switch (msg->sig) {
    case SCREEN_ENTRY:
        APP_DBG("[SCREEN_INFO] SCREEN_INFO_ENTRY\n");
        text_info_pos_x = 33;
        text_info_pos_y = 65;
        view_screen_info_update();
        timer_set(TASK_DISPLAY_ID, SG_ANIMATION_SCREEN_INFO, 50, TIMER_PERIODIC);
        break;

    case SG_ANIMATION_SCREEN_INFO:
        text_info_pos_y--;
        if (text_info_pos_y < 50) {
            timer_remove(TASK_DISPLAY_ID, SG_ANIMATION_SCREEN_INFO);
            text_info_pos_y = 50;
            view_screen_info_update();
            timer_set(TASK_DISPLAY_ID, SG_SCREEN_INFO_EXIT, 3000, TIMER_ONE_SHOT);
            dac_attr.volume = -20;
            xprintf(filter_type_send_to_dac[dac_attr.filter_type]);
            delay_ms(100);
            xprintf(input_mode_send_to_dac[dac_attr.input_mode]);
            delay_ms(100);
            xprintf("V%d\n", dac_attr.volume);
        }
        else {
            view_screen_info_update();
        }
        break;
    
    case SG_SCREEN_INFO_EXIT:
        SCREEN_TRANS(&screen_volume_handler);
        break;

    default:
        break;
    }
}

void view_screen_info_update() {
    view_render.clear();

    view_render.fillRoundRect(info_logo_pos_x, info_logo_pos_y, 100, 40, 5, 1);
    view_render.setTextSize(2);
    view_render.setTextColor(0);
    view_render.setCursor(info_logo_pos_x + 25, info_logo_pos_y + 5);
    view_render.print("Vien");
    
    view_render.setTextSize(1);
    view_render.setTextColor(0);
    view_render.setCursor(info_logo_pos_x + 6, info_logo_pos_y + 27);
    view_render.print("AUDIO HANDCRAFT");

    view_render.setTextColor(1);
    view_render.setCursor(text_info_pos_x, text_info_pos_y);
    view_render.print("DAC DAM1941");

    view_render.update();
}

void screen_info_configurated(const char* _str) {
    view_render.clear();

    view_render.setTextSize(1);
    view_render.setTextColor(1);
    view_render.setCursor(5, 28);
    view_render.print(_str);
    
    view_render.update();
}