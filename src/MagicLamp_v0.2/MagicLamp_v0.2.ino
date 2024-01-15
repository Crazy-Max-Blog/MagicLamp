#include "config.h"
#include "wifi.h"
#include "ghub.h"
#include "led.h"
#include "ota.h"

void setup() {
  led_setup();
  Serial.begin(115200);
  wifi_setup();
  ghub_setup();
  ota_setup();
  hub.mqtt.config(MQTT_SERV, MQTT_PORT, MQTT_SSID, MQTT_PASS);  // + MQTT
}

void loop() {
  //Serial.println("tick");
  ghub_tick();
  led_tick();
  ota_tick();
}
