#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "funciones.h"

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

void liberarMatrix(double **matrix,int tam){
    for(int i=0;i<tam;i++){
        free(matrix[i]);
    }
    free(matrix);
}

void verMatrix(double** matrix,int tam){
    for(int i =0;i<tam;i++){
        for (int j =0;j<tam;j++)
            printf(" %lf ",matrix[i][j]);
        printf("\n");    
    }
}