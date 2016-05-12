% N-point DFT
N = 100;

% DFT bin k = 32
k = 32;


%%     Reference DFT   
s = sin(2*pi*(0:N-1)*k/N+pi/6);
X = fft(s);
S_dft = X(k+1); % k+1 because MATLAB and Octave 
				% vector indexation starts from 1. 



%%  Goertzel algorithm from DSPLIB.ORG 
%
%			   W - z^-1
% H(z) = ---------------------------
%		  1 - alpha * z^-1 + z^-2
%
%
%	W = W_N^(-k) = exp(2i*pi*k/N).
%	alpha = 2*cos(2*pi*k/N).
%

% Complex coefficient
w = exp(2i*pi*k/N);

%alpha
alpha = 2*cos(2*pi*k/N);

% IIR filter according to DSPLIB.ORG 
b_dsplib = [w, -1, 0];
a_dsplib = [1, -alpha, 1];
X = filter(b_dsplib, a_dsplib, s);
S_dsplib = X(end);



%% Goertzel algorithm from Alan V. Oppenheim 
%
%			   1 - W * z^-1
% H(z) = ---------------------------
%		  1 - alpha * z^-1 + z^-2
%
%
%	W = W_N^(k) = exp(-2i*pi*k/N).
%	alpha = 2*cos(2*pi*k/N).
%

% Complex coefficient
w = exp(-2i*pi*k/N);

%alpha
alpha = 2*cos(2*pi*k/N);
b_opp = [1, -w,     0];
a_opp = [1, -alpha, 1];

X = filter(b_opp, a_opp, s);
S_opp = X(end);





%%  PRINT 
fprintf('Reference DFT...........................%9.4f %+9.4f i\n', real(S_dft), imag(S_dft));
fprintf('Goertzel alg. from dspib.org............%9.4f %+9.4f i\n', real(S_dsplib), imag(S_dsplib));
fprintf('Goertzel alg. from Alan V. Oppenheim....%9.4f %+9.4f i\n', real(S_opp), imag(S_opp));