/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-08     luobeihai    first version
 * 2023-04-07     luobeihai    add uart/can/sdio peripherals Init
 */

#include <rtthread.h>
#include "board.h"
#include "drv_common.h"
#include "apm32_msp.h"

/**
 * @brief apm32 usart gpio init
 *
 * @note This function is only used as an example, please initialize
 *       the peripherals according to the specific hardware board.
 */
void apm32_usart_init(void)
{
    GPIO_Config_T GPIO_ConfigStruct;

#ifdef BSP_USING_UART1
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOA | RCM_APB2_PERIPH_USART1);

    GPIO_ConfigStruct.mode = GPIO_MODE_AF_PP;
    GPIO_ConfigStruct.pin = GPIO_PIN_9;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);

    GPIO_ConfigStruct.mode = GPIO_MODE_IN_PU;
    GPIO_ConfigStruct.pin = GPIO_PIN_10;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
#endif

#ifdef BSP_USING_UART2
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOA);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_USART2);

    GPIO_ConfigStruct.mode = GPIO_MODE_AF_PP;
    GPIO_ConfigStruct.pin = GPIO_PIN_2;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);

    GPIO_ConfigStruct.mode = GPIO_MODE_IN_PU;
    GPIO_ConfigStruct.pin = GPIO_PIN_3;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
#endif

#ifdef BSP_USING_UART3
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOB);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_USART3);

    GPIO_ConfigStruct.mode = GPIO_MODE_AF_PP;
    GPIO_ConfigStruct.pin = GPIO_PIN_10;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOB, &GPIO_ConfigStruct);

    GPIO_ConfigStruct.mode = GPIO_MODE_IN_FLOATING;
    GPIO_ConfigStruct.pin = GPIO_PIN_11;
    GPIO_Config(GPIOB, &GPIO_ConfigStruct);
#endif

#ifdef BSP_USING_UART4
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOC);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_UART4);

    GPIO_ConfigStruct.mode = GPIO_MODE_AF_PP;
    GPIO_ConfigStruct.pin = GPIO_PIN_10;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOC, &GPIO_ConfigStruct);

    GPIO_ConfigStruct.mode = GPIO_MODE_IN_FLOATING;
    GPIO_ConfigStruct.pin = GPIO_PIN_11;
    GPIO_Config(GPIOC, &GPIO_ConfigStruct);
#endif
}

/**
 * @brief apm32 spi gpio init
 *
 * @note This function is only used as an example, please initialize
 *       the peripherals according to the specific hardware board.
 */
void apm32_msp_spi_init(void *Instance)
{
#if defined (BSP_USING_SPI1) || defined (BSP_USING_SPI2) || defined (BSP_USING_SPI3)
    GPIO_Config_T gpioConfig;
    SPI_T *spi_x = (SPI_T *)Instance;

    if(spi_x == SPI3)
    {
        /* Enable related Clock */
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_SPI3);
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOB | RCM_APB2_PERIPH_AFIO);

        GPIO_ConfigPinRemap(GPIO_REMAP_SWJ_JTAGDISABLE);

        /* Configure FLASH_SPI pins: SCK */
        gpioConfig.pin =  GPIO_PIN_3;
        gpioConfig.mode = GPIO_MODE_AF_PP;
        gpioConfig.speed = GPIO_SPEED_50MHz;
        GPIO_Config(GPIOB, &gpioConfig);

        /* Configure FLASH_SPI pins: MOSI */
        gpioConfig.pin = GPIO_PIN_5;
        GPIO_Config(GPIOB, &gpioConfig);

        /* Configure FLASH_SPI pins: MISO */
        gpioConfig.pin = GPIO_PIN_4;
        gpioConfig.mode = GPIO_MODE_IN_FLOATING;
        GPIO_Config(GPIOB, &gpioConfig);
    }
#endif
}

/**
 * @brief apm32 timer gpio init
 *
 * @note This function is only used as an example, please initialize
 *       the peripherals according to the specific hardware board.
 */
void apm32_msp_timer_init(void *Instance)
{
#ifdef BSP_USING_PWM3
    GPIO_Config_T gpio_config;
    TMR_T *tmr_x = (TMR_T *)Instance;

    if (tmr_x == TMR3)
    {
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR3);
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOC | RCM_APB2_PERIPH_AFIO);

        GPIO_ConfigPinRemap(GPIO_FULL_REMAP_TMR3);

        /* TMR3 channel 1 gpio config */
        gpio_config.pin = GPIO_PIN_6;
        gpio_config.mode = GPIO_MODE_AF_PP;
        gpio_config.speed = GPIO_SPEED_50MHz;
        GPIO_Config(GPIOC, &gpio_config);

        /* TMR3 channel 2 gpio config */
        gpio_config.pin = GPIO_PIN_7;
        GPIO_Config(GPIOC, &gpio_config);

        /* TMR3 channel 3 gpio config */
        gpio_config.pin = GPIO_PIN_8;
        GPIO_Config(GPIOC, &gpio_config);

        /* TMR3 channel 4 gpio config */
        gpio_config.pin = GPIO_PIN_9;
        GPIO_Config(GPIOC, &gpio_config);
    }
#endif
}

/**
 * @brief apm32 sdio gpio init
 *
 * @note This function is only used as an example, please initialize
 *       the peripherals according to the specific hardware board.
 */
void apm32_msp_sdio_init(void *Instance)
{
#ifdef BSP_USING_SDIO
    GPIO_Config_T  GPIO_InitStructure;

    /* Enable the GPIO and DMA2 Clock */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOC | RCM_APB2_PERIPH_GPIOD);

    /* Enable the SDIO Clock */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_SDIO);

    /* Configure the GPIO pin */
    GPIO_InitStructure.pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
    GPIO_InitStructure.mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.pin = GPIO_PIN_2;
    GPIO_Config(GPIOD, &GPIO_InitStructure);
#endif
}

/**
 * @brief apm32 can gpio init
 *
 * @note This function is only used as an example, please initialize
 *       the peripherals according to the specific hardware board.
 */
void apm32_msp_can_init(void *Instance)
{
#if defined(BSP_USING_CAN1) || defined(BSP_USING_CAN2)
    GPIO_Config_T  GPIO_InitStructure;
    CAN_T *CANx = (CAN_T *)Instance;

    if (CAN1 == CANx)
    {
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_CAN1);

        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_AFIO);
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOD);

        GPIO_ConfigPinRemap(GPIO_REMAP2_CAN1);

        /* CAN1 Tx */
        GPIO_InitStructure.pin   = GPIO_PIN_1;
        GPIO_InitStructure.mode  = GPIO_MODE_AF_PP;
        GPIO_InitStructure.speed = GPIO_SPEED_50MHz;
        GPIO_Config(GPIOD, &GPIO_InitStructure);

        /* CAN1 Rx */
        GPIO_InitStructure.pin = GPIO_PIN_0;
        GPIO_InitStructure.mode = GPIO_MODE_IN_FLOATING;
        GPIO_Config(GPIOD, &GPIO_InitStructure);
    }
    else if (CAN2 == CANx)
    {
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_CAN2);

        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_AFIO);
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOB);

        GPIO_ConfigPinRemap(GPIO_REMAP_CAN2);

        /* CAN2 Tx */
        GPIO_InitStructure.pin   = GPIO_PIN_6;
        GPIO_InitStructure.mode  = GPIO_MODE_AF_PP;
        GPIO_InitStructure.speed = GPIO_SPEED_50MHz;
        GPIO_Config(GPIOB, &GPIO_InitStructure);

        /* CAN2 Rx */
        GPIO_InitStructure.pin  = GPIO_PIN_5;
        GPIO_InitStructure.mode = GPIO_MODE_IN_FLOATING;
        GPIO_Config(GPIOB, &GPIO_InitStructure);
    }
#endif
}

/**
 * @brief apm32 eth gpio init
 *
 * @note This function is only used as an example, please initialize
 *       the peripherals according to the specific hardware board.
 */
void apm32_msp_eth_init(void *Instance)
{
#ifdef BSP_USING_ETH
    GPIO_Config_T GPIO_ConfigStruct;

    /* Enable SYSCFG clock */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_AFIO);

    /* Enable GPIOs clocks */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOA | RCM_APB2_PERIPH_GPIOB
        | RCM_APB2_PERIPH_GPIOC | RCM_APB2_PERIPH_GPIOD);

    /* ETHERNET pins remapp in APM32107-EVAL board: RX_DV and RxD[3:0] */
    GPIO_ConfigPinRemap(GPIO_REMAP_ETH_MAC);

    /* MII/RMII Media interface selection */
    GPIO_ConfigPinRemap(GPIO_REMAP_MACEISEL_RMII);

    /*********************** Ethernet pins configuration ***************************/
    /*
        ETH_MDIO -------------------------> PA2
        ETH_MDC --------------------------> PC1
        ETH_MII_RX_CLK/ETH_RMII_REF_CLK---> PA1
        ETH_MII_RX_DV/ETH_RMII_CRS_DV ----> PD8
        ETH_MII_RXD0/ETH_RMII_RXD0 -------> PD9
        ETH_MII_RXD1/ETH_RMII_RXD1 -------> PD10
        ETH_MII_TX_EN/ETH_RMII_TX_EN -----> PB11
        ETH_MII_TXD0/ETH_RMII_TXD0 -------> PB12
        ETH_MII_TXD1/ETH_RMII_TXD1 -------> PB13
    */
    /* Configure PA1 as input floating */
    GPIO_ConfigStruct.pin = GPIO_PIN_1;
    GPIO_ConfigStruct.mode  = GPIO_MODE_IN_FLOATING;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);

    /* Configure PD8, PD9, PD10 as input floating */
    GPIO_ConfigStruct.pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_ConfigStruct.mode = GPIO_MODE_IN_FLOATING;
    GPIO_Config(GPIOD, &GPIO_ConfigStruct);

    /* Configure PA2 as alternate function output Push-pull*/
    GPIO_ConfigStruct.pin = GPIO_PIN_2;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_ConfigStruct.mode  = GPIO_MODE_AF_PP;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);

    /* Configure PC1 as alternate function output Push-pull */
    GPIO_ConfigStruct.pin = GPIO_PIN_1;
    GPIO_Config(GPIOC, &GPIO_ConfigStruct);

    /* Configure PB11, PB12, PB13 as alternate function push-pull */
    GPIO_ConfigStruct.pin = GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
    GPIO_Config(GPIOB, &GPIO_ConfigStruct);
#endif
}
