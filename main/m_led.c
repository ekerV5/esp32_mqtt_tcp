#include "driver/gpio.h"

#define GPIO_LED_R            5
#define GPIO_LED_G            10
#define GPIO_LED_B            9
#define GPIO_LEDS_MASK        ((1ULL<<GPIO_LED_R) | (1ULL<<GPIO_LED_G) | (1ULL<<GPIO_LED_B))

void led_init(void)
{
	gpio_config_t io_conf;
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;//禁用中断
    io_conf.mode = GPIO_MODE_OUTPUT;          //设置为输出
    io_conf.pin_bit_mask = GPIO_LEDS_MASK;    //要设置的GPIO的bit mask
    io_conf.pull_down_en = 0;                 //不下拉
    io_conf.pull_up_en = 0;                   //不上拉
    gpio_config(&io_conf);

	gpio_set_level(GPIO_LED_R, 0);
	gpio_set_level(GPIO_LED_G, 0);
	gpio_set_level(GPIO_LED_B, 0);
}

void led_r_on(void)
{
	gpio_set_level(GPIO_LED_R, 1);
}

void led_r_off(void)
{
	gpio_set_level(GPIO_LED_R, 0);
}

void led_g_on(void)
{
	gpio_set_level(GPIO_LED_G, 1);
}

void led_g_off(void)
{
	gpio_set_level(GPIO_LED_G, 0);
}

void led_b_on(void)
{
	gpio_set_level(GPIO_LED_B, 1);
}

void led_b_off(void)
{
	gpio_set_level(GPIO_LED_B, 0);
}

void led_all_on(void)
{
	led_r_on();
	led_g_on();
	led_b_on();
}

void led_all_off(void)
{
	led_r_off();
	led_g_off();
	led_b_off();
}
