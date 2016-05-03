clear all; close all;            

N = 131072;
K = 512;

n = 0:N-1;
x = exp(2i*pi * n *0.2);


while(N>2)
	t = tic;
	for(k = 1:K)
		y = fft(x(1:N));
		
	end
	t = toc(t);
	
	fprintf("N = %12d, K = %8d, OCTAVE FFT time %.7f ms\n",N,K,1000*t/K);
	N = N/2;
	K = floor(K*1.5);
end