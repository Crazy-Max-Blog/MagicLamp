#pragma once

#define GH_INCLUDE_PORTAL
#include <GyverHub.h>
GyverHub hub;

//#define GH::core::AnyPtr GH::core::AnyPtr

void mqtt_reconnect();

void gh_home(GH::Builder& b) {
  b.Label().valueStr("Home").noLabel(1).noTab(1);
  if(b.beginRow()) {
    b.Switch_("b", &bb).label("State").noTab();
    if(b.Slider_("l", &l).label("Bright").noTab().size(4).click()) Serial.println(l);
    b.endRow();
  }
  
  //b.addJSON_File("ui.json");
}

void gh_sets(GH::Builder& b) {
  b.Label().valueStr("Settings").noLabel(1).noTab(1);
  b.Spinner(&sets.led.pin).label("Pin").noTab(1).click();                           //)      //Serial.println(sets.led.pin);
  if(b.Button().label("Save and Update").noTab(1).click())    {data.updateNow();pinMode(sets.led.pin, OUTPUT);}
  
  b.Label().valueStr("WiFi").noLabel(1).noTab(1).noTab(1);
  b.Input(sets.wifi.ssid).label("Ssid").noTab(1).click();                           //)      //Serial.println((String)sets.wifi.ssid);
  b.Pass(sets.wifi.pass ).label("Password").noTab(1).click();                       //)  //Serial.println((String)sets.wifi.pass);
  if(b.Button().label("Save and Restart").noTab(1).click())   {data.updateNow();ESP.restart();}
  
  b.Label().valueStr("MQTT").noLabel(1).noTab(1);
  b.Input_("as1", sets.mqtt.host).label("Host").noTab(1).click();                           //)      //Serial.println((String)sets.mqtt.host);
  b.Input_("ds2", sets.mqtt.port).label("Port").noTab(1).click();                           //)      //Serial.println((String)sets.mqtt.port);
  b.Input_("vf3", sets.mqtt.ssid).label("Login").noTab(1).click();                          //)     //Serial.println((String)sets.mqtt.ssid);
  b.Pass(sets.mqtt.pass).label("Password").noTab(1).click();                        //)   //Serial.println((String)sets.mqtt.pass);
  
  //if(b.Button().label("Save").noTab(1).click())               {data.updateNow();}
  //if(b.Button().label("Reconnect").noTab(1).click())          {mqtt_reconnect();}
  if(b.Button().label("Save and Reconnect").noTab(1).click()) {data.updateNow();mqtt_reconnect();}
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
  if(WiFi.status() == WL_CONNECTED) 
    Serial.println("123");//mqtt_reconnect(); //hub.mqtt.config(sets.mqtt.host, sets.mqtt.port.toInt(), sets.mqtt.ssid, sets.mqtt.pass);  // + MQTT
  
  hub.config(F("MyDevices2"), F("ESP"), "", 0x55443420);
  hub.onBuild(build);
  hub.setVersion("Crazy-Max-Blog/MagicLamp@0.3");
  hub.begin();
}

void ghub_tick() {
  hub.tick();
  //data.tick();
}

void mqtt_reconnect() {
  int mport;
  //itoa(mport, sets.mqtt.port, DEC);
  mport = String(sets.mqtt.port).toInt();
  Serial.println(mport);
  if(WiFi.status() == WL_CONNECTED)     hub.mqtt.config(sets.mqtt.host, mport, sets.mqtt.ssid, sets.mqtt.pass);  // + MQTT
}
