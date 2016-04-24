clear all; close all;            

addpath('functions');


N = 131072;
K = 16;

n = 0:N-1;
x = exp(2i*pi * n *0.2);


while(N>2)
	t = tic;
	for(k = 1:K)
		y = fft(x(1:N));
		
	end
	t = toc(t);
	
	fprintf("N = %d, K = %d, %d sec\n",N,K,t);
	N = N/2;
	K = K*2;
end