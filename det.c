#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <omp.h>
#include "funciones.h"
#include <time.h>

double determinantLaplace(double **matrix, int size);
void ijMinor(double **matrix, double **minorMatrix, int size, int row, int column);

int main(int argc, char *argv[]){
    clock_t start, end;
    double cpu_time_used;
    char *nombreArchivo;
    int c = 1;
    int b = 1;
    int a = 1;
    int N, option, hebras;
    double **matrix;

    while ((option = getopt(argc, argv, "i:N:H:d")) != -1){

        switch (option){
            case 'i':
            nombreArchivo = optarg;
            b = 0;
            break;
            case 'N':
            N = atoi(optarg);
            a = 0;
            break;
            case 'H':
            hebras = atoi(optarg);
            c = 0;
            break;
            case 'd':
            c = 0;
            break;
        }
    }

    if (a == 1 || b == 1 || c == 1 || hebras <= 0)
    {
        printf("flag invalida\n");
    }

    else{
        start = clock(); // Registra el tiempo de inicio
        // leer matriz
        matrix = leerMatriz(nombreArchivo, N);
        // definir numero de hebras
        omp_set_num_threads(hebras);
        // deshabilitar paralelismo anidado
        omp_set_nested(0);
        double result = determinantLaplace(matrix, N);
        printf("Determinante: %4.e\n", result);
        // Liberar memoria
        liberarMatrix(matrix,N);
        end = clock(); // Registra el tiempo de finalización
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Tiempo de ejecución: %lf segundos\n", cpu_time_used);
        return 0;
    }
}

