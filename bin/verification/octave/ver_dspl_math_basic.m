
clear all; close all;

addpath('functions');

[x, n, m] = dspl_readbin('../dat/math_basic_x.bin');

[y, n, m] = dspl_readbin('../dat/math_basic_acos.bin');
dspl_verification('dspl_acos_cmplx', y, acos(x));

[y, n, m] = dspl_readbin('../dat/math_basic_asin.bin');
dspl_verification('dspl_asin_cmplx', y, asin(x));

[y, n, m] = dspl_readbin('../dat/math_basic_cos.bin');
dspl_verification('dspl_cos_cmplx', y, cos(x));

[y, n, m] = dspl_readbin('../dat/math_basic_sin.bin');
dspl_verification('dspl_sin_cmplx', y, sin(x));


[y, n, m] = dspl_readbin('../dat/math_basic_sqrt.bin');
dspl_verification('dspl_sqrt_cmplx', y, sqrt(x));

[y, n, m] = dspl_readbin('../dat/math_basic_log.bin');
dspl_verification('dspl_log_cmplx', y, log(x));
