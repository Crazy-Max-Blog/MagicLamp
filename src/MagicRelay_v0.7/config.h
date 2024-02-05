#pragma once

#include <Arduino.h>
#include <FileData.h>
#include <LittleFS.h>
#define GH_INCLUDE_PORTAL
#include <GyverHub.h>

#define PR_VERSION "0.13"

#pragma message ("delaying...")
#define CONCAT(x,y) x##y
//#define pmsg ("You use a CrazyRelay project "##PR_VERSION)
#define PMSG "You use a CrazyRelay project "
#pragma message CONCAT(PMSG,PR_VERSION)

#define LED_PIN sets.devs.led.pin // 2

struct Settings {
  struct {
    struct {
      int pin;
    } led;
    struct {
      int pin;
    } btn;
  } devs;
  struct {
    char ssid[25]="";
    char pass[25]="";
  } wifi;
  struct {
    char host[25]="";
    char port[10]="";
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
