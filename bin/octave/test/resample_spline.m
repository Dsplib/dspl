clear all;
close all; 
clc;

P = 1;
Q = 50; 

N = 7;
Y = [0  0 0 0 1 0 0 0 0 0 0 0];
X = [-1 0:N+3];

dt = P/Q;

for k = 1:N/dt
  t(k) = (k-1) * dt;
  i = floor(t(k));
  T = t(k) - i;
  
  y = Y(i+1:i+4);
  
  dy0 = (y(3) - y(1))/2;
  dy1 = (y(4) - y(2))/2;
  
 
  
  a0 = y(2);
  a1 = dy0;
  A = y(3) - a0 - a1;
  B = dy1 - dy0;
  a3 = B-2*A;
  a2  = 3*A - B;
  z(k) = a0+T.*(a1+T.*(a2+T*a3));
end

figure; plot(X,Y, t,z)

figure; plot(20*log10(abs(fft(z))))


if 0
dy0 = (y(3) - y(1))/2;
dy1 = (y(4) - y(2))/2;
a0 = y(2);
a1 = dy0;
A = y(3) - a0 - a1;
B = dy1 - dy0;
a3 = B-2*A;
a2  = 3*A - B;


t = 0:0.01:1;
z = a0+t.*(a1+t.*(a2+t*a3));

figure; plot(x,y,t,z);
end