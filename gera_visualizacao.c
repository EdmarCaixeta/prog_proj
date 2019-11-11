/* 
	Programa desenvolvido por: Edmar Caixeta Filho & Juan Carlos Conceição de Lima Sales
	Instrução para compilação: gcc gera_visualizacao.c -o gera_visualizacao -Wall -lm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Programa principal
int main(int argc, char *argv[])
{
	char nome_arq_entrada[100],
		  nome_arq_saida[100];
	

	FILE *arq_entrada,	// Arquivo binário de entrada
		  *arq_saida; 	// Arquivo texto de saída

	unsigned int n_vertices, n_arestas, inter_col;
	unsigned char byte_char;
	
	if (argc != 3)
	{
		printf("\nErro nos argumentos da linha de comando\n");
		exit(1);
	}

	// Obtém nome dos arquivos de entrada e saída
	strcpy(nome_arq_entrada, argv[1]);
	strcpy(nome_arq_saida, argv[2]);

	// Abre arquivo binário de entrada
	arq_entrada = fopen(nome_arq_entrada, "rb");

	if (arq_entrada == NULL)
	{
		printf("\nArquivo binário de entrada não encontrado\n");
		exit(1);
	}

	// Cria arquivo texto de saída
	arq_saida = fopen(nome_arq_saida, "wt");

	if (arq_saida == NULL)
	{
		printf("\nArquivo texto de saída não pode ser criado\n");
		exit(1);
	}

	// Lê do arquivo binário de entrada n de vertices e n de arestas:
	fread(&n_vertices, sizeof(n_vertices), 1, arq_entrada);
	fread(&n_arestas, sizeof(n_arestas), 1, arq_entrada);
	
	// Número de colunas da  matriz de adjacência compacta
	int teto = ceil((float)n_vertices/8);

	// Matriz de adjacência comapacta
    unsigned char matriz_adj_compacta[n_vertices][teto];
	
	// Inicializa a matriz de adjacência compacta com valor 0
	unsigned char *p;
	for (p = &matriz_adj_compacta[0][0]; p <= &matriz_adj_compacta[n_vertices-1][teto-1]; p++) *p=0; 

	fprintf(arq_saida, "graph\n{\n");

	for (int i=0; i < n_vertices; i++)
	{
		for (int j=0; j < teto; j++)
		{
			fread(&byte_char, sizeof(byte_char), 1, arq_entrada);
			for (int k=7; k>=0; k--)
				
				//Verifica se forma arestas
				if (byte_char & (1<<k))
				{
					/* 
					 * Coluna de intersecção 
					 * j*8 = colunas anteriores da matriz de adjacência compacta (
					 * 0, se o bit se encontra na primeira coluna )
					 * 7-k = conversão da potência para posição da matriz
					 */
					inter_col = j*8 + 7-k;
					
					//Elimina repetições
					if ((inter_col) > i)
						fprintf(arq_saida, "	%d -- %d\n", i, inter_col);
				}
			matriz_adj_compacta[i][j] = byte_char;
		}
	}
    
	fprintf(arq_saida, "}");

	// Fecha arquivo binário de entrada
	fclose(arq_entrada);
	// Fecha arquivo texto de saída
	fclose(arq_saida);

	return 0;
}