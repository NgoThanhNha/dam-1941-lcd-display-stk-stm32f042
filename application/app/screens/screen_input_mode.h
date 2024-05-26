/**
 ******************************************************************************
 * @author: Nark
 * @date:   04/04/2024
 ******************************************************************************
**/

#ifndef __SCREEN_INPUT_MODE_H_
#define __SCREEN_INPUT_MODE_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "message.h"

#define ANIMATION_DISABLE           (0x00)
#define ANIMATION_ACTION_1          (0x01)
#define ANIMATION_ACTION_2          (0x02)
#define ANIMATION_ACTION_3          (0x03)
#define ANIMATION_ACTION_4          (0x04)

extern uint8_t polling_select_input_animation;
extern void screen_input_mode_handler(stk_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __SCREEN_INPUT_MODE_H_ */