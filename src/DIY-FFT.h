#pragma once
#include <cmath>
#include <complex>

class DIY_FFT{
    public:
    void calculateFFT(double *vReal, int samples, int samplingFreq);
    private:
    void fft_rec(std::complex<float> *x, int N);
};