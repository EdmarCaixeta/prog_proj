#include <stdio.h>
#include <stdlib.h>

struct no_st
{
	int chave;
	struct no_st* prox;
};

typedef struct no_st no;

struct lcc_st
{
	no* cabeca;
};

typedef struct lcc_st lcc;

//Prototipação das funções
lcc* cria_nova_lcc();
void imprime_lcc(lcc*);
void insere_lcc(lcc*, int, no*);
no* busca_lcc(lcc*, int);
void remove_sucessor_lcc(lcc*, no*);
void remove_chave_lcc(lcc*, int);
void insere_antes_lcc(lcc*, int, int);
void insere_pos_lcc(lcc*, int, int);

int main(void)
{
	lcc* lista;
	no* ptr;
	int num;
	
	//Cria uma lista vazia com cabeça
	lista = cria_nova_lcc();
	
	imprime_lcc(lista);
	
	insere_lcc(lista, 10, lista->cabeca);
	
	imprime_lcc(lista);
	
	insere_lcc(lista, 20, lista->cabeca);
	
	imprime_lcc(lista);
	
	insere_lcc(lista, 30, lista->cabeca->prox);
	
	imprime_lcc(lista);
	
	/*printf("Remover o elemento: ");
	scanf("%d", &num);
	
	remove_chave_lcc(lista, num);
	
	imprime_lcc(lista);*/
	
	/*ptr = busca_lcc(lista, num);
	
	if (ptr)
	{
		printf("ACHEI!\n");
		remove_sucessor_lcc(lista, ptr);
		imprime_lcc(lista);
	}
	else
		printf("NÃO ACHEI!\n");
	*/
	insere_antes_lcc(lista, 40, 30);
	imprime_lcc(lista);
	
	insere_antes_lcc(lista, 50, 80);
	imprime_lcc(lista);
	
	insere_pos_lcc(lista, 60, 0);
	imprime_lcc(lista);
	
	insere_pos_lcc(lista, 70, 2);
	imprime_lcc(lista);
	
	insere_pos_lcc(lista, 80, 1000);
	imprime_lcc(lista);
	
	//ptr = busca_lcc(lista, num);
	
	/*if (ptr != NULL)
		printf("O elemento %d esta na lista\n", num);
	else
		printf("O elemento %d nao esta na lista\n", num);
		
	remove_sucessor_lcc(lista, lista->cabeca);
	imprime_lcc(lista);
	
	ptr = busca_lcc(lista, 20);
	remove_sucessor_lcc(lista, ptr);
	imprime_lcc(lista);
	
	remove_sucessor_lcc(lista, ptr);
	imprime_lcc(lista);*/
	
	//remove_chave_lcc(lista, num);
	//imprime_lcc(lista);
		
	return 0;
}

lcc* cria_nova_lcc()
{
	lcc* l = (lcc*) malloc(sizeof(lcc));
	l->cabeca = (no*) malloc(sizeof(no));
	l->cabeca->prox = NULL;
	
	return l;
}

void imprime_lcc(lcc* l)
{
	no* ptr;
	
	if (l->cabeca->prox == NULL)
		printf("Lista vazia!\n");
	
	for (ptr = l->cabeca->prox; ptr != NULL; ptr = ptr->prox)
		printf("%d ", ptr->chave);
		
	printf("\n");
}

void insere_lcc(lcc* l, int y, no* p)
{
	no* novo;
	
	novo = (no*) malloc(sizeof(no));
	
	novo->chave = y;	
	novo->prox = p->prox;
	p->prox = novo; 
}

no* busca_lcc(lcc* l, int chave)
{
	no* p;
	
	p = l->cabeca->prox;
	
	while(p != NULL && p->chave != chave)
		p = p->prox;
		
	return p;
}

void remove_sucessor_lcc(lcc* l, no* p)
{
	no* lixo;
	
	lixo = p->prox;
	p->prox = lixo->prox;
	
	free(lixo);
}

void remove_chave_lcc(lcc* l, int x)
{
	no *p, *q;
	
	p = l->cabeca;
	q = l->cabeca->prox;
	
	while(q != NULL && q->chave != x)
	{
		p = q;
		q = q->prox;
	}
	
	if (q != NULL)
	{
		p->prox = q->prox;
		
		free(q);
	}
}

void insere_antes_lcc(lcc* l, int nova_chave, int x)
{
	no *p, *q, *novo;
	
	novo = (no*) malloc(sizeof(no));
	novo->chave = nova_chave;
	
	p = l->cabeca;
	q = l->cabeca->prox;
	
	while(q != NULL && q->chave != x)
	{
		p = q;
		q = q->prox;
	}
	
	novo->prox = q;
	p->prox = novo;
}

void insere_pos_lcc(lcc* l, int nova_chave, int pos)
{
	no *p, *q, *novo;
	int i;
	
	novo = (no*) malloc(sizeof(no));
	novo->chave = nova_chave;
	
	p = l->cabeca;
	q = l->cabeca->prox;
	i = 0;
	
	while(q != NULL && i < pos)
	{
		p = q;
		q = q->prox;
		i++;
	}
	
	novo->prox = q;
	p->prox = novo;
}
