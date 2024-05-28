int sensor = A0; 
int ledpin = 13; 
boolean on_or_off = false; 

void setup() {
  pinMode(sensor, INPUT); 
  pinMode(led, OUTPUT); 

}

void loop() {

  int data = digitalRead(sensor); 

  if (data == 1) { 
    if (on_or_off == true) { 
      digitalWrite(led, 0);
      on_or_off = false;
    }
    else { 
      digitalWrite(led, 1);
      on_or_off = true;
    }
  }
}
