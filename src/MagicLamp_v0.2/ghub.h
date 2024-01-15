#pragma once

#define GH_INCLUDE_PORTAL
#include <GyverHub.h>
GyverHub hub;

//#define GH::core::AnyPtr GH::core::AnyPtr

void mqtt_reconnect();

bool bb=0;

void gh_home(GH::Builder& b) {
  b.Label().valueStr("Home").noLabel(1).noTab(1);
  if(b.beginRow()) {
    b.Switch_("b", &bb).label("State").noTab();
    static byte s;
    if(b.Slider(&s).label("Bright").noTab().size(4).click()) Serial.println(s);
    b.endRow();
  }
  
  //b.addJSON_File("ui.json");
}

void gh_sets(GH::Builder& b) {
  b.Label().valueStr("Settings").noLabel(1).noTab(1);
  if(b.Spinner(&sets.led.pin).label("Pin").click())       Serial.println(sets.led.pin);
  if(b.Button().label("Save and Update").click())    {data.updateNow();}
  
  b.Label().valueStr("WiFi").noLabel(1).noTab(1); 
  if(b.Input(sets.wifi.ssidd).label("Ssid").click())      Serial.println(sets.wifi.ssidd); // STRTAP
  /*
  if(b.Input(sets.wifi.ssid).label("Ssid").click())      Serial.println(((String*)sets.wifi.ssid.ptr)->c_str());
  if(b.Pass(sets.wifi.pass ).label("Password").click())  Serial.println(((String*)sets.wifi.pass.ptr)->c_str());
  if(b.Button().label("Save and Restart").click())   {data.updateNow();}
  */
  b.Label().valueStr("MQTT").noLabel(1).noTab(1);/*
  if(b.Input(sets.mqtt.host).label("Host").click())      Serial.println(((String*)sets.mqtt.host.ptr)->c_str());
  if(b.Input(sets.mqtt.port).label("Port").click())      Serial.println(((String*)sets.mqtt.port.ptr)->c_str());
  if(b.Input(sets.mqtt.ssid).label("Login").click())     Serial.println(((String*)sets.mqtt.ssid.ptr)->c_str());
  if(b.Pass(sets.mqtt.pass).label("Password").click())   Serial.println(((String*)sets.mqtt.pass.ptr)->c_str());
  */
  if(b.Button().label("Save").click())               {data.updateNow();}
  if(b.Button().label("Reconnect").click())          {mqtt_reconnect();}
  //if(b.Button().label("Save and Reconnect").click()) {data.updateNow();mqtt_reconnect();}
  //if(b.Button().label("Save and Reconnect").click()) {hub.mqtt.config(sets.mqtt.host, sets.mqtt.port.toInt(), sets.mqtt.ssid, sets.mqtt.pass);}
}

/*void gh_wifi(GH::Builder& b) {
  b.Label().valueStr("WiFi").noLabel(1).noTab(1);
  if(b.Input(&(GH::core::AnyPtr)sets.wifi.ssid).label("Ssid").click())      Serial.println(sets.wifi.ssid);
  if(b.Pass(&(GH::core::AnyPtr)sets.wifi.pass).label("Password").click())   Serial.println(sets.wifi.pass);
  if(b.Button().label("Save and Restart").click())   {data.updateNow();}
}

void gh_mqtt(GH::Builder& b) {
  b.Label().valueStr("MQTT").noLabel(1).noTab(1);
  if(b.Input(&(GH::core::AnyPtr)sets.mqtt.host).label("Host").click())      Serial.println(sets.mqtt.host);
  if(b.Input(&(GH::core::AnyPtr)sets.mqtt.port).label("Port").click())      Serial.println(sets.mqtt.port);
  if(b.Input(&(GH::core::AnyPtr)sets.mqtt.ssid).label("Login").click())     Serial.println(sets.mqtt.ssid);
  if(b.Input(&(GH::core::AnyPtr)sets.mqtt.pass).label("Password").click())  Serial.println(sets.mqtt.pass);
  
  if(b.Button().label("Save").click()) {data.updateNow();}
  if(b.Button().label("Reconnect").click()) {mqtt_reconnect();}
  //if(b.Button().label("Save and Reconnect").click()) {data.updateNow();mqtt_reconnect();}
  //if(b.Button().label("Save and Reconnect").click()) {hub.mqtt.config(sets.mqtt.host, sets.mqtt.port.toInt(), sets.mqtt.ssid, sets.mqtt.pass);}
}*/

// билдер
void build(GH::Builder& b) {
  b.Menu("Home;Settings"); /*;WiFi;MQTT*/
  switch (b.menu()) {
    case 0:
      gh_home(b);
      break;
    case 1:
      gh_sets(b);
      break;
    /*case 2:
      gh_wifi(b);
      break;
    case 3:
      gh_mqtt(b);
      break;*/
    default:
      break;
  }
}

void ghub_setup() {  
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
  
  if(WiFi.status() == WL_CONNECTED) 
    //mqtt_reconnect(); //hub.mqtt.config(sets.mqtt.host, sets.mqtt.port.toInt(), sets.mqtt.ssid, sets.mqtt.pass);  // + MQTT
  
  hub.config(F("MyDevices2"), F("ESP"), "", 0x55443420);
  hub.onBuild(build);
  hub.begin();
}

void ghub_tick() {
  hub.tick();
  //data.tick();
}

void mqtt_reconnect() {
  //if(WiFi.status() == WL_CONNECTED) 
  //  hub.mqtt.config(APTSTR(sets.mqtt.host), APTSTR(sets.mqtt.port).toInt(), APTSTR(sets.mqtt.ssid), APTSTR(sets.mqtt.pass));  // + MQTT
}
