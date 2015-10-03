% this file is dspl_fft verification

clear all; close all; clc;

pkg load signal;

% load input signal and fft result
in = load("../dat/ex_dspl_fft_in.txt");
x = in(:,1) + 1i* in(:,2);
out = load("../dat/ex_dspl_fft_out.txt");
y = out(:,1) + 1i* out(:,2);

% calculate fft
t = tic;
for k = 1:10000
  z = fft(x);
end
toc(t)

N = length(y);

% plot real fft result from dspl_fft (variable y)
% and calculated by octave (Matlab) 
figure; plot(1:N, real(y),1:N, real(z));

% plot image fft result from dspl_fft (variable y)
% and calculated by octave (Matlab) 
figure; plot(1:N, imag(y),1:N, imag(z));

% plot error
figure; plot(1:N, abs((y-z)./abs(y)));