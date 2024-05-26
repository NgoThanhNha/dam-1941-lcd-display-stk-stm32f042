/**
 ******************************************************************************
 * @author: Nark
 * @date:   06/04/2024
 ******************************************************************************
**/

#include "screen_filter_type.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "console.h"
#include "hard_timer.h"
#include "screen_manager.h"
#include "utils.h"

#include "app.h"
#include "task_list.h"
#include "task_display.h"

#include "bitmaps.h"
#include "screen_volume.h"
#include "screen_input_mode.h"

static uint8_t cursor_in_screen;
static uint8_t show_item_filters;

uint8_t polling_filter_icon_animation = FILTER_ANIMATION_DISABLE;
static unsigned char filter_icon_view[144];

static void view_screen_filter_type_update();

void screen_filter_type_handler(stk_msg_t* msg) {
    switch (msg->sig) {
    case SCREEN_ENTRY:
        APP_DBG("[SCREEN_FILTER] SCREEN_FILTER_ENTRY\n");
        polling_filter_icon_animation = FILTER_ANIMATION_ACTION_1;
        mem_cpy(filter_icon_view, filter_icon_action_1, 144);
        view_screen_filter_type_update();
        timer_set(TASK_DISPLAY_ID, SG_ANIMATION_FILTER_TYPE, 250, TIMER_PERIODIC);

        break;

    case SG_DISPLAY_BUTTON_MODE_PRESSED:
        APP_DBG("[SCREEN_FILTER] BUTTON_MODE_PRESSED\n");
        polling_filter_icon_animation = FILTER_ANIMATION_DISABLE;
        xprintf(filter_type_send_to_dac[dac_attr.filter_type]);
        timer_remove(TASK_DISPLAY_ID, SG_ANIMATION_FILTER_TYPE);
        SCREEN_TRANS(&screen_volume_handler);
        break;

    case SG_DISPLAY_BUTTON_UP_PRESSED:
        APP_DBG("[SCREEN_FILTER] BUTTON_DOWN_PRESSED\n");
        if (cursor_in_screen == 0) {
            cursor_in_screen = 0;
            if (show_item_filters == 0) {
                show_item_filters = 0;
            }

            else {
                show_item_filters--;
            }
        }
        else {
            cursor_in_screen--;
        }

        if (dac_attr.filter_type == 0) {
            dac_attr.filter_type = 0;
        }
        else {
            dac_attr.filter_type--;
        }

        /* show items to screen */
        view_screen_filter_type_update();
        break;

    case SG_DISPLAY_BUTTON_DOWN_PRESSED:
        APP_DBG("[SCREEN_FILTER] BUTTON_UP_PRESSED\n");
        cursor_in_screen++;
        dac_attr.filter_type++;
        if (cursor_in_screen > 2) {
            cursor_in_screen = 2;
            show_item_filters++;
            if (show_item_filters > 1) {
                show_item_filters = 1;
            }
        }

        if (dac_attr.filter_type > 3) {
            dac_attr.filter_type = 3;
        }

        /* show items to screen */
        view_screen_filter_type_update();
        break;
        
    case SG_ANIMATION_FILTER_TYPE:
        switch (polling_filter_icon_animation) {
        case ANIMATION_ACTION_1:
            mem_cpy(filter_icon_view, filter_icon_action_1, 144);
            polling_filter_icon_animation = ANIMATION_ACTION_2;

            /* show items to screen */
            view_screen_filter_type_update();
            break;
        
        case ANIMATION_ACTION_2:
            mem_cpy(filter_icon_view, filter_icon_action_2, 144);
            polling_filter_icon_animation = ANIMATION_ACTION_3;
            
            /* show items to screen */
            view_screen_filter_type_update();
            break;

        case ANIMATION_ACTION_3:
            mem_cpy(filter_icon_view, filter_icon_action_3, 144);
            polling_filter_icon_animation = ANIMATION_ACTION_4;
            
            /* show items to screen */
            view_screen_filter_type_update();
            break;

        case ANIMATION_ACTION_4:
            mem_cpy(filter_icon_view, filter_icon_action_2, 144);
            polling_filter_icon_animation = ANIMATION_ACTION_1;
            
            /* show items to screen */
            view_screen_filter_type_update();
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }
}

void view_screen_filter_type_update() {
    view_render.clear();

    /* draw frame */
    view_render.drawRoundRect(45, 0, 78, 22, 5, 1);
    view_render.drawRoundRect(45, 21, 78, 22, 5, 1);
    view_render.drawRoundRect(45, 42, 78, 22, 5, 1);
    view_render.drawBitmap(10, 17, filter_icon_view, 25, 30, 1);
    view_render.drawBitmap(126, 2, scroll_bar_icon, 1, 64, 1);

    /* draw text options */
    view_render.setTextSize(1);
    view_render.setTextColor(1);

    view_render.setCursor(60, 8);
    view_render.print(filter_type_arr[show_item_filters]);
    view_render.setCursor(60, 28);
    view_render.print(filter_type_arr[show_item_filters + 1]);
    view_render.setCursor(60, 49);
    view_render.print(filter_type_arr[show_item_filters + 2]);

    /* draw cursor select */
    switch (cursor_in_screen) {
        case 0:
            view_render.fillRoundRect(45, 0, 78, 22, 5, 1);
            view_render.fillRect(125, 3, 3, 16, 1);
            view_render.setTextColor(0);
            view_render.setCursor(60, 8);
            view_render.print(filter_type_arr[show_item_filters]);
            break;
    
        case 1:
            view_render.fillRoundRect(45, 21, 78, 22, 5, 1);
            view_render.fillRect(125, 24, 3, 16, 1);
            view_render.setTextColor(0);
            view_render.setCursor(60, 28);
            view_render.print(filter_type_arr[show_item_filters + 1]);
            break;

        case 2:
            view_render.fillRoundRect(45, 42, 78, 22, 5, 1);
            view_render.fillRect(125, 45, 3, 16, 1);
            view_render.setTextColor(0);
            view_render.setCursor(60, 49);
            view_render.print(filter_type_arr[show_item_filters + 2]);
            break;

    default:
        break;
    }

    view_render.update();
}