#include "bsp.h"

/* private variables */
static uint32_t GPIO_PORT[LEDn] = {LED1_GPIO_PORT, LED2_GPIO_PORT, LED3_GPIO_PORT};
static uint32_t GPIO_PIN[LEDn] = {LED1_PIN, LED2_PIN, LED3_PIN};
static rcu_periph_enum GPIO_CLK[LEDn] = {LED1_GPIO_CLK, LED2_GPIO_CLK, LED3_GPIO_CLK};

static rcu_periph_enum COM_CLK[COMn] = {EVAL_COM1_CLK};
static uint32_t COM_TX_PIN[COMn] = {EVAL_COM1_TX_PIN};
static uint32_t COM_RX_PIN[COMn] = {EVAL_COM1_RX_PIN};
static uint32_t COM_GPIO_PORT[COMn] = {EVAL_COM1_GPIO_PORT};
static rcu_periph_enum COM_GPIO_CLK[COMn] = {EVAL_COM1_GPIO_CLK};

static uint32_t KEY_PORT[KEYn] = {KEY0_GPIO_PORT, KEY1_GPIO_PORT, KEY2_GPIO_PORT};
static uint32_t KEY_PIN[KEYn] = {KEY0_PIN, KEY1_PIN, KEY2_PIN};
static rcu_periph_enum KEY_CLK[KEYn] = {KEY0_GPIO_CLK, KEY1_GPIO_CLK, KEY2_GPIO_CLK};
static exti_line_enum KEY_EXTI_LINE[KEYn] = {KEY0_EXTI_LINE, KEY1_EXTI_LINE, KEY2_EXTI_LINE};
static uint8_t KEY_PORT_SOURCE[KEYn] = {KEY0_EXTI_PORT_SOURCE, KEY1_EXTI_PORT_SOURCE, KEY2_EXTI_PORT_SOURCE};
static uint8_t KEY_PIN_SOURCE[KEYn] = {KEY0_EXTI_PIN_SOURCE, KEY1_EXTI_PIN_SOURCE, KEY2_EXTI_PIN_SOURCE};
static IRQn_Type KEY_IRQn[KEYn] = {KEY0_EXTI_IRQn, KEY1_EXTI_IRQn, KEY2_EXTI_IRQn};

void led_init(led_typedef_enum lednum)
{
    /* enable the led clock */
    rcu_periph_clock_enable(GPIO_CLK[lednum]);
    /* configure led GPIO port */
    gpio_init(GPIO_PORT[lednum], GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN[lednum]);

    GPIO_BC(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

void led_on(led_typedef_enum lednum)
{
    GPIO_BOP(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

void led_off(led_typedef_enum lednum)
{
    GPIO_BC(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

void led_toggle(led_typedef_enum lednum)
{
    gpio_bit_write(GPIO_PORT[lednum], GPIO_PIN[lednum],
                   (bit_status)(1 - gpio_input_bit_get(GPIO_PORT[lednum], GPIO_PIN[lednum])));
}

void key_init(key_typedef_enum key_num, keymode_typedef_enum key_mode)
{
    /* enable the key clock */
    rcu_periph_clock_enable(KEY_CLK[key_num]);
    rcu_periph_clock_enable(RCU_AF);

    /* configure button pin as input */
    gpio_init(KEY_PORT[key_num], GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, KEY_PIN[key_num]);

    if (key_mode == KEY_MODE_EXTI)
    {
        /* enable and set key EXTI interrupt to the lowest priority */
        nvic_irq_enable(KEY_IRQn[key_num], 2U, 0U);

        /* connect key EXTI line to key GPIO pin */
        gpio_exti_source_select(KEY_PORT_SOURCE[key_num], KEY_PIN_SOURCE[key_num]);

        /* configure key EXTI line */
        exti_init(KEY_EXTI_LINE[key_num], EXTI_INTERRUPT, EXTI_TRIG_FALLING);
        exti_interrupt_flag_clear(KEY_EXTI_LINE[key_num]);
    }
}

uint8_t key_state_get(key_typedef_enum key)
{
    return (uint8_t)gpio_input_bit_get(KEY_PORT[key], KEY_PIN[key]);
}

void com_init(uint32_t com)
{
    uint32_t com_id = 0U;
    if (EVAL_COM1 == com)
    {
        com_id = 0U;
    }

    /* enable GPIO clock */
    rcu_periph_clock_enable(COM_GPIO_CLK[com_id]);

    /* enable USART clock */
    rcu_periph_clock_enable(COM_CLK[com_id]);

    /* connect port to USARTx_Tx */
    gpio_init(COM_GPIO_PORT[com_id], GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, COM_TX_PIN[com_id]);

    /* connect port to USARTx_Rx */
    gpio_init(COM_GPIO_PORT[com_id], GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, COM_RX_PIN[com_id]);

    /* USART configure */
    usart_deinit(com);
    usart_baudrate_set(com, 115200U);
    usart_receive_config(com, USART_RECEIVE_ENABLE);
    usart_transmit_config(com, USART_TRANSMIT_ENABLE);
    usart_enable(com);
}
