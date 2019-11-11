/* 
	Programa desenvolvido por: Edmar Caixeta Filho & Juan Carlos Conceição de Lima Sales
	Instrução para compilação: gcc compacta.c -o compacta -Wall -lm
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototipação de funções
void acendeBit(int, unsigned char*);

// Programa principal
int main(int argc, char *argv[])
{
	char nome_arq_entrada[100],
		  nome_arq_saida[100];

	FILE *arq_entrada,	// Arquivo texto de entrada
		  *arq_saida; 	// Arquivo binário de saída

    int n_vertices, n_arestas, aresta_x, aresta_y;

	// Coluna do valor na matriz de adjacência compacta
	int coluna, coluna_transposta;

	if (argc != 3)
	{
		printf("\nErro nos argumentos da linha de comando\n");
		exit(1);
	}

	// Obtém nome dos arquivos de entrada e saída
	strcpy(nome_arq_entrada, argv[1]);
	strcpy(nome_arq_saida, argv[2]);

	// Abre arquivo texto de entrada
	arq_entrada = fopen(nome_arq_entrada, "rt");

	if (arq_entrada == NULL)
	{
		printf("\nArquivo texto de entrada não encontrado\n");
		exit(1);
	}

	// Cria arquivo binário de saída
	arq_saida = fopen(nome_arq_saida, "wb");

	if (arq_saida == NULL)
	{
		printf("\nArquivo binário de saída não pode ser criado\n");
		exit(1);
	}

	// Lê o número de vértices e arestas
    fscanf(arq_entrada, "%d %d", &n_vertices, &n_arestas);

	// Número de colunas da  matriz de adjacência compacta	
    int teto = ceil((float)n_vertices/8);

	// Matriz de adjacência comapacta
    unsigned char matriz_adj_compacta[n_vertices][teto];
	
	// Inicializa a matriz de adjacência compacta com valor 0
	unsigned char *p;
	for (p = &matriz_adj_compacta[0][0]; p <= &matriz_adj_compacta[n_vertices-1][teto-1]; p++) *p=0; 

	// Lê cada uma das arestas
	/*
	* Como a matriz é espelhada é necessário passar na função
	* acendeBit duas vezes porém de forma transposta,
	*/
    while (fscanf(arq_entrada, "%d %d", &aresta_x, &aresta_y) != EOF)
    {
		coluna = aresta_y/8;
		coluna_transposta = aresta_x/8;
        acendeBit(aresta_y, &matriz_adj_compacta[aresta_x][coluna]);
        acendeBit(aresta_x, &matriz_adj_compacta[aresta_y][coluna_transposta]);
    }

	// Escreve no arquivo binário
	fwrite(&n_vertices, sizeof(int), 1, arq_saida);
	fwrite(&n_arestas, sizeof(int), 1, arq_saida);
	fwrite(matriz_adj_compacta, sizeof(char), sizeof(matriz_adj_compacta), arq_saida);


	// Fecha arquivo texto de entrada
	fclose(arq_entrada);
	// Fecha arquivo binário de saída
	fclose(arq_saida);

	return 0;
}

void acendeBit(int aresta, unsigned char* matriz_adj_compacta_pos) 
{
	// Peso do bit
    int potencia = 7 - (aresta % 8);
    unsigned char mascara = 1 << potencia;

	// Acende o bit da mascara na posição correspondente da matriz de adjacência compacta 
    *matriz_adj_compacta_pos |= mascara;
}