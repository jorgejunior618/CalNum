#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.00000001
#define ITERACOES 1000

double * formulaLagrangeIntervaloRaizesPositivas(double *coeficientesP, double *coeficientesP1, int grauDaEquacao);
double * formulaLagrangeIntervaloRaizesNegativas(double *coeficientesP2, double *coeficientesP3, int grauDaEquacao);
void aplicaBisseccaoComBolzano(double *coeficientesDaEquacao, int grauDaEquacao, double valorMinimoIntervalo, double valorMaximoIntervalo, double precisao, int limiteIteracoes);
void resolveEquacaoAlgebrica();

int main()
{
	resolveEquacaoAlgebrica();

	return 0;
}

double * formulaLagrangeIntervaloRaizesPositivas(double *coeficientesP, double *coeficientesP1, int grauDaEquacao)
{
	int np = grauDaEquacao,
	    np1 = grauDaEquacao,
	    anp = coeficientesP[grauDaEquacao],
	    anp1 = coeficientesP1[grauDaEquacao],
	    kp = 0,
	    kp1 = 0; 

	double bp = 0,
	      bp1 = 0,
	      *intervaloRaizesPositivas = NULL;

	intervaloRaizesPositivas = malloc(2 * sizeof(double));


	if(intervaloRaizesPositivas == NULL)
	{
		printf("%s", "Houve um problema ao alocar memoria para esta funcao, cheque seu computador.\n");
	}
	else
	{
		for(int i = grauDaEquacao; i >= 0; --i)
		{
			if(coeficientesP[i] < 0)
			{
				if(i > kp)
				{
					kp = i;
				}
				
				if(coeficientesP[i] < bp)
				{
					bp  = coeficientesP[i];
				}
			}
	
			
	
			if(coeficientesP1[i] < 0)
			{
				if(i > kp1)
				{
					kp1 = i;
				}
				
				if(coeficientesP1[i] < bp1)
				{
					bp1  = coeficientesP1[i];
				}
			}


		}

		bp = fabs(bp);
		bp1 = fabs(bp1);

		if(kp == 0)
		{
			printf("%s", "Nao existem raizes reais positivas para esta equacao.\n");
		}
		else
		{
			//printf("%s", "Limite inferior para as raizes reais positivas.\n");
			//printf("%s%d%s%d%s%d%s%lf%c", "n = ", np1, ", an = ", anp1, ", k = ", kp1, ", b = ", bp1, '\n');

			intervaloRaizesPositivas[0] = 1/(1 + pow(bp1 / anp1, 1.0/(np1 - kp1)));


			//printf("%s", "Limite superior para as raizes reais positivas.\n");
			//printf("%s%d%s%d%s%d%s%lf%c", "n = ", np, ", an = ", anp, ", k = ", kp, ", b = ", bp, '\n');

			intervaloRaizesPositivas[1] = 1 + pow(bp / anp, 1.0/(np - kp));
		}
	}

	return intervaloRaizesPositivas;
}

double * formulaLagrangeIntervaloRaizesNegativas(double *coeficientesP2, double *coeficientesP3, int grauDaEquacao)
{
	int np2 = grauDaEquacao,
	    np3 = grauDaEquacao,
	    anp2 = coeficientesP2[grauDaEquacao],
	    anp3 = coeficientesP3[grauDaEquacao],
	    kp2 = 0,
	    kp3 = 0; 

	double bp2 = 0,
	      bp3 = 0,
	      *intervaloRaizesNegativas = malloc(2 * sizeof(double));


	if(intervaloRaizesNegativas == NULL)
	{
		printf("%s", "Houve um problema ao alocar memoria para esta funcao, cheque seu computador.\n");
	}
	else
	{
		for(int i = grauDaEquacao; i >= 0; --i)
		{
			if(coeficientesP2[i] < 0)
			{
				if(i > kp2)
				{
					kp2 = i;
				}
				
				if(coeficientesP2[i] < bp2)
				{
					bp2  = coeficientesP2[i];
				}
			}
	
			
	
			if(coeficientesP3[i] < 0)
			{
				if(i > kp3)
				{
					kp3 = i;
				}
				
				if(coeficientesP3[i] < bp3)
				{
					bp3  = coeficientesP3[i];
				}
			}


		}

		bp2 = fabs(bp2);
		bp3 = fabs(bp3);

		//printf("%s", "Limite inferior para as raizes reais negativas.\n");
		//printf("%s%d%s%d%s%d%s%lf%c", "n = ", np2, ", an = ", anp2, ", k = ", kp2, ", b = ", bp2, '\n');

		intervaloRaizesNegativas[0] = -(1 + pow(bp2 / anp2, 1.0/(np2 - kp2)));

		//printf("%s", "Limite superior para as raizes reais negativas.\n");
		//printf("%s%d%s%d%s%d%s%lf%c", "n = ", np3, ", an = ", anp3, ", k = ", kp3, ", b = ", bp3, '\n');

		intervaloRaizesNegativas[1] = -1/(1 + pow(bp3 / anp3, 1.0/(np3 - kp3)));

	}

	return intervaloRaizesNegativas;
}

void resolveEquacaoAlgebrica()
{
	int grauDaEquacao = 0;

	double L = 0,
	      L1 = 0,
	      L2 = 0,
	      L3 = 0,
	      valorMinimoIntervalo = 0,
	      valorMaximoIntervalo = 0,
	      *coeficientesP = NULL,
	      *coeficientesP1 = NULL,
	      *coeficientesP2 = NULL,
	      *coeficientesP3 = NULL,
	      *intervaloRaizesPositivas = NULL,
	      *intervaloRaizesNegativas = NULL;

	printf("%s", "Informe o grau da equacao: ");
	scanf("%d", &grauDaEquacao);

	//Serão disponibilizados grauDaEquacao + 1 blocos de memória do tamanho de um double, pois uma equação de grau n tem n+1 termos, considerando os termos nulos.
	coeficientesP = malloc((grauDaEquacao + 1) * sizeof(double));
	coeficientesP1 = malloc((grauDaEquacao + 1) * sizeof(double));
	coeficientesP2 = malloc((grauDaEquacao + 1) * sizeof(double));
	coeficientesP3 = malloc((grauDaEquacao + 1) * sizeof(double));
	
	intervaloRaizesPositivas = malloc(2 * sizeof(double));
	intervaloRaizesNegativas = malloc(2 * sizeof(double));
	


	if(coeficientesP == NULL || coeficientesP1 == NULL || coeficientesP2 == NULL || coeficientesP3 == NULL || intervaloRaizesPositivas == NULL || intervaloRaizesNegativas == NULL)
	{
		printf("%s", "Houve um problema ao alocar memoria para esta funcao, verifique seu computador.\n");
	}
	else
	{
		//Para simplificar o código, os coeficientes serão armazenados ao contrário no bloco de memória, ou seja, o termo an ficará no final do bloco e o termo a0 no início.
		//Portanto, toda vez que for necessário iterar sobre os valores armazenados, deve-se utilizar como modelo o laço for imediatamente abaixo. 
		for(int i = grauDaEquacao; i >= 0; --i)
		{

			printf("%s%d%s", "Insira o coeficiente de a", i, ": ");
			scanf("%lf", &coeficientesP[i]);

			//Verificando se an é maior que zero. Caso sim, repetir a mesma iteração.
			if(i == grauDaEquacao && coeficientesP[i] <= 0)
			{
				printf("%c%d%s", 'a', grauDaEquacao, " deve ser maior que zero.\n");
				++i;
			}
			//Verificando se a0 é igual a zero. Caso sim, repetir a mesma iteração.
			else if(i == 0 && coeficientesP[i] == 0)
			{
				printf("%s", "a0 deve ser diferente de zero.\n");
				++i;
			}		
		}
		
		//Invertendo a ordem dos coeficientes e armazenando-os em outro bloco memória previamente alocado para P1.
		for(int i = 0; i <= grauDaEquacao; ++i)
		{
			coeficientesP1[i] = coeficientesP[grauDaEquacao - i];
		}

		//Invertendo o sinal dos termos de grau ímpar de P e armazenado-os em outro bloco de memória previamente alocado para P2.		
		for(int i = grauDaEquacao; i >= 0; --i)
		{
			coeficientesP2[i] = i % 2 == 1 ? -coeficientesP[i] : coeficientesP[i];
		}

		//Invertendo o sinal dos termos de grau ímpar de P1 e armazenado-os em outro bloco de memória previamente alocado para P3.
		for(int i = grauDaEquacao; i >= 0; --i)
		{
			coeficientesP3[i] = i % 2 == 1 ? -coeficientesP1[i] : coeficientesP1[i];
		}

		/*

		printf("%s", "Os termos de P sao:\n");

		for(int i = grauDaEquacao; i >= 0; --i)
		{
			printf("%lf%s%d%c", coeficientesP[i],"X^", i, '\n');
		}

		printf("%s", "Os termos de P1 sao:\n");

		for(int i = grauDaEquacao; i >= 0; --i)
		{
			printf("%lf%s%d%c", coeficientesP1[i],"X^", i, '\n');
		}

		printf("%s", "Os termos de P2 sao:\n");

		for(int i = grauDaEquacao; i >= 0; --i)
		{
			printf("%lf%s%d%c", coeficientesP2[i],"X^", i, '\n');
		}

		printf("%s", "Os termos de P3 sao:\n");

		for(int i = grauDaEquacao; i >= 0; --i)
		{
			printf("%lf%s%d%c", coeficientesP3[i],"X^", i, '\n');
		}

		*/

		intervaloRaizesPositivas = formulaLagrangeIntervaloRaizesPositivas(coeficientesP, coeficientesP1, grauDaEquacao);
		intervaloRaizesNegativas = formulaLagrangeIntervaloRaizesNegativas(coeficientesP2, coeficientesP3, grauDaEquacao);

		printf("%s", "Intervalo das raizes reais negativas: ");
		printf("%c%lf%c%lf%s", '[', intervaloRaizesNegativas[0], ',', intervaloRaizesNegativas[1], "]\n");

		printf("%s", "Intervalo das raizes reais positivas: ");
		if(intervaloRaizesPositivas[0] == 0 && intervaloRaizesPositivas[1] == 0)
		{
			printf("%s" "Inexistente.\n");
		}
		else
		{
			printf("%c%lf%c%lf%s", '[', intervaloRaizesPositivas[0], ',', intervaloRaizesPositivas[1], "]\n");
		}

	}

	printf("%s", "\nDigite o primeiro valor do intervalo: ");
	scanf("%lf", &valorMinimoIntervalo);

	printf("%s", "\nDigite o segundo valor do intervalo: ");
	scanf("%lf", &valorMaximoIntervalo);

	//Trocando os valores, caso necessário
	if(valorMinimoIntervalo > valorMaximoIntervalo)
	{
		double temp = 0;
		temp = valorMaximoIntervalo;
		valorMaximoIntervalo = valorMinimoIntervalo;
		valorMinimoIntervalo = temp;
	}

	

	aplicaBisseccaoComBolzano(coeficientesP, grauDaEquacao, valorMinimoIntervalo, valorMaximoIntervalo, EPSILON, ITERACOES);

	for(int i = 0; i < grauDaEquacao; ++i)
	{
        	free(&coeficientesP[i]);
		free(&coeficientesP1[i]);
		free(&coeficientesP2[i]);
		free(&coeficientesP3[i]);
    	}

	for(int i = 0; i < 2; ++i)
	{
        	free(&intervaloRaizesPositivas[i]);
		free(&intervaloRaizesNegativas[i]);
    	}

	free(coeficientesP);
	free(coeficientesP1);
	free(coeficientesP2);
	free(coeficientesP3);
	free(intervaloRaizesPositivas);
	free(intervaloRaizesNegativas);

	return;
}

void aplicaBisseccaoComBolzano(double *coeficientesDaEquacao, int grauDaEquacao, double valorMinimoIntervalo, double valorMaximoIntervalo, double precisao, int limiteIteracoes)
{
	int qtdIteracoes = 0;
	double a = valorMinimoIntervalo,
	       b = valorMaximoIntervalo,
	       valorMedio = 0,
	       fa = 0,
	       fb = 0,
	       fValorMedio = 0;

	for(int i = grauDaEquacao; i >= 0; --i)
	{
		fa += (coeficientesDaEquacao[i] * pow(a, i));
		fb += (coeficientesDaEquacao[i] * pow(b, i));
	}
	
	if(fa * fb < 0)
	{
		printf("%s", "Existe um numero impar de raizes neste intervalo.\n");
		while(valorMaximoIntervalo - valorMinimoIntervalo > precisao && qtdIteracoes <= limiteIteracoes)
		{
			fa = fValorMedio = 0;
			valorMedio = (a + b)/2;
	
			for(int i = grauDaEquacao; i >= 0; --i)
			{
				fa += (coeficientesDaEquacao[i] * pow(a, i));
				fValorMedio += (coeficientesDaEquacao[i] * pow(valorMedio, i));
			}
	
			if(fa * fValorMedio <= 0)
			{
				b = valorMedio;
			}
			else
			{
				a = valorMedio;
			}

			++qtdIteracoes;
		}

		if(qtdIteracoes > limiteIteracoes)
			{
				printf("%s", "O limite de iteracoes foi atingido.\n");
			}

		printf("%lf%s", a, " e uma raiz aproximada da equacao.\n");

	}
	else if(fa * fb > 0)
	{
		printf("%s", "Existe um numero par de raizes neste intervalo.\n");
	}
	
}