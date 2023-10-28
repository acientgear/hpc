#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "funciones.h"
#include <time.h>

/**
 * construye la matriz a partir de un archivo 
 * entradas: nombre string tamaño int
 * salidas: matriz double
 */
double** leerMatriz(char* nombre , int tam ){
    //char *aux;
    char numero[100];

    FILE* texto=fopen(nombre,"r");
    if (texto==NULL){
        printf("nombre invalido");
        return NULL;
        }

    double **matrix=(double**)malloc(sizeof(double*)*tam);
    
    for (int x = 0; x < tam; x++)
    {
        matrix[x]=(double*)malloc(sizeof(double)*tam);
    }

    for (int i=0 ;i<tam;i++){
        for (int j=0;j<tam;j++){
            fscanf(texto,"%s",numero);
            matrix[i][j] = atof(numero);
            //fscanf(texto,"%lf",&matrix[i][j]);
    }
    }
    fclose(texto);
    return matrix;
}

/**
 * funcion que libera el espacio de una matriz
 * entradas: matriz double tamaño int
 * salida: void
 */
void liberarMatrix(double **matrix,int tam){
    for(int i=0;i<tam;i++){
        free(matrix[i]);
    }
    free(matrix);
}

/**
 * funcion para visualizar una matriz
 * entradas: matriz double tamaño int
 */
void verMatrix(double** matrix,int tam){
    for(int i =0;i<tam;i++){
        for (int j =0;j<tam;j++)
            printf(" %lf ",matrix[i][j]);
        printf("\n");    
    }
}

/**
 * funcion que obtiene el determinante de una matriz mediante recursion algoritmo de laplace
 * entradas: matriz double , tamaño int 
 * salida: double
 * 
 */

double determinantLaplace(double **matrix, int size) {
    clock_t start = clock();
    if (size == 1) return matrix[0][0];
    double result = 0;

    #pragma omp parallel for default(none) shared(size, matrix,start) reduction(+ : result)
    for (int j = 0; j < size; j++) {
        int sign = (j % 2) ? -1 : 1;
        double **minorMatrix = (double **)malloc((size - 1) * sizeof(double *));
        for (int k = 0; k < size - 1; k++) {
            minorMatrix[k] = (double *)malloc((size - 1) * sizeof(double));
        }

        ijMinor(matrix, minorMatrix, size, 0, j);
         
        result += sign * matrix[0][j] * determinantLaplace(minorMatrix, size - 1);
        clock_t end  = clock(); // Registra el tiempo de finalización
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        if(size==16) 
        printf("Tiempo de ejecución: %f segundos , matriz de orden  : %d     hebra numero:%d   \n", cpu_time_used,size,omp_get_thread_num());
        for (int i = 0; i < size - 1; i++) {
            free(minorMatrix[i]);
        }
        free(minorMatrix);
    }
   
    return result;
}


/**
 * funcion auxiliar para determinante laplace crea una sub matriz del indice recorrido
 * entrdas: matrix double , submatrix double , int tamaño , int columna y fila 
 * salidas: void 
 * 
 */
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