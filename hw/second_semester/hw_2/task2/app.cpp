#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

int gauss(double *a, int m, int n, double eps = 1e-12);
// double *f(double*array, double m, double n);

int main(void) {
    FILE*fin = fopen("input.txt", "r");
    FILE*fout = fopen("output.txt", "w");
    int m, n;
    double *array;
    if (fin == NULL) {
        perror("Cannot open an input file");
        fclose(fin);
        return -1;
    }
    if (fscanf(fin, "%d", &m) != 1) {
        fprintf(stderr, "Incorrect file format\n");
        fclose(fin);
        return -1;
    }
    fscanf(fin, "%d", &n);
    if (m != n) {
        printf("Incorrect format input file");
        free(array);
        return -1;
    }
    array = (double*)malloc(n*2*n * sizeof(double));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 2*n; ++j) {
            if (j < n){
                fscanf(fin, "%lf", &array[i*2*n + j]);
            }
            else{
                if (n + i == j) array[i*2*n + j] = 1;
                else array[i*2*n + j] = 0;
            }
        }
    }
    fclose(fin);
    if (fout == NULL) {
        perror("Cannot open an input file");
        free(array);
        return -1;
    }

    printf("%d", gauss(array, m, n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fprintf(fout, "%lf ", array[i*2*n  + j]);
        }
        fprintf(fout, "\n");
    }
    for (int i = 0; i < n; ++i) {
        for (int j = n; j < 2*n; ++j) {
            fprintf(fout, "%lf ", array[i*2*n + j]);
        }
        fprintf(fout, "\n");
    }
    fclose(fout);
    free(array);
    return 0;
}

// double *f(double*array, double m, double n) {

// }

int gauss(double *a, int m, int n, double eps/* = 1e-12*/) {
    int i = 0; int j = 0;
    while (i < m && j < n) {
        //1. search for max element in j-th column
        double maxelem = fabs(a[i*2*n + j]);
        int k = i;
        for (int l = i + 1; l < m; ++l) {
            if (fabs(a[l*2*n + j]) > maxelem) {
                maxelem = fabs(a[l*2*n + j]);
                k = l;
            }
        }

        if (fabs(maxelem) <= eps) {
            ++j;
            continue;
        }

        if (k != i) {
            //swap i-th and k-th rows
            for (int s = j; s < m; ++s){
                double tmp = a[i*2*n + s];
                a[i*2*n + s] = a[k*2*n + s];
                a[k*2*n + s] = (-tmp);
            }
            
        }
        //sum with lambda 
        double r = a[i*2*n + j];
        for (int l = 0; l != i && l < m; ++l) {
            double c = a[l*2*n + j] / r;
            for (int s = j; s < 2*n; ++s) {
                a[l*2*n + s] -= a[l*2*n + s]*c;
            }
        }
        ++i; ++j;
    }
    return i;
}