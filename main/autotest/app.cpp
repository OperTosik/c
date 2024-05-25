#include <stdio.h>
#include <malloc.h>
#include <math.h>

void swapCol(double* array, int j1, int j2, int n, int m);
double weight(const double* array, int j, int n, int m);
void sort(double* array, int n, int m);
double mult(double* array, int m, int i);

int main(void) {
    FILE*fin;
    FILE*fout;
    int n, m;
    double*array;

    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");

    if (!fin) return -1;
    if (!fout) {
        fclose(fin);
        return -1;
    }

    if (fscanf(fin, "%d%d", &n, &m) < 2) return -1;
    if (n < 1 || m < 2) return -1;

    array = (double*)malloc(n*m * sizeof(double));
    if (!array) {
        fclose(fin);
        fclose(fout);
        return -1;
    }

    for(int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j < n && fscanf(fin, "%lg", &(array[i*m + j])) < 1) {
                free(array);
                fclose(fin);
                fclose(fout);
                return -1;
            }
        }
    }

    sort(array, n, m);
    fprintf(fout, "%d %d\n", n, m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fprintf(fout, "%lf    ", array[i*m + j]);
        }
        fprintf(fout, "\n");
    }

    for (int i = 0; i < n; ++i) {
        fprintf(fout, "%lf    ", mult(array, m, i));
    }

    fclose(fin);
    fclose(fout);
    free(array);
    return 0;
}

void swapCol(double* array, int j1, int j2, int n, int m) {
    if (j1 == j2) return;
    for (int i = 0; i < n; ++i) {
        double temp = array[i*m + j1];
        array[i*m + j1] = array[i*m + j2];
        array[i*m + j2] = temp;
    }
    return;
}

double weight(const double* array, int j, int n, int m) {
    double sum = 0;
    for (int i = 0; i < n - 1; ++i) {
        sum += fabs(array[i*m + j] - array[(i-1)*m + j]);
    }
    return sum;
}

void sort(double* array, int n, int m) {
    for (int j = 1; j < m; ++j) {
        for (int i = j; i > 0 && weight(array, i - 1, n, m) < weight(array, i, n, m); --i)
            swapCol(array, i-1, i, n, m);
    }
}

double mult(double* array, int m, int i) {
    double sum = 0;
    for (int j = 0; j < m; ++j) {
        sum += array[i*m + j] * array[j];
    }
    return sum;
}
