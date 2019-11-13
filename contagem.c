/*TODOLIST:
Ocorrencia = alocação dinamica
função print_list deve ser excluida
eliminar o case-sensitive
*/
//Inclusão de bibliotecas
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

//Declaração de novos tipos
    typedef struct lista_duplamente_encadeada
    {
        char chave[100];
        int ocorrencia[10];
        struct lista_duplamente_encadeada* ant;
        struct lista_duplamente_encadeada* prox;
    } no;

    typedef struct cabeca
    {
        no* cabeca;
    } lde;

//Prototipação de Funções
    lde* new_list();
    no* search_in_list(lde*, char[]);
    void print_list(lde*, int);
    void print_list_in_file(lde*, int, FILE*);
    char* tolower_string(char []);

//Main
    int main(int argc, char* argv[])
    {
        //Definição de Variáveis
        FILE* arq_saida, *arq_entrada;
        unsigned int num_param = argc - 2;
        lde* lista;
        no* ptr, *aux;
        char nome_arq_entrada[100], palavra[100];
        
        arq_saida = fopen("resultado.out", "r+");

        for(int i = 0; i < num_param; i++) 
        {    
            strcpy(nome_arq_entrada, argv[i]);
        
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

            //Manipulação de listas & verificação de arquivos
            lista = new_list();
            ptr = lista->cabeca->prox;

            while(fscanf(arq_entrada, "%s ", palavra) != EOF)
            {
                fscanf(arq_entrada, "%s ", palavra);
                strcpy(ptr->chave, tolower_string(palavra));
                
                //Verificação se já existe palavra na lista
                aux = search_in_list(lista, ptr->chave);
                
                if(aux == NULL)
                {
                    fscanf(arq_entrada, "%s ", ptr->chave);
                    ptr->ocorrencia[i]++;
                }
                
                else
                {
                    ptr = aux;
                    ptr->ocorrencia[i]++;    
                }                    
                ptr = ptr->prox;
            }

        }
        
        fclose(arq_entrada);
        fclose(arq_saida);

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

    no* search_in_list(lde* lista, char x[])
    {
        no* p;
        p = lista->cabeca->prox;
        while(p != NULL && p->chave != x)
            p = p->prox;
        
        return p;
    }

    void print_list(lde* lista, int num_elementos)
    {
        no* ptr;
        
        if(lista->cabeca->prox == NULL)
            printf("Lista vazia!\n");

        for(ptr = lista->cabeca->prox; ptr != NULL; ptr = ptr->prox)
        {
            printf("%s \n", ptr->chave);
            for(int i = 0; i < num_elementos; i++)
            {
                printf("%d ", ptr->ocorrencia[i]);
            }
        }
        printf("\n");   
    }

    void print_list_in_file(lde* lista, int num_elementos, FILE* arq_saida)
    {
        no* ptr;
        
        if(lista->cabeca->prox == NULL)
            fprintf(arq_saida, "Lista vazia!\n");

        for(ptr = lista->cabeca->prox; ptr != NULL; ptr = ptr->prox)
        {
            fprintf(arq_saida, "%s ", ptr->chave);
            for(int i = 0; i < num_elementos; i++)
            {
                fprintf(arq_saida, "%d ", ptr->ocorrencia[i]);
            }
        fprintf(arq_saida, "\n");   
        }
    }

    char* tolower_string(char string[])
    {
        int i = 0;
        while (string[i]) 
        {
            string[i] = tolower(string[i]);
            i++;
        }
        return string;
    }