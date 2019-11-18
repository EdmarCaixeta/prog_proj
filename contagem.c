/*TODOLIST:
Ocorrencia = alocação dinamica
função print_list deve ser excluida
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
    int list_lenght(lde*);

//Main
    int main(int argc, char* argv[])
    {
        //Definição de Variáveis
        FILE* arq_saida, *arq_entrada;
        int num_param = argc, list_len;
        lde* lista;
        no* ptr, *aux;
        char nome_arq_entrada[100], palavra[100];
        
        arq_saida = fopen("resultado.out", "w");

        lista = new_list();
        ptr = lista->cabeca->prox;
        
        printf("ARGC = %d\n", argc);
        printf("ARGV = %s\n", argv[2]);
        /*for(int i = 2; i < num_param; i++) 
        { */  
            strcpy(nome_arq_entrada, argv[2]);
            //printf("I = %d\n", i);
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
            while(fscanf(arq_entrada, "%s", palavra) != EOF)
            {
                printf("%s\n", palavra); 
                
                //Verificação se já existe palavra na lista
                aux = search_in_list(lista, palavra);
                
                if(aux == NULL)
                {
                    //printf("NULL case\n");
                    strcpy(ptr->chave, tolower_string(palavra));
                    //printf("strcpy case\n");
                    ptr->ocorrencia[0]++;
                }
                
                else
                {
                    ptr = aux;
                    ptr->ocorrencia[0]++;    
                }                    
                
                //ptr = ptr->prox;
            }
        
        fclose(arq_entrada);
        //}
        list_len = list_lenght(lista);
        print_list(lista, list_len);
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
        
        printf("busca\n");
        return p;
    }

    void print_list(lde* lista, int num_elementos)
    {
        no* ptr;
        if(lista->cabeca->prox == NULL)
            printf("Lista vazia!\n");

        for(ptr = lista->cabeca->prox; ptr != NULL; ptr = ptr->prox)
        {
            printf("%s ", ptr->chave);
            for(int i = 0; i < num_elementos; i++)
            {
                printf("%d ", ptr->ocorrencia[i]);
            }
        }
        printf("\n");   
    }

    void print_list_in_file(lde* lista, int lista_length, FILE* arq_saida)
    {
        no* ptr;
        
        if(lista->cabeca->prox == NULL)
            fprintf(arq_saida, "Lista vazia!\n");

        for(ptr = lista->cabeca->prox; ptr != NULL; ptr = ptr->prox)
        {
            fprintf(arq_saida, "%s ", ptr->chave);
            for(int i = 0; i < lista_length; i++)
            {
                fprintf(arq_saida, "%d ", ptr->ocorrencia[i]);
            }
        fprintf(arq_saida, "\n");   
        }
    }

    char* tolower_string(char str[])
    {
        int i = 0;
        while (str[i]) 
        {
            str[i] = tolower(str[i]);
            i++;
        }
        return str;
    }

    int list_lenght(lde* lista)
    {
        int len = 0;
        no* ptr;
        for(ptr = lista->cabeca->prox; ptr != NULL; ptr = ptr->prox)
            len++;
        return len;
    }

    void insere_lcc(lcc* l, int y, no* p)
    {
        no* novo;
        
        novo = (no*) malloc(sizeof(no));
        
        novo->chave = y;    
        novo->prox = p->prox;
        p->prox = novo; 
    }