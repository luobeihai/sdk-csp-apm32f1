/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     Abbcc        first version
 * 2023-03-08     luobeihai    modified FLASH and RAM micro definition
 */

#ifndef __DRV_COMMON_H__
#define __DRV_COMMON_H__

#include <rtthread.h>
#include <rthw.h>
#include <apm32f10x.h>

#include "apm32f10x_gpio.h"
#include "apm32f10x_rcm.h"
#include "apm32f10x_misc.h"
#include "apm32f10x_rcm.h"
#include "apm32f10x_eint.h"
#include "apm32f10x_usart.h"
#include "apm32f10x_dma.h"

#ifdef __cplusplus
extern "C" {
#endif

#define APM32_FLASH_START_ADRESS       ROM_START
#define APM32_FLASH_SIZE               ROM_SIZE
#define APM32_FLASH_END_ADDRESS        ROM_END

#define APM32_SRAM_SIZE                RAM_SIZE
#define APM32_SRAM_START               RAM_START
#define APM32_SRAM_END                 RAM_END

#if defined(__ARMCC_VERSION)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN      (__segment_end("CSTACK"))
#else
extern int __bss_end;
#define HEAP_BEGIN      ((void *)&__bss_end)
#endif

#define HEAP_END        APM32_SRAM_END

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
}
#endif

#endif
