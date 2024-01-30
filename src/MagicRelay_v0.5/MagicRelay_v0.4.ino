#include "config.h"
#include "led.h"
#include "btn.h"
#include "wifi.h"
#include "ghub.h"

void setup() {
  Serial.begin(115200);
   btn_begin();
   led_begin();
  data_begin();
  wifi_begin();
  ghub_begin();
}

void loop() {
  ghub_tick();
  btn_tick();
  led_tick();
}
