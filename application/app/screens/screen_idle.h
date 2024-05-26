/**
 ******************************************************************************
 * @author: Nark
 * @date:   02/04/2024
 ******************************************************************************
**/

#ifndef __SCREEN_IDLE_H_
#define __SCREEN_IDLE_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "message.h"

#define SCREEN_WIDTH            (128)
#define SCREEN_HEIGHT           (64)
#define NUM_BALL_MAX            (6)

typedef struct {
    int x, y, axis_x, axis_y, radius, slope;
} ball_t;

extern void screen_idle_handler(stk_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __SCREEN_IDLE_H_ */