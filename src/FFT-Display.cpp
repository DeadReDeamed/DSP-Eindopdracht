#include "FFT-Display.h"
#include <string>

#define FFTLIB true

void Analyser::Visualizer()
{
  //   //Collect Samples
  lastTime = millis();
  getSamples();

  // Update Display
  displayUpdate();
}

void Analyser::getSamples()
{
  for (int i = 0; i < NUM_BANDS; i++)
  {
    bandValues[i] = 0;
  }

  for (int i = 0; i < SAMPLES; i++)
  {
    newTime = micros();
    vReal[i] = analogRead(AUDIO_IN_PIN); // A conversion takes about 9.7uS on an ESP32
    vImag[i] = 0;
    while ((micros() - newTime) < sampling_period_us)
    { /* chill */
    }
  }

  if(FFTLIB){
  // Compute FFT
    FFT.DCRemoval();
    FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(FFT_FORWARD);
    FFT.ComplexToMagnitude();
  } else {
    fft.calculateFFT(vReal, SAMPLES, SAMPLING_FREQ);
  }

  for (int i = 2; i < (SAMPLES / 2); i++)
    if (vReal[i] > NOISE)
    {
      if (i <= 2)
        bandValues[0] += (int)vReal[i];
      if (i > 2 && i <= 2)
        bandValues[1] += (int)vReal[i];
      if (i > 2 && i <= 3)
        bandValues[2] += (int)vReal[i];
      if (i > 3 && i <= 3)
        bandValues[3] += (int)vReal[i];
      if (i > 3 && i <= 4)
        bandValues[4] += (int)vReal[i];
      if (i > 4 && i <= 4)
        bandValues[5] += (int)vReal[i];
      if (i > 4 && i <= 5)
        bandValues[6] += (int)vReal[i];
      if (i > 5 && i <= 5)
        bandValues[7] += (int)vReal[i];
      if (i > 5 && i <= 6)
        bandValues[8] += (int)vReal[i];
      if (i > 6 && i <= 7)
        bandValues[9] += (int)vReal[i];
      if (i > 7 && i <= 8)
        bandValues[10] += (int)vReal[i];
      if (i > 8 && i <= 9)
        bandValues[11] += (int)vReal[i];
      if (i > 9 && i <= 10)
        bandValues[12] += (int)vReal[i];
      if (i > 10 && i <= 12)
        bandValues[13] += (int)vReal[i];
      if (i > 12 && i <= 13)
        bandValues[14] += (int)vReal[i];
      if (i > 13 && i <= 15)
        bandValues[15] += (int)vReal[i];
      if (i > 15 && i <= 17)
        bandValues[16] += (int)vReal[i];
      if (i > 17 && i <= 19)
        bandValues[17] += (int)vReal[i];
      if (i > 19 && i <= 22)
        bandValues[18] += (int)vReal[i];
      if (i > 22 && i <= 25)
        bandValues[19] += (int)vReal[i];
      if (i > 25 && i <= 29)
        bandValues[20] += (int)vReal[i];
      if (i > 29 && i <= 32)
        bandValues[21] += (int)vReal[i];
      if (i > 32 && i <= 37)
        bandValues[22] += (int)vReal[i];
      if (i > 37 && i <= 42)
        bandValues[23] += (int)vReal[i];
      if (i > 42 && i <= 48)
        bandValues[24] += (int)vReal[i];
      if (i > 48 && i <= 54)
        bandValues[25] += (int)vReal[i];
      if (i > 54 && i <= 62)
        bandValues[26] += (int)vReal[i];
      if (i > 62 && i <= 70)
        bandValues[27] += (int)vReal[i];
      if (i > 70 && i <= 80)
        bandValues[28] += (int)vReal[i];
      if (i > 80 && i <= 91)
        bandValues[29] += (int)vReal[i];
      if (i > 91 && i <= 103)
        bandValues[30] += (int)vReal[i];
      if (i > 103 && i <= 117)
        bandValues[31] += (int)vReal[i];
      if (i > 117 && i <= 134)
        bandValues[32] += (int)vReal[i];
      if (i > 134 && i <= 152)
        bandValues[33] += (int)vReal[i];
      if (i > 152 && i <= 173)
        bandValues[34] += (int)vReal[i];
      if (i > 173 && i <= 196)
        bandValues[35] += (int)vReal[i];
      if (i > 196 && i <= 223)
        bandValues[36] += (int)vReal[i];
      if (i > 223 && i <= 254)
        bandValues[37] += (int)vReal[i];
      if (i > 254 && i <= 289)
        bandValues[38] += (int)vReal[i];
      if (i > 289)
        bandValues[39] += (int)vReal[i];
  }
}

void Analyser::displayUpdate()
{
  for (byte band = 0; band < NUM_BANDS; band++)
  {
    // Scale the bars for the display
    int barHeight = bandValues[band] / AMPLITUDE;
    if (barHeight > TOP)
      barHeight = TOP;

    // Small amount of averaging between frames
    barHeight = ((oldBarHeights[band] * 1) + barHeight) / 2;

    // Move peak up
    if (barHeight > peak[band])
    {
      peak[band] = min(TOP, barHeight);
    }
    lcd.fillRect(band*4, 0, 4, TOP, 0x0000);
    lcd.fillRect(band*4, 0, 4, barHeight, COLOR);
  }
  deltaTime = millis() - lastTime;
  lcd.drawString(String(deltaTime), 0, 110);
}