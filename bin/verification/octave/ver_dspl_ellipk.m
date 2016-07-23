
clear all; close all;

addpath('functions');

[x, n, m] = dspl_readbin('../dat/ellipk.bin');


k = real(x);
K = imag(x);

Z = ellipke(k.^2);
                                
dspl_verification('dspl_ellipk', K, Z);