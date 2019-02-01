# ESP32_MQTT_TCP应用
## 介绍
硬件：
```
ESP32-PICO-KIT V4迷你板
RGB 3色LED
DHT11温湿度模块
```
软件：
```
ESP-IDF
```
此应用实现了通过MQTT的TCP方式连接到阿里云，通过DHT11模块周期性检测温度和湿度并上报到云端，通过订阅的云端发布的消息来判断是否打开LED。

手机端采用阿里云的移动应用开发功能简单的做了一个安卓APP。

## 使用
### 1.配置
```
make menuconfig
```
设置串口号

设置Wifi ssid和密码

如果想在运行的时候从终端手动输入ssid和密码，可以把头文件“user_cfg.h”中宏“WIFI_SSID_PASSWORD_FROM_STDIN”的值置1。
### 2.修改代码
根据阿里云设备三元组信息生成MQTT连接信息，参考阿里官方文档https://help.aliyun.com/document_detail/73742.html?spm=a2c4g.11174283.6.650.528816687sa9MQ

用生成的MQTT连接信息及发布订阅等的主题替换user_cfg.h头文件中的宏
![img](https://github.com/ekerV5/resources/blob/master/user_cfg.jpg)

## 实际效果
![gif](https://github.com/ekerV5/resources/blob/master/esp32_connect_to_alicloud.gif)
      
      
