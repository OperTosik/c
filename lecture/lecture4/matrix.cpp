#include <stdio.h>
#include <math.h>

int gauss(double *a, int m, int n, double eps = 1e-12);
bool readMatrix(FILE *f, double* &a, int &m, int &n);
bool writeMatrix(FILE *f, double* &a, int &m, int &n);


int main(void) {
    
    return 0;
}

int gauss(double *a, int m, int n, double eps/* = 1e-12*/) {
    int i = 0; int j = 0;
    while (i < m && j < n) {
        //1. search for max element in j-th column
        double maxelem = fabs(a[i*n + j]);
        int k = i;
        for (int l = i + 1; l < m; ++l) {
            if (fabs(a[l*n + j]) > maxelem) {
                maxelem = fabs(a[l*n + j]);
                k = l;
            }
        }
        if (maxelem <= eps) {
            ++j;
            continue;
        }
        if (k != i) {
            //swap i-th and k-th rows
            for (int s = j; s < n; ++s){
                double tmp = a[i*n + s];
                a[i*n + s] = a[k*n + s];
                a[k*n + s] = (-tmp);
            }
        }
        double r = a[i*n + j];
        for (int l = i + 1; l < m; ++l) {
            double c = a[l*n + j] / r;
            for (int s = j; s < n; ++s) {
                a[l*n + s] -= a[l*n + s]*c;
            }
        }
        ++i; ++j;
    }
    return i;
}

bool readMatrix(FILE *f, double* &a, int &m, int &n) {
    a = 0;
    if (fscanf(f, "%d%d", &m, &n) < 2) return false;
    a = new double [m*n];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (fscanf(f, "%lg", &a[i*n + j]) < 1) {
                delete[] a;
                a = 0;
                
            }
        }
    }
}

bool writeMatrix(FILE *f, double* &a, int &m, int &n) {

}