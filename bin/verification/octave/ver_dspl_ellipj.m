clear all; close all;

addpath('functions');

[u, n, m] = dspl_readbin('../dat/ellip_u.bin');

[c, n, m] = dspl_readbin('../dat/ellip_cd_0.999.bin');
C = cde(u, 0.999);                                
dspl_verification('dspl_ellip_cd k = 0.999', c, C);

[c, n, m] = dspl_readbin('../dat/ellip_cd_0.990.bin');
C = cde(u, 0.990);                                
dspl_verification('dspl_ellip_cd k = 0.990', c, C);

[c, n, m] = dspl_readbin('../dat/ellip_cd_0.900.bin');
C = cde(u, 0.900);                                
dspl_verification('dspl_ellip_cd k = 0.900', c, C);

[c, n, m] = dspl_readbin('../dat/ellip_cd_0.700.bin');
C = cde(u, 0.700);                                
dspl_verification('dspl_ellip_cd k = 0.700', c, C);




[c, n, m] = dspl_readbin('../dat/ellip_sn_0.999.bin');
C = sne(u, 0.999);                                
dspl_verification('dspl_ellip_sn k = 0.999', c, C);

[c, n, m] = dspl_readbin('../dat/ellip_sn_0.990.bin');
C = sne(u, 0.990);                                
dspl_verification('dspl_ellip_sn k = 0.990', c, C);

[c, n, m] = dspl_readbin('../dat/ellip_sn_0.900.bin');
C = sne(u, 0.900);                                
dspl_verification('dspl_ellip_sn k = 0.900', c, C);

[c, n, m] = dspl_readbin('../dat/ellip_sn_0.700.bin');
C = sne(u, 0.700);                                
dspl_verification('dspl_ellip_sn k = 0.700', c, C);