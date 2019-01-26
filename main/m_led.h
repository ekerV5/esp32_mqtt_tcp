#ifndef __M_LED_H__
#define __M_LED_H__

void led_init(void);
void led_r_on(void);
void led_r_off(void);
void led_g_on(void);
void led_g_off(void);
void led_b_on(void);
void led_b_off(void);
void led_all_on(void);
void led_all_off(void);

void ledc_init(void);
void ledc_r_intensity_set(uint8_t percent);
void ledc_g_intensity_set(uint8_t percent);
void ledc_b_intensity_set(uint8_t percent);

#endif
