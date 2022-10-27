/*
 * Programa que converte um número decimal em binário, octal e hexadecimal.
 */

#include <stdio.h>

//Constante que controla o número máximo de casas decimais a serem exibidas na conversão de bases dos números
#define MAX_CASAS_DECIMAIS 20

//Declaração das funções utilizadas, as quais serão definidas depois do main()
void converteParteInteira(long int, int);
void converteParteFracionaria(double, int);
void converte();

//Variável de controle que indica a casa decimal atual
int casaDecimalAtual = 1;

//Array que define as bases disponíveis para conversão. O zero no final tem o propósito de terminar o laço de repetição, pois em C o zero significa False.
//Portanto, todas as bases devem ser inseridas antes do zero.
int bases[4] = {2, 8, 16, 0};

int main()
{

    converte();

    return 0;

}//Fim main()

void converteParteInteira(long int numParteInteira, int base)
{

    int resto = numParteInteira % base;

    if(numParteInteira == 0)
    {
        return;
    }

    converteParteInteira(numParteInteira / base, base);
    if(resto < 10)
    {
        printf("%d", resto);
    }
    else
    {
        printf("%c", resto - 10 + 'A' );
    }

}// Fim converteParteInteira()

void converteParteFracionaria(double numParteFracionaria, int base)
{

    double produto = numParteFracionaria * base;

    int parteInteiraProduto = produto;

    numParteFracionaria = produto - parteInteiraProduto;

    if(parteInteiraProduto < 10)
    {
        printf("%d", parteInteiraProduto);
    }
    else
    {
        //Aproveitando o fato do C utilizar a tabela ASCII para representar caracteres e de ser possível efetutar operações aritméticas com char e int
        printf("%c", parteInteiraProduto - 10 + 'A' );
    }


    if(numParteFracionaria == 0 || casaDecimalAtual == MAX_CASAS_DECIMAIS)
    {
        casaDecimalAtual = 1;
        return;
    }
    else
    {
        ++casaDecimalAtual;

        converteParteFracionaria(numParteFracionaria, base);
    }

}

void converte()
{
    double num = 0;

    printf("Insira um numero decimal: ");
    scanf("%lf", &num);

    //Conversão implícita double para long int (retira parte fracionária).
    long int numParteInteira = num;

    double numParteFracionaria = num - numParteInteira;

    printf("Em decimal: %lf\n", num);

    //Itera sobre o array até encontrar zero, que ocasionará a saída do laço; pois, no C, o zero significa False
    for(int i = 0; bases[i]; ++i)
    {
        printf("Base %d: ", bases[i]);
        converteParteInteira(numParteInteira, bases[i]);
        printf(".");
        converteParteFracionaria(numParteFracionaria, bases[i]);
        printf("\n");
    }

}// Fim converte()
