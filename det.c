#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <omp.h>
#include "funciones.h"

double determinantLaplace(double **matrix, int size);
void ijMinor(double **matrix, double **minorMatrix, int size, int row, int column);

int main(int argc, char *argv[]){

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

    if (a == 1 || b == 1 || c == 1)
    {
        printf("flag invalida\n");
    }

    else{
        // leer matriz
        matrix = leerMatriz(nombreArchivo, N);
        // definir numero de hebras
        omp_set_num_threads(hebras);
        // deshabilitar paralelismo anidado
        omp_set_nested(0);
        double result = determinantLaplace(matrix, N);
        printf("Determinante: %lf\n", result);
        // Liberar memoria
        for (int i = 0; i < N; i++){
            free(matrix[i]);
        }
        free(matrix);
        return 0;
    }
}

double determinantLaplace(double **matrix, int size) {
    if (size == 1) return matrix[0][0];
    double result = 0;

    #pragma omp parallel for default(none) shared(size, matrix) reduction(+ : result)
    for (int j = 0; j < size; j++) {
        int sign = (j % 2) ? -1 : 1;
        double **minorMatrix = (double **)malloc((size - 1) * sizeof(double *));
        for (int k = 0; k < size - 1; k++) {
            minorMatrix[k] = (double *)malloc((size - 1) * sizeof(double));
        }

        ijMinor(matrix, minorMatrix, size, 0, j);

        result += sign * matrix[0][j] * determinantLaplace(minorMatrix, size - 1);

        for (int i = 0; i < size - 1; i++) {
            free(minorMatrix[i]);
        }
        free(minorMatrix);
    }
    return result;
}


void ijMinor(double **matrix, double **minorMatrix, int size, int row, int column) {
    int minorRow = 0;
    for (int i = 0; i < size; i++) {
        if (i == row) continue;
        
        int minorCol = 0;
        for (int j = 0; j < size; j++) {
            if (j == column) continue;
            minorMatrix[minorRow][minorCol] = matrix[i][j];
            minorCol++;
        }
        minorRow++;
    }
}