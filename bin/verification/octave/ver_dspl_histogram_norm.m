clear all; close all;   
         
isOctave = exist('OCTAVE_VERSION', 'builtin');
if(isOctave)
	pkg load signal;
else
  fprintf('ver_dspl_histogram_norm.m is OCTAVE verification script!\n');
  return;
end
addpath('functions');



[y, n, m] = dspl_readbin('../dat/dspl_histogram_norm/rand_y.bin');
[h, n, m] = dspl_readbin('../dat/dspl_histogram_norm/rand_h.bin');
[n, x] = hist(y, length(h));
n = n/(length(y)*(x(2)-x(1)));
dspl_verification('dspl_histogram_norm for rand',  x+1i*n, h.');


[y, n, m] = dspl_readbin('../dat/dspl_histogram_norm/randn_y.bin');
[h, n, m] = dspl_readbin('../dat/dspl_histogram_norm/randn_h.bin');
[n, x] = hist(y, length(h));
n = n/(length(y)*(x(2)-x(1)));
dspl_verification('dspl_histogram_norm for randn',  x+1i*n, h.');
