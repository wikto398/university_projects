#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
extern void error(int, char*);
extern double** allocate_tab(FILE*, int);
extern double* allocate_vec(FILE*, int);
extern void M_x_V(double**, double*, double*, int);
extern void free_matrix(double**, int);

void argumenty(int argc, char* argv[])
{
	int len;
	char* usage;
	if (argc != 3)
	{
		len = strlen(argv[0]) + 19;
		if (!(usage = (char*)malloc((unsigned)len * sizeof(char))))
			error(3, "tablica usage");
		strcpy(usage, argv[0]);
		strcat(usage, " file_in file_out");
		error(4, usage);
	}
}

int main(int argc, char* argv[])
{
	double** tab;
	double* vec, *mac_x_vec;
	FILE* fd, * fw;
	int n, err;
	argumenty(argc, argv);
	if (!(fd = fopen(argv[1], "r"))) error(2, "dane");
	if (!(fw = fopen(argv[2], "w"))) error(2, "wyniki");
	err = fscanf(fd, "%d", &n);
	if (err == 0 || err == EOF)
	{
		error(5, "dlugosc tablicy");
	}
	tab = allocate_tab(fd, n);
	for (int k = 0; k < n; k++)
	{
		printf("Tab[%d] - ", k);
		for (int i = 0; i < (n - k); i++)
		{
			printf("%lf, ", tab[k][i]);
		}
		printf(" ");
	}
	printf("\n");
	vec = allocate_vec(fd, n);
	printf("Vec - ");
	for (int i = 0; i < n; i++)
	{
		printf("%lf, ", vec[i]);
	}
	printf("\n");
	mac_x_vec = (double*)malloc(sizeof(double) * n);
	if (!mac_x_vec)
	{
		error(3, "Wektor");
	}
	M_x_V(tab, vec, mac_x_vec, n);
	free_matrix(tab, n);
	if (vec)
	{
		free(vec);
		vec = NULL;
	}
	printf("Mac_x_Vec - ");
	for (int i = 0; i < n; i++)
	{
		fprintf(stdout, "%lf, ", mac_x_vec[i]);
		fprintf(fw,"%lf, ", mac_x_vec[i]);
	}
	if (mac_x_vec)
	{
		free(mac_x_vec);
		mac_x_vec = NULL;
	}
	return 0;
}
