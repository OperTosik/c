#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void f(double *array, int d);

int main(void) {
    FILE*fin = fopen("input.txt", "r");
    FILE*fout = fopen("output.txt", "w");
    int d = 0;
    double *array;
    double x;
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
    while (fscanf(fin, "%lf", &x) == 1) ++d;
    rewind(fin);
    array = (double*)malloc((d + 2) * sizeof(double));
    for (int i = 0; fscanf(fin, "%lf", &x) == 1; ++i) array[i] = x;
    fclose(fin);
    f(array, d);
    for (int i = 0; i < d + 2; i++) {
        fprintf(fout, "%lf ", array[i]);
    }
    fclose(fout);
    free(array);
    return 0;
}

void f(double *array, int d) {
    for (int i = d + 2; i > 0; --i) {
        array[i] = array[i - 1];
    }
    array[0] = 0;
    for (int i = 2; i < d + 2; ++i) {
        array[i] /= i;
    }
}