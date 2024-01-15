#pragma once

#include <ESP8266WiFi.h>

void wifi_setup() {
//#ifdef GH_ESP_BUILD
    // подключение к роутеру
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println(WiFi.localIP());

    // ИЛИ

    // режим точки доступа
    //WiFi.mode(WIFI_AP);
    //WiFi.softAP("My Hub");
    //Serial.println(WiFi.softAPIP());
//#endif
}
