/**
 ******************************************************************************
 * @author: Nark
 * @date:   29/02/2024
 ******************************************************************************
**/

#include "bsp.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "io_cfg.h"

#include "console.h"
#include "hard_timer.h"
#include "button.h"
#include "screen_manager.h"

#include "app.h"
#include "task_list.h"

#include "screen_idle.h"
#include "screen_volume.h"
#include "screen_info.h"

button_t button_pwr;
button_t button_mode;
button_t button_up;
button_t button_down;

void button_pwr_callback(void* _button) {

    button_t* button = (button_t*)(_button);

    switch (button->state) {
    case BUTTON_STATE_PRESSED:
        APP_PRINT("[BUTTON_CALLBACK] BUTTON_PWR_PRESSED\n");
        break;

    case BUTTON_STATE_LONG_PRESSED:
        APP_PRINT("[BUTTON_CALLBACK] BUTTON_PWR_LONG_PRESSED\n");
        if (dac_state == DAC_STATE_POWER_ON) {
            dac_state = DAC_STATE_POWER_OFF;
            SCREEN_TRANS(&screen_idle_handler);
            relay_off();
        }
        else if (dac_state == DAC_STATE_POWER_OFF) {
            dac_state = DAC_STATE_POWER_ON;
            timer_remove(TASK_DISPLAY_ID, SG_DISPLAY_IDLE_SCREEN_UPDATE);
            SCREEN_TRANS(&screen_info_handler);
            relay_on();
        }
        break;

    case BUTTON_STATE_RELEASED:
        APP_PRINT("[BUTTON_CALLBACK] BUTTON_PWR_RELEASED\n");
        break;

    default:
        break;
    }
}

void button_mode_callback(void* _button) {

    button_t* button = (button_t*)(_button);

    switch (button->state) {
    case BUTTON_STATE_PRESSED:
        APP_PRINT("[BUTTON_CALLBACK] BUTTON_MODE_PRESSED\n");
        if (dac_state == DAC_STATE_POWER_ON) {
            task_post_pure_msg(TASK_DISPLAY_ID, SG_DISPLAY_BUTTON_MODE_PRESSED);
        }

        break;

    case BUTTON_STATE_LONG_PRESSED:
        APP_PRINT("[BUTTON_CALLBACK] BUTTON_MODE_LONG_PRESSED\n");

        break;

    case BUTTON_STATE_RELEASED:
        APP_PRINT("[BUTTON_CALLBACK] BUTTON_MODE_RELEASED\n");

        break;

    default:
        break;
    }
}

void button_up_callback(void* _button) {

    button_t* button = (button_t*)(_button);

    switch (button->state) {
    case BUTTON_STATE_PRESSED:
        APP_PRINT("[BUTTON_CALLBACK] BUTTON_UP_PRESSED\n");
        if (dac_state == DAC_STATE_POWER_ON) {
            task_post_pure_msg(TASK_DISPLAY_ID, SG_DISPLAY_BUTTON_UP_PRESSED);
        }
        break;

    case BUTTON_STATE_LONG_PRESSED:
        APP_PRINT("[BUTTON_CALLBACK] BUTTON_UP_LONG_PRESSED\n");

        break;

    case BUTTON_STATE_RELEASED:
        APP_PRINT("[BUTTON_CALLBACK] BUTTON_UP_RELEASED\n");

        break;

    default:
        break;
    }
}

void button_down_callback(void* _button) {

    button_t* button = (button_t*)(_button);

    switch (button->state) {
    case BUTTON_STATE_PRESSED:
        APP_PRINT("[BUTTON_CALLBACK] BUTTON_DOWN_PRESSED\n");
        if (dac_state == DAC_STATE_POWER_ON) {
            task_post_pure_msg(TASK_DISPLAY_ID, SG_DISPLAY_BUTTON_DOWN_PRESSED);
        }
        break;

    case BUTTON_STATE_LONG_PRESSED:
        APP_PRINT("[BUTTON_CALLBACK] BUTTON_DOWN_LONG_PRESSED\n");

        break;

    case BUTTON_STATE_RELEASED:
        APP_PRINT("[BUTTON_CALLBACK] BUTTON_DOWN_RELEASED\n");

        break;

    default:
        break;
    }
}