#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"
#include "sistemas_lineares.h"

int main(void)
{
    double** criaMatriz(double linhas, double colunas);
    void preencheMatriz(double** mat, int lin, int col);
    void exibeMatriz(double** mat, int lin, int col);
    void exibeVetor(double* vet, int n);
    int substituicaoRetroativa(double** mat, int n, double* sol);

    int n, tipo;
    double **matriz, *solucao;

    printf("Digite a quantidade de variaveis do sitema: ");
    scanf("%d", &n);

    matriz = criaMatriz(n, n+1);
    if(matriz == NULL) {
        printf("\nErro ao criar matriz\nFalta de memoria\n");
        return 1;
    }

    solucao = malloc(sizeof(solucao) * n);
    if(solucao == NULL) {
        printf("\nErro ao criar vetor de solucoes\nFalta de memoria\n");
        return 1;
    }

    preencheMatriz(matriz, n, n+1);
    exibeMatriz(matriz, n, n+1);

    gauss(matriz, n);
    printf("\nSL Triangular Superior:");
    exibeMatriz(matriz, n, n+1);

    tipo = substituicaoRetroativa(matriz, n, solucao);
    switch(tipo) {
        case 2:
            printf("\n\nEste SL eh INCOMPATIVEL!!!\n\n");
            break;
        case 1:
            printf("\n\nEste SL eh Indeterminado!\n");
            printf("Uma das soluções para o SL eh:\n");
            exibeVetor(solucao, n);
            break;
        case 0:
            printf("\n\nEste SL eh Determinado!\n");
            printf("A solucao para o SL eh:");
            exibeVetor(solucao, n);
            break;
    }


    return 0;
}


