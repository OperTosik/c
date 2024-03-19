#include <stdio.h>
#include <math.h>
#include <assert.h>

int gauss(double *a, int m, int n, double eps = 1e-12);
bool readMatrix(FILE* f, double* &a, int& m, int& n);
bool readMatrix(const char* path, double* &a, int& m, int& n);
bool writeMatrix(FILE* f, const double* a, int m0, int m_n, int m, int n);
bool writeMatrix(const char* path, const double* a, int m0, int m_n, int m, int n);
void reversePass(double *a, int m, int n, int rank, double eps = 1e-12); 

int main(void) {
    double *a;
    int m, n;
    if (!readMatrix("input.txt", a, m, n)) {
        perror("Could not read the matrix");
        delete[] a;
        return -1;
    }
    writeMatrix(stdout, a, 0, m, m, n); // Print the initial maatrix
    
    int rank = gauss(a, m, n);
    printf("rank of matrix: %d\n", rank);
    
    
    reversePass(a, m, n, rank);
    printf("Reverse matrix\n");
    writeMatrix(stdout, a, m, 2*m, m, n);
    writeMatrix("output.txt", a, m, 2*m, m, n);
    
    delete[] a;
    return 0;
}

int gauss(double *a, int m, int n, double eps) {
    int i = 0; int j = 0;
    while (i < m && j < n) {
        // Search for the maximal element in j-th column
        double maxelem = fabs(a[i*2*n + j]);
        int k = i;
        for (int l = i+1; l < m; ++l) {
            if (fabs(a[l*2*n + j]) > maxelem) {
                maxelem = fabs(a[l*2*n + j]);
                k = l;
            }
        }

        if (maxelem <= eps) {
            ++j;
            continue;
        }

        if (k != i) {
            // Swap i-th and k-th rows
            for (int s = j; s < 2*n; ++s) {
                double tmp = a[i*2*n + s];
                a[i*2*n + s] = a[k*2*n + s];
                a[k*2*n + s] = (-tmp);
            }
        }
        
        // Zero the j-th column of matrix starting from i+1-th row
        double r = a[i*2*n + j];
        for (int l = i+1; l < m; ++l) {
            double c = a[l*2*n + j]/r;
            // Subtract i-th row multiplied by coeff. c from the l-th row
            a[l*2*n + j] = 0.;
            for (int s = j+1; s < 2*n; ++s) {
                a[l*2*n + s] -= a[i*2*n + s]*c;
            }
        }
        ++i; ++j;
    }
    return i;
}

bool readMatrix(FILE* f, double* &a, int& m, int& n) {
    a = 0;
    if (fscanf(f, "%d%d", &m, &n) < 2 && n == m)
        return false;
    a = new double[m*2*n];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 2*n; ++j) {
            if (j < n && fscanf(f, "%lg", &(a[i*2*n + j])) < 1) {
                delete[] a; a = 0;
                return false;
            }
            else if (j > n - 1) {
                if (i + n == j) a[i*2*n + j] = 1;
                else a[i*2*n + j] = 0;
            }
        }
    }
    return true;
}

bool readMatrix(const char *path, double* &a, int& m, int& n) {
    FILE *f = fopen(path, "rt");
    if (f == NULL)
        return false;
    bool res = readMatrix(f, a, m, n);
    fclose(f);
    return res;
}

bool writeMatrix(FILE* f, const double* a, int m0, int m_n, int m, int n) {
    fprintf(f, "%d %d\n", m, n);
    for (int i = 0; i < m; ++i) {
        for (int j = m0; j < m_n; ++j) {
            if (j > 0)
                fprintf(f, " ");        // Delimiter
            fprintf(f, "%12.4f", a[i*2*n + j]);
        }
        fprintf(f, "\n");   // Delimiter
    }
    return true;
}

bool writeMatrix(const char *path, const double* a, int m0, int m_n, int m, int n) {
    FILE *f = fopen(path, "wt");
    if (f == NULL)
        return false;
    bool res = writeMatrix(f, a, m0, m_n, m, n);
    fclose(f);
    return res;
}   

void reversePass(double *a, int m, int n, int rank, double eps) {
    assert(rank <= m);
    int i = rank - 1;
    while (i >= 0) {
        // Search for the first nonzero element in i-th rows
        int j = 0;
        while (j < n && fabs(a[i*2*n + j]) <= eps)
            ++j;
        if (j >= n)
            assert(false);
        int j0 = j;
        double r = a[i*2*n + j0];
        assert(fabs(r) > eps);
        while (j < 2*n) {
            a[i*2*n + j] /= r;
            ++j;
        }
    
        // Annihilate j-th column in rows 0..i-1
        for (int k = 0; k < i; ++k) {
            r = a[k*2*n + j0];
            a[k*2*n + j0] = 0.;
            for (j = j0 + 1; j < 2*n; ++j) {
                a[k*2*n + j] -= a[i*2*n + j]*r;
            }
        }
        --i;
    }
}
