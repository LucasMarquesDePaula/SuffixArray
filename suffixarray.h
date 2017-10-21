#ifndef SUFFIXARRAY_H_INCLUDED
#define SUFFIXARRAY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "suffix.h"
#include "mergesort.h"

int *make_suffix_array(const char *text, const int text_len)
{
    Suffix *suffixes;
    int *result;
    int i;
    suffixes = (Suffix *)malloc(sizeof(Suffix) * text_len);
    for (i = 0; i < text_len; i++)
    {
        suffixes[i].index = i;
        suffixes[i].suffix = (text + i);
        printf("Ent: %s\n", suffixes[i].suffix);
    }
    /* aumenta a complexidade do algoritmo
    quicksort( sufixos, sufixos+n, cmp); */
    merge_sort(suffixes, 0, text_len - 1);
    result = (int *)malloc(sizeof(int) * text_len);
    for (i = 0; i < text_len; i++) {
        result[i] = suffixes[i].index;
    }
    free(suffixes);
    return result;
}

int find(char *key, char *txt, const int *suffixes, int suffixes_size)
{
    int key_length = strlen(key);
    // Binary search
    int left = 0, right = suffixes_size - 1;
    int middle, cmp;
    while (left <= right)
    {
        middle = left + (right - left) / 2;

        cmp = strncmp(key, txt + suffixes[middle], key_length);

        if (cmp == 0)
        {
            return middle;
        }

        if (cmp < 0)
        {
            right = middle - 1;
        }
        else
        {
            left = middle + 1;
        }

    }
    return -1;
}

#endif