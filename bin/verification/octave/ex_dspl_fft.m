clear all; close all; clc;
% Load bin file

if(exist('OCTAVE_VERSION', 'builtin') ~= 0)
	
end


[x, n, m] = dspl_readbin('../dat/dspl_fft/fft_in.bin');
[y, n, m] = dspl_readbin('../dat/dspl_fft/fft_out.bin');
[z, n, m] = dspl_readbin('../dat/dspl_fft/ifft_out.bin');


Y = fft(x);
Z = ifft(Y);

freq = (0:n-1)/n;
t  = 0:n-1;

figure; 
subplot(211); plot(freq, abs(y), freq, abs(Y) );
subplot(212); plot(freq, abs(y - Y)./max(abs(Y)));


figure; 
subplot(221); plot(t, real(x), t, real(z), t, real(Z) );
subplot(222); plot(t, real(x - z),'r', t, real(x-Z));

subplot(223); plot(t, imag(x), t, imag(z), t, imag(Z) );
subplot(224); plot(t, imag(x - z),'r', t, imag(x-Z));


