/**
 ******************************************************************************
 * @author: Nark
 * @date:   10/05/2024
 ******************************************************************************
**/

#ifndef __TASK_IR_REMOTE_H__
#define __TASK_IR_REMOTE_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "message.h"

enum {
    REMOTE_PWR      = 0x00,
    REMOTE_UP       = 0x0D,
    REMOTE_DOWN     = 0x15,
    REMOTE_MODE     = 0x41,
    REMOTE_ENTER    = 0x11,
    REMOTE_VOL_UP   = 0x0A,
    REMOTE_VOL_DWN  = 0x08,
};

extern void task_remote_handler(stk_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __TASK_IR_REMOTE_H__ */