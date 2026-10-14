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

//TIEMPOS

void tiempos_ins1(){
	int i, j, k = 1000;
	int v[64000];
	double antes, despois, t, antesf, despoisf, tf, tf2;
	printf("\nOrdenacion por insercion con inicializacion ascendente\n");
	printf("%15s%15s%15s%15s%15s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");
	for (i = 500; i <= 64000; i = i*2) {
		ascendente(v, i);
		antes = microsegundos();
		ordenacionInsercion(v, i);
		despois = microsegundos();
		t = despois-antes;
		if (t<500){
			antesf= microsegundos();
			for(j = k; j >= 0; j--){
				ascendente(v, i);
				ordenacionInsercion(v, i);
			}
			despoisf = microsegundos();
			tf = despoisf - antesf;
			antesf = microsegundos();
			for(j = k; j >= 0; j--){
				ascendente(v, i);
			}
			despoisf = microsegundos();
			tf2 = despoisf - antesf;
			t = (tf-tf2)/k;
			printf("%5s%10d%15.3f%15f%15f%15f\n", "(*)", i, t, t/pow(i, 1.8), t/pow(i, 2), t/pow(i, 2.2));
		}else{
			printf("%15d%15.3f%15f%15f%15f\n", i, t, t/pow(i, 1.8), t/pow(i, 2), t/pow(i, 2.2));
		}
	}
	printf("Las casillas marcadas con (*) corresponden a un tiempo promedio de K ejecuciones del algoritmo donde k = 1000\n");
}

void tiempos_ins2(){
	int i, j, k = 1000;
	int v[64000];
	double antes, despois, t, antesf, despoisf, tf, tf2;
	printf("\nOrdenacion por insercion con inicializacion descendente\n");
	printf("%15s%15s%15s%15s%15s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");
	for (i = 500; i <= 64000; i = i*2) {
		descendente(v, i);
		antes = microsegundos();
		ordenacionInsercion(v, i);
		despois = microsegundos();
		t = despois-antes;
		if (t<500){
			antesf= microsegundos();
			for(j = k; j >= 0; j--){
				descendente(v, i);
				ordenacionInsercion(v, i);
			}
			despoisf = microsegundos();
			tf = despoisf - antesf;
			antesf = microsegundos();
			for(j = k; j >= 0; j--){
				descendente(v, i);
			}
			despoisf = microsegundos();
			tf2 = despoisf - antesf;
			t = (tf-tf2)/k;
			printf("%5s%10d%15.3f%15f%15f%15f\n", "(*)", i, t, t/pow(i, 1.8), t/pow(i, 2), t/pow(i, 2.2));
		}else{
			printf("%15d%15.3f%15f%15f%15f\n", i, t, t/pow(i, 1.8), t/pow(i, 2), t/pow(i, 2.2));
		}
	}
	printf("Las casillas marcadas con (*) corresponden a un tiempo promedio de K ejecuciones del algoritmo donde k = 1000\n");
}

void tiempos_ins3(){
	int i, j, k = 1000;
	int v[64000];
	double antes, despois, t, antesf, despoisf, tf, tf2;
	printf("\nOrdenacion por insercion con inicializacion aleatoria\n");
	printf("%15s%15s%15s%15s%15s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");
	for (i = 500; i <= 64000; i = i*2) {
		aleatorio(v, i);
		antes = microsegundos();
		ordenacionInsercion(v, i);
		despois = microsegundos();
		t = despois-antes;
		if (t<500){
			antesf= microsegundos();
			for(j = k; j >= 0; j--){
				aleatorio(v, i);
				ordenacionInsercion(v, i);
			}
			despoisf = microsegundos();
			tf = despoisf - antesf;
			antesf = microsegundos();
			for(j = k; j >= 0; j--){
				aleatorio(v, i);
			}
			despoisf = microsegundos();
			tf2 = despoisf - antesf;
			t = (tf-tf2)/k;
			printf("%5s%10d%15.3f%15f%15f%15f\n", "(*)", i, t, t/pow(i, 1.8), t/pow(i, 2), t/pow(i, 2.2));
		}else{
			printf("%15d%15.3f%15f%15f%15f\n", i, t, t/pow(i, 1.8), t/pow(i, 2), t/pow(i, 2.2));
		}
	}
	printf("Las casillas marcadas con (*) corresponden a un tiempo promedio de K ejecuciones del algoritmo donde k = 1000\n");
}

int main()
{
	inicializar_semilla();
    test_ins();
	tiempos_ins1();
	tiempos_ins2();
	tiempos_ins3();
    return 0;
}
