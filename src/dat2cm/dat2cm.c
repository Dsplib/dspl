#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct
{
	double *x;
	double *y;
	int n;
	double xmin;
	double xmax;
	int    xauto;
	double ymin;
	double ymax;
	double yshift;
	int    yauto;
	double w;
	double h;
	char *fi;
	char *fo;	
} data_t;





int read_arg(char* arg, char* val, data_t *d)
{
	float t;
	if(!strcmp(arg, "-i"))
	{
		d->fi = val;
		return 1;
	}
	
	if(!strcmp(arg, "-o"))
	{
		d->fo = val;
		return 1;
	}
	
	if(!strcmp(arg, "-xmin"))
	{
		if(sscanf(val, "%E", &t))
		{
			d->xmin = t;
			d->xauto = 0;
			return 1;
		}
		else
			printf("ERROR! Parameter [xmin] is wrong!\n");		
	}
	
	if(!strcmp(arg, "-xmax"))
	{
		if(sscanf(val, "%E", &t))
		{
			d->xmax = t;
			d->xauto = 0;
			return 1;
		}
		else
			printf("ERROR! Parameter [xmax] is wrong!\n");		
	}
	
	if(!strcmp(arg, "-ymin"))
	{
		if(sscanf(val, "%E", &t))
		{
			d->ymin = t;
			d->yauto = 0;
			return 1;
		}
		else
			printf("ERROR! Parameter [ymin] is wrong!\n");		
	}
	
	if(!strcmp(arg, "-ymax"))
	{
		if(sscanf(val, "%E", &t))
		{
			d->ymax = t;
			d->yauto = 0;
			return 1;
		}
		else
			printf("ERROR! Parameter [ymax] is wrong!\n");		
	}
	
	if(!strcmp(arg, "-w"))
	{
		if(sscanf(val, "%E", &t))
		{
			d->w = t;
			return 1;
		}
		else
			printf("ERROR! Parameter [w] is wrong!\n");		
	}
	
	if(!strcmp(arg, "-h"))
	{
		if(sscanf(val, "%E", &t))
		{
			d->h = t;
			return 1;
		}
		else
			printf("ERROR! Parameter [h] is wrong!\n");		
	}
	
	if(!strcmp(arg, "-dy"))
	{
		if(sscanf(val, "%E", &t))
		{
			d->yshift = t;
			return 1;
		}
		else
			printf("ERROR! Parameter [dy] is wrong!\n");		
	}
	
	printf("ERROR! Unknown parameter [%s]\n", arg);
	
	return 0;	
}



int read_in(data_t *d)
{
	float x, y;
	int n = 0;
	FILE * pFile;

	pFile = fopen(d->fi, "r");
	if (pFile==NULL)
	{
		printf("ERROR! Cannot to open file %s\n", d->fi);
		return 0;		
	}
	while(fscanf(pFile, "%E\t%E\n", &x, &y)!=EOF)
	{
		if(d->n <= n)
		{
			d->n += 1024;
			d->x = (double*)realloc(d->x, d->n*sizeof(double));
			d->y = (double*)realloc(d->y, d->n*sizeof(double));			
		}
		d->x[n] = x;
		d->y[n] = y;
		n++;		
	}
	d->x = (double*)realloc(d->x, n*sizeof(double));
	d->y = (double*)realloc(d->y, n*sizeof(double));	
	d->n = n;
	fclose(pFile);
	return 1;
}


int write_out(data_t *d)
{
	float x, y;
	int n = 0;
	FILE * pFile;

	pFile = fopen(d->fo, "w");
	if (pFile==NULL)
	{
		printf("ERROR! Cannot to write to file %s\n", d->fi);
		return 0;		
	}
	for(n =0; n < d->n; n++)
		fprintf(pFile, "%E\t%E\n", d->x[n], d->y[n]);
		
	fclose(pFile);
	return 1;
}





void axis_calc(data_t *d)
{
	int n;
	if(d->xauto)
	{
		d->xmin = d->xmax = d->x[0];
		for(n = 0; n < d->n; n++)
		{
			if(d->x[n] < d->xmin)
				d->xmin = d->x[n];
			if(d->x[n] > d->xmax)
				d->xmax = d->x[n];
		}
	}
	if(d->yauto)
	{
		d->ymin = d->ymax = d->y[0];
		for(n = 0; n < d->n; n++)
		{
			if(d->y[n] < d->ymin)
				d->ymin = d->y[n];
			if(d->y[n] > d->ymax)
				d->ymax = d->y[n];
		}
	}
}






int transform(data_t *d)
{
	int n;
	double kx, ky;
	if(d->xmax<=d->xmin)
	{
		printf("ERROR! Parameter [xmin] must to be less than [xmax]\n");
		return 0;
	}
	
	if(d->ymax<=d->ymin)
	{
		printf("ERROR! Parameter [ymin] must to be less than [ymax]\n");
		return 0;
	}
	
	if(d->w <= 0)
	{
		printf("ERROR! Parameter [w] must to be more than zero\n");
		return 0;
	}
	if(d->h <= 0)
	{
		printf("ERROR! Parameter [h] must to be more than zero\n");
		return 0;
	}
	
	
	kx = d->w / (d->xmax - d->xmin) ;
	ky = d->h / (d->ymax - d->ymin) ;
	

	for(n = 0; n < d->n; n++)
	{
		d->y[n] = ky*(d->y[n] - d->ymin) + d->yshift;
		d->x[n] = kx*(d->x[n] - d->xmin);
	}
	return 1;
}






int main(int argc, char* argv[])
{
	data_t data;
	int n = 1;
	memset(&data, 0, sizeof(data_t));
	
	data.xauto = data.yauto = 1;
	
	while(n+1 < argc)
	{
		if(!read_arg(argv[n], argv[n+1], &data))
			return 0;
		n+=2;		
	}
	
	if(!read_in(&data))
		return 0;
	
	axis_calc(&data);
	
	if(!transform(&data))
		return 0;
	
	write_out(&data);
	return 0;

}