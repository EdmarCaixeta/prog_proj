#include <stdio.h>

int main()
{
    char palavra[100];
    scanf("%29[A-Za-zÀ-ú]", &palavra);
    printf("%s ", palavra);
}