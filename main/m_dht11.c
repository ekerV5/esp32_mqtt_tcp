#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "driver/gpio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#define GPIO_DHT11_DATA    0


static void dht11_data_gpio_set(uint32_t level)
{
    gpio_set_level(GPIO_DHT11_DATA, level);
}

static bool dht11_data_gpio_get()
{
    return gpio_get_level(GPIO_DHT11_DATA);
}

/**
 * 从DHT11模块读取1个bit
 */
static int dht11_read_bit(void)
{
    int count = 0;

    //等待50us低电平
    while(dht11_data_gpio_get() && count <100){
        count++;
        usleep(1);
    }

    if (count >= 100) {
        printf("DHT11 read bit failed.\n");
        return -1;
    }
    
    count = 0;

    //等待高电平
    while(!dht11_data_gpio_get() && count <100){
        count++;
        usleep(1);
    }

    if (count >= 100) {
        printf("DHT11 read bit failed.\n");
        return -1;
    }

    usleep(40);
    if (dht11_data_gpio_get()) {
        return 1; //bit 1: 50us低 + 70us高
    }
    else
    {
        return 0; //bit 0: 50us低 + 26-28us高
    }
}

/**
 * 从DHT11模块读取1个byte
 */
static uint8_t dht11_read_byte(void)
{
    uint8_t data = 0;

    for(int i = 0; i < 8; i++)
    {
        int bit = dht11_read_bit();
        if (!(bit < 0)) {
            data <<= 1; //DHT11模块的数据高位先发出
            data |= bit;
        }
    }

    return data;
}

/**
 * 等待DHT11模块初始化完成
 * 80us低 + 80us高
 */
static bool dht11_wait(void)
{
    int count = 0;

    //等待80us低电平
    while(dht11_data_gpio_get() && count <100){
        count++;
        usleep(1);
    }

    if (count >= 100) {
        printf("No low level response.\n");
        return false;
    }
    
    count = 0;

    //等待80us高电平
    while(!dht11_data_gpio_get() && count <100){
        count++;
        usleep(1);
    }

    if (count >= 100) {
        printf("No low level response.\n");
        return false;
    }
    
    return true;
}

/**
 * DHT11模块初始化
 */
static void dht11_init(void)
{
    gpio_set_direction(GPIO_DHT11_DATA, GPIO_MODE_OUTPUT);
    gpio_pullup_en(GPIO_DHT11_DATA);
    dht11_data_gpio_set(0);
    vTaskDelay(20 / portTICK_PERIOD_MS); //至少拉低18ms
    dht11_data_gpio_set(1);
    usleep(30); //拉高20-40us

    gpio_set_direction(GPIO_DHT11_DATA, GPIO_MODE_INPUT);
}

/**
 * 读取湿度和温度值
 */
void dht11_get_data(uint8_t *phumidity, uint8_t *ptemperature)
{
    uint8_t data[5] = {0};

    dht11_init();

    if (dht11_wait()) {
        for(int i = 0; i < 5; i++)
        {
            data[i] = dht11_read_byte();
        }
        *phumidity = data[0];
        *ptemperature = data[2];
        printf("Humidity = %d, Temperature = %d\n", *phumidity, *ptemperature);
    }
    else
    {
        printf("DHT11 module init failed.\n");
    }
}
