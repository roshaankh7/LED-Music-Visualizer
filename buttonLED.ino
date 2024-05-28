#include <FastLED.h>

const int BUTTON_PIN = 7;         
const int LED_STRIP_PIN = 3;    
const int NUM_LEDS = 10;          

CRGB leds[NUM_LEDS];

int ledState = LOW;
int lastButtonState;
int currentButtonState;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  FastLED.addLeds<WS2812B, LED_STRIP_PIN, GRB>(leds, NUM_LEDS);
  FastLED.show();               
  currentButtonState = digitalRead(BUTTON_PIN);
}

void loop() {
  lastButtonState = currentButtonState;                    
  currentButtonState = digitalRead(BUTTON_PIN);              

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.print("The button is pressed: ");

   
    if (ledState == LOW) {
      ledState = HIGH;
      Serial.println("Turning LED Strip on");
      fill_solid(leds, NUM_LEDS, CRGB::White);   
    } else {
      ledState = LOW;
      Serial.println("Turning LED Strip off");
      fill_solid(leds, NUM_LEDS, CRGB::Black);   
    }
    FastLED.show();   
  }
}
