#pragma once

#include <Arduino.h>
#include <FileData.h>
#include <LittleFS.h>
#define GH_INCLUDE_PORTAL
#include <GyverHub.h>

#define WIFI_SSID "MiHome"
#define WIFI_PASS "!vlad-02072015!"

#define MQTT_SERV "m4.wqtt.ru"
#define MQTT_SSID "u_8KMJY9"
#define MQTT_PASS "01W9SxQB"
#define MQTT_PORT 10084

#define LED_PIN sets.led.pin // 2

struct Settings {
  struct {
    int pin;
  } led;
  struct {
    char ssid[25]="";
    char pass[25]="";
  } wifi;
  struct {
    char host[25]="";
    char port[5] ="";
    char ssid[25]="";
    char pass[25]="";
  } mqtt;
};

Settings sets;

FileData data(&LittleFS, "/data.dat", 'B', &sets, sizeof(sets));

void data_begin() {
  LittleFS.begin();
  
  // прочитать данные из файла в переменную
  // при первом запуске в файл запишутся данные из структуры
  FDstat_t stat = data.read();

  switch (stat) {
    case FD_FS_ERR: Serial.println("FS Error");
      break;
    case FD_FILE_ERR: Serial.println("Error");
      break;
    case FD_WRITE: Serial.println("Data Write");
      break;
    case FD_ADD: Serial.println("Data Add");
      break;
    case FD_READ: Serial.println("Data Read");
      break;
    default:
      break;
  }
}
