/**
 ******************************************************************************
 * @author: Nark
 * @date:   29/03/2024
 ******************************************************************************
**/

#include "task_polling.h"

#include "stk.h"
#include "message.h"

#include "io_cfg.h"

#include "console.h"
#include "hard_timer.h"
#include "led.h"
#include "button.h"

#include "app.h"
#include "bsp.h"
#include "task_list.h"

#include "screen_info.h"
#include "screen_idle.h"
#include "screen_volume.h"
#include "screen_input_mode.h"
#include "screen_filter_type.h"

void task_polling_handler() {
    /* button polling */
    button_polling(&button_pwr);
    button_polling(&button_mode);
    button_polling(&button_up);
    button_polling(&button_down);

    /* led polling */
    led_polling(&led_life);
}