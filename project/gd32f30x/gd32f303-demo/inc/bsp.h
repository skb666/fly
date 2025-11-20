#ifndef _BSP_H_
#define _BSP_H_

#include "gd32f30x.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* exported types */
typedef enum
{
    LED1 = 0,
    LED2 = 1,
    LED3 = 2,
} led_typedef_enum;

typedef enum
{
    KEY0 = 0,
    KEY1 = 1,
    KEY2 = 2,
} key_typedef_enum;

typedef enum
{
    KEY_MODE_GPIO = 0,
    KEY_MODE_EXTI = 1,
} keymode_typedef_enum;

/* eval board low layer led */
#define LEDn 3U

#define LED1_PIN GPIO_PIN_2
#define LED1_GPIO_PORT GPIOD
#define LED1_GPIO_CLK RCU_GPIOD

#define LED2_PIN GPIO_PIN_9
#define LED2_GPIO_PORT GPIOB
#define LED2_GPIO_CLK RCU_GPIOB

#define LED3_PIN GPIO_PIN_5
#define LED3_GPIO_PORT GPIOC
#define LED3_GPIO_CLK RCU_GPIOC

#define COMn 1U

#define EVAL_COM1 USART1
#define EVAL_COM1_CLK RCU_USART1
#define EVAL_COM1_TX_PIN GPIO_PIN_2
#define EVAL_COM1_RX_PIN GPIO_PIN_3
#define EVAL_COM1_GPIO_PORT GPIOA
#define EVAL_COM1_GPIO_CLK RCU_GPIOA

#define KEYn 3U

/* k0 push-button */
#define KEY0_PIN GPIO_PIN_5
#define KEY0_GPIO_PORT GPIOB
#define KEY0_GPIO_CLK RCU_GPIOB
#define KEY0_EXTI_LINE EXTI_5
#define KEY0_EXTI_PORT_SOURCE GPIO_PORT_SOURCE_GPIOB
#define KEY0_EXTI_PIN_SOURCE GPIO_PIN_SOURCE_5
#define KEY0_EXTI_IRQn EXTI5_9_IRQn

/* k1 push-button */
#define KEY1_PIN GPIO_PIN_11
#define KEY1_GPIO_PORT GPIOB
#define KEY1_GPIO_CLK RCU_GPIOB
#define KEY1_EXTI_LINE EXTI_11
#define KEY1_EXTI_PORT_SOURCE GPIO_PORT_SOURCE_GPIOB
#define KEY1_EXTI_PIN_SOURCE GPIO_PIN_SOURCE_11
#define KEY1_EXTI_IRQn EXTI10_15_IRQn

/* k2 push-button */
#define KEY2_PIN GPIO_PIN_0
#define KEY2_GPIO_PORT GPIOC
#define KEY2_GPIO_CLK RCU_GPIOC
#define KEY2_EXTI_LINE EXTI_0
#define KEY2_EXTI_PORT_SOURCE GPIO_PORT_SOURCE_GPIOC
#define KEY2_EXTI_PIN_SOURCE GPIO_PIN_SOURCE_0
#define KEY2_EXTI_IRQn EXTI0_IRQn

/* function declarations */
/* configure led GPIO */
void led_init(led_typedef_enum lednum);
/* turn on selected led */
void led_on(led_typedef_enum lednum);
/* turn off selected led */
void led_off(led_typedef_enum lednum);
/* toggle the selected led */
void led_toggle(led_typedef_enum lednum);
/* configure key */
void key_init(key_typedef_enum key_num, keymode_typedef_enum key_mode);
/* return the selected key state */
uint8_t key_state_get(key_typedef_enum key);
/* configure COM port */
void com_init(uint32_t com);

#ifdef __cplusplus
}
#endif

#endif
