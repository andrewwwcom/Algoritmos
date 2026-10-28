#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

void inicializar_semilla() {
    srand(time(NULL));
}

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
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

double cota_sobre_al(int n){
    return pow(n,2.2);    
}

double cota_sub_al(int n){
    return pow(n,1.8);    
}

double cota_aj_al(int n){
    return n*n;
}

double cota_sobre_asc(int n){
    return pow(n,0.8);    
}

double cota_sub_asc(int n){
    return pow(n,1.2);    
}

double cota_aj_asc(int n){
    return n;
}

double cota_sobre_desc(int n){
    return pow(n,2.2);    
}

double cota_sub_desc(int n){
    return pow(n,1.8);    
}

double cota_aj_desc(int n){
    return n*n;
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

void tiempos(int *v, int n, void (*vectorCreado)(int *,int),
double (*cota_sub)(int),double (*cota_aj)(int),double (*cota_sobre)(int)){
    int i;
    int iter=1000;
    double t1,t2,ta,tb,t,x,y,z;
    vectorCreado(v,n);
    t1 = microsegundos();
    ordenacionInsercion(v,n);
    t2 = microsegundos();
    t = t2-t1;
    if (t < 500){ 
        ta = microsegundos ();
        for(i=0;i<iter;i++) {
            vectorCreado(v,n);
            ordenacionInsercion(v,n);
        }
        tb = microsegundos();
        t1=tb-ta; 
        ta = microsegundos();
        for(i=0;i<iter;i++){
            vectorCreado(v,n);
        }
        tb = microsegundos();
        t2=tb-ta;
        t=(t1-t2)/iter;
    }
    x = t / cota_sub(n);
    y = t / cota_aj(n);
    z = t / cota_sobre(n);
    if(t < 500)
        printf("%12d%15.4f*%15.8f%15.8f%15.8f\n",n,t, x, y, z);
 
    else printf("%12d%15.4f%15.8f%15.8f%15.8f\n",n,t, x, y, z);  
    
}

void tablasTiempos(int *v){
    int i;
    int j;
    printf("Ordenacion por insercion con inicializacion aleatoria\n");
    for(j=0;j<3;j++){
        printf("%12s%13s%17s%13s%17s\n\n"
        ,"n","t(n)","t(n)/n^1.8","t(n)/n^2","t(n)/n^2.2");
        for(i=1000;i<=32000;i*=2){
            tiempos(v,i,aleatorio,cota_sub_al,cota_aj_al,cota_sobre_al);
        }
        printf("\n");
    }
    
    printf("Ordenacion por insercion con vector ascendente\n");
    for(j=0;j<3;j++){
        printf("%12s%13s%17s%13s%18s\n\n"
        ,"n","t(n)","t(n)/n^0.8","t(n)/n","t(n)/n^1.2");
        for(i=1000;i<=32000;i*=2){
            tiempos(v,i,ascendente,cota_sub_asc,cota_aj_asc,cota_sobre_asc);
        }
        printf("\n");
    }

    printf("Ordenacion por insercion con vector descendente\n");
    for(j=0;j<3;j++){
        printf("%12s%13s%17s%13s%17s\n\n"
        ,"n","t(n)","t(n)/n^1.8","t(n)/n^2","t(n)/n^2.2");
        for(i=1000;i<=32000;i*=2){
            tiempos(v,i,descendente,cota_sub_desc,cota_aj_desc,cota_sobre_desc);
        }
        printf("\n");
    }
}
    
int main(){
    int v[32000];
    inicializar_semilla();
    printf("Ordenacion por insercion vector aleatorio\n");
    testInsercion(v,10,aleatorio);
    printf("Ordenacion por insercion vector ascendente\n");
    testInsercion(v,18,ascendente);
    printf("Ordenacion por insercion vector descendente\n");
    testInsercion(v,18,descendente);
    tablasTiempos(v);
}