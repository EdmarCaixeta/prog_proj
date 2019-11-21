//Inclusão de bibliotecas
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

//Declaração de novos tipos
    typedef struct lista_duplamente_encadeada
    {
        unsigned char chave[100];
        unsigned int ocorrencia[10];
        struct lista_duplamente_encadeada* ant;
        struct lista_duplamente_encadeada* prox;
    } no;

    typedef struct cabeca
    {
        no* cabeca;
    } lde;

//Prototipação de Funções
    lde* new_list();
    no* search_in_list(lde*, unsigned char[]);
    void print_list_in_file(lde*, int, FILE*);
    unsigned char* tolower_string(unsigned char []);
    void insert_in_list(lde*, unsigned char*, no*, int, int);
    unsigned char* rmv_special_char(unsigned char []);
    void search_and_insert(lde*, unsigned char*);
    void fix_ocorrencias(lde* , int );

//Main
    int main(int argc, unsigned char* argv[])
    {
        //Definição de Variáveis
        FILE* arq_saida, *arq_entrada;
        int num_param = argc - 2, list_len;
        lde* lista;
        no* ptr, *aux;
        unsigned char nome_arq_entrada[100], palavra[100];
        
        arq_saida = fopen("resultado.out", "w");

        lista = new_list();
        ptr = lista->cabeca->prox;
        for(int i = 0; i < num_param; i++) 
        {   
            strcpy(nome_arq_entrada, argv[i+2]);
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
            while(fscanf(arq_entrada, "%s", &palavra) != EOF)
            {
                //Remove pontuação
                strcpy(palavra, rmv_special_char(palavra));
                //Verificação se já existe palavra na lista
                
                aux = search_in_list(lista, palavra);

                if(aux == NULL)
                {
                    insert_in_list(lista, palavra, lista->cabeca, i, num_param);
                }
                
                else
                {
                    ptr = aux;
                    ptr->ocorrencia[i]++;    
                }                    
                
            }
        
        fclose(arq_entrada);
        }
        print_list_in_file(lista, num_param, arq_saida);
        fclose(arq_saida);
    }

//Definição de Funções
//->Funções relacionadas a Listas
    lde* new_list()
    {
        lde* lista = (lde*) malloc(sizeof(lde));

        lista->cabeca = (no*) malloc(sizeof(no));
        lista->cabeca->ant = NULL;
        lista->cabeca->prox = NULL;

        return lista;
    }

    no* search_in_list(lde* lista, unsigned char x[])
    {
        no* p;
        p = lista->cabeca->prox;
        while(p != NULL && strcmp(x, p->chave) != 0) 
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
            printf("%s ", ptr->chave);
            for(int i = 0; i < num_elementos; i++)
            {
                printf("%d ", ptr->ocorrencia[i]);
            }
        printf("\n");   
        }
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

    void insert_in_list(lde* lista, unsigned char* chave, no* ptr, int indice, int n_arquivos)
    {
        no* novo;
        
        novo = (no*) malloc(sizeof(no));
        
        strcpy(novo->chave, tolower_string(chave));
        for(int i = 0; i < n_arquivos; i++)
        {
            novo->ocorrencia[i] = 0;
        }
        novo->ocorrencia[indice] = 1;    
        novo->prox = ptr->prox;
        ptr->prox = novo; 
        novo->ant = ptr;
    }

//->Funções relacionadas a Strings
    unsigned char* tolower_string(unsigned char str[])
    {
        int i = 0;
        while (str[i]) 
        {
            str[i] = tolower(str[i]);
            i++;
        }
        return str;
    }


    unsigned char* rmv_special_char(unsigned char str[])
    {
        int i = 0;
        while (str[i]) 
        {
            switch (str[i])
            {
            case '.':
            case '!':
            case '?':
            case '/':
            case ',':
            case '(':
            case ')':
            case '{':
            case '}':
            case ':':
            case '[':
            case ']':    
                str[i] = '\0';
                
            }
            i++;
        }
        return str;
    }
