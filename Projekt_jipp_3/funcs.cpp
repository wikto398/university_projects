#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

extern void error(int, char*);

char** allocate_tab(FILE *f, int n)
{
	int i, k = 0;
	double** tab = (double**)malloc(sizeof(double*) * n);
	int p;
	if (!tab)
	{
		error(3, "Macierz");
	}
	while (k < n)
	{
		tab[k] = malloc(sizeof(double) * (n - k));
		for (int i = 0; i < (n - k); i++)
		{
			p = fscanf(f, "%lf", &tab[k][i]);
				if (p == 0 || p == EOF)
			{
				error(5, "macierz");
			}
		}
		k++;
	}
	return tab;
}

char* allocate_vec(FILE* f, int n)
{
	int i, k = 0;
	double* vec = (double*)malloc(sizeof(double) * n);
	int p;
	if (!vec)
	{
		error(3, "wektor");
	}

	for (int i = 0; i < n; i++)
	{
		p = fscanf(f, "%lf", &vec[i]);
		if (p == 0 || p == EOF)
		{
			error(5, "wektor");
		}
	}
	return vec;
}

void M_x_V(double **tab, double *vd, double *vw, int n)
{
	int j, k;
	double* dd;
	for (k = 0; k < n; k++)
	{	
		vw[k] = 0;
		j = 0;
		while (j < k)
		{
			vw[k] += tab[j][k-j] * vd[j];
			j++;
		}
		dd = tab[k];
		while(j < n)
		{
			vw[k] += *dd * vd[j];
			j++;
			dd++;
		}
	}
}

void free_matrix(double** tab, int n)
{
	if (tab)
	{
		int i = 0;
		while (i < n)
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	tab = NULL;
}