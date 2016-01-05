
clear all; close all; clc;
graphics_toolkit("gnuplot");
% Load bin file

w = dspl_readbin("../dat/ex_dspl_freqs_w.bin");
H = dspl_readbin("../dat/ex_dspl_freqs_h.bin"); 

figure; semilogx(w, H);
title("Batterworth filter magnitude");
xlabel("w, rad/s");
ylabel("|H(jw)|^2, dB");
grid on;
axis([0.01, 100, -120, 5]);
