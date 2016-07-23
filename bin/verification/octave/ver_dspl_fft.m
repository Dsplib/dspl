clear all; close all;            

addpath('functions');

[x, n, m] = dspl_readbin('../dat/fft_in.bin');
[y, n, m] = dspl_readbin('../dat/fft_out.bin');
[z, n, m] = dspl_readbin('../dat/ifft_out.bin');


Y = fft(x);
Z = ifft(Y);

dspl_verification('dspl_fft',  y, Y);
dspl_verification('dspl_ifft', z, Z);