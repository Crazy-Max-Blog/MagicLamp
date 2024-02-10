#include "config.h"
#include "led.h"
#include "btn.h"
#include "wifi.h"
#include "ghub.h"

void setup() {
  Serial.begin(115200);
  data_begin();
   btn_begin();
   led_begin();
  wifi_begin();
  ghub_begin();
}

void loop() {
  ghub_tick();
   btn_tick();
   led_tick();
}
