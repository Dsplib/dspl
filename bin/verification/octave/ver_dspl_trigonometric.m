
clear all; close all;

addpath('functions');

[x, n, m] = dspl_readbin('../dat/dspl_trigonometric/trig_x.bin');
[c, n, m] = dspl_readbin('../dat/dspl_trigonometric/trig_cos.bin');
[s, n, m] = dspl_readbin('../dat/dspl_trigonometric/trig_sin.bin');
                                
dspl_verification('dspl_cos_cmplx', c, cos(x));
dspl_verification('dspl_sin_cmplx', s, sin(x));