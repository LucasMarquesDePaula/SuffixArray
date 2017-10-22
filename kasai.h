#ifndef KASAI_H_INCLUDED
#define KASAI_H_INCLUDED

#include <stdlib.h>

// Longest Common Prefix by Kasai
int *lcp_kasai(const char *text, int *suffixes, int suffixes_length)
{
    int *lcp = NULL, *inv = NULL;
    int i, j, k;

    lcp = (int *)malloc(sizeof(int) * suffixes_length);

    // Mem was allocated
    if (lcp == NULL)
    {
        return NULL;
    }


    inv = (int *)malloc(sizeof(int) * suffixes_length);

    // Mem was allocated
    if (inv == NULL)
    {
        free(lcp);
        return NULL;
    }


    // Fill initial data
    for (i = 0; i < suffixes_length; i++)
    {
        lcp[i] = 0;
        inv[suffixes[i]] = i;
    }


    /**
     * Main algorithm
     */

    // Initialize length of previous LCP
    k = 0;


    // Process all suffixes one by one starting from
    // first suffix in txt[]
    for (i = 0, k = 0; i < suffixes_length; i++)
    {

        //  If the current suffix is at n-1, then we don’t
        // have next substring to consider. So lcp is not
        // defined for this substring, we put zero. 
        if (inv[i] == suffixes_length - 1)
        {
            k = 0;
            continue;
        }


        //  j contains index of the next substring to
        // be considered  to compare with the present
        // substring, i.e., next string in suffix array
        j = suffixes[inv[i] + 1];

        // Directly start matching from k'th index as
        // at-least k-1 characters will match
        while (i + k < suffixes_length && j + k < suffixes_length && text[i + k] == text[j + k])
        {
            k++;
        }

        lcp[inv[i]] = k;

        // Deleting the starting character from the string.
        if (k > 0)
        {
            k--;
        }

    }

    free(inv);
    return lcp;
}

#endif