
Fs = 1024;
N = 2048;
f0 = 128;
f1 = f0 + Fs/N/2;

n = 0:N-1;
K = 16;
t = n/Fs;


s0 = [sin(2*pi*f0*t) zeros(1,(K-1)*N)];
s1 = [sin(2*pi*f1*t) zeros(1,(K-1)*N)];

S0 = fftshift(abs(fft(s0)));
S1 = fftshift(abs(fft(s1)));

frq = (0:K*N-1)/K/N * Fs - Fs/2;

plot(frq, S0, frq, S1)