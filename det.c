#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <omp.h>
#include "funciones.h"




int main(int argc, char *argv[]){
    char* nombre,*tam,*hebras;
    int c = 1;
    int b=1;
    int a=1;
    int N;
    int option;
    int det = 0;
    float** matrix;
    while((option = getopt(argc, argv, "i:N:H:d")) != -1){
        switch(option){
            case 'i':
                nombre = optarg;
                b=0;
                break;
            case 'N':
                tam = optarg;
                N=atoi(tam);
                a=0;
                break;
            case 'H':
                hebras= optarg;
                c = 0;
                break;
            case 'd':
                c=0;
                break;

        }
    }
    if (a==1 || b==1 || c==1){
        printf("flag invalida\n");

    }
    else {
        printf("nombre %s, tamaño %s,hebras %s \n",nombre,tam,hebras);
        matrix=leerMatriz(nombre,tam);
        if (matrix==NULL)
        {
            printf("\n");
        }
        else{
            verMatrix(matrix,tam);
            //det=parallel_det(matrix,N,atoi(hebras),0,N);
            //det=determinant(matrix,N);
            size_t  a=sizeof(matrix)*N*N;
            printf("el determinante es: %d",a);
            
          

            liberarMatrix(matrix,tam);
        }
        
    
    }
    return 0;
}