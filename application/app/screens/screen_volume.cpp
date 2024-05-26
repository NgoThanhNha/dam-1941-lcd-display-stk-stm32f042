/**
 ******************************************************************************
 * @author: Nark
 * @date:   02/04/2024
 ******************************************************************************
**/

#include "screen_volume.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "utils.h"
#include "console.h"
#include "screen_manager.h"

#include "app.h"
#include "task_list.h"
#include "task_display.h"

#include "bitmaps.h"
#include "screen_idle.h"
#include "screen_input_mode.h"
#include "screen_filter_type.h"

uint8_t polling_volume_animation =  VOLUME_ANIMATION_DISABLE;
static unsigned char volume_icon_view[96];

static void view_screen_volume_update();

void screen_volume_handler(stk_msg_t* msg) {
    switch (msg->sig) {
    case SCREEN_ENTRY:
        APP_DBG("[SCREEN_VOLUME] SCREEN_VOLUME_ENTRY\n");
        polling_volume_animation = VOLUME_ANIMATION_ACTION_1;
        mem_cpy(volume_icon_view, volume_icon_action_1, 96);
        view_screen_volume_update();
        timer_set(TASK_DISPLAY_ID, SG_ANIMATION_VOLUME, 400, TIMER_PERIODIC);
        break;

    case SG_DISPLAY_BUTTON_MODE_PRESSED:
        APP_DBG("[SCREEN_VOLUME] BUTTON_MODE_PRESSED\n");
        polling_volume_animation = VOLUME_ANIMATION_DISABLE;
        timer_remove(TASK_DISPLAY_ID, SG_ANIMATION_VOLUME);
        SCREEN_TRANS(&screen_input_mode_handler);

        break;

    case SG_DISPLAY_BUTTON_UP_PRESSED:
        APP_DBG("[SCREEN_VOLUME] BUTTON_UP_PRESSED\n");
        dac_attr.volume += 1;
        if (dac_attr.volume > 10) {
            dac_attr.volume = 10;
        }
        /* send volume to dac */
        xprintf("V%d\n", dac_attr.volume);

        /* update screen */
        view_screen_volume_update();
        break;

    case SG_DISPLAY_BUTTON_DOWN_PRESSED:
        APP_DBG("[SCREEN_VOLUME] BUTTON_DOWN_PRESSED\n");
        dac_attr.volume -= 1;
        if (dac_attr.volume < -90) {
            dac_attr.volume = -90;
        }
        /* send volume to dac */
        xprintf("V%d\n", dac_attr.volume);

        /* update screen */
        view_screen_volume_update();
        break;

    case SG_ANIMATION_VOLUME:
        switch (polling_volume_animation) {
        case VOLUME_ANIMATION_ACTION_1:
            mem_cpy(volume_icon_view, volume_icon_action_1, 96);
            view_screen_volume_update();
            polling_volume_animation = VOLUME_ANIMATION_ACTION_2;
            break;
        
        case VOLUME_ANIMATION_ACTION_2:
            mem_cpy(volume_icon_view, volume_icon_action_2, 96);
            view_screen_volume_update();
            polling_volume_animation = VOLUME_ANIMATION_ACTION_3;
            break;

        case VOLUME_ANIMATION_ACTION_3:
            mem_cpy(volume_icon_view, volume_icon_action_3, 96);
            view_screen_volume_update();
            polling_volume_animation = VOLUME_ANIMATION_ACTION_1;
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }


}

void view_screen_volume_update() {
    view_render.clear();

    view_render.drawBitmap(3, 19, volume_icon_view, 22, 22, 1);
    view_render.setTextColor(1);
    view_render.setTextSize(3);
    view_render.setCursor(35, 20);
    view_render.print(dac_attr.volume);
    view_render.print("dB");

    view_render.update();
}