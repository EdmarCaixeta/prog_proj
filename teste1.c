#include <stdio.h>
#include <string.h>

int main()
{
    FILE* arq_entrada;
    char palavra[100];
    int i;
    arq_entrada = fopen("teste1.txt", "rt");
    while(fscanf(arq_entrada, "%s ", &palavra) != EOF)
        printf("%s ", palavra);
}