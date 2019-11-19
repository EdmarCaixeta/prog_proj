/*TODOLIST:
Ocorrencia = alocação dinamica
função print_list deve ser excluida
*/

//Inclusão de bibliotecas
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include <locale.h>

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
    void insert_in_list(lde*, char*, no*, int);
    char* rmv_special_char(char []);
    void Selection_Sort(lde* lista);

//Main
    int main(int argc, char* argv[])
    {
        setlocale(LC_ALL, "");
        //Definição de Variáveis
        FILE* arq_saida, *arq_entrada;
        int num_param = argc - 2, list_len;
        lde* lista;
        no* ptr, *aux;
        char nome_arq_entrada[100], palavra[100];
        
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
                   insert_in_list(lista, palavra, lista->cabeca, i);
                   Selection_Sort(lista);
                }
                
                else
                {
                    ptr = aux;
                    ptr->ocorrencia[i]++;    
                }                    
                
            }
        
        fclose(arq_entrada);
        }
        print_list(lista, num_param);
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

    no* search_in_list(lde* lista, char x[])
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

    void insert_in_list(lde* lista, char* chave, no* ptr, int indice)
    {
        no* novo;
        
        novo = (no*) malloc(sizeof(no));
        
        strcpy(novo->chave, tolower_string(chave));
        novo->ocorrencia[indice]++;    
        novo->prox = ptr->prox;
        ptr->prox = novo; 
    }

//->Funções relacionadas a Strings
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


    char* rmv_special_char(char str[])
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

    void search_and_insert(lde* lista, char nova[], char anterior[])
    {
        
    }