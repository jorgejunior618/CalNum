#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define EPSILON 0.000001

int main(void)
{
    char menuPrincipal();
    void conversaoNumerica();
    void sistemaLinear();
    void equacaoAlgebrica();

    double** criaMatriz(double linhas, double colunas);
    void preencheMatriz(double** mat, int lin, int col);
    void exibeMatriz(double** mat, int lin, int col);
    void exibeVetor(double* vet, int n);
    int substituicaoRetroativa(double** mat, int n, double* sol);
    void gauss(double** mat, int n);

    char opcao;
    // int n, tipo;
    // double **matriz, *solucao;

    while (1) {
        system("cls");
        opcao = menuPrincipal();

        switch (opcao) {
            case 'C':
                system("cls");
                conversaoNumerica();
                break;
            case 'S':
                system("cls");
                sistemaLinear();
                Sleep(3000);
                break;
            case 'E':
                system("cls");
                equacaoAlgebrica();
                Sleep(3000);
                break;
            case 'F':
                return 0;
            default:
                system("cls");
                printf(" ********************************************\n");
                printf(" * POR FAVOR SELECIONE UMA OPCAO VALIDA\n\n\n");
                Sleep(3000);
        }
    }

    return 0;
}

/** MENU PRINCIPAL */
char menuPrincipal() {
    char op;

    printf(" ********************************************\n");
    printf(" *              MENU PRINCIPAL              *\n");
    printf(" ********************************************\n");

    printf("\n Selecione a opcao que deseja realizar:\n");
    printf("\n 'C' - Conversao");
    printf("\n 'S' - Sistema Linear");
    printf("\n 'E' - Equacao Algebrica");
    printf("\n 'F' - Finalizar\n");
    printf("\n Digite uma opcao: ");

    fflush(stdin);
    op = getchar();
    fflush(stdin);

    if (op > 90) {
        op -= 32;
    }

    return op;
}


void conversaoNumerica() {
    double decimal;

    char intBinario[20] = "0";
    char fracBinario[20] = "0";

    char intOctal[10] = "0";
    char fracOctal[20] = "0";

    char intHex[10] = "0";
    char fracHex[20] = "0";

    printf(" ********************************************\n");
    printf(" *            CONVERSAO NUMERICA            *\n");
    printf(" ********************************************\n");

    printf("\n Digite o numero que deseja converter: ");

    fflush(stdin);
    scanf(" %lf", &decimal);
    fflush(stdin);

    printf("\n * Numero digitado: %lf \n\n", decimal);
    printf(" Binario:     %s.%s\n", intBinario, fracBinario);
    printf(" Octal:       %s.%s\n", intOctal, fracOctal);
    printf(" Hexadecimal: %s.%s\n", intHex, fracHex);
    printf(" ********************************************\n");
    printf("\n Pressione Enter para continuar ...");
    getchar();
}
void sistemaLinear() {
    printf(" ********************************************\n");
    printf(" *              SISTEMA LINERAR             *\n");
    printf(" ********************************************\n");
}
void equacaoAlgebrica() {
    printf(" ********************************************\n");
    printf(" *             EQUACAO ALGEBRICA            *\n");
    printf(" ********************************************\n");
}

/** FUNCOES PARA MANIPULACAO DE MATRIZES E VETORES */
double** criaMatriz(double linhas, double colunas) {
    /** Se houver Memoria suficiente, cria uma matriz Double
     * com a qtd de linhas e de colunas fornecidas e devolve um ponteiro para a matriz,
     * caso contrario, devolve NULL
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
     * Le e preenche a matriz (mat) de Double com (lin) Linhas e (col) Colunas
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

/** FUNCOES UTEIS PARA SISTEMAS LINEARES */

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
    /**
     * Recebe a matriz aumentada (mat) de um SL com (n) variaveis
     * e o manipula de forma a transforma-lo em um SLTS
     */

    int i, j, k;
    double mult, *aux;

    for (i = 0; i <= n-1; i++) {
        if (mat[i][i] == 0) { // Piv nulo
            j = i+1;
            while (j < n && mat[j][i] == 0) {
                j++;
            }

            if (j < n) { // Troca das linhas (i) e (j)
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
