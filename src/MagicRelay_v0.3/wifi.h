#pragma once

#include <ESP8266WiFi.h>

void wifi_setup() {
//#ifdef GH_ESP_BUILD
    // подключение к роутеру
    WiFi.mode(WIFI_STA);
    WiFi.begin(sets.wifi.ssid, sets.wifi.pass);
    int c=0;
    while (WiFi.status() != WL_CONNECTED and c<=15) {
        c++;
        delay(500);
        Serial.print(".");
    }
    if(WiFi.status() != WL_CONNECTED) {WiFi.disconnect();WiFi.softAP("ESP");}
    Serial.println();
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.softAPIP());

    // ИЛИ

    // режим точки доступа
    //WiFi.mode(WIFI_AP);
    //WiFi.softAP("My Hub");
    //Serial.println(WiFi.softAPIP());
//#endif
}
