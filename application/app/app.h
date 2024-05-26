/**
 ******************************************************************************
 * @author: Nark
 * @date:   29/03/2024
 ******************************************************************************
**/

#ifndef __APP_H__
#define __APP_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#define DAC_STATE_POWER_OFF         (0x00)
#define DAC_STATE_POWER_ON          (0x01)

/*---------------------------------------------------------------------------*/
/*                            APP DEFINE SIGNALS                             */
/*---------------------------------------------------------------------------*/
enum {
    /* TASK DISPLAY */
    SG_DISPLAY_IDLE_SCREEN_UPDATE,
    SG_ANIMATION_SCREEN_INFO,
    SG_SCREEN_INFO_EXIT,
    SG_ANIMATION_VOLUME,
    SG_ANIMATION_SELECT_INPUT,
    SG_ANIMATION_FILTER_TYPE,
    
    SG_REMOTE_PUSH,
    SG_DISPLAY_BUTTON_PWR_PRESSED,
    SG_DISPLAY_BUTTON_MODE_PRESSED,
    SG_DISPLAY_BUTTON_MODE_LONG_PRESSED,
    SG_DISPLAY_BUTTON_UP_PRESSED,
    SG_DISPLAY_BUTTON_DOWN_PRESSED,
};

typedef enum {
    USB,
    AES,
    BNC,
    RCA,
    TOSLINK,
    I2S,
    AUTO,
} input_mode_t;

typedef enum {
    LINEAR = 4,
    MIXED,
    MINIMUM,
    SOFT,
} filter_type_t;

typedef struct {
    /* operational attributes */
    int8_t volume;
    uint8_t input_mode;
    uint8_t filter_type;
} dam1941_attr_t;

extern dam1941_attr_t dac_attr;
extern uint8_t dac_state;
extern const char* input_mode_arr[];
extern const char* filter_type_arr[];
extern const char* input_mode_send_to_dac[];
extern const char* filter_type_send_to_dac[];
extern void main_app();

#ifdef __cplusplus
}
#endif

#endif /* __APP_H__ */
