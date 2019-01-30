#ifndef __USER_CFG_H__
#define __USER_CFG_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "cJSON.h"
#include "m_data.h"
#include "m_led.h"
#include "mqtt_client.h"

#define MQTT_URI                         "mqtt://a1CNfFYXMJu.iot-as-mqtt.cn-shanghai.aliyuncs.com"
#define MQTT_PORT                        1883
#define MQTT_CLIENT_ID                   "1234567890|securemode=3,signmethod=hmacsha1,timestamp=789|"
#define MQTT_USER_NAME                   "GNUm2MKbwNmSkXS6nQ0K&a1CNfFYXMJu"
#define MQTT_USER_PWD                    "28b8f83b086fa02cb54243a04d18486314ae357e"
#define TOPIC_PROPERTY_POST              "/sys/a1CNfFYXMJu/GNUm2MKbwNmSkXS6nQ0K/thing/event/property/post"
#define TOPIC_PROPERTY_SET               "/sys/a1CNfFYXMJu/GNUm2MKbwNmSkXS6nQ0K/thing/service/property/set"
#define TOPIC_DEVICE_INFO_UPDATE         "/sys/a1CNfFYXMJu/GNUm2MKbwNmSkXS6nQ0K/thing/deviceinfo/update"
#define TOPIC_USER_UPDATE                "/a1CNfFYXMJu/GNUm2MKbwNmSkXS6nQ0K/user/update"
#define TOPIC_USER_UPDATE_ERROR          "/a1CNfFYXMJu/GNUm2MKbwNmSkXS6nQ0K/user/update/error"
#define TOPIC_USER_GET                   "/a1CNfFYXMJu/GNUm2MKbwNmSkXS6nQ0K/user/get"

#define WIFI_SSID_PASSWORD_FROM_STDIN    1

void mqtt_publish(char *topic, char *pdata);
void mqtt_subscribe(char *topic);

#endif
