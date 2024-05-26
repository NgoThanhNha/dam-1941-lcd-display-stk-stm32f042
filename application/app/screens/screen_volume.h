/**
 ******************************************************************************
 * @author: Nark
 * @date:   02/04/2024
 ******************************************************************************
**/

#ifndef __SCREEN_VOLUME_H_
#define __SCREEN_VOLUME_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "message.h"

#define VOLUME_ANIMATION_DISABLE       (0x00)
#define VOLUME_ANIMATION_ACTION_1      (0x01)
#define VOLUME_ANIMATION_ACTION_2      (0x02)
#define VOLUME_ANIMATION_ACTION_3      (0x03)

extern uint8_t polling_volume_animation;
extern void screen_volume_handler(stk_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __SCREEN_VOLUME_H_ */