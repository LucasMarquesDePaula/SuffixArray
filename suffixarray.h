#ifndef SUFFIXARRAY_H_INCLUDED
#define SUFFIXARRAY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mergesort.h"
#include "suffix.h"


int *build_suffix_array(char *text, const int text_length)
{
    int *result;
    int i;
    Suffix *suffixes = (Suffix *)malloc(sizeof(Suffix) * text_length);
    
    for (i = 0; i < text_length; i++)
    {
        suffixes[i].index = i;
        suffixes[i].suffix = &text[i];
        printf("Ent: %s\n", suffixes[i].suffix);
    }

    // aumenta a complexidade do algoritmo
    // quicksort(sufixos, sufixos + n, cmp); 
    merge_sort(suffixes, 0, text_length - 1);
    result = (int *)malloc(sizeof(int) * text_length);
    for (i = 0; i < text_length; i++) {
        result[i] = suffixes[i].index;
    }
    free(suffixes);
    return result;
}

int find(char *key, char *txt, const int *suffixes, int suffixes_length)
{
    int key_length = strlen(key);
    // Binary search
    int left = 0, right = suffixes_length - 1;
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