/**
 ******************************************************************************
 * @author: Nark
 * @date:   06/04/2024
 ******************************************************************************
**/

#ifndef __SCREEN_FILTER_TYPE_H_
#define __SCREEN_FILTER_TYPE_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "message.h"

#define FILTER_ANIMATION_DISABLE       (0x00)
#define FILTER_ANIMATION_ACTION_1      (0x01)
#define FILTER_ANIMATION_ACTION_2      (0x02)
#define FILTER_ANIMATION_ACTION_3      (0x03)
#define FILTER_ANIMATION_ACTION_4      (0x04)

extern uint8_t polling_filter_icon_animation;
extern void screen_filter_type_handler(stk_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __SCREEN_FILTER_TYPE_H_ */