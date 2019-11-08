//Inclusão de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declaração de novos tipos
typedef struct lista_duplamente_encadeada
{
    unsigned char chave[100];
    struct lista_duplamente_encadeada* ant;
    struct lista_duplamente_encadeada* prox;
} no;

typedef struct cabeca
{
    no* cabeca;
} lde;

//Prototipação de Funções
lde* new_list();
no* search_in_list(lde*, int);

//Main
int main(int argc, char* argv[])
{
    //Declaração de Variáveis
    FILE* arq_saida;
    unsigned int num_param = argc - 2;
    lde* lista = new_list();
    
    //Tratamento de erros de entrada
        //TODO: tratamento caso o arquivo não seja encontrado
    if(argc == 1) {
        printf("Entrada inválida!");
        exit(1);
    }

    arq_saida = fopen("resultado.out", "r+");

     
}

//Definição de Funções
lde* new_list()
{
    lde* lista = (lde*) malloc(sizeof(lde));

    lista->cabeca = (no*) malloc(sizeof(no));
    lista->cabeca->ant = NULL;
    lista->cabeca->prox = NULL;

    return lista;
}

no* search_in_list(lde* lista, int x)
{
    no* p;
    p = lista->cabeca->prox;
    while(p != NULL && p->chave !=x)
        p = p->prox;
    
    return p;
}