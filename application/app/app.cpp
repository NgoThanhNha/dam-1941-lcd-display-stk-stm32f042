/**
 ******************************************************************************
 * @author: Nark
 * @date:   29/03/2024
 ******************************************************************************
**/

#include "app.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "io_cfg.h"

#include "console.h"
#include "hard_timer.h"
#include "screen_manager.h"
#include "button.h"
#include "led.h"

#include "bsp.h"
#include "task_list.h"
#include "task_display.h"

#include "screen_idle.h"

#include <math.h>

uint8_t dac_state = DAC_STATE_POWER_OFF;
dam1941_attr_t dac_attr;

const char* input_mode_arr[] = {"USB", "AES", "BNC", "RCA", "Toslink", "I2S", "Auto"};
const char* filter_type_arr[] = {"Linear", "Mixed", "Minimum", "Soft"};

const char* input_mode_send_to_dac[] = {"I0\n", "I1\n", "I2\n", "I3\n", "I4\n", "I5\n", "I7\n"};
const char* filter_type_send_to_dac[] = {"F4\n", "F5\n", "F6\n", "F7\n"};

void main_app() {
    /* system tick init */
    systick_init();

    /* io init */
    io_init();

    /* stk kernel init */
    msg_init();
    task_create((task_t*)app_task_table);
    timer_init();
    delay_ms(1000);

    dac_attr.volume = -20;
    dac_attr.input_mode = 6;
    dac_attr.filter_type = 0;

    /* screen init */
    view_render_init();
    scr_mng_init(&app_screen, screen_idle_handler);

    /* button init */
    button_init_func(&button_pwr, button_pwr_read, button_pwr_callback);
    button_init_func(&button_mode, button_mode_read, button_mode_callback);
    button_init_func(&button_up, button_up_read, button_up_callback);
    button_init_func(&button_down, button_down_read, button_down_callback);

    /* led init */
    led_init_func(&led_life, led_life_on, led_life_off);
    led_blink_set(&led_life, 1000);

    for (;;) {
        task_scheduler();
    }
}

