#ifndef MATRIZES_H_INCLUDED
#define MATRIZES_H_INCLUDED


double** criaMatriz(double linhas, double colunas) {
    /** Se houver Memória suficiente, cria uma matriz Double
     * com a qtd de linhas e de colunas fornecidas e devolve um ponteiro para a matriz,
     * caso contrário, devolve NULL
     */

    int i, j;
    double **matriz;
    matriz = malloc(sizeof(matriz) * linhas);

    if (matriz == NULL) {
        return NULL;
    }

    for (i = 0; i< linhas; i++) {
        double *linha;
        linha = malloc(sizeof(double) * colunas);

        if (linha == NULL) {
            for(j = 0; j < i-1; j++) { // Limpando as linhas que ja foram criadas
                free(matriz[j]);
            }
            free(matriz);
            return NULL;
        }

        matriz[i] = linha;
    }

    return matriz;
}

void preencheMatriz(double** mat, int lin, int col) {
    /**
     * Lê e preenche a matriz (mat) de Double com (lin) Linhas e (col) Colunas
     */
    int i, j;

    printf("\n");
    for (i = 0; i < lin; i++) {
        for (j = 0; j < col; j++) {
            printf("m[%d][%d]: ", i+1, j+1);
            scanf("%lf", &mat[i][j]);
        }
    }
}

void exibeMatriz(double** mat, int lin, int col) {
    /**
     * Exibe o conteudo da matriz (mat) de Double com (lin) Linhas e (col) Colunas
     */
    int i, j;

    printf("\nSua Matriz Aumentada:\n");
    for (i = 0; i < lin; i++) {
        for (j = 0; j < col; j++) {
            printf("%10.3lf ", mat[i][j]);
        }
        printf("\n");
    }
}

void exibeVetor(double* vet, int n) {
    /**
     * Exibe o conteudo do vetor (vet) de Double com (n) Itens
     */
    int i;

    printf("\nSeu vetor de solucoes:\n");
    for (i = 0; i < n; i++) {
        printf("sol[%d] = %10.3lf;\n", i, vet[i]);
    }
}


#endif // MATRIZES_H_INCLUDED
