/**
 ******************************************************************************
 * @author: Nark
 * @date:   02/04/2024
 ******************************************************************************
**/

#include "task_list.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "console.h"

#include "app.h"
#include "task_display.h"
#include "task_ir_remote.h"

task_t app_task_table[] = {
    /*************************************************************************/
	/* SYSTEM TASKS */
	/*************************************************************************/
    {TASK_TIMER_TICK_ID,              task_timer_handler},

    /*************************************************************************/
	/* APP TASKS */
	/*************************************************************************/
    {TASK_DISPLAY_ID,                 task_display_handler},
    {TASK_REMOTE_ID,                  task_remote_handler},
};