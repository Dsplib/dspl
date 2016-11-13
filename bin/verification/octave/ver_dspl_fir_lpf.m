clear all; close all;            

addpath('functions');

[he, n, m] = dspl_readbin('../dat/fir_lpf_even_time.bin');
[He, n, m] = dspl_readbin('../dat/fir_lpf_even_freq.bin');

w = real(He);
H = imag(He);

figure; stem(he);
figure; plot(w/pi, H)

[ho, n, m] = dspl_readbin('../dat/fir_lpf_odd_time.bin');
[Ho, n, m] = dspl_readbin('../dat/fir_lpf_odd_freq.bin');

w = real(Ho);
H = imag(Ho);

figure; stem(ho);
figure; plot(w/pi, H)

