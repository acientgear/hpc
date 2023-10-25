#include <stdio.h>


float** leerMatriz(char* nombre,char* tam);

void liberarMatrix(float** nombre,char* tam);

void verMatrix(float** nombre,char* tam);

float parallel_det(float** mat, int size, int num_threads, int col_offset, int col_range);

float det2x2(float mat[2][2]);
float determinant(float **matrix, int N);
