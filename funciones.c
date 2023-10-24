#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

