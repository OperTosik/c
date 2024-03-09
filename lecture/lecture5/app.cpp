#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <malloc.h>
#include <assert.h>

//determinant of squad diagonal matrix
double refDet(const double *a, int m, int n);

int main(void){
    
    return 0;
}

double refDet(const double *a, int m, int n) {
    assert(m == n);
    double d = a[0];
    for (int i = 1; i < m; ++i) {
        d *= a[i*n + i];
    }
    return d;
}