#include "driver/gpio.h"
#include "driver/ledc.h"

#define GPIO_LED_R            5
#define GPIO_LED_G            10
#define GPIO_LED_B            9
#define GPIO_LEDS_MASK        ((1ULL<<GPIO_LED_R) | (1ULL<<GPIO_LED_G) | (1ULL<<GPIO_LED_B))

#define PWM_DUTY_RESOLUTION   LEDC_TIMER_13_BIT
#define PWM_FREQUENCY         5000
#define DUTY_FULL             8191    //2 ^ PWM_DUTY_RESOLUTION - 1

static ledc_channel_config_t ledc_r_channel, ledc_g_channel, ledc_b_channel;


/**
 * LED开关控制初始化
 */
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

/**
 * 红色LED打开
 */
void led_r_on(void)
{
	gpio_set_level(GPIO_LED_R, 1);
}

/**
 * 红色LED关闭
 */
void led_r_off(void)
{
	gpio_set_level(GPIO_LED_R, 0);
}

/**
 * 绿色LED打开
 */
void led_g_on(void)
{
	gpio_set_level(GPIO_LED_G, 1);
}

/**
 * 绿色LED关闭
 */
void led_g_off(void)
{
	gpio_set_level(GPIO_LED_G, 0);
}

/**
 * 蓝色LED打开
 */
void led_b_on(void)
{
	gpio_set_level(GPIO_LED_B, 1);
}

/**
 * 蓝色LED关闭
 */
void led_b_off(void)
{
	gpio_set_level(GPIO_LED_B, 0);
}

/**
 * 所有LED打开
 */
void led_all_on(void)
{
	led_r_on();
	led_g_on();
	led_b_on();
}

/**
 * 所有LED关闭
 */
void led_all_off(void)
{
	led_r_off();
	led_g_off();
	led_b_off();
}

/**
 * LED亮度控制初始化
 */
void ledc_init(void)
{
	//LEDC定时器配置
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = PWM_DUTY_RESOLUTION,
        .freq_hz = PWM_FREQUENCY,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
    };

    ledc_timer.timer_num = LEDC_TIMER_0;
    ledc_timer_config(&ledc_timer);

    ledc_timer.timer_num = LEDC_TIMER_1;
    ledc_timer_config(&ledc_timer);

    ledc_timer.timer_num = LEDC_TIMER_2;
    ledc_timer_config(&ledc_timer);

	//LED通道配置
	ledc_r_channel.gpio_num   = GPIO_LED_R;
	ledc_r_channel.speed_mode = LEDC_HIGH_SPEED_MODE;
	ledc_r_channel.channel    = LEDC_CHANNEL_0;
	ledc_r_channel.timer_sel  = LEDC_TIMER_0;
	ledc_r_channel.duty       = 0;
	ledc_r_channel.hpoint     = 0;
	ledc_channel_config(&ledc_r_channel);

	ledc_g_channel.gpio_num   = GPIO_LED_G;
	ledc_g_channel.speed_mode = LEDC_HIGH_SPEED_MODE;
	ledc_g_channel.channel    = LEDC_CHANNEL_1;
	ledc_g_channel.timer_sel  = LEDC_TIMER_1;
	ledc_g_channel.duty       = 0;
	ledc_g_channel.hpoint     = 0;
	ledc_channel_config(&ledc_g_channel);

	ledc_b_channel.gpio_num   = GPIO_LED_B;
	ledc_b_channel.speed_mode = LEDC_HIGH_SPEED_MODE;
	ledc_b_channel.channel    = LEDC_CHANNEL_2;
	ledc_b_channel.timer_sel  = LEDC_TIMER_2;
	ledc_b_channel.duty       = 0;
	ledc_b_channel.hpoint     = 0;
	ledc_channel_config(&ledc_b_channel);
}

/**
 * 改变LED亮度
 */
void ledc_intensity_set(ledc_channel_config_t *ch, uint8_t percent)
{
	if(percent > 100)
	{
		printf("The parameter percent must be 0-100 value!\n");
		return;
	}

	uint32_t duty = DUTY_FULL * percent / 100;
	ledc_set_duty(ch->speed_mode, ch->channel, duty);
	ledc_update_duty(ch->speed_mode, ch->channel);
}

/**
 * 改变红色LED亮度
 */
void ledc_r_intensity_set(uint8_t percent)
{
	ledc_intensity_set(&ledc_r_channel, percent);
}

/**
 * 改变绿色LED亮度
 */
void ledc_g_intensity_set(uint8_t percent)
{
	ledc_intensity_set(&ledc_g_channel, percent);
}

/**
 * 改变蓝色LED亮度
 */
void ledc_b_intensity_set(uint8_t percent)
{
	ledc_intensity_set(&ledc_b_channel, percent);
}
