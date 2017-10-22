#include <stdio.h>

#include "mergesort.h"
#include "kasai.h"
#include "suffixarray.h"

#define MAX_BUFFER 65536

int main(int argc, char *argv[])
{
    char buffer[MAX_BUFFER];
    int *suffixes = NULL, i, buffer_length;
    int *lcp = NULL;

    printf("Texto: ");
    gets(buffer);
    buffer_length = strlen(buffer);

    suffixes = build_suffixes(buffer, buffer_length);

    for (i = 0; i < buffer_length; i++) 
    {
        printf("%3d  %s\n", suffixes[i], &buffer[suffixes[i]]);
    }

    // teste para busca exata
    printf("Busca pelo padrao %s\n", buffer + 1);
    i = find(buffer + 1, buffer, suffixes, buffer_length);
    printf("i=%d sa=%d  sufixo: %s\n", i, i >= 0 ? suffixes[i] : -1, i >= 0 ? &buffer[suffixes[i]] : "");

    // construcao do vetor lcp - longest common prefix
    lcp = lcp_kasai(buffer, suffixes, buffer_length);
    printf("SA   LCP  Sufixos\n");
    for (i = 0; i < buffer_length; i++) 
    {
        printf("%3d  %3d  %s\n", suffixes[i], lcp[i], &buffer[suffixes[i]]);
    }


    free(suffixes);

    // getchar();

}