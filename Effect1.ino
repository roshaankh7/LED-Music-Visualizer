#include <FastLED.h>

#define NUM_LEDS  18
#define LED_PIN   7
#define SENSOR_PIN 2

CRGB leds[NUM_LEDS];
unsigned long lastClapTime = 0;
const unsigned long debounceTime = 400; 
boolean waveActive = false; 
int waveLength = 10; 
int waveStart = 0; 
int waveEnd = waveStart + waveLength - 1; 
CRGB waveColors[] = {CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Yellow, CRGB::Purple, CRGB::Orange}; 
int currentColorIndex = 0; 

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
}
void loop() {
  if (millis() - lastClapTime > debounceTime && !waveActive) {
    int data = digitalRead(SENSOR_PIN);
    if (data == HIGH) {
      lastClapTime = millis();
      waveActive = true;
      currentColorIndex = (currentColorIndex + 1) % (sizeof(waveColors) / sizeof(waveColors[0]));
    }
  }

  if (waveActive) {
    for(int i = waveStart; i <= waveEnd; i++) {
      for(int j = waveStart; j <= waveEnd; j++) {
        leds[j] = CRGB::Black;
      }
      
      leds[i] = waveColors[currentColorIndex];
      FastLED.show();
      delay(50);
    }
    
    waveActive = false;
  }
}
