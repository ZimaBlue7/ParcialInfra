#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int fibonacci(int n)
{
    if (n < 2)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
    const int M = 40; // Tamaño del vector
    int vector[M];
    const int num_threads = 4;
    int counts[num_threads];
    int hilo_0, hilo_1, hilo_2, hilo_3;

// números aleatorios en el rango [30, 35]
#pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < M; i++)
        vector[i] = 30 + rand() % 6;

    // política de scheduling static
    printf("\nUsando schedule(static):\n");
    // printf("\nUsando schedule(dynamic, 1):\n");
    // printf("\nUsando schedule(guided, 1):\n");
    double start_time = omp_get_wtime();

#pragma omp parallel for num_threads(num_threads) schedule(static)
    // #pragma omp parallel for num_threads(num_threads) schedule(dynamic, 1)
    // #pragma omp parallel for num_threads(num_threads) schedule(guided, 1)
    for (int i = 0; i < M; i++)
    {
        int fib = fibonacci(vector[i]);
        int thread_id = omp_get_thread_num();
#pragma omp atomic
        counts[thread_id]++;
#pragma omp critical
        if (thread_id == 0)
            hilo_0++;
        else if (thread_id == 1)
            hilo_1++;
        else if (thread_id == 2)
            hilo_2++;
        else if (thread_id == 3)
            hilo_3++;
    }

    printf("Hilo 0: iteraciones = %d\n", hilo_0);
    printf("Hilo 1: iteraciones = %d\n", hilo_1);
    printf("Hilo 2: iteraciones = %d\n", hilo_2);
    printf("Hilo 3: iteraciones = %d\n", hilo_3);

    double end_time = omp_get_wtime();
    printf("Tiempo total de ejecucion: %.6f segundos\n", end_time - start_time);

    // participación de los hilos
    printf("Participacion de los hilos:\n");
    for (int i = 0; i < num_threads; i++)
        printf("Hilo %d: %d iteraciones\n", i, counts[i]);

    return 0;
}
