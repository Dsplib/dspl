% this file is dspl_polynom and dspl_polynom_cmplx verification

clear all; close all; clc;

pkg load signal;


aR = [1.0, 2.0, -1.0, 0.5];
aI = [-1.0, 1.0, -2.0, -2.0];

x = 4;

y = polyval(fliplr(aR+1i*aI) , 4-3i)