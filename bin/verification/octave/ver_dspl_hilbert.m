clear all; close all;            
isOctave = exist('OCTAVE_VERSION', 'builtin');
if(isOctave)
	pkg load signal;
end
addpath('functions');

[x, n, m] = dspl_readbin('../dat/hilbert_fft_even.bin');
z = hilbert(real(x));
dspl_verification('dspl_hilbert (even length)',  x, z);


[x, n, m] = dspl_readbin('../dat/hilbert_fft_odd.bin');
z = hilbert(real(x));
dspl_verification('dspl_hilbert (odd length)',  x, z);