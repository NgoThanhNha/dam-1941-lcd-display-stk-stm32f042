/**
 ******************************************************************************
 * @author: Nark
 * @date:   10/05/2024
 ******************************************************************************
**/

#include "task_ir_remote.h"

#include "stk.h"
#include "message.h"

#include "console.h"
#include "button.h"
#include "screen_manager.h"
#include "system_irq.h"

#include "io_cfg.h"
#include "app.h"
#include "bsp.h"
#include "task_list.h"

#include "screen_idle.h"
#include "screen_input_mode.h"
#include "screen_volume.h"
#include "screen_filter_type.h"

void task_remote_handler(stk_msg_t* msg) {
    uint8_t remote_cmd = get_remote_data();
    APP_PRINT("[TASK_REMOTE] REMOTE_CMD: %02X\n", remote_cmd);
    switch (remote_cmd) {
    case REMOTE_PWR:
        button_pwr.state = BUTTON_STATE_LONG_PRESSED;
        button_pwr_callback(&button_pwr);
        break;

    case REMOTE_VOL_UP:
        if (dac_state == DAC_STATE_POWER_ON) {
            SCREEN_TRANS(&screen_volume_handler);
            task_post_pure_msg(TASK_DISPLAY_ID, SG_DISPLAY_BUTTON_UP_PRESSED);
        }
        break;

    case REMOTE_VOL_DWN:
        if (dac_state == DAC_STATE_POWER_ON) {
            SCREEN_TRANS(&screen_volume_handler);
            task_post_pure_msg(TASK_DISPLAY_ID, SG_DISPLAY_BUTTON_DOWN_PRESSED);
        }
        break;

    case REMOTE_MODE:
        if (dac_state == DAC_STATE_POWER_ON) {
            task_post_pure_msg(TASK_DISPLAY_ID, SG_DISPLAY_BUTTON_MODE_PRESSED);
        }
        break;

    case REMOTE_ENTER:
        if (dac_state == DAC_STATE_POWER_ON) {
            task_post_pure_msg(TASK_DISPLAY_ID, SG_DISPLAY_BUTTON_MODE_PRESSED);
        }
        break;

    case REMOTE_UP:
        if (dac_state == DAC_STATE_POWER_ON) {
            task_post_pure_msg(TASK_DISPLAY_ID, SG_DISPLAY_BUTTON_UP_PRESSED);
        }
        break;
    
    case REMOTE_DOWN:
        if (dac_state == DAC_STATE_POWER_ON) {
            task_post_pure_msg(TASK_DISPLAY_ID, SG_DISPLAY_BUTTON_DOWN_PRESSED);
        }
        break;

    default:
        break;
    }
}
