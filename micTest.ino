const int OUT_PIN = A0
void setup() {
  Serial.begin(9000);

}

void loop() {
  Serial.println(analogRead(OUT_PIN));

}
