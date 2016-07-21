clear all; close all;            
isOctave = exist('OCTAVE_VERSION', 'builtin');
if(isOctave)
	pkg load signal;
end
addpath('functions');

[x, n, m] = dspl_readbin('../dat/dspl_pwelch/pwelch_in_even.bin');
[y, n, m] = dspl_readbin('../dat/dspl_pwelch/pwelch_out_even.bin');

Fs = 2;
N = length(y);
w = hamming(N, 'periodic');

if(isOctave)
  [z,f] = pwelch(x,w,0.5,length(y),Fs);
else

end

dspl_verification('dspl_pwelch (psd even length)',   imag(y), z);
dspl_verification('dspl_pwelch (freq even length)',  real(y), f);

