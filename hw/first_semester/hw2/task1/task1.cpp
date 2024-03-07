#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

double f(const double *array, int len);

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
    fprintf(fout, "%lf\n", f(array, len));
    fclose(fout);
    free(array);
    return 0;
}

double f(const double *array, int len) {
    double sum = 0;
    double len_possitive = 0;
    double eps = 1e-16;
    for (int i = 0; i < len; ++i) 
        if (array[i] > eps)  {
            sum += array[i];
            ++len_possitive;
        }
    return sum / len_possitive;
}