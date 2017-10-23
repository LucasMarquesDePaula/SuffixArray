#include <stdio.h>
#include <string.h>

#include "mergesort.h"
#include "merge.h"
#include "kasai.h"
#include "suffixarray.h"

#define MAX_BUFFER 65536

void test1();
void test2();

int main(int argc, char *argv[])
{
    test2();
    getchar();
}

void test2() {
    char *text1 = "banana";
    char *text2 = "bacana";

    int length1 = strlen(text1);
    int length2 = strlen(text2);
    int length3 = length1 + length2;

    char *text3 = (char *)malloc(sizeof(char) * (length3 + 1));
    text3[0] = '\0';
    strcat(text3, text1);
    // strcat(text3, "$");
    strcat(text3, text2);

    int *suffixes1 = build_suffix_array(text1, length1);
    int *suffixes2 = build_suffix_array(text2, length2);
    int *suffixes3 = build_suffix_array(text3, length3);

    int *suffixes_merged = merge(text1, suffixes1, length1, text2, suffixes2, length2);

    int i;

    printf("%s\n", text1);
    for (i = 0; i < length1; i++)
    {
        printf("%3d  %s\n", suffixes1[i], &text1[suffixes1[i]]);
    }

    printf("%s\n", text2);
    for (i = 0; i < length2; i++)
    {
        printf("%3d  %s\n", suffixes2[i], &text2[suffixes2[i]]);
    }

    printf("%s\n", text3);
    for (i = 0; i < length3; i++)
    {
        printf("%3d  %s\n", suffixes3[i], &text3[suffixes3[i]]);
    }

    printf("%s\n", text3);
    for (i = 0; i < length3; i++)
    {
        printf("%3d  %s\n", suffixes_merged[i], &text3[suffixes_merged[i]]);
    }


}

void test1() {
    char buffer[MAX_BUFFER];
    int *suffixes = NULL, i, buffer_length;
    int *lcp = NULL;

    printf("Texto: ");
    gets(buffer);
    buffer_length = strlen(buffer);

    suffixes = build_suffix_array(buffer, buffer_length);

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
}