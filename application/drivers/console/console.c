/**
 ******************************************************************************
 * @author: Nark
 * @date:   29/02/2024
 ******************************************************************************
**/

#include "console.h"
#include "io_cfg.h"

void console_init() {
    xfunc_output = (void(*)(int))usart2_put_char;
}