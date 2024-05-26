/**
 ******************************************************************************
 * @author: Nark
 * @date:   02/04/2024
 ******************************************************************************
**/

#ifndef __TASK_LIST_H__
#define __TASK_LIST_H__

#ifdef __cplusplus
 extern "C" {
#endif 

#include <stdint.h>
#include "stk.h"

enum {
    /* KERNEL TASKS */
    TASK_TIMER_TICK_ID,

    /* APP TASKS */
    TASK_DISPLAY_ID,
    TASK_REMOTE_ID,
};

extern task_t app_task_table[];

#ifdef __cplusplus
}
#endif

#endif /* __TASK_LIST_H__ */