#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

void ordenacionInsercion (int v[], int n){
	int i, j, x;
    for (i = 1; i <= n-1; i++){
        x = v[i];
        j = i-1;
        while (j >= 0 && v[j] > x ){
            v[j+1] = v[j];
            j--;
        }
		v[j+1] = x;  
    }
    
}

void inicializar_semilla() {
srand(time(NULL));
}

void aleatorio(int v [], int n) {/* se generan números pseudoaleatorios entre -n y +n */
int i, m=2*n+1;
for (i=0; i < n; i++)
v[i] = (rand() % m) - n;
}
//Auxiliares de vectores

int ordenado(int v[], int n){
	int i, ord = 1;
	for (i=0; i < n-1; i++){
		if (v[i]>v[i+1]){
			ord = 0;
		}
	}
	return ord;
}	

void listar_vector (int v[], int n){
	int i;
	for (i=0; i<n;i++){
		printf("%7d", v[i]);
	}
	printf("\n");
}

void ascendente(int v [], int n) {
int i;
for (i=0; i < n; i++)
v[i] = i;
}

void descendente(int v [], int n) {
int i;
for (i = 0; i < n; i++)
v[i] = n-i;
}

//TEST

void test_ins(){
	int v[1000];
	printf("Inicializacion Aleatoria\n");
	aleatorio(v, 10);
	listar_vector(v, 10);
	printf("ordenado? %d\n", ordenado(v, 10));
	printf("Ordenacion por Insercion\n");
	ordenacionInsercion(v, 10);
	listar_vector(v, 10);
	printf("ordenado? %d\n", ordenado(v, 10));
	printf("Inicializacion Descendente\n");
	descendente(v, 17);
	listar_vector(v, 17);
	printf("ordenado? %d\n", ordenado(v, 17));
	printf("Ordenacion por Insercion\n");
	ordenacionInsercion(v, 17);
	listar_vector(v, 17);
	printf("ordenado? %d\n", ordenado(v, 17));
}

int main()
{
    test_ins();
    return 0;
}
