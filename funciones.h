#include <stdio.h>

double** leerMatriz(char* nombre,int tam);
void liberarMatrix(double** nombre,int tam);
void verMatrix(double** nombre,int tam);
void ijMinor(double **matrix, double **minorMatrix, int size, int row, int column);
double determinantLaplace(double **matrix, int size);