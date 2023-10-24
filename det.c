#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "funciones.h"



int main(int argc, char *argv[]){
    char* nombre1,*nombre2,*nombre3;
    int c = 1;
    int b=1;
    int a=1;
    int option;
    float** matrix;
    while((option = getopt(argc, argv, "i:N:H:d")) != -1){
        switch(option){
            case 'i':
                nombre1 = optarg;
                b=0;
                break;
            case 'N':
                nombre2 = optarg;
                a=0;
                break;
            case 'H':
                nombre3= optarg;
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
        printf("nombre %s, tamaño %s,hebras %s \n",nombre1,nombre2,nombre3);
        matrix=leerMatriz(nombre1,nombre2);
        if (matrix==NULL)
        {
            printf("\n");
        }
        else{
            verMatrix(matrix,nombre2);
            liberarMatrix(matrix,nombre2);
        }
        
    
    }
    return 0;
}