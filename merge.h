#ifndef MERGE_H_INCLUDED
#define MERGE_H_INCLUDED

#include <stdlib.h>
#include <string.h>

int *merge_suffix_array(char *text1, int *suffixes1, int suffixes1_length, char *text2, int *suffixes2, int suffixes2_length) {
    
    int beginning = 0,
        middle = suffixes1_length - 1,
        end = suffixes1_length + suffixes2_length - 2;

    int *sulffixes_aux = (int *)malloc(sizeof(int) * end);

    int com1 = beginning,
        com2 = beginning,
        com_aux = beginning;
    
    while (com1 <= middle && com2 + middle <= end)
    {
        if (strcmp(text1 + suffixes1[com1], text2 + suffixes2[com2]) < 0)
        {
            sulffixes_aux[com_aux] = suffixes1[com1];
            com1++;
        }
        else
        {
            sulffixes_aux[com_aux] = suffixes2[com2] + middle + 1;
            com2++;
        }
        com_aux++;
    }
    
    while (com1 <= middle)
    {
        sulffixes_aux[com_aux] = suffixes1[com1];
        com_aux++;
        com1++;
    }

    while (com2 <= end)
    {
        sulffixes_aux[com_aux] = suffixes2[com2] + middle + 1;
        com_aux++;
        com2++;
    }
    return sulffixes_aux;
}

#endif
