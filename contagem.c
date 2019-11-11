//TODOLIST: laço de repetição para incrementar para todos os argumentos, basta incrementar o argv
//Inclusão de bibliotecas
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

//Declaração de novos tipos
    typedef struct lista_duplamente_encadeada
    {
        char chave[100];
        int ocorrencia;
        struct lista_duplamente_encadeada* ant;
        struct lista_duplamente_encadeada* prox;
    } no;

    typedef struct cabeca
    {
        no* cabeca;
    } lde;

//Prototipação de Funções
    lde* new_list();
    no* search_in_list(lde*, char);
    void print_list(lde*);

//Main
    int main(int argc, char* argv[])
    {
        //Definição de Variáveis
            FILE* arq_saida, *arq_entrada;
            unsigned int num_param = argc - 2;
            lde* lista;
            no* ptr;
            char nome_arq_entrada[100];
            
            strcpy(nome_arq_entrada, argv[0]);
        //Tratamento de erros de entrada
            arq_entrada = fopen(nome_arq_entrada, "r");
            
            if(arq_entrada == NULL)
            {
                printf("Entrada inválida!\n");
                exit(1);
            }

            if(argc == 1) 
            {
                printf("Entrada inválida!");
                exit(1);
            }

            arq_saida = fopen("resultado.out", "r+");

        //Manipulação de listas & verificação de arquivos

            lista = new_list();
            ptr = lista->cabeca->prox;
 
            while(fscanf(arq_entrada, "%s ", ptr->chave) != EOF)
            {
                fscanf(arq_entrada, "%s ", ptr->chave);
                ptr->ocorrencia++;
                ptr = ptr->prox;
            }


        

         
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

    no* search_in_list(lde* lista, char x)
    {
        no* p;
        p = lista->cabeca->prox;
        while(p != NULL && p->chave != x)
            p = p->prox;
        
        return p;
    }

    void print_list(lde* lista)
    {
        no* ptr;
        
        if(lista->cabeca->prox == NULL)
            printf("Lista vazia!\n");

        for(ptr = lista->cabeca->prox; ptr != NULL; ptr = ptr->prox)
            printf("%s %d\n", ptr->chave, ptr->ocorrencia);

        printf("\n");   
    }