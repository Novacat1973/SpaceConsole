#include <FastLED.h>

// Konfiguration
#define NUM_LEDS 18
#define DATA_PIN 6

#define BUTTON1_PIN 2
#define BUTTON2_PIN 3
#define POTI1_PIN A0
#define POTI2_PIN A1

// Debouncing
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long debounceDelay = 50;
bool lastButtonState1 = LOW;
bool lastButtonState2 = LOW;

// LEDs
CRGB leds[NUM_LEDS];
uint8_t brightness = 150;  // Anfangshelligkeit
uint8_t currentColor = 1;  // 0=Weiß, 1=Rot, 2=Grün, 3=Blau, 4=Regenbogen
uint8_t currentMode = 1;   // 0=Konstant, 1=Blinken, 2=Lauflicht

// Fading
const int pwmIntervals = 1023;  // Number of steps between LED on and off

// Geschwindigkeit
unsigned long lastUpdateTime = 0;
int speed = 1000;  // Anfangsgeschwindigkeit (ms)
int minSpeed = 100;
int maxSpeed = 1000;
int speedFactor = 5; // Faktor, um den das Lauflicht schneller läuft

// Farben
CRGB colors[] = { CRGB::White, CRGB::Red, CRGB::Green, CRGB::Blue };

// Hilfsfunktionen
void setColor(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
  FastLED.show();
}

void rainbow() {
  static uint8_t hue = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue + (i * 10), 255, brightness);
  }
  FastLED.show();
  hue++;
}

// LED Modi
void updateLEDs() {
  static bool blinkState = false;
  static int position = 0;

  switch (currentMode) {
    case 0:  // Konstant
      if (currentColor < 4) {
        setColor(colors[currentColor]);
      } else {
        rainbow();
      }
      break;

    case 1:  // Blinken
      if (millis() - lastUpdateTime > speed) {
        lastUpdateTime = millis();
        blinkState = !blinkState;
        if (blinkState) {
          if (currentColor < 4) {
            setColor(colors[currentColor]);
          } else {
            rainbow();
          }
        } else {
          setColor(CRGB::Black);
        }
      }
      break;

    case 2:  // Lauflicht
      if (millis() - lastUpdateTime > (speed / speedFactor)) {
        lastUpdateTime = millis();
        for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = CRGB::Black;
        }
        leds[position] = (currentColor < 4) ? colors[currentColor] : CHSV((position * 10), 255, brightness);
        FastLED.show();
        position = (position + 1) % NUM_LEDS;
      }
      break;
  }
}

// Setup
void setup() {
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
}

// Loop
void loop() {
  // Potentiometer
  if (currentColor < 4) {
    brightness = map(analogRead(POTI1_PIN), 0, pwmIntervals, 5, 50);
  }
  else {
    brightness = map(analogRead(POTI1_PIN), 0, pwmIntervals, 80, 160);
  }

  FastLED.setBrightness(brightness);

  speed = map(analogRead(POTI2_PIN), 1023, 0, minSpeed, maxSpeed);

  // Taster 1 - Modus wechseln
  bool buttonState1 = digitalRead(BUTTON1_PIN);
  if (buttonState1 != lastButtonState1) {
    if (buttonState1 == LOW && (millis() - lastDebounceTime1) > debounceDelay) {
      lastDebounceTime1 = millis();
      currentMode = (currentMode + 1) % 3;
    }
    lastButtonState1 = buttonState1;
  }

  // Taster 2 - Farbe wechseln
  bool buttonState2 = digitalRead(BUTTON2_PIN);
  if (buttonState2 != lastButtonState2) {
    if (buttonState2 == LOW && (millis() - lastDebounceTime2) > debounceDelay) {
      lastDebounceTime2 = millis();
      currentColor = (currentColor + 1) % 5;
    }
    lastButtonState2 = buttonState2;
  }

  // LEDs aktualisieren
  updateLEDs();
}
