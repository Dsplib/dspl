

y = randn(1,100000);
[nn,xx]  = hist(y, 30);

nn = nn / (100000*(xx(2) - xx(1)));

x  = -5:0.01:5;
w = 1/sqrt(2*pi) * exp(-0.5*x.^2);


plot(xx,nn,x,w);
