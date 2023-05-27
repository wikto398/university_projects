#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algorytmy.h"

void reverse(int *tab, int n)
{
    int i = n, k;
    FILE *f;
    f = fopen("dane.txt", "r");
    while(i > 0)
    {
        fscanf(f,"%d", &k);
        tab[i] = k;
        i--;
    }
    tab[0] = -101;
    fclose(f);
}

void enter_dane(int *tab, int n)
{
    int i = 1, k;
    FILE *f;
    f = fopen("dane.txt", "r");
    while(i <= n)
    {
        fscanf(f,"%d", &k);
        tab[i] = k;
        i++;
    }
    tab[0] = -101;
    fclose(f);
}

void write_tab(int *tab, int n)
{
    FILE *f;
    f = fopen("dane.txt", "w");
    for(int i = 1; i <= n; i++)
    {
        fprintf(f,"%d\n", tab[i]);
    }
    fclose(f);
}

int test_sort(int n);

// funkcja ułatwiająca testowanie algorytmów sortowania
void test(int *tab, int n, void func(int*, int), char* name, int wart)
{
    int *tab_cp;
    if(wart == 1)
    {
        tab_cp = malloc(sizeof(int)*(n+1));
        for(int i = 0; i<=n; i++)
        {
            tab_cp[i] = tab[i]; 
        }
    }
    else
    {
        tab_cp = malloc(sizeof(int)*n);
        for(int i = 1; i<=n; i++)
        {
            tab_cp[i-1] = tab[i]; 
        }
    }
    
    double time_taken;
    clock_t t;
    t = clock();
    func(tab_cp, n);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("Czas sortowania z uzyciem %s = %.10lf sekund\n", name, time_taken);
    FILE *f;
    f = fopen("czasy.txt", "a");
    fprintf(f, "%.10lf \n", time_taken);
    fclose(f);
    write_tab(tab_cp, n);
    printf("Wpisano tablice do pliku dane\n");
    int err = test_sort(n);
    if(err == 1)
    {
        printf("Dane poprawnie posortowane\n\n");
    }
    else
    {
        printf("Dane blednie posortowane\n");
        printf("Blad na indeksie %d\n\n",err);
    }
    free(tab_cp);
}

// funkcja testująca poprawność sortowania
int test_sort(int n)
{
    FILE *f;
    int n1,n2;
    f = fopen("dane.txt", "r");
    fscanf(f, "%d", &n1);
    for(int i = 1; i < n; i++)
    {
        fscanf(f, "%d", &n2);
        if(n2 < n1)
        {
            return i;
        }
        n1 = n2;
    }
    fclose(f);
    return 1;
}

int main()
{
    int n;
    printf("Podaj dlugosc tablicy\n");
    scanf("%d", &n);
    int *tab;
    tab = malloc(sizeof(int)*(n+1));
    for(int i = 1; i<=n; i++)
    {
        tab[i] = rand() % 201 - 100; 
    }
    tab[0] = -101;

    test(tab, n, bubble_sort,"bubble_sort", 1);

    test(tab, n, insertion_sort, "insertion_sort", 1);

    test(tab, n, selection_sort, "selection_sort", 1);

    test(tab, n, shell_sort, "shell_sort", 1);

    test(tab, n, quick_sort_main, "quick_sort", 1);

    test(tab, n, heap_sort, "heap_sort", 0);

    printf("Zakonczono Testy 1\n");

    enter_dane(tab, n);

    test(tab, n, bubble_sort,"bubble_sort", 1);

    test(tab, n, insertion_sort, "insertion_sort", 1);

    test(tab, n, selection_sort, "selection_sort", 1);

    test(tab, n, shell_sort, "shell_sort", 1);

    test(tab, n, quick_sort_main, "quick_sort", 1);

    test(tab, n, heap_sort, "heap_sort", 0);

    printf("Zakonczono Testy 2\n");

    reverse(tab, n);
    
    test(tab, n, bubble_sort,"bubble_sort", 1);

    test(tab, n, insertion_sort, "insertion_sort", 1);

    test(tab, n, selection_sort, "selection_sort", 1);

    test(tab, n, shell_sort, "shell_sort", 1);

    test(tab, n, quick_sort_main, "quick_sort", 1);

    test(tab, n, heap_sort, "heap_sort", 0);

    printf("Zakonczono Testy 3\n");
}