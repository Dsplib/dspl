clear all; close all;

addpath('functions');

[u, n, m] = dspl_readbin('../dat/ellip_w.bin');

[c, n, m] = dspl_readbin('../dat/ellip_acd_0.999.bin');
C = acde(u, 0.999);                                
dspl_verification('dspl_ellip_acd k = 0.999', c, C);

[c, n, m] = dspl_readbin('../dat/ellip_acd_0.990.bin');
C = acde(u, 0.990);                                
dspl_verification('dspl_ellip_acd k = 0.990', c, C);

[c, n, m] = dspl_readbin('../dat/ellip_acd_0.900.bin');
C = acde(u, 0.900);                                
dspl_verification('dspl_ellip_acd k = 0.900', c, C);

[c, n, m] = dspl_readbin('../dat/ellip_acd_0.700.bin');
C = acde(u, 0.700);                                
dspl_verification('dspl_ellip_acd k = 0.700', c, C);



[c, n, m] = dspl_readbin('../dat/ellip_asn_0.999.bin');
C = asne(u, 0.999);                                
dspl_verification('dspl_ellip_asn k = 0.999', c, C);

[c, n, m] = dspl_readbin('../dat/ellip_asn_0.990.bin');
C = asne(u, 0.990);                                
dspl_verification('dspl_ellip_asn k = 0.990', c, C);

[c, n, m] = dspl_readbin('../dat/ellip_asn_0.900.bin');
C = asne(u, 0.900);                                
dspl_verification('dspl_ellip_asn k = 0.900', c, C);

[c, n, m] = dspl_readbin('../dat/ellip_asn_0.700.bin');
C = asne(u, 0.700);                                
dspl_verification('dspl_ellip_asn k = 0.700', c, C);






%[c, n, m] = dspl_readbin('../dat/ellip_sn_0.999.bin');
%C = sne(u, 0.999);                                
%dspl_verification('dspl_ellip_sn k = 0.999', c, C);
%
%[c, n, m] = dspl_readbin('../dat/ellip_sn_0.990.bin');
%C = sne(u, 0.990);                                
%dspl_verification('dspl_ellip_sn k = 0.990', c, C);
%
%[c, n, m] = dspl_readbin('../dat/ellip_sn_0.900.bin');
%C = sne(u, 0.900);                                
%dspl_verification('dspl_ellip_sn k = 0.900', c, C);
%
%[c, n, m] = dspl_readbin('../dat/ellip_sn_0.700.bin');
%C = sne(u, 0.700);                                
%dspl_verification('dspl_ellip_sn k = 0.700', c, C);