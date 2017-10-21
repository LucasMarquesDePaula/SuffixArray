#ifndef KASAI_H_INCLUDED
#define KASAI_H_INCLUDED

#include <stdlib.h>

// Longest Common Prefix
int *lcp_kasai(const char *txt, int *suffixes, int n)
{
    int *lcp = NULL, *inv = NULL;
    int i, j, k;

    lcp = (int *)malloc(sizeof(int) * n);

    // Mem was allocated
    if (lcp == NULL)
    {
        return NULL;
    }


    inv = (int *)malloc(sizeof(int) * n);

    // Mem was allocated
    if (inv == NULL)
    {
        free(lcp);
        return NULL;
    }


    // Fill initial data
    for (i = 0; i < n; i++)
    {
        lcp[i] = 0;
        inv[suffixes[i]] = i;
    }


    // Main algorithm
    for (i = 0, k = 0; i < n; i++)
    {
        if (inv[i] == n - 1)
        {
            k = 0;
            continue;
        }
        /**
        * j keeps the index of next substring
        * to be considered on the comparation with the
        * current substring or the next string in the suffix array
        */
        j = suffixes[inv[i] + 1];

        while (i + k < n && j + k < n && txt[i + k] == txt[j + k])
        {
            k++;
        }

        lcp[inv[i]] = k;

        if (k > 0)
        {
            k--;
        }

    }

    free(inv);
    return lcp;
}

#endif