#include "DIY-FFT.h"

void DIY_FFT::calculateFFT(double *vReal, int samples, int samplingFreq){
    
    std::complex<float> complexArray[samples];

    for (int i = 0; i < samples; i++) {
		complexArray[i] = std::complex<float>(vReal[i], 0);
		complexArray[i] *= 1; // Window
	}
    
    fft_rec(complexArray, samples);

    for (int i = 0; i < samples; i++) {
		vReal[i] = sqrt((vReal[i] * vReal[i]) + abs(complexArray[i] * complexArray[i]));
	}
}

void DIY_FFT::fft_rec(std::complex<float> *x, int N) {
	// Check if it is splitted enough
	if (N <= 1) {
		return;
	}

	// Split even and odd
	std::complex<float> odd[N/2];
	std::complex<float> even[N/2];
	for (int i = 0; i < N / 2; i++) {
		even[i] = x[i*2];
		odd[i] = x[i*2+1];
	}

	// Split on tasks
	fft_rec(even, N/2);
	fft_rec(odd, N/2);


	// Calculate DFT
	for (int k = 0; k < N / 2; k++) {
		std::complex<float> t = exp(std::complex<float>(0, -2 * M_PI * k / N)) * odd[k];
		x[k] = even[k] + t;
		x[N / 2 + k] = even[k] - t;
	}
}