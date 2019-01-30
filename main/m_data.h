#ifndef __M_DATA_H__
#define __M_DATA_H__

void led_state_update(bool boolean);
void humidity_and_temperature_post(uint8_t humidity, uint8_t temperature);
void data_parse(char *pdata);

#endif
