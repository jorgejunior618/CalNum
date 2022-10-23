#ifndef SISTEMAS_LINEARES_H_INCLUDED
#define SISTEMAS_LINEARES_H_INCLUDED


#include <math.h>
#define EPSILON 0.000001

int substituicaoRetroativa(double** mat, int n, double* sol) {
    /**
     * Recebe a matriz aumentada (mat) de um SLTS com (n) variaveis
     * Se o SL for determinado, armasena em (sol) a solucao do SL e devolve 0
     * Se for indeterminado armazena em (sol) uma das Solucoes e devolve 1
     * Se for Incompativel, devolve 2
     */

     int i, j, tipo = 0;
     double soma;

     for (i = n-1; i >= 0; i--) {
        soma = 0;

        for (j = i+1; j < n; j++) {
            soma += mat[i][j] * sol[j];
        }

        if (mat[i][i] == 0) {
            if (fabs(mat[i][n] - soma) < EPSILON) { // sol[i] e variavel livre
                sol[i] = 0;
                tipo = 1;
            } else { // SL incompativel
                return 2;
            }
        } else {
            sol[i] = (mat[i][n] - soma)/mat[i][i];
        }
     }
     return tipo;
}

void gauss(double** mat, int n) {
    int i, j, k;
    double mult, *aux;

    for (i = 0; i <= n-1; i++) {
        if (mat[i][i] == 0) { // Pivô nulo
            j = i+1;
            while (j < n && mat[j][i] == 0) {
                j++;
            }

            if (j < n) { // Troca das linhas (i) e (j)
                printf("\n\nTtrocando Linhas!\n\n");
                aux = mat[i];
                mat[i] = mat[j];
                mat[j] = aux;
            }
        }
        if (mat[i][i] != 0) { // Caso o pivo ainda seja == 0, pula para a proxima iteracao (a linha ja esta pivotada)
            for (j = i+1; j < n; j++) {
                mult = (-1) * mat[j][i] / mat[i][i];
                mat[j][i] = 0;

                for (k = i+1; k <= n; k++) {
                    mat[j][k] += mat[i][k] * mult;
                }
            }
        }
    }
}

#endif // SISTEMAS_LINEARES_H_INCLUDED
