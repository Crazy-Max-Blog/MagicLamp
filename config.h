#pragma once

#include <Arduino.h>
#include <FileData.h>
#include <LittleFS.h>
#include <GyverHub.h>

#define WIFI_SSID ""
#define WIFI_PASS ""

#define MQTT_SERV ""
#define MQTT_SSID ""
#define MQTT_PASS ""
#define MQTT_PORT 12312

#define LED_PIN 2

struct Settings {
  struct {
    int pin;
  } led;
  struct {
    GH::core::AnyPtr ssid="";
    GH::core::AnyPtr pass="";
  } wifi;
  struct {
    GH::core::AnyPtr host="";
    GH::core::AnyPtr port="";
    GH::core::AnyPtr ssid="";
    GH::core::AnyPtr pass="";
  } mqtt;
};

Settings sets;

FileData data(&LittleFS, "/data.dat", 'B', &sets, sizeof(sets));
