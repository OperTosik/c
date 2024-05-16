#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int checkFile(FILE *file);
int readFile(FILE *file, int **arr, int i, int j);
void printArray(int **arr, int i, int j);
void findMaxInColumns(int **arr, int *max, int i, int j, int *numberMaxString);
int removeDuplicateString(int **arr, int *numberMaxString, int i, int j);
void writeToFile(FILE *file, int **arr, int i, int j);
