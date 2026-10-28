#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

/* 1. ALGORITMOS DE ORDENACION */

void ordenacionInsercionAux(int v[], int izq, int der) {
    int i, j, x;
    for (i = izq + 1; i <= der; i++) {
        x = v[i];
        j = i - 1;
        while (j >= izq && v[j] > x) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = x;
    }
}

void ordenacionInsercion(int v[], int tam) {
    ordenacionInsercionAux(v, 0, tam - 1);
}

void fusionar(int v[], int izq, int medio, int der, int aux[]) {
    int i, j, k;
    i = izq;
    j = medio + 1;
    k = izq;
    while (i <= medio && j <= der) {
        if (v[i] <= v[j]) {
            aux[k] = v[i];
            k++;
            i++;
        } else {
            aux[k] = v[j];
            k++;
            j++;
        }
    }
    while (i <= medio) {
        aux[k] = v[i];
        k++;
        i++;
    }
    while (j <= der) {
        aux[k] = v[j];
        k++;
        j++;
    }
    for (i = izq; i <= der; i++) {
        v[i] = aux[i];
    }
}

void ordenacionFusionHibridaAux(int v[], int izq, int der,
                                int aux[], int umbral) {
    int medio;
    if (izq < der) {
        if ((der - izq + 1) <= umbral) {
            ordenacionInsercionAux(v, izq, der);
        } else {
            medio = izq + (der - izq) / 2;
            ordenacionFusionHibridaAux(v, izq, medio, aux, umbral);
            ordenacionFusionHibridaAux(v, medio + 1, der, aux, umbral);
            fusionar(v, izq, medio, der, aux);
        }
    }
}

void ordenacionFusionHibrida(int v[], int tam, int umbral) {
    int *aux;
    aux = malloc(tam * sizeof(int));
    if (aux == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria.\n");
        exit(EXIT_FAILURE);
    }
    ordenacionFusionHibridaAux(v, 0, tam - 1, aux, umbral);
    free(aux);
}

void ordenacionFusion_1(int v[], int tam) {
    ordenacionFusionHibrida(v, tam, 1);
}

void ordenacionFusion_20(int v[], int tam) {
    ordenacionFusionHibrida(v, tam, 20);
}

void ordenacionFusion_200(int v[], int tam) {
    ordenacionFusionHibrida(v, tam, 200);
}

/* 2. FUNCIONES AUXILIARES Y DE TIEMPO */

void inicializar_semilla(void) {
    srand(time(NULL));
}

double microsegundos(void) {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

int ordenado(int v[], int n) {
    int i;
    for (i = 0; i < n - 1; i++) {
        if (v[i] > v[i + 1]) {
            return 0;
        }
    }
    return 1;
}

void listar_vector(int v[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%3d ", v[i]);
    }
}

void ascendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++)
        v[i] = i;
}

void descendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++)
        v[i] = n - i;
}

void aleatorio(int v[], int n) {
    int i, m;
    m = 2 * n + 1;
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
}

/* 3. VALIDACION (TESTS) */

typedef void (*func_vector)(int[], int);

void ejecutar_test(func_vector alg, func_vector ini, int n, const char *tit) {
    int v[100];
    printf("%s\n", tit);
    ini(v, n);
    listar_vector(v, n);
    printf("\nordenando...\n");
    alg(v, n);
    listar_vector(v, n);
    if (ordenado(v, n)) {
        printf("\testa ordenado\n\n");
    } else {
        printf("\tNO esta ordenado\n\n");
    }
}

void tests(void) {
    ejecutar_test(ordenacionInsercion, aleatorio, 10,
                  "Ordenacion por insercion con inicializacion aleatoria");
    ejecutar_test(ordenacionInsercion, descendente, 17,
                  "Ordenacion por insercion con inicializacion descendente");
    ejecutar_test(ordenacionFusion_1, aleatorio, 10,
                  "Ordenacion por fusion (umbral 1) aleatoria");
    ejecutar_test(ordenacionFusion_20, descendente, 17,
                  "Ordenacion por fusion (umbral 20) descendente");
    ejecutar_test(ordenacionFusion_200, aleatorio, 25,
                  "Ordenacion por fusion (umbral 200) aleatoria");
}

/* 4. MEDICION DE TIEMPOS */

double calcular_tiempo(func_vector alg, func_vector ini,
                       int v[], int n, int *prom) {
    int j, k;
    double a, d, t, tf, tf2;
    k = 1000;
    *prom = 0;
    ini(v, n);
    a = microsegundos();
    alg(v, n);
    d = microsegundos();
    t = d - a;
    if (t < 500) {
        *prom = 1;
        a = microsegundos();
        for (j = 0; j < k; j++) {
            ini(v, n);
            alg(v, n);
        }
        d = microsegundos();
        tf = d - a;
        a = microsegundos();
        for (j = 0; j < k; j++) {
            ini(v, n);
        }
        d = microsegundos();
        tf2 = d - a;
        t = (tf - tf2) / k;
    }
    return t;
}

void medir_insercion(func_vector alg, func_vector ini, const char *tit,
                     double c_sub, double c_aj, double c_sob) {
    int i, rep, prom;
    int *v;
    double t, sub, aj, sob;
    char s1[25], s2[25], s3[25];
    v = malloc(32000 * sizeof(int));
    if (v == NULL) exit(EXIT_FAILURE);
    sprintf(s1, "t(n)/n^%.1f", c_sub);
    sprintf(s2, "t(n)/n^%.1f", c_aj);
    sprintf(s3, "t(n)/n^%.1f", c_sob);
    for (rep = 0; rep < 3; rep++) {
        printf("\n%s\n", tit);
        printf("%15s%15s%15s%15s%15s\n", "n", "t(n)", s1, s2, s3);
        for (i = 1000; i <= 32000; i = i * 2) {
            t = calcular_tiempo(alg, ini, v, i, &prom);
            sub = t / pow(i, c_sub);
            aj = t / pow(i, c_aj);
            sob = t / pow(i, c_sob);
            if (prom) {
                printf("%5s%10d%15.3f%15.8f%15.8f%15.8f\n",
                       "(*)", i, t, sub, aj, sob);
            } else {
                printf("%15d%15.3f%15.8f%15.8f%15.8f\n",
                       i, t, sub, aj, sob);
            }
        }
    }
    free(v);
}

void medir_fusion(func_vector alg, func_vector ini, const char *tit) {
    int i, rep, prom;
    int *v;
    double t, sub, aj, sob;
    v = malloc(512000 * sizeof(int));
    if (v == NULL) exit(EXIT_FAILURE);
    for (rep = 0; rep < 3; rep++) {
        printf("\n%s\n", tit);
        printf("%15s%15s%15s%18s%20s\n", "n", "t(n)", "t(n)/n",
               "t(n)/(n*ln(n))", "t(n)/(n*ln^2(n))");
        for (i = 1000; i <= 512000; i = i * 2) {
            t = calcular_tiempo(alg, ini, v, i, &prom);
            sub = t / i;
            aj = t / (i * log(i));
            sob = t / (i * pow(log(i), 2));
            if (prom) {
                printf("%5s%10d%15.3f%15.8f%18.8f%20.8f\n",
                       "(*)", i, t, sub, aj, sob);
            } else {
                printf("%15d%15.3f%15.8f%18.8f%20.8f\n",
                       i, t, sub, aj, sob);
            }
        }
    }
    free(v);
}

/* 5. PROGRAMA PRINCIPAL */

int main(void) {
    inicializar_semilla();
    tests();
    medir_insercion(ordenacionInsercion, ascendente,
        "Ordenacion por insercion con inicializacion ascendente",
        0.8, 1.0, 1.2);
    medir_insercion(ordenacionInsercion, descendente,
        "Ordenacion por insercion con inicializacion descendente",
        1.8, 2.0, 2.2);
    medir_insercion(ordenacionInsercion, aleatorio,
        "Ordenacion por insercion con inicializacion aleatoria",
        1.8, 2.0, 2.2);
    medir_fusion(ordenacionFusion_1, ascendente,
        "Ordenacion por fusion con umbral 1 e inicializacion ascendente");
    medir_fusion(ordenacionFusion_1, descendente,
        "Ordenacion por fusion con umbral 1 e inicializacion descendente");
    medir_fusion(ordenacionFusion_1, aleatorio,
        "Ordenacion por fusion con umbral 1 e inicializacion aleatoria");
    medir_fusion(ordenacionFusion_20, ascendente,
        "Ordenacion por fusion con umbral 20 e inicializacion ascendente");
    medir_fusion(ordenacionFusion_20, descendente,
        "Ordenacion por fusion con umbral 20 e inicializacion descendente");
    medir_fusion(ordenacionFusion_20, aleatorio,
        "Ordenacion por fusion con umbral 20 e inicializacion aleatoria");
    medir_fusion(ordenacionFusion_200, ascendente,
        "Ordenacion por fusion con umbral 200 e inicializacion ascendente");
    medir_fusion(ordenacionFusion_200, descendente,
        "Ordenacion por fusion con umbral 200 e inicializacion descendente");
    medir_fusion(ordenacionFusion_200, aleatorio,
        "Ordenacion por fusion con umbral 200 e inicializacion aleatoria");
    return 0;
}