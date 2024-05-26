/**
 ******************************************************************************
 * @author: Nark
 * @date:   01/04/2024
 ******************************************************************************
**/

#include "stk_startup.h"

#include "stk.h"
#include "message.h"

#include "system_stm32f0xx.h"
#include "system_irq.h"

#include "app.h"
#include "io_cfg.h"

#include "platform.h"
#include "console.h"

/* define the addresses of data and bss sections */
extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss, _estack;
extern void (*__preinit_array_start[])();
extern void (*__preinit_array_end[])();
extern void (*__init_array_start[])();
extern void (*__init_array_end[])();

static void sys_banner();

/* reset handler */
void reset_handler(void) {
    /* call the system init function */
    SystemInit();

    uint32_t *src, *dest;

    /*------------------------------------------------------------------*/
    /*      copy the data segment initializers from flash to SRAM       */
    /*------------------------------------------------------------------*/
    /* pointer start address in flash */
    src = &_sidata;
    /* pointer start address in sram */
    dest = &_sdata;
    while (dest < &_edata) {
        *dest++ = *src++;
    }

    /* zero fill to .bss section */
    dest = &_sbss;
    while (dest < &_ebss) {
        *dest++ = 0;
    }

    volatile unsigned i, cnt;
    
	/* invoke all static constructors */
	cnt = __preinit_array_end - __preinit_array_start;
	for (i = 0; i < cnt; i++)
		__preinit_array_start[i]();

	cnt = __init_array_end - __init_array_start;
	for (i = 0; i < cnt; i++)
		__init_array_start[i]();

    /* usart1 init */
	usart2_init(9600);

    /* console init */
    console_init();

    /* system banner */
    sys_banner();
    
    /* go to the main application */
    main_app();
}

/* STM32F042 cortex-M0 processor exception vector table */
__attribute__((section(".isr_vector"))) void (*const g_pfnVectors[])(void) = {
    (void (*)(void))&_estack,                       // Stack pointer
    reset_handler,                                  // Reset Handler
    nmi_handler,                                    // NMI Handler
    hardfault_handler,                              // Hard Fault Handler
    mem_manage_handler,                             // MemManage Handler
    bus_fault_handler,                              // BusFault Handler
    usage_fault_handler,                            // UsageFault Handler
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
    svc_handler,                                    // SVCall Handler
    0,                                              // Debug Monitor Handler
    0,                                              // Reserved
    pendsv_handler,                                 // PendSV Handler
    system_tick_handler,                            // SysTick Handler

    0,                                              // Window WatchDog
    0,                                              // Reserved 
    0,                                              // RTC through EXTI Line
    0,                                              // FLASH
    0,                                              // RCC
    0,                                              // EXTI Line 0 and 1
    0,                                              // EXTI Line 2 and 3 
    0,
    0,                                              // EXTI Line 4 to 15
    0,                                              // DMA1 Channel 1
    0,                                              // DMA1 Channel 2 and Channel 3
    0,                                              // DMA1 Channel 4 and Channel 5
    0,                                              // ADC
    0,                                              // TIM1 Break, Update, Trigger and Commutation
    0,                                              // TIM1 Capture Compare
    0,                                              // Reserved
    tim3_irq_handler,                               // TIM3
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // TIM14
    0,                                              // Reserved
    0,                                              // TIM16
    0,                                              // TIM17
    0,                                              // I2C1
    0,                                              // Reserved
    0,                                              // SPI1
    0,                                              // Reserved
    0,                                              // USART1
    usart2_irq_handler,                             // USART2
    0,                                              // Reserved
    0,                                              // Reserved
    0,                                              // Reserved
};

void sys_banner() {
    SYS_PRINT("\n");
    SYS_PRINT(" ___  ____  _  _ \n");
    SYS_PRINT("/ __)(_  _)( )/ )\n");
    SYS_PRINT("\\__ \\  )(  (   (\n");
    SYS_PRINT("(___/ (__) (_)\\_)\n");
    SYS_PRINT("\n");
    SYS_PRINT("Kernel version: %s\n", STK_VERSION);
}