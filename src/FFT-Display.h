#pragma once
#include <arduinoFFT.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#define SAMPLES 1024
#define SAMPLING_FREQ 40000
#define AMPLITUDE 300
#define AUDIO_IN_PIN 39
#define MAX_MILLIAMPS 2000
#define NUM_BANDS 40
#define NOISE 500
#define TOP 128
#define COLOR 0x00FF11

class Analyser
{
public:
    unsigned int sampling_period_us;
    byte peak[40] = {0}; // The length of these arrays must be >= NUM_BANDS
    int oldBarHeights[40] = {0};
    int bandValues[40] = {0};
    double vReal[SAMPLES];
    double vImag[SAMPLES];
    unsigned long newTime;
    arduinoFFT FFT = arduinoFFT(vReal, vImag, SAMPLES, SAMPLING_FREQ);
    TFT_eSPI lcd = TFT_eSPI();
    void displayUpdate();
    void getSamples();
    void Visualizer();
};