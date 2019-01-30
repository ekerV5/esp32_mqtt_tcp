#include "user_cfg.h"

cJSON *json, *param;

static void data_json_init(void)
{
    json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "id", "123");
    cJSON_AddStringToObject(json, "version", "1.0");
    cJSON_AddStringToObject(json, "method", "thing.event.property.post");

    param = cJSON_AddObjectToObject(json, "params");
}

static void data_json_add_bool(const char *key, cJSON_bool boolean)
{
    cJSON_AddBoolToObject(param, key, boolean);
}

static void data_json_add_number(const char *key, double number)
{
    cJSON_AddNumberToObject(param, key, number);
}

static void data_json_add_string(const char *key, char *string)
{
    cJSON_AddStringToObject(param, key, string);
}

static char *data_json_parse_to_string(void)
{
    char *json_str = cJSON_Print(json);
    printf("%s\n", json_str);

    cJSON_Delete(json);

    return json_str;
}

/**
 * 更新LED状态到云端
 */
void led_state_update(bool boolean)
{
    data_json_init();
    data_json_add_number("LightSwitch", boolean);
    mqtt_publish(TOPIC_PROPERTY_POST, data_json_parse_to_string());
}

/**
 * 解析从服务器接收的json
 */
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
        if (json_data->valueint) {
            printf("Light on.\n");
            led_r_on();
            led_state_update(1);
        }
        else
        {
            printf("Light off.\n");
            led_r_off();
            led_state_update(0);
        }
    }
}
