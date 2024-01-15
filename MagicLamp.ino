#include "config.h"
#include "wifi.h"
#include "ghub.h"
#include "led.h"

void setup() {
  led_setup();
  Serial.begin(115200);
  wifi_setup();
  ghub_setup();
}

void loop() {
  ghub_tick();
  led_tick();
}
