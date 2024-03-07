#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void f(double *array, int len);

int main(void) {
    FILE*fin = fopen("input.txt", "r");
    FILE*fout = fopen("output.txt", "w");
    int len = 1;
    double x;
    double *array;
    if (fin == NULL) {
        perror("Cannot open an input file");
        fclose(fin);
        return -1;
    }
    if (fscanf(fin, "%lf", &x) != 1) {
        fprintf(stderr, "Incorrect file format\n");
        fclose(fin);
        return -1;
    }
    while (fscanf(fin, "%lf", &x) == 1) ++len;
    rewind(fin);
    array = (double*)malloc(len * sizeof(double));
    for (int i = 0; i < len; ++i) 
        fscanf(fin, "%lf", array + i);
    fclose(fin);
    if (fout == NULL) {
        perror("Cannot open an input file");
        free(array);
        return -1;
    }
    f(array, len);
    for (int i = 0; i < len; ++i) 
        fprintf(fout, "%lf ", array[i]);
    fclose(fout);
    free(array);
    return 0;
}

void f(double *array, int len) {
    int temp;
    for (int i = 2; i < len; i += 2) {
        for (int j = i; j > 0 && array[j - 2] > array[j]; j -= 2) {
            temp = array[j - 2];
            array[j - 2] = array[j];
            array[j] = temp;
        }
    }
}