#include <stdlib.h>
#include <stdio.h>
#include "algorytmy.h"
// wszystkie procz heap sorta dzialaja na tablicach z wartownikiem na indeksie 0

void bubble_sort(int *tab, int n)
{
    // indeksowanie od takich elementów, ponieważ tablica ma wartownika na początku i na końcu
    int x;
    int change;
    do
    {   
        change = 0;
        for(int i = 2; i <= n; i++)
        {
            if(tab[i] < tab[i-1])
            {
                x = tab[i];
                tab[i] = tab[i-1];
                tab[i-1] = x;
                change = 1;
            }
        }
    } while (change);
}

void insertion_sort(int *tab, int n)
{
    int x;
    int i = 2, j;
    while(i <= n)
    {
        x = tab[i];
        j = i;
        while(x < tab[j - 1])
        {
            tab[j] = tab[j - 1];
            j--;
        }
        tab[j] = x;
        i++;
    }
}

// selection sort z minimum i maksimum
void selection_sort(int *tab, int n)
{
    int i = 1;
    // int j = n;
    int k, min, help;
    while(i <= n)
    {
        min = i;
        for(k = i + 1; k <= n; k++)
        {
            if(tab[k] < tab[min])
            {
                min = k;
            }
            
        }
        help = tab[min];
        tab[min] = tab[i];
        tab[i] = help;
        i++;
    }
}

void shell_sort(int *tab, int n)
{
    int x;
    int i = 2, j, k = n >> 1;
    while(k > 0)
    {
        i = k + 1;
        while(i <= n)
        {
            x = tab[i];
            j = i;
            while(j >= k && x < tab[j - k])
            {
                tab[j] = tab[j - k];
                j -= k;
            }
            tab[j] = x;
            i++;
        }
        k = k >> 1;
    }
}

void quick_sort_main(int *tab, int n)
{
    quick_sort(tab, 1, n);
}

void quick_sort(int *tab, int a, int b)
{
    if(a < b)
    {
        int pi = partition(tab, a, b);
        quick_sort(tab, a, pi - 1);
        quick_sort(tab, pi+1, b);
    }
}

int partition(int *tab, int a, int b)
{
    int pivot = tab[b];
    int i = a - 1;
    int help;
    for(int j = a; j <= b - 1; j++)
    {
        if(tab[j] < pivot)
        {
            i++;
            help = tab[i];
            tab[i] = tab[j];
            tab[j] = help;
        }
    }
    help = tab[i+1];
    tab[i+1] = tab[b];
    tab[b] = help;
    return (i + 1);
}

void heap_sort(int *tab, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heap(tab, n, i);
    }

    for(int i = n - 1; i >= 0; i --)
    {
        int help = tab[0];
        tab[0] = tab[i];
        tab[i] = help;
        heap(tab, i, 0);
    }
}

void heap(int *tab, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if(left < n && tab[left] > tab[largest])
    {
        largest = left;
    }

    if(right < n && tab[right] > tab[largest])
    {
        largest = right;
    }

    if(largest != i)
    {
        int help = tab[i];
        tab[i] = tab[largest];
        tab[largest] = help;
        heap(tab, n, largest);
    }
}