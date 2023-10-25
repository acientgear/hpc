#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "funciones.h"

float** leerMatriz(char* nombre , char* tam ){
    //char *aux;
    char numero[100];

    FILE* texto=fopen(nombre,"r");
    if (texto==NULL){
        printf("nombre invalido");
        return NULL;
        }

    int len=atoi(tam);
    float **matrix=(float**)malloc(sizeof(float*)*len);
    
    for (int x = 0; x < len; x++)
    {
        matrix[x]=(float*)malloc(sizeof(float)*len);
    }

    for (int i=0 ;i<len;i++){
        for (int j=0;j<len;j++){
            fscanf(texto,"%s",numero);
            matrix[i][j]=atof(numero);
            //fscanf(texto,"%lf",&matrix[i][j]);
    }
    }    
    fclose(texto);
    return matrix;
}

void liberarMatrix(float **matrix,char* tam){

    for(int i=0;i<atoi(tam);i++){
        free(matrix[i]);
    }
    free(matrix);

}


void verMatrix(float** matrix,char* tam){
    int len=atoi(tam);
    for(int i =0;i<len;i++){
        for (int j =0;j<len;j++)
            printf(" %lf ",matrix[i][j]);
        printf("\n");    
    }
}




// Function to calculate the determinant of a 2x2 matrix
float det2x2(float mat[2][2]) {
    return (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]);
}

// Function to calculate the determinant of a square matrix with column-wise parallelization
// Function to calculate the determinant of a square matrix with column-wise parallelization
float parallel_det(float **mat, int size, int num_threads, int col_offset, int col_range) {
    if (size == 2 || num_threads == 1) {
        float submatrix[2][2];
        for (int i = 0; i < 2; i++) {
            for (int j = col_offset; j < col_offset + col_range; j++) {
                submatrix[i][j - col_offset] = mat[i + 1][j];
            }
            return det2x2(submatrix);
        }
    }

    float det = 0.0;
    #pragma omp parallel for reduction(+:det) num_threads(num_threads) firstprivate(mat)
    for (int col = col_offset; col < col_offset + col_range; col++) {
        int subcol = 0;
        for (int j = col_offset; j < col_offset + col_range; j++) {
            if (j == col) {
                continue;
            }
            int subrow = 0;
            for (int i = 1; i < size; i++) {
                mat[i - 1][subcol] = mat[i][j];
                subrow++;
            }
            subcol++;
        }
        int sign = (col % 2 == 0) ? 1 : -1;
        det += sign * mat[0][col] * parallel_det(mat, size - 1, num_threads, 0, col_range - 1);
    }

    return det;
}

float determinant(float **matrix, int N) {
    if (N == 1) {
        return matrix[0][0];
    }
    
    if (N == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    float det = 0;
    
    #pragma omp parallel for reduction(+:det)
    for (int j = 0; j < N; j++) {
        float **submatrix = (float **)malloc((N - 1) * sizeof(float *));
        for (int i = 0; i < N - 1; i++) {
            submatrix[i] = (float *)malloc((N - 1) * sizeof(float));
        }
        
        for (int i = 1; i < N; i++) {
            for (int k = 0, l = 0; k < N; k++) {
                if (k != j) {
                    submatrix[i - 1][l] = matrix[i][k];
                    l++;
                }
            }
        }
        
        int sign = (j % 2 == 0) ? 1 : -1;
        det += sign * matrix[0][j] * determinant(submatrix, N - 1);

        for (int i = 0; i < N - 1; i++) {
            free(submatrix[i]);
        }
        free(submatrix);
    }
    
    return det;
}
