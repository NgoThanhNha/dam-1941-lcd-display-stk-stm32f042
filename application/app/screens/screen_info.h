/**
 ******************************************************************************
 * @author: Nark
 * @date:   06/04/2024
 ******************************************************************************
**/

#ifndef __SCREEN_INFO_H_
#define __SCREEN_INFO_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "message.h"

#define POLLING_INFO_ANIMATION_DISABLE          (0x00)
#define POLLING_INFO_ANIMATION_ENABLE           (0x01)

extern uint32_t polling_dac_text_animation;
extern void screen_info_handler(stk_msg_t* msg);
extern void screen_info_configurated(const char* _str);

#ifdef __cplusplus
}
#endif

#endif /* __SCREEN_INFO_H_ */