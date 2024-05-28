#include <FastLED.h>

#define NUM_LEDS  18
#define LED_PIN   7
#define SENSOR_PIN A0  
CRGB leds[NUM_LEDS];
unsigned long lastUpdateTime = 0;
int peak = 0; 
int lastNumLedsLit = 0;  
CRGB waveColors[] = {CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Yellow, CRGB::Purple, CRGB::Orange};
int currentColorIndex = 0; 

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
}

void loop() {
  
  int sensorValue = analogRead(SENSOR_PIN);
  int numLedsToLight = map(sensorValue, 0, 1023, 0, NUM_LEDS);
  if (numLedsToLight > peak) {
    peak = numLedsToLight;
    currentColorIndex = (currentColorIndex + 1) % (sizeof(waveColors) / sizeof(waveColors[0]));
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < numLedsToLight) {
      leds[i] = waveColors[currentColorIndex];
    } else {
      if (leds[i]) leds[i].fadeToBlackBy(10);  
    }
  }
  if (millis() - lastUpdateTime > 500) { 
    if (peak > 0) peak--;
    lastUpdateTime = millis();
  }

  FastLED.show();
}
