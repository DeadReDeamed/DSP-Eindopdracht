#include "FFT-Display.h"

Analyser ana;

void setup()
{
  pinMode(AUDIO_IN_PIN, INPUT);
  Serial.begin(9600); // Initialize Serial
  delay(3000);        // power-up safety delay
  ana.lcd.init();
  ana.lcd.setRotation(1);
  ana.lcd.fillScreen(0x0000);
  delay(100);
  ana.sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQ));
}

void loop()
{
  ana.Visualizer();
}