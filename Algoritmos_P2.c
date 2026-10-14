#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void inicializar_semilla() {
    srand(time(NULL));
}
void aleatorio(int v [], int n) {/* se generan números pseudoaleatorios entre -n y +n */
    int i, m=2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
}

void ascendente(int v [], int n) {
    int i;
    for (i=0; i < n; i++)
        v[i] = i;
}

void descendente(int v[], int n){
    int i;
    for(i=0;i<n;i++)
        v[i]=n-i;
}

void mostrarVector(int *v,int n){
    int i;
    for(i=0;i<n;i++){
        printf("%d ",v[i]);
    }
    printf("\n");
}




void ordenacionInsercionAux(int *v,int izq,int der){
    int i,x,j;
    for(i=izq+1;i<=der;i++){
        x = v[i];
        j = i-1;
        while(j>=izq && v[j]>x){
            v[j+1] = v[j] ;
            j = j-1;
        }
        v[j+1] = x;
    }
}

void ordenacionInsercion (int *v,int n){
    ordenacionInsercionAux(v,0,n-1);
}

void testInsercion(int *v,int n,void (*vectorCreado)(int *,int)){
    vectorCreado(v,n);
    mostrarVector(v,n);
    printf("Ordenando...\n");
    ordenacionInsercion(v,n);
    mostrarVector(v,n);
    printf("Esta ordenado\n\n");
}

int main(){
    int v[18];
    inicializar_semilla();
    printf("Ordenacion por insercion vector aleatorio\n");
    testInsercion(v,10,aleatorio);
    printf("Ordenacion por insercion vector ascendente\n");
    testInsercion(v,18,ascendente);
    printf("Ordenacion por insercion vector descendente\n");
    testInsercion(v,18,descendente);
}