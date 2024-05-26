/**
 ******************************************************************************
 * @author: Nark
 * @date:   02/04/2024
 ******************************************************************************
**/

#include "screen_idle.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "console.h"
#include "screen_manager.h"

#include "app.h"
#include "task_list.h"
#include "task_display.h"

#include <math.h>

ball_t ball[NUM_BALL_MAX];
static void ball_idle_init();
static void view_screen_idle_update();

void screen_idle_handler(stk_msg_t* msg) {
    switch (msg->sig){
    case SCREEN_ENTRY:
        APP_DBG("[SCREEN] SCREEN_IDLE_ENTRY\n");
        ball_idle_init();
        view_screen_idle_update();
        timer_set(TASK_DISPLAY_ID, SG_DISPLAY_IDLE_SCREEN_UPDATE, 100, TIMER_PERIODIC);
        break;

    case SG_DISPLAY_IDLE_SCREEN_UPDATE:
        view_screen_idle_update();
        break;

    default:
        break;
    }
}

void ball_idle_init() {
    for (uint8_t i = 0; i < NUM_BALL_MAX; i++) {
        ball[i].axis_x = 1;
        ball[i].axis_y = 1;
        ball[i].slope = (rand() % (31)) - 15;
        ball[i].radius = (rand() % (7)) + 6;
        ball[i].x = rand() % (SCREEN_WIDTH - ball[i].radius);
        ball[i].y = rand() % (SCREEN_HEIGHT - ball[i].radius);
    }
}


void view_screen_idle_update() {
    view_render.clear();
    for (uint8_t i = 0; i < NUM_BALL_MAX; i++) {

        if( ball[i].axis_x > 0) {
            ball[i].x = ball[i].x + 2;
        }
        else {
            ball[i].x = ball[i].x - 2;
        }

        if (ball[i].axis_y > 0) {
            ball[i].y += 2 * atan(ball[i].slope);
        }
        else {
            ball[i].y -= 2 * atan(ball[i].slope);
        }

        if (ball[i].x > (SCREEN_WIDTH - ball[i].radius) || ball[i].x < ball[i].radius) {
            ball[i].axis_x = - ball[i].axis_x;
            if (ball[i].x < ball[i].radius) {
                ball[i].x = ball[i].radius;
            }
        }

        if (ball[i].y > (SCREEN_HEIGHT - ball[i].radius) || ball[i].y < ball[i].radius ) {
            ball[i].axis_y = - ball[i].axis_y;
            if (ball[i].y < ball[i].radius) {
                ball[i].y = ball[i].radius;
        }
        }
        view_render.drawCircle(ball[i].x, ball[i].y, ball[i].radius, 1);
    }
    view_render.update();
}