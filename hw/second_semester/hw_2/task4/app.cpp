#include <stdio.h>
#include <math.h>
#include <assert.h>

int gauss(double *a, int m, int n, double eps = 1e-12);
bool readMatrix(FILE* f, double* &a, int& m, int& n);
bool readMatrix(const char* path, double* &a, int& m, int& n);
bool writeMatrix(FILE* f, const double* a, int m, int n);
bool writeMatrix(const char* path, const double* a, int m, int n);
void reversePass(double *a, int m, int n, int rank, double eps = 1e-12); 
bool writeResult(FILE* f, const double* a, int m, int n);
bool writeResult(const char* path, const double* a, int m, int n);


int main(void) {
    double *a;
    int m, n;
    if (!readMatrix("input.txt", a, m, n)) {
        perror("Could not read the matrix");
        delete[] a;
        return -1;
    }
    writeMatrix(stdout, a, m, n); // Print the initial maatrix
    
    int rank = gauss(a, m, n);
    printf("rank of matrix: %d\n", rank);
    reversePass(a, m, n, rank);
    printf("Reverse Pass (Reduced Row Echelon Form):\n");
    writeMatrix(stdout, a, m, n);
    printf("Answer:\n");
    writeResult(stdout, a, m, n);       // Print the Result
    writeResult("output.txt", a, m, n); // and write in into the file    
    
    delete[] a;
    return 0;
}

int gauss(double *a, int m, int n, double eps) {
    int i = 0; int j = 0;
    while (i < m && j < n) {
        // Search for the maximal element in j-th column
        double maxelem = fabs(a[i*n + j]);
        int k = i;
        for (int l = i+1; l < m; ++l) {
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
            // Swap i-th and k-th rows
            for (int s = j; s < n; ++s) {
                double tmp = a[i*n + s];
                a[i*n + s] = a[k*n + s];
                a[k*n + s] = (-tmp);
            }
        }
        
        double r = a[i*n + j];  // Resolving element
        for (int l = i+1; l < m; ++l) {
            double c = a[l*n + j]/r;
            // Subtract i-th row multiplied by coeff. c from the l-th row
            a[l*n + j] = 0.;
            for (int s = j+1; s < n; ++s) {
                a[l*n + s] -= a[i*n + s]*c;
            }
        }

        ++i; ++j;
    }
    return i;
}

bool readMatrix(FILE* f, double* &a, int& m, int& n) {
    a = 0;
    if (fscanf(f, "%d%d", &m, &n) < 2)
        return false;
    a = new double[m*n];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (fscanf(f, "%lg", &(a[i*n + j])) < 1) {
                delete[] a; a = 0;
                return false;
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

bool writeMatrix(FILE* f, const double* a, int m, int n) {
    fprintf(f, "%d %d\n", m, n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0)
                fprintf(f, " ");        // Delimiter
            fprintf(f, "%12.4f", a[i*n + j]);
        }
        fprintf(f, "\n");   // Delimiter
    }
    return true;
}

bool writeMatrix(const char *path, const double* a, int m, int n) {
    FILE *f = fopen(path, "wt");
    if (f == NULL)
        return false;
    bool res = writeMatrix(f, a, m, n);
    fclose(f);
    return res;
}

void reversePass(double *a, int m, int n, int rank, double eps) {
    assert(rank <= m);
    int i = rank - 1;
    while (i >= 0) {
        // Search for the first nonzero element in i-th rows
        int j = 0;
        while (j < n && fabs(a[i*n + j]) <= eps)
            ++j;
        if (j >= n)
            assert(false);
        int j0 = j;
        double r = a[i*n + j0];
        assert(fabs(r) > eps);
        while (j < n) {
            a[i*n + j] /= r;
            ++j;
        }
    
        // Annihilate j-th column in rows 0..i-1
        for (int k = 0; k < i; ++k) {
            r = a[k*n + j0];
            a[k*n + j0] = 0.;
            for (j = j0 + 1; j < n; ++j) {
                a[k*n + j] -= a[i*n + j]*r;
            }
        }
        --i;
    }
}

bool writeResult(FILE* f, const double* a, int m, int n) {
    double eps = 1e-12;
    for (int i = 0; i < m; ++i) {
        double temp = 0; //value of lider
        for (int j = 0; j < n; ++j) {
            if (a[i*n + j] - 1.0 < eps) {
                //find lider of row
                for (int k = j + 1; k < n; ++k){
                    temp -= a[i*n + k];
                }
                break;
            }
        }
        fprintf(f, "%12.4f", temp);
        fprintf(f, "\n");   // Delimiter
    }
    return true;
}

bool writeResult(const char *path, const double* a, int m, int n) {
    FILE *f = fopen(path, "wt");
    if (f == NULL)
        return false;
    bool res = writeMatrix(f, a, m, n);
    fclose(f);
    return res;
}