void es(bool s);

void led_setup() {
  pinMode(LED_PIN, OUTPUT);
}

void led_tick() {
  static bool bbb;
  if(bbb!=bb) {bbb=bb;es(bb);}
}

void es(bool s) {
  Serial.println(s);
  digitalWrite(LED_PIN, s);
}
