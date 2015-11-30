clear all; close all; clc;

out = load_dat("../dat/ex_dspl_dft.bin");

for(k = 1 : length(out))
	eval([out{k}.vn(1:end-1) " = out{" num2str(k) "}.dat;"]);
endfor

clear k, out; 

z = fft(xin);
N = length(xin);

freq = (0:N-1)/N;

figure; 
subplot(211); plot(freq, abs(xout), freq, abs(z) );
subplot(212); plot(freq, abs(xout - z) );