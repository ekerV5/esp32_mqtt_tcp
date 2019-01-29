#include <stdio.h>
#include "cJSON.h"
#include "m_data.h"

cJSON *json, *param;

void data_json_init(void)
{
    json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "id", "123");
    cJSON_AddStringToObject(json, "version", "1.0");
    cJSON_AddStringToObject(json, "method", "thing.event.property.post");

    param = cJSON_AddObjectToObject(json, "params");
}

void data_json_add_bool(const char *key, cJSON_bool boolean)
{
    cJSON_AddBoolToObject(param, key, boolean);
}

void data_json_add_number(const char *key, double number)
{
    cJSON_AddNumberToObject(param, key, number);
}

void data_json_add_string(const char *key, char *string)
{
    cJSON_AddStringToObject(param, key, string);
}

char *data_json_parse_to_string(void)
{
    char *json_str = cJSON_Print(json);
    printf("%s\n", json_str);

    cJSON_Delete(json);

    return json_str;
}

void data_parse(char *pdata)
{
    cJSON *json = cJSON_Parse(pdata);
    if (json == NULL) {
        printf("Parse data error.\n");
        return;
    }
    
    cJSON *json_params = cJSON_GetObjectItem(json, "params");
    if (json_params == NULL) {
        printf("Get params error.\n");
        return;
    }

    cJSON *json_data = cJSON_GetObjectItem(json_params, "LightSwitch");
    if (json_data != NULL) {
        printf("Light %s\n", json_data->valueint ? "on" : "off");
    }
}
