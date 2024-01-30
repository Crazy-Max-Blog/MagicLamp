void es(bool s);
byte l  = 100;
byte ll = l;
bool bb=0;

void led_begin() {
  analogWriteResolution(8);
  pinMode(LED_PIN, OUTPUT);
}

void led_tick() {
  static bool bbb;
  if(bbb!=bb) {bbb=bb;es(bb);}
  if(ll!=l)   {ll=l;  es(bb);}
}

void es(bool s) {
  Serial.println(s);
  if(s) analogWrite(LED_PIN, map(l,0,100,0,255)); else analogWrite(LED_PIN, 0);
  //digitalWrite(LED_PIN, s);
}
