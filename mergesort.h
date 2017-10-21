#ifndef MERGESORT_H_INCLUDED
#define MERGESORT_H_INCLUDED

#include <stdlib.h>
#include <string.h>

#include "suffix.h"

void suffix_merge(Suffix *suffixes, const int beginning, const int middle, const int end)
{
    int com1 = beginning, com2 = middle + 1, com_aux = 0;
    Suffix *suffix_aux = (Suffix *)malloc(sizeof(Suffix) * end - beginning + 1);
    while (com1 <= middle && com2 <= end)
    {
        if (strcmp(suffixes[com1].suffix, suffixes[com2].suffix) <= 0)
        {
            suffix_aux[com_aux] = suffixes[com1];
            com1++;
        }
        else
        {
            suffix_aux[com_aux] = suffixes[com2];
            com2++;
        }
        com_aux++;
    }
    while (com1 <= middle)
    {
        suffix_aux[com_aux] = suffixes[com1];
        com_aux++;
        com1++;
    }
    while (com2 <= end)
    {
        suffix_aux[com_aux] = suffixes[com2];
        com_aux++;
        com2++;
    }
    for (com_aux = beginning; com_aux <= end; com_aux++)
    {
        suffixes[com_aux] = suffix_aux[com_aux - beginning];
    }
}

void suffix_merge_sort(Suffix *suffixes, const int beginning, const int end)
{
    int middle;
    if (beginning < end) {
        middle = (end + beginning) / 2;
        suffix_merge_sort(suffixes, beginning, middle);
        suffix_merge_sort(suffixes, middle + 1, end);
        suffix_merge(suffixes, beginning, middle, end);
    }
}

#endif