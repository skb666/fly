#include <stdio.h>

#include "SEGGER_RTT.h"
#include "systick.h"
#include "main.h"
#include "bsp.h"

/*!
    \brief      toggle the led every 500ms
    \param[in]  none
    \param[out] none
    \retval     none
*/
void led_spark(void)
{
    static __IO uint32_t timingdelaylocal = 0U;

    if (timingdelaylocal)
    {
        if (timingdelaylocal < 500U)
        {
            led_on(LED1);
        }
        else
        {
            led_off(LED1);
        }

        timingdelaylocal--;
    }
    else
    {
        timingdelaylocal = 1000U;
    }
}

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/

int main(void)
{
#ifdef __FIRMWARE_VERSION_DEFINE
    uint32_t fw_ver = 0;
#endif

    /* configure systick */
    systick_config();

    SEGGER_RTT_Init();
    gpio_pin_remap_config(GPIO_SWJ_SWDPENABLE_REMAP, ENABLE);

    /* initialize the LEDs, USART and key */
    led_init(LED1);
    led_init(LED2);
    led_init(LED3);
    com_init(EVAL_COM1);
    key_init(KEY0, KEY_MODE_GPIO);

#ifdef __FIRMWARE_VERSION_DEFINE
    fw_ver = gd32f30x_firmware_version_get();
    /* print firmware version */
    printf("\r\nGD32F30x series firmware version: V%d.%d.%d\r\n", (uint8_t)(fw_ver >> 24), (uint8_t)(fw_ver >> 16), (uint8_t)(fw_ver >> 8));
#endif /* __FIRMWARE_VERSION_DEFINE */

    /* print out the clock frequency of system, AHB, APB1 and APB2 */
    printf("CK_SYS is %u\r\n", (unsigned int)rcu_clock_freq_get(CK_SYS));
    printf("CK_AHB is %u\r\n", (unsigned int)rcu_clock_freq_get(CK_AHB));
    printf("CK_APB1 is %u\r\n", (unsigned int)rcu_clock_freq_get(CK_APB1));
    printf("CK_APB2 is %u\r\n", (unsigned int)rcu_clock_freq_get(CK_APB2));

    while (1)
    {
        if (RESET == key_state_get(KEY0))
        {
            led_on(LED2);
            delay_1ms(500);
            led_off(LED2);
            led_toggle(LED3);
        }
    }
}
