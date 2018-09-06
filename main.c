#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define EPSILON 0.000001

double **alocaMatriz(int L, int C){
	/* se houver memória disponível, aloca uma matriz de double com L linhas e C colunas 
	e devolver um ponteiro para a matriz;
	caso contrário, devolve um ponteiro nulo. */
	double **m;
	int i, j;
	m = malloc(sizeof(double*)*L);
	if (m==NULL) /* falta de memória */
		{ return NULL; }
	for (i=0; i<L; i++){
		m[i] = malloc(sizeof(double)*C);
		if (m[i]==NULL){
			for (j=0; j<i; j++)
				{ free(m[j]); }
			free(m);
			return NULL;
		}
	}
	return m;
}
/* fim do alocaMatriz */

void Gauss (double **m, int n) {
	int i, j, k;
	double mult, *aux;
	for(i = 0; i < n -1; i++) {
		if (m[i][i] == 0) {
			j = i + 1;
			while(j < n && m[j][i] == 0) {
				j++;
			}
			if (j < n) {
				aux = m[i];
				m[i] = m[j];
				m[j] = aux;
			}
		}
		if (m[i][i] != 0) {
			for (j = i + 1; j < n; j++) {
				mult = -m[j][i]/m[i][i];
				m[j][i] = 0;
				for (k = i + 1; k <= n; k++) {
					m[j][k] += mult * m[i][k];
				}
			}
		}
	}
}

/* lê valores para uma matriz de double alocada dinamicamente com L linhas e C colunas */
void leMatriz (double **m, int L, int C){
	int i, j;
	for (i=0; i<L; i++){
		for (j=0; j<C; j++){
		printf("m[%d][%d]= ", i+1, j+1);
		scanf("%lf", &m[i][j]);
		}
	}
}
/* fim leMatriz */

void imprimeMatriz(double **m, int L, int C){
	/* imprime o conteúdo de uma matriz de uma matriz de double, alocada
	dinamicamente, com L linhas e com C colunas */
	int i, j;
	for (i=0; i<L; i++){
		for (j=0; j<C; j++)
			{ printf("%10.3lf ", m[i][j]);}
		printf("\n");
	}
}
/* fim do imprimeMatriz */

int sretro(double **m, int n, double x[]) {
	/* Recebe m, a matriz aumentada de um SL TS com n variáveis. Se o SL for determinado, armazena em X a solução do SL e devolve 0.
	Se for indeterminado, armazena uma solução do SL e devolve 1. Se for incompatível, devolve 2. */
	int i, j, tipo = 0;
	double soma;
	for (i = n-1; i >= 0; i--) {
		soma = 0;
		for (j = i+1; j < n; j++) {
			soma += m[i][j]*x[j];
		}
		if (m[i][i] == 0) {
			if(fabs(m[i][n] - soma) < EPSILON) {
				x[i] = 0; /* Variável livre */
				tipo = 1;
			} else {
				return 2; /*SL incompatível */
			}
		} else {
			x[i] = (m[i][n] - soma)/m[i][i];
		}
	}
	return tipo;
} /* Fim sretro */

int main(){
	int i, n, tipo;
	double **m, *x;
	printf("Quantidade de variaveis: ");
	scanf("%d", &n);
	m = alocaMatriz(n, n+1);
	x = malloc(sizeof(double) * n);
	if (m == NULL || x == NULL){/* falta de memória */
		printf("Falta de memoria\n");
		return 1;
	}
	leMatriz(m, n, n+1);
	imprimeMatriz(m, n, n+1);
	Gauss(m, n);
	printf("Matriz triangularizada: \n");
	imprimeMatriz(m, n, n+1);
	tipo = sretro(m, n, x);
	if (tipo == 2) {
		printf("SL incompativel.\n");
	} else {
		printf("SL %sdeterminado.\n", tipo ? "in":"");
		for (i = 0; i < n; i++) {
			printf("x[%d] = %10.3lf \n", i+1, x[i]);
		}
	}
	
	return 0; 	
} 
/* fim main */
