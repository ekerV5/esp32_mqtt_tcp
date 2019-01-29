#ifndef __M_DATA_H__
#define __M_DATA_H__

#include "cJSON.h"

void data_json_init(void);
void data_json_add_bool(const char *key, cJSON_bool boolean);
void data_json_add_number(const char *key, double number);
void data_json_add_string(const char *key, char *string);
char *data_json_parse_to_string(void);
void data_parse(char *pdata);

#endif
