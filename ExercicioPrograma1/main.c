#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define EPSILON 0.00000001
#define MAX_CASAS_DECIMAIS 20

void limpaTela();
// Funcoes de Menu
char menuPrincipal();
void menuConversaoNumerica();
void menuSistemaLinear();
void menuEquacaoAlgebrica();

// Funcoes da Conversao Numerica
void converteParteInteira(long int, int);
void converteParteFracionaria(double, int);
void converter();
// Fim da Conversao Numerica

// funcoes da resolucao de Sistema Linear
void jordan(double** mat, int* posicaoVariaveis, int n);
void trocaColunas(double** matriz, int* posicaoVariaveis, int qtdVariaveis, int col1, int col2);int solucionaMatrizDiagonal(double** matriz, double* solucao, int* posicaoVariaveis, int qtdVariaveis);
void sistemaLinear();
// fim Sistema Linear

// Funcoes de Equacao Algebrica
// Fim Equacao Algebrica

// Funcoes gerais
double** criaMatriz(int linhas, int colunas);
int** criaMatrizInteiros(int linhas, int colunas);
void preencheMatriz(double** mat, int lin, int col);
void exibeMatriz(double** mat, int lin, int col);
void exibeVetor(double* vet, int n);
int substituicaoRetroativa(double** mat, int n, double* sol);
void gauss(double** mat, int n);

int main(void) {
    char opcao; // Variavel que recebe qual opcao sera executada

    while (1) {
        limpaTela();
        opcao = menuPrincipal();

        switch (opcao) {
            case 'C':
                limpaTela();
                menuConversaoNumerica();
                break;
            case 'S':
                limpaTela();
                menuSistemaLinear();
                break;
            case 'E':
                limpaTela();
                menuEquacaoAlgebrica();
                break;
            case 'F':
                return 0;
            default:
                limpaTela();
                printf(" ********************************************\n");
                printf(" * POR FAVOR SELECIONE UMA OPCAO VALIDA\n\n\n");
                Sleep(3000);
        }
    }

    return 0;
}

void limpaTela()  {
    if(system("clear")) { // se o SO nao for Unix (linux ou MacOS) devolve o cod. de erro 1
        system("cls"); // utliza o comando de limpar a tela correto
    }
}

/** MENU PRINCIPAL */
char menuPrincipal() {
    char op;

    printf(" ****************************************************************************************\n");
    printf(" *                                    MENU PRINCIPAL                                    *\n");
    printf(" ****************************************************************************************\n");

    printf("\n Selecione a opcao que deseja realizar:\n");
    printf("\n 'C' - Conversao Numerica");
    printf("\n 'S' - Sistema Linear");
    printf("\n 'E' - Equacao Algebrica");
    printf("\n 'F' - Finalizar\n");
    printf("\n Digite uma opcao: ");

    fflush(stdin); // Limpeza de Buffer de teclado evita que o proximo input seja preenchido acidentalmente
    op = getchar();
    fflush(stdin);

    if (op > 90) {
        op -= 32;
    }

    return op;
}
/** FIM MENU PRINCIPAL */

/** FUNCOES PARA CONVERSAO NUMERICA */
void converteParteInteira(long int numParteInteira, int base) {
    // Converte o numero inteiro <numParteInteira> para a base <base>
    // E imprime o resultado da conversao inteira

    if(numParteInteira == 0) { // retornando a pilha de recursao
        return;
    }

    int resto = numParteInteira % base;
    converteParteInteira(numParteInteira / base, base);

    if(resto < 10) {
        printf("%d", resto);
    } else { // Imprimindo os digitos representados por letras
        printf("%c", resto - 10 + 'A' );
    }
}// Fim converteParteInteira()

void converteParteFracionaria(double numParteFracionaria, int base) {
    // Converte a parte fracionaria do numero <numParteFracionaria> para a base <base>
    // E imprime apenas os digitos da parte fracionaria da conversao

    double produto = numParteFracionaria * base;
    int parteInteiraProduto = produto, casaDecimalAtual = 1;

    numParteFracionaria = produto - parteInteiraProduto;

    if(parteInteiraProduto < 10) {
        printf("%d", parteInteiraProduto);
    } else { // Imprimindo os digitos representados por letras
        printf("%c", parteInteiraProduto - 10 + 'A' );
    }

    if(numParteFracionaria == 0 || casaDecimalAtual == MAX_CASAS_DECIMAIS) {
        casaDecimalAtual = 1;
        return;
    } else {
        ++casaDecimalAtual;
        converteParteFracionaria(numParteFracionaria, base);
    }
} // Fim converteParteFracionaria

void converter() {
    int i;
    long int numParteInteira;
    double numParteFracionaria, numDecimal;

    // Array que define as bases disponíveis para conversão.
    int bases[4] = { 2, 8, 16 };

    printf(" Insira um numero decimal: ");
    fflush(stdin);
    scanf("%lf", &numDecimal);
    fflush(stdin);

    numParteInteira = (long int) numDecimal; // retirando a parte fracionaria
    numParteFracionaria = numDecimal - numParteInteira; // mantendo somente a parte fracionaria

    printf(" Base 10: %lf\n", numDecimal);

    // Itera sobre o array de bases numericas
    for(i = 0; i < 3; ++i) {
        printf(" Base %2d: ", bases[i]);
        converteParteInteira(numParteInteira, bases[i]);
        printf(".");
        converteParteFracionaria(numParteFracionaria, bases[i]);
        printf("\n");
    }
}// Fim converter

void menuConversaoNumerica() {
    printf(" ****************************************************************************************\n");
    printf(" *                                  CONVERSAO NUMERICA                                  *\n");
    printf(" ****************************************************************************************\n");

    converter();

    printf(" ********************************************\n");
    printf("\n Pressione Enter para continuar ...");

    fflush(stdin);
    getchar();
}
/** FIM CONVERSAO NUMERICA*/

/** FUNCOES PARA SISTEMA LINEAR */
void sistemaLinear() {
    /**
     * Funcao cria matriz aumentada com a quantidade de variaveis informada
     * Diagonaliza a mesma com o metodo de Jordan e imprime a matriz diagonal
     * Se o SL for compativel, imprime o vetor de solucoes e se eh determinado ou indeterminado
     * Caso contrario imprime que o SL eh Incompativel
     */
    int qtdVariaveis, tipo, *posicaoVariaveis;
    double **matriz, *solucao;

    printf(" Insira a quantidade de variaveis do SL: ");
    fflush(stdin);
    scanf("%d", &qtdVariaveis);
    fflush(stdin);

    // Criacao dos ponteiros e respectivas checagens
    matriz = criaMatriz(qtdVariaveis, qtdVariaveis + 1);
    if (matriz == NULL) { // Verificando se a matriz foi criada
        printf(" ****************************************\n");
        printf(" Erro por Falta de memoria!\n");
        return;
    }
    solucao = malloc(sizeof(solucao) * qtdVariaveis);
    if (solucao == NULL) { // Verificando se o vetor foi criado
        printf(" ****************************************\n");
        printf(" Erro por Falta de memoria!\n");
        return;
    }
    posicaoVariaveis = malloc(sizeof(posicaoVariaveis) * qtdVariaveis);
    if (posicaoVariaveis == NULL) { // Verificando se o vetor foi criado
        printf(" ****************************************\n");
        printf(" Erro por Falta de memoria!\n");
        return;
    }

    preencheMatriz(matriz, qtdVariaveis, qtdVariaveis + 1); // Recebe o SL
    jordan(matriz, posicaoVariaveis, qtdVariaveis); // Diagonaliza a matriz

    printf("\n Matriz Diagonal Aumentada do SL:\n");
    exibeMatriz(matriz, qtdVariaveis, qtdVariaveis + 1);

    tipo = solucionaMatrizDiagonal(matriz, solucao, posicaoVariaveis, qtdVariaveis); // Tenta solucionar o SL
    if (tipo != 2) { // Checa se o SL eh incompativel (nao possui solucao)
        exibeVetor(solucao, qtdVariaveis);
    }

    printf("\n O SL eh ");
    switch(tipo) {
        case 0:
            printf("Determinado\n");
            break;
        case 1:
            printf("Indeterminado\n");
            break;
        default:
            printf("Incompativel\n");
            break;
    }

    // Limpando as alocacoes de ponteiros
    for(int i = 0; i < qtdVariaveis; i++) { // Desalocando as linhas da matriz
        free(matriz[i]);
    }
    free(matriz);
    free(solucao);
    free(posicaoVariaveis);
}

void jordan(double** matriz, int* posicaoVariaveis, int n) {
    /**
     * Recebe a matriz aumentada (matriz) de um SL com (n) variaveis
     * e aplica o metodo de Jordan para transforma-lo em um SL diagonal
     */

    int i, j, k;
    double mult;

    for (i = 0; i < n; i++) { // preenchendo o veor de posicoes com seus indices em ordem
        posicaoVariaveis[i] = i;
    }

    for (i = 0; i <= n-1; i++) {
        if (matriz[i][i] == 0) { // Pivo nulo
            j = i+1;
            while (j < n && matriz[i][j] == 0) {
                j++;
            }

            if (j < n) { // Troca das colunas (i) e (j)
                trocaColunas(matriz, posicaoVariaveis, n, i, j);
            }
        }
        if (matriz[i][i] != 0) { // Caso o pivo ainda seja 0 (nao houve troca), toda a coluna sera igualada a 0
            for (j = 0; j < n; j++) {
                if (j != i) {
                    mult = (-1) * matriz[j][i] / matriz[i][i];
                    matriz[j][i] = 0;

                    for (k = i+1; k <= n; k++) {
                        matriz[j][k] += matriz[i][k] * mult;
                    }
                }
            }
        } else { // igualando toda a coluna [i] a 0
            for (j = 0; j < n; j++) {
                matriz[j][i] = 0;
            }
        }
    }
}

void trocaColunas(double** matriz, int* posicaoVariaveis, int qtdVariaveis, int col1, int col2) {
    /**
     * metodo auxiliar para realizar a troca de colunas de uma matriz
     * e organizar o vetor referente as posicoes das variaveis apos a troca
     * recebe a matriz, o vetor das posicoes e as colunas que deverao ser trocadas
     * retorna a matriz com as colunas trocadas e o vetor de posicoes organizado
     */
    int i, auxPosicao;
    double auxTroca;

    auxPosicao          = posicaoVariaveis[col1];
    posicaoVariaveis[col1] = posicaoVariaveis[col2];
    posicaoVariaveis[col2] = auxPosicao;

    for (i = 0; i < qtdVariaveis; i++) {// loop nas linhas para trocar as colunas
        auxTroca        = matriz[i][col1];
        matriz[i][col1] = matriz[i][col2];
        matriz[i][col2] = auxTroca;
    }
}

int solucionaMatrizDiagonal(double** matriz, double* solucao, int* posicaoVariaveis, int qtdVariaveis) {
    /**
     * Recebe a matriz aumentada de um SL Diagonal com (qtdVariaveis) variaveis
     * e o vetor com a posicao adequada das variaveis para envia-lo em ordem
     * Se o SL:
     * - For determinado, armazena em (solucao) a solucao do SL e devolve 0
     * - For indeterminado armazena em (solucao) uma das Solucoes e devolve 1
     * - For Incompativel, devolve 2
     */

     int i, tipo = 0;

     for (i = qtdVariaveis-1; i >= 0; i--) {
        if (matriz[i][i] == 0) {
            if (matriz[i][qtdVariaveis] != 0) {
                // multiplicação por 0 com resultado diferente de Zero
                // Logo o SL é Incompativel
                return 2;
            }
            solucao[posicaoVariaveis[i]] = 0; // atribui Zero a variavel ja na posicao correta
            tipo = 1; // como qualquer valor de x multiplicado por 0 == 0, SL indeterminado
        } else {
            solucao[posicaoVariaveis[i]] = matriz[i][qtdVariaveis] / matriz[i][i];
            if (fabs(solucao[posicaoVariaveis[i]]) < EPSILON) {
                solucao[posicaoVariaveis[i]] = 0;
            }
        }
     }
     return tipo;
}

void menuSistemaLinear() {
    printf(" ****************************************************************************************\n");
    printf(" *                                    SISTEMA LINEAR                                    *\n");
    printf(" ****************************************************************************************\n");

    sistemaLinear();

    printf(" ********************************************\n");
    printf("\n Pressione Enter para continuar ...");

    fflush(stdin);
    getchar();
}

/** FUNCOES PARA EQUACAO ALGEBRICA */

void lerCoeficientes(int** coeficientes, int grauDaEquacao) {
    /** recebe a matriz de coeficientes e atribui os valores lidos a equacao 0 [p(x)]
     * depois calcula os coeficientes de:
     * - p1(x) = x^n * p(1/x)
     * - p2(x) = p(-x)
     * - p3(x) = x^n * p(-1/x)
     */
    int valorRecebido, i, j;
    for(int i = grauDaEquacao; i >= 0; --i) {
        printf(" Insira o coeficiente de a[%d]: ", i);
        scanf("%d", &valorRecebido);

        //Verificando se an é maior que zero. Caso sim, repetir a mesma iteração.
        if(i == grauDaEquacao && valorRecebido <= 0) {
            printf(" a[%d] deve ser maior que zero.\n", grauDaEquacao);
            ++i;
        }
        //Verificando se a0 é igual a zero. Caso sim, repetir a mesma iteração.
        else if(i == 0 && valorRecebido == 0) {
            printf(" a[0] deve ser diferente de zero.\n");
            ++i;
        }

        // preenchendo as equacoes
        coeficientes[0][i] = valorRecebido;
        coeficientes[1][grauDaEquacao - i] = valorRecebido; // invertendo a ordem dos coeficientes
        coeficientes[2][i] = i % 2 == 0 ? valorRecebido : valorRecebido * (-1); // fazendo p2(x) = p(-x), multiplicando os termos de ordem impar por (-1)
        coeficientes[3][grauDaEquacao - i] = (grauDaEquacao - i) % 2 == 0 ? valorRecebido : valorRecebido * (-1); // invertendo os coeficientes e multiplicando os de ordem impar por (-1)
    }

    for (i = 0; i < 4; i++) {
        if (coeficientes[i][grauDaEquacao] < 0) { // Se an < 0 multiplica todos os coeficientes por -1
            for (j = grauDaEquacao; j > 0; j--) {
                coeficientes[i][j] *= -1;
            }
            coeficientes[i][j] *= -1;
        }
    }
}
void calculaLimites(double limites[4], int** coeficientes, int grauEquacao) {
/** Limites das raizes reais (rr) da equacao onde:
 * - L0: limite superior das rr+
 * - L1: limite inferior das rr+
 * - L2: limite superior das rr-
 * - L3: limite inferior das rr-
 */
    int k = 0, b = 0; // K: maior INDICE entre os coef. negativos; B: Modulo do Menor coef. negativo
    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j <= grauEquacao; j++) {
            if (coeficientes[i][j] < 0) {
                k = j; // Selecionando o maior indice (aproveitando que o coeficiente a0 ja esta na posicao 0)
                if (coeficientes[i][j] < b) { // Selecionando o menor coeficiente de cada equacao obtida
                    b = coeficientes[i][j];
                }
            }
        }

        b *= -1;
        if (b == 0) {
            limites[i] = 0;
        } else {
            limites[i] = 1;
            limites[i] += pow((b*1.0)/coeficientes[i][grauEquacao], 1.0/(grauEquacao - k));
        }
    }

    if (limites[0] == 0) {
        printf("\n * A equacao nao possui Raizes Reais Positivas\n");
    } else {
        printf("\n * As Raizes Reais Positivas da equacao estao no intervalo: [");
        printf("%lf, %lf", 1/limites[1], limites[0]);
        printf(" ]\n");
    }


    printf(" * As Raizes Reais Negativas da equacao estao no intervalo: [");
    printf("%lf, %lf", (-1.0) * limites[2], (-1.0)/limites[3]);
    printf(" ]\n");
}

double horner(double valorDeX,  int* coeficientes, int grauDaEquacao) {
/** Calcula o valor da equacao de forma eficiente dado o valor de X no parametro
 *  de acordo com o metodo de Horner
 */
    int i;
    double resultado = coeficientes[grauDaEquacao];

    for (i = grauDaEquacao - 1; i >= 0; i--) {
        resultado = resultado * valorDeX + coeficientes[i];
    }

    return resultado;
}

int raizesImparBolzano(double limInferior, double limSuperior, int* coeficientes, int grauDaEquacao) {
/** Calcula se dentro do intervalo ha uma quantidade impar de raizes
 *  Em caso positivo retorna:
 *  * 1 se o limite inferior for raiz
 *  * 2 se o limite superior for raiz
 *  * -1 se os limites nao forem raiz
 *  Caso contrario retorna 0
 */
    double resultadoLimInferior ,resultadoLimSuperior;

    resultadoLimInferior = horner(limInferior, coeficientes, grauDaEquacao);
    resultadoLimSuperior = horner(limSuperior, coeficientes, grauDaEquacao);

    if (resultadoLimInferior * resultadoLimSuperior <= 0) {
        if (resultadoLimInferior == 0) {
            return 1;
        }
        if (resultadoLimInferior == 0) {
            return 2;
        }
        return -1;
    }
    return 0;
}

double bissecao(double limInferior, double limSuperior, int* coeficientes, int grauDaEquacao) {
/** Utiliza o metodo de bissecao para calcular sucessivas aproximacoes para araiz da funcao
 *  retorna o valor de X que torne a equacao mais proxima, ou exatamente igual, a 0
 *  limitada a uma maximo de 1000 iteracoes ou margem de erro abaixo de 10^(-8)
 */
    double metadeIntervalo, erro, valorAtual;
    int i = 0;

    metadeIntervalo = (limInferior + limSuperior) / 2.0;
    erro = (limInferior - limSuperior) / 2.0;
    valorAtual = horner(limInferior, coeficientes, grauDaEquacao);

    if (valorAtual > 0) { // convencao para realizar a atribuicao dos novos limites do intervalo
        valorAtual = limInferior;
        limInferior = limSuperior;
        limSuperior = valorAtual;
    }

    while (fabs(erro) > EPSILON && i++ < 1000) { // itera ate um erro aceitavel ou um maximo de 1000 iteracoes
        valorAtual = horner(metadeIntervalo, coeficientes, grauDaEquacao);
        // Convencao de caso o valor obtido seja negativo, troca-se o limite inferior, caso contrario, troca-se o superior
        if(valorAtual < 0) {
            limInferior = metadeIntervalo;
        } else if (valorAtual > 0) {
            limSuperior = metadeIntervalo;
        } else { // O valor da equacao eh exatamente igual a 0 (ZERO) para este valor
            return metadeIntervalo;
        }

        // Atualizando o valor das variaveis para a proxima iteracao
        metadeIntervalo = (limInferior + limSuperior) / 2;
        erro = erro / 2;
    }

    return metadeIntervalo;
}

void solucaoEquacaoAlgebrica() {
	int grauDaEquacao = 0,
        **coeficientes, raizesImpar;
        // Matriz onde a linha 0 representara a equacao digitada , e usada para calcular L0
        // e as linhas 1 representa "p1" para calculo de L1, e assim por diante
	double limites[4], limInferior, limSuperior, raizEquacao;
        // Limites das raizes reais (rr) da equacao

	printf(" Informe o grau da equacao: ");
	scanf("%d", &grauDaEquacao);

	// Serão disponibilizados grauDaEquacao + 1 blocos de memória do tamanho de um int,
	// pois uma equação de grau n tem n+1 termos, considerando os termos nulos.
	coeficientes = criaMatrizInteiros(4, grauDaEquacao + 1);
	//malloc((grauDaEquacao + 1) * sizeof(coeficientes));

	if(coeficientes == NULL) {
		printf(" ****************************************\n");
		printf(" Erro por Falta de memoria!\n");
		return;
	}
    //Para simplificar o código, os coeficientes serão armazenados ao contrário no bloco de memória, ou seja, o termo an ficará no final do bloco e o termo a0 no início.
    //Portanto, toda vez que for necessário iterar sobre os valores armazenados, deve-se utilizar como modelo o laço for imediatamente abaixo.
    lerCoeficientes(coeficientes, grauDaEquacao);
    calculaLimites(limites, coeficientes, grauDaEquacao);

    printf("\n Digite um intervalo para encontrar uma raiz da funcao:\n");
    printf(" Inicio do Intervalo: ");
    scanf("%lf", &limInferior);
    printf(" Fim do Intervalo: ");
    scanf("%lf", &limSuperior);

    raizesImpar = raizesImparBolzano(limInferior, limSuperior, coeficientes[0], grauDaEquacao);
    if(raizesImpar == 0) {
        printf("\n A equacao possui um numero PAR de Raizes Reais no intervalo\n");
    } else if (raizesImpar > 0) {
        printf("\n Para X = %lf a equacao eh igual a 0 (ZERO)\n", raizesImpar == 1 ? limInferior : limSuperior);
    } else {
        raizEquacao = bissecao(limInferior, limSuperior, coeficientes[0], grauDaEquacao);
        printf("\n Para X = %lf a equacao eh igual a 0 (ZERO)\n", raizEquacao);
    }

    for(int i = 0; i < 4; i++) { // Desalocando as linhas da matriz
        free(coeficientes[i]);
    }
    free(coeficientes);
}

void menuEquacaoAlgebrica() {
    printf(" ****************************************************************************************\n");
    printf(" *                                  EQUACAO ALGEBRICA                                   *\n");
    printf(" ****************************************************************************************\n");

    solucaoEquacaoAlgebrica();

    printf(" ********************************************\n");
    printf("\n Pressione Enter para continuar ...");

    fflush(stdin);
    getchar();
}

/** FUNCOES PARA MANIPULACAO DE MATRIZES E VETORES */
double** criaMatriz(int linhas, int colunas) {
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

    for (i = 0; i < linhas; i++) {
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

int** criaMatrizInteiros(int linhas, int colunas) {
    /** Se houver Memoria suficiente, cria uma matriz Double
     * com a qtd de linhas e de colunas fornecidas e devolve um ponteiro para a matriz,
     * caso contrario, devolve NULL
     */

    int i, j;
    int **matriz;
    matriz = malloc(sizeof(matriz) * linhas);

    if (matriz == NULL) {
        return NULL;
    }

    for (i = 0; i< linhas; i++) {
        int *linha;
        linha = malloc(sizeof(linha) * colunas);

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
            printf(" m[%d][%d]: ", i+1, j+1);
            scanf("%lf", &mat[i][j]);
        }
    }
}

void exibeMatriz(double** mat, int lin, int col) {
    /**
     * Exibe o conteudo da matriz (mat) de Double com (lin) Linhas e (col) Colunas
     */
    int i, j;

    for (i = 0; i < lin; i++) {
        printf(" ");
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

    printf("\n Seu vetor de solucoes:\n");
    for (i = 0; i < n; i++) {
        printf(" sol[%d] = %10.3lf;\n", i + 1, vet[i]);
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
