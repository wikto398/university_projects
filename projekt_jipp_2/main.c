#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#pragma warning(disable: 4996)

#define MAX_LINES 1000
#define MAX_LINE 1000

FILE* fd;
FILE* fw;

int main(int argc, char** argv)
{
    char windows[] = { -91, -58, -54, -93, -47, -45, -116, -113, -81, -71, -26, -22, -77, -15, -13, -100, -97, -65 };
    char dos[] = { -92, -113, -88, -99, -29, -32, -105, -115, -67, -91, -122, -87, -120, -28, -94, -104, -85, -66 };
    char* d[MAX_LINES], bufor[MAX_LINE];
    setlocale(LC_ALL, "Polish_Poland.1250");
    int len, i;
    if (argc != 3)
    {
        fprintf(stderr, "Zła liczba argumentów\n");
        exit(1);
    }
    if (!(fd = fopen(argv[1], "r")))
    {
        fprintf(stderr, "Blad otwarcia zbioru danych\n");
        exit(2);
    }
    if (!(fw = fopen(argv[2], "w")))
    {
        fprintf(stderr, "Blad otwarcia zbioru wyników\n");
        exit(3);
    }
    i = 0;
    while (i < MAX_LINES && fgets(bufor, MAX_LINE, fd))
    {
        len = strlen(bufor);
        bufor[len - 1] = '\0';
        if (!(d[i] = (char*)malloc((unsigned)len)))
        {
            printf("Brak pamieci\n");
            exit(4);
        }
        strcpy(d[i], bufor);
        i++;
    }
    d[i] = (char*)0;
    char* dd = NULL;
    char tekst[MAX_LINE];
    printf("Podaj tekst \n");
    if (fgets(tekst, MAX_LINE, stdin))
    {
        len = strlen(tekst);
        tekst[len - 1] = '\0';
        for (int g = 0; g < len - 1; g++)
        {
            for (int h = 0; h < 18; h++)
                if (tekst[g] == dos[h])
                {
                    tekst[g] = windows[h];
                    break;
                }
        }
        int end;
        char* ddl = NULL;
        i = 0;
        while (i < MAX_LINES && d[i] != NULL)
        {
            end = 1;
            dd = d[i];
            while (*dd != '\0')
            {
                if (*tekst == *dd)
                {
                    int k;
                    ddl = dd;
                    dd++;
                    for (k = 1; k < len - 1; k++)
                    {
                        if (tekst[k] != *dd) break;
                        dd++;
                    }
                    if (k == len - 1)
                    {
                        end = 0;
                        break;
                    }
                    dd = ddl;
                }
                dd++;
            }
            if (end == 1)
            {
                dd = d[i];
                while (*dd != '\0')
                {
                    fprintf(fw, "%c", *dd);
                    dd++;
                }
                fprintf(fw, "\n");
            }
            i++;
        }
        return 0;
    }
    else
    {
        fprintf(stderr, "Błąd wczytywania linijki");
        return -1;
    }
}
