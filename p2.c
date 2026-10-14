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

//misc
void inicializar_semilla() {
srand(time(NULL));
}

double microsegundos() { /* obtiene la hora del sistema en microsegundos */
struct timeval t;
if (gettimeofday(&t, NULL) < 0 )
return 0.0;
return (t.tv_usec + t.tv_sec * 1000000.0);
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

void aleatorio(int v [], int n) {/* se generan números pseudoaleatorios entre -n y +n */
int i, m=2*n+1;
for (i=0; i < n; i++)
v[i] = (rand() % m) - n;
}

//TEST

void test_ins(){//mejorable
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

//TIEMPOS

typedef void (*func_vector)(int[], int);

void medir_tiempos(func_vector algoritmo, func_vector inicializar, 
                   const char *titulo, double cota_sub, double cota_aj, double cota_sob) {
    int i, j, k = 1000;
    int v[64000];
    double antes, despues, t, antesf, despuesf, tf, tf2;
    char col_sub[20], col_aj[20], col_sob[20];

    // Formateamos los títulos de las columnas dinámicamente según las cotas recibidas
    sprintf(col_sub, "t(n)/n^%.1f", cota_sub);
    sprintf(col_aj,  "t(n)/n^%.1f", cota_aj);
    sprintf(col_sob, "t(n)/n^%.1f", cota_sob);

    printf("\n%s\n", titulo);
    printf("%15s%15s%15s%15s%15s\n", "n", "t(n)", col_sub, col_aj, col_sob);

    for (i = 500; i <= 64000; i = i * 2) {
        inicializar(v, i);
        antes = microsegundos();
        algoritmo(v, i);
        despues = microsegundos();
        t = despues - antes;

        if (t < 500) {
            antesf = microsegundos();
            for (j = 0; j < k; j++) {
                inicializar(v, i);
                algoritmo(v, i);
            }
            despuesf = microsegundos();
            tf = despuesf - antesf;

            antesf = microsegundos();
            for (j = 0; j < k; j++) {
                inicializar(v, i);
            }
            despuesf = microsegundos();
            tf2 = despuesf - antesf;

            t = (tf - tf2) / k;
            printf("%5s%10d%15.3f%15.6f%15.6f%15.6f\n", "(*)", i, t, 
                   t / pow(i, cota_sub), t / pow(i, cota_aj), t / pow(i, cota_sob));
        } else {
            printf("%15d%15.3f%15.6f%15.6f%15.6f\n", i, t, 
                   t / pow(i, cota_sub), t / pow(i, cota_aj), t / pow(i, cota_sob));
        }
    }
    printf("Las casillas marcadas con (*) corresponden a un tiempo promedio de K = %d ejecuciones.\n", k);
}
int main()
{
	inicializar_semilla();
    test_ins();
	// 1. Caso mejor (Ascendente) -> Complejidad O(n)
    medir_tiempos(ordenacionInsercion, ascendente, 
                  "Ordenacion por insercion con inicializacion ascendente", 
                  0.8, 1.0, 1.2);

    // 2. Caso peor (Descendente) -> Complejidad O(n^2)
    medir_tiempos(ordenacionInsercion, descendente, 
                  "Ordenacion por insercion con inicializacion descendente", 
                  1.8, 2.0, 2.2);

    // 3. Caso medio (Aleatorio) -> Complejidad O(n^2)
    medir_tiempos(ordenacionInsercion, aleatorio, 
                  "Ordenacion por insercion con inicializacion aleatoria", 
                  1.8, 2.0, 2.2);
    return 0;
}
