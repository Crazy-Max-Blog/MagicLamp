#include "config.h"
#include "wifi.h"
#include "led.h"
#include "ghub.h"

void setup() {
  Serial.begin(115200);
  led_setup();
  data_begin();
  wifi_setup();
  ghub_setup();
}

void loop() {
  ghub_tick();
  led_tick();
}
