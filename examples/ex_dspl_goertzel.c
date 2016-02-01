#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"

#define N	32
#define K	3

int main()
{

	/* Input signal vector */
	double xR[N];
	double xI[N];
	
	/* N-points DFT vector */
	double yR[N];
	double yI[N];
	
	/* K spectral samples is
	calculated by Goertzel alggorithm */
	double gR[K];
	double gI[K];
	
	/* signal frequency vector */
	double w[K] = {0.1, 0.25, 0.4};
	
	/* spectral samples indexes */
	int k[K]; 
	
	int n, p;
	
	HINSTANCE hInstDLL;

	/* Load dspl.dll */
	hInstDLL = dspl_load();
	if(!hInstDLL)
	{
		printf("dspl.dll Loading Error!\n");
		return 0;
	}

	
	/*print current dspl.dll version */
	dspl_get_version(1);
	
	for(n = 0; n < N; n++)
	{
		xR[n] = xI[n] = 0.0;
		for(p = 0; p < K; p++)
		{
			xR[n] += cos(M_2PI * w[p] * (double)n);
			xI[n] += sin(M_2PI * w[p] * (double)n);
		}
	}
	
	for(p = 0; p < K; p++)
	{
		k[p] = floor(w[p]*N + 0.5);
	}
	
	printf("N-points DFT calculation....................");
	n = dspl_dft(xR, xI, N, yR, yI);
	dspl_print_err(n,1);
	
	printf("K-samples Goertzel algorithm................");
	n = dspl_goertzel(xR, xI, N, k, K, gR, gI);
	dspl_print_err(n,1);
	
	printf("/n");
	for(p = 0; p < K; p++)
	{
		printf("yR[%d] = %.4f\tyI[%d] = %.4f\tgR[%d] = %.4f\tgI[%d] = %.4f\n",
		k[p], yR[k[p]],k[p], yI[k[p]], p ,gR[p], p, gI[p]);
	}
	
	
	FreeLibrary(hInstDLL);
	
	return 0;
}
