/**
 ******************************************************************************
 * @author: Nark
 * @date:   04/04/2024
 ******************************************************************************
**/

#include "screen_input_mode.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "hard_timer.h"
#include "console.h"
#include "screen_manager.h"

#include "app.h"
#include "task_list.h"
#include "task_display.h"

#include "bitmaps.h"
#include "screen_volume.h"
#include "screen_filter_type.h"

uint8_t polling_select_input_animation = ANIMATION_DISABLE;
static uint8_t cursor_in_screen;
static uint8_t show_item_inputs;
static uint8_t cable_pos_x = 23;
static uint8_t cable_pos_y = 7;

static void view_screen_input_mode_update();

void screen_input_mode_handler(stk_msg_t* msg) {
    switch (msg->sig) {
    case SCREEN_ENTRY:
        APP_DBG("[SCREEN_INPUT] SCREEN_INPUT_ENTRY\n");
        polling_select_input_animation = ANIMATION_ACTION_1;
        view_screen_input_mode_update();
        timer_set(TASK_DISPLAY_ID, SG_ANIMATION_SELECT_INPUT, 250, TIMER_PERIODIC);
        break;

    case SG_DISPLAY_BUTTON_MODE_PRESSED:
        APP_DBG("[SCREEN_INPUT] BUTTON_MODE_PRESSED\n");
        polling_select_input_animation = ANIMATION_DISABLE;
        xprintf(input_mode_send_to_dac[dac_attr.input_mode]);
        timer_remove(TASK_DISPLAY_ID, SG_ANIMATION_SELECT_INPUT);
        SCREEN_TRANS(&screen_filter_type_handler);
        break;

    case SG_DISPLAY_BUTTON_UP_PRESSED:
        APP_DBG("[SCREEN_INPUT] BUTTON_DOWN_PRESSED\n");
        if (cursor_in_screen == 0) {
            cursor_in_screen = 0;
            if (show_item_inputs == 0) {
                show_item_inputs = 0;
            }
            else {
                show_item_inputs--;
            }
        }
        else {
            cursor_in_screen--;
        }
        if (dac_attr.input_mode == 0) {
            dac_attr.input_mode = 0;
        }
        else {
            dac_attr.input_mode--;
        }

        /* show items to screen */
        view_screen_input_mode_update();
        break;
        
    case SG_DISPLAY_BUTTON_DOWN_PRESSED:
        APP_DBG("[SCREEN_INPUT] BUTTON_UP_PRESSED\n");
        cursor_in_screen++;
        dac_attr.input_mode++;
        if (cursor_in_screen > 2) {
            cursor_in_screen = 2;
            show_item_inputs++;
            if (show_item_inputs > 4) {
                show_item_inputs = 4;
            }
        }
        if (dac_attr.input_mode > 6) {
            dac_attr.input_mode = 6;
        }

        /* show items to screen */
        view_screen_input_mode_update();
        break;

    case SG_ANIMATION_SELECT_INPUT:
        switch (polling_select_input_animation) {
        case ANIMATION_DISABLE:
            view_screen_input_mode_update();
            polling_select_input_animation = ANIMATION_ACTION_1;
            break;
        
        case ANIMATION_ACTION_1:
            cable_pos_y = 7;
            view_screen_input_mode_update();
            polling_select_input_animation = ANIMATION_ACTION_2;
            break;

        case ANIMATION_ACTION_2:
            cable_pos_y = 12;
            view_screen_input_mode_update();
            polling_select_input_animation = ANIMATION_ACTION_3;
            break;

        case ANIMATION_ACTION_3:
            cable_pos_y = 17;
            view_screen_input_mode_update();
            polling_select_input_animation = ANIMATION_ACTION_4;
            break;

        case ANIMATION_ACTION_4:
            cable_pos_y = 12;
            view_screen_input_mode_update();
            polling_select_input_animation = ANIMATION_ACTION_1;
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }
}

void view_screen_input_mode_update() {
    view_render.clear();

    /* draw frame */
    view_render.drawRoundRect(45, 0, 78, 22, 5, 1);
    view_render.drawRoundRect(45, 21, 78, 22, 5, 1);
    view_render.drawRoundRect(45, 42, 78, 22, 5, 1);
    view_render.drawBitmap(10, 35, case_icon, 26, 15, 1);
    view_render.drawBitmap(cable_pos_x, cable_pos_y, cable_icon, 5, 15, 1);
    view_render.drawBitmap(126, 2, scroll_bar_icon, 1, 64, 1);

    /* draw text options */
    view_render.setTextSize(1);
    view_render.setTextColor(1);

    view_render.setCursor(60, 8);
    view_render.print(input_mode_arr[show_item_inputs]);
    view_render.setCursor(60, 28);
    view_render.print(input_mode_arr[show_item_inputs + 1]);
    view_render.setCursor(60, 49);
    view_render.print(input_mode_arr[show_item_inputs + 2]);

    /* draw cursor select */
    switch (cursor_in_screen) {
    case 0:
        view_render.fillRoundRect(45, 0, 78, 22, 5, 1);
        view_render.fillRect(125, 3, 3, 16, 1);
        view_render.setTextColor(0);
        view_render.setCursor(60, 8);
        view_render.print(input_mode_arr[show_item_inputs]);
        break;

    case 1:
        view_render.fillRoundRect(45, 21, 78, 22, 5, 1);
        view_render.fillRect(125, 24, 3, 16, 1);
        view_render.setTextColor(0);
        view_render.setCursor(60, 28);
        view_render.print(input_mode_arr[show_item_inputs + 1]);
        break;

    case 2:
        view_render.fillRoundRect(45, 42, 78, 22, 5, 1);
        view_render.fillRect(125, 45, 3, 16, 1);
        view_render.setTextColor(0);
        view_render.setCursor(60, 49);
        view_render.print(input_mode_arr[show_item_inputs + 2]);
        break;

    default:
        break;
    }
    view_render.update();
}