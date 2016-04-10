clear all; close all;            

addpath('functions');

[x, n, m] = dspl_readbin('../dat/dspl_fft/fft_in.bin');
[y, n, m] = dspl_readbin('../dat/dspl_fft/fft_out.bin');
[z, n, m] = dspl_readbin('../dat/dspl_fft/ifft_out.bin');


Y = fft(x);
Z = ifft(Y);

dspl_verification('FFT',  y, Y);
dspl_verification('IFFT', z, Z);