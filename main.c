#include <stdio.h>
#include <string.h>

#include "mergesort.h"
#include "merge.h"
#include "kasai.h"
#include "suffixarray.h"

#define MAX_BUFFER 65536

void test1();
int test2();
void print_suffixes(char *text, int *suffixes, int length);

int main(int argc, char *argv[])
{
    return test2();
}

int test2() {
    char *text1 = "macabra";
    char *text2 = "abracadabra";

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

    int *suffixes_merged = merge_suffix_array(text1, suffixes1, length1, text2, suffixes2, length2);

    int i;

    printf("\n\n");
    printf("###############################\n");
    printf("# Suffix Arrays de cada texto #\n");
    printf("###############################\n");

    printf("\n\n");
    printf("build_suffix_array\n");
    print_suffixes(text1, suffixes1, length1);

    printf("\n\n");
    printf("build_suffix_array\n");
    print_suffixes(text2, suffixes2, length2);


    printf("\n\n");
    printf("#################################\n");
    printf("# Suffix Arrays da concatenacao #\n");
    printf("#################################\n");

    printf("\n\n");
    printf("build_suffix_array\n");
    print_suffixes(text3, suffixes3, length3);

    printf("\n\n");
    printf("merge_suffix_array\n");
    print_suffixes(text3, suffixes_merged, length3);

    // Validação:
    //  suffixes_merged e suffixes3 foram construidos 
    // com funcoes diferentes. Porem devem ser iguais
    for (i = 0; i < length3; i++) 
    {
        if (suffixes3[i] != suffixes_merged[i])
        {
            printf("# Erro:\n");
            printf("# build_suffix_array != merge_suffix_array\n");
            printf("# Indíce: %d, build_suffix_array: %d, merge_suffix_array: %d\n", i, suffixes3[i], suffixes_merged[i]);
           return 1;
        }
    }

    printf("\n\n");
    printf("# Sucesso:\n");
    printf("# build_suffix_array == merge_suffix_array\n");
    return 0;
}

void test1() {
    char buffer[MAX_BUFFER];
    int *suffixes = NULL, i, buffer_length;
    int *lcp = NULL;

    printf("# Texto: ");
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

void print_suffixes(char *text, int *suffixes, int length) {
    int i;

    int *lcp = lcp_kasai(text, suffixes, length);

    printf("SA   LCP  Sufixos\n");
    for (i = 0; i < length; i++)
    {
        printf("%3d  %3d  %s\n", suffixes[i], lcp[i], &text[suffixes[i]]);
    }
    free(lcp);
}