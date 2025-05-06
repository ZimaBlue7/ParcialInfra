/**
 * Codigo tomado de
 *   https://stackoverflow.com/questions/17138599/cpu-cache-understanding-using-a-c-program
 * Codigo derivado de
 *   http://igoro.com/archive/gallery-of-processor-cache-effects/
 *
 * Forma de compilacion
 *   gcc -Wall -O3  demo.c -o demo
 *
 **/
#include <omp.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
#define MAX_SIZE (4096 * 4096)
    // omp_set_num_threads(8);
    clock_t start, end;
    double cpu_time;
    double total_time = 0.0;
    int i = 0;
    int j = 0;
    int k = 0;

    int *arr = (int *)malloc(MAX_SIZE * sizeof(int));

    if (arr == NULL)
    {
        printf("Asignacion de memoria a la variable 'arr' fallo");
        return 1;
    }

    for (i = 0; i < MAX_SIZE; i++)
    {
        arr[i] = rand() % 100;
    }

    // Recorrido por filas (paralelo)
    printf("Recorrido por filas (paralelo)\n");
    for (j = 1; j <= 1024; j <<= 1)
    {
        start = clock();
#pragma omp parallel for num_threads(1)
        for (i = 0; i < 4096; i++)
            for (k = 0; k < 4096; k++)
                arr[i,k] += 3; // Acceso simulado como matriz
        end = clock();
        cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        total_time += cpu_time; // Acumular el tiempo total
    }
    printf("\tCPU time with %d threads: %.6f secs.\n", j, total_time);

    free(arr);
    return 0;
}
