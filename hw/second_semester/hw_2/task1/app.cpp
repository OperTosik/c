#include <stdio.h>
#include <math.h>
#include <assert.h>

int gauss(double *a, int m, int n, double eps = 1e-12);
bool readMatrix(FILE* f, double* &a, int& m, int& n);
bool readMatrix(const char* path, double* &a, int& m, int& n);
bool writeMatrix(FILE* f, const double* a, int m, int n);
bool writeMatrix(const char* path, const double* a, int m, int n);
void reversePass(double *a, int m, int n, int rank, double eps = 1e-12); 
bool writeResult(FILE* f, const double* a, int m, int n, int rank);
bool writeResult(const char* path, const double* a, int m, int n, int rank);

int main(void) {
    double *a;
    double *b;
    int m, n;
    if (!readMatrix("input.txt", a, m, n)) {
        perror("Could not read the matrix");
        delete[] a;
        return -1;
    }
    if (!readMatrix("input.txt", b, m, n)) {
        perror("Could not read the matrix");
        delete[] b;
        return -1;
    }
    writeMatrix(stdout, a, m, n); // Print the initial maatrix
    
    int rank = gauss(a, m, n);
    // printf("rank of matrix: %d\n", rank);
    reversePass(a, m, n, rank);
    writeResult(stdout, b, m, n, rank);       // Print the Result
    writeResult("output.txt", b, m, n, rank); // and write in into the file
    
    delete[] a;
    return 0;
}

int gauss(double *a, int m, int n, double eps) {
    int i = 0; int j = 0;
    while (i < m && j < n) {
        // Search for the maximal element in j-th column
        double maxelem = fabs(a[i*(n + 1) + j]);
        int k = i;
        for (int l = i+1; l < m; ++l) {
            if (fabs(a[l*(n + 1) + j]) > maxelem) {
                maxelem = fabs(a[l*(n + 1) + j]);
                k = l;
            }
        }

        if (maxelem <= eps) {
            ++j;
            continue;
        }
        if (k != i) {
            // Swap i-th and k-th rows
            for (int s = j; s < n + 1; ++s) {
                double tmp = a[i*(n + 1) + s];
                a[i*(n + 1) + s] = a[k*(n + 1) + s];
                a[k*(n + 1) + s] = (-tmp);
            }
        }
        double r = a[i*(n + 1) + j];  // Resolving element
        for (int l = i+1; l < m; ++l) {
            double c = a[l*(n + 1) + j]/r;
            a[l*(n + 1) + j] = 0.;
            for (int s = j+1; s < n; ++s) {
                a[l*(n + 1) + s] -= a[i*(n + 1) + s]*c;
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
    a = new double[m*(n + 1)];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n + 1; ++j) {
            if (j < n && fscanf(f, "%lg", &(a[i*(n + 1) + j])) < 1) {
                delete[] a; a = 0;
                return false;
            }
            else if (j == n) a[i*(n + 1) + j] = i;
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
            fprintf(f, "%12.4f", a[i*(n + 1) + j]);
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
        while (j < n && fabs(a[i*(n + 1) + j]) <= eps)
            ++j;
        if (j >= n)
            assert(false);
        int j0 = j;
        double r = a[i*(n + 1) + j0];
        assert(fabs(r) > eps);
        while (j < n) {
            a[i*(n + 1) + j] /= r;
            ++j;
        }
    
        // Annihilate j-th column in rows 0..i-1
        for (int k = 0; k < i; ++k) {
            r = a[k*(n + 1) + j0];
            a[k*(n + 1) + j0] = 0.;
            for (j = j0 + 1; j < n; ++j) {
                a[k*(n + 1) + j] -= a[i*(n + 1) + j]*r;
            }
        }
        --i;
    }
}

bool writeResult(FILE* f, const double* a, int m, int n, int rank) {
    fprintf(f, "Rank: %d\n", rank);
    fprintf(f, "Lenght of vectors: %d\n", n);
    for (int i = 0; i < rank; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0)
                fprintf(f, " ");        // Delimiter
            fprintf(f, "%12.4f", a[i*(n + 1) + j]);
        }
        fprintf(f, "\n");   // Delimiter
    }
    return true;
}

bool writeResult(const char *path, const double* a, int m, int n, int rank) {
    FILE *f = fopen(path, "wt");
    if (f == NULL)
        return false;
    bool res = writeResult(f, a, m, n, rank);
    fclose(f);
    return res;
}