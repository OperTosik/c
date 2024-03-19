#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

void bubbleSort(
    double *a,  // Pointer to the beginning of array
    int n       // Size of array
);
void insertionSort(
    double *a,  // Pointer to the beginning of array
    int n       // Size of array
);

void heapSort(
    double *a,  // Pointer to the beginning of array
    int n       // Size of array
);

void bubbleDown(
    double *a,  // Pointer to the beginning of array
    int n,      // Size of array
    int i       // index of element to sieve
);

void makePyramid(
    double* a,
    int n
);

inline void swap(double& a, double& b) {
    double tmp = a; a = b; b = tmp;
}

void merge(
    const double *a,    // Beginning of first array
    int size_a,         // Size of first array
    const double *b ,   // Beginning of second array
    int size_b,         // Size of second array
    double *c           // Beginning of resulting array
);

void mergeSortRecursive(
    double *a,          // Beginning of array
    int n,              // Size of array
    double* tmpMemory = nullptr // Temporary memory to use
);

void mergeSortBottomTop(
    double *a,          // Beginning of array
    int n,              // Size of array
    double* tmpMemory = nullptr // Temporary memory to use
);

void printArray(
    const double *a,    // Beginning of array
    int n               // Size of array
);

void copyArray(
    const double *a,    // Beginning of the source array
    int n,              // Size of the source array
    double *b           // Beginning of the destination array
);

int main() {
    time_t tim;
    tim = time(&tim);
    srand(int(tim));
    double *a = nullptr;
    while (true) {
        int n;
        printf("Enter the size of array: ");
        if (scanf("%d", &n) < 1 || n <= 0)
            break;
            
        printf(
            "Enter the number of sorting algorithm:\n"
            "  1 BubbleSort, 2 InsertionSort, 3 HeapSort,\n"
            "  4 Recursive merge sort, 5 Bottom-Top merge sort\n"
        );
        int sortAlg;
        if (scanf("%d", &sortAlg) < 1)
            break;
        // Generate a random array of size n
        delete[] a; a = new double[n];
        for (int i = 0; i < n; ++i) {
            double x = (double(rand())/double(RAND_MAX)) * 1000.;
            a[i] = x;
        }
        printf("Random array:\n");
        printArray(a, n);
        printf("----\n");

        if (sortAlg == 1)
            bubbleSort(a, n);
        else if (sortAlg == 2)
            insertionSort(a, n);
        else if (sortAlg == 3)
            heapSort(a, n);
        else if (sortAlg == 4)
            mergeSortRecursive(a, n);
        else if (sortAlg == 5)
            mergeSortBottomTop(a, n);
        else
            continue;
        printf("Sorted array:\n");
        printArray(a, n);
        printf("----\n");
    }            
    delete[] a;
    return 0;
}

void bubbleSort(
    double *a,  // Pointer to the beginning of array
    int n       // Size of array
) {
    bool inversions = true;
    int pass = 0;
    while (inversions) {
        inversions = false;
        for (int i = 0; i < n-1-pass; ++i) {
            if (a[i] > a[i+1]) {
                swap(a[i], a[i+1]);
                inversions = true;
            }
        }
        ++pass;
    }
}

void printArray(
    const double *a,  // Pointer to the beginning of array
    int n
) {
    if (n <= 1000) {
        // Print all array
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                // Print a delimiter
                if (i%5 == 0)
                    printf("\n");
                else
                    printf(" ");
            }
            printf("%.3f", a[i]);
        }
    } else {
        // The array is too big, print its beginning and end only
        // (100 first and 100 last elements)
        for (int i = 0; i < 100; ++i) {
            if (i > 0) {
                // Print a delimiter
                if (i%5 == 0)
                    printf("\n");
                else
                    printf(" ");
            }
            printf("%.3f", a[i]);
        }
        printf("\n. . .\n");
        for (int i = n - 100; i < n; ++i) {
            if (i > n - 100) {
                // Print a delimiter
                if (i%5 == 0)
                    printf("\n");
                else
                    printf(" ");
            }
            printf("%.3f", a[i]);
        }
    }
    printf("\n");
}

void insertionSort(
    double *a,  // Pointer to the beginning of array
    int n       // Size of array
) { 
    int k = 0;
    while (k < n) {
        // Invariant: a[] <= a[1] <= ... <= a[k-1]
        double x = a[k];
        int i = k;
        while (i > 0 && x < a[i-1]) {
            a[i] = a[i-1];
            --i;
        }
        if (i < k)
            a[i] = x;
        ++k;
    }
}

void heapSort(
    double* a,
    int n
) {
    makePyramid(a, n);
    int k = n;
    while (k > 1) {
        --k;
        swap(a[0], a[k]);
        bubbleDown(a, k ,0);
    }
    
}    
    
void bubbleDown(
    double *a,  // Pointer to the beginning of array
    int n,      // Size of array
    int i       // index of element to sieve
) {
    while (true) {
        int s0 = 2*i + 1;
        int s1 = s0 + 1;
        if (s0 >= n)
            break;
        // Define elder son
        int s = s0;
        if (s1 < n && a[s1] > a[s0])
            s = s1;
        if (a[i] >= a[s])
            break;
        swap(a[i], a[s]);
        i = s;
    }
}

void makePyramid(
    double*a,
    int n
) {
    int k = n / 2;
    assert(2*k + 1 >= n);
    while ((k > 0)) {
        --k;
        bubbleDown(a, n, k);
    }
    
}

void merge(
    const double *a,    // Beginning of first array
    int size_a,         // Size of first array
    const double *b ,   // Beginning of second array
    int size_b,         // Size of second array
    double *c           // Beginning of resulting array
) {
    int idx_a = 0;
    int idx_b = 0;
    while (idx_a < size_a && idx_b < size_b) {
        if (a[idx_a] <= b[idx_b]) {
            *c = a[idx_a];
            ++idx_a;
        } else {
            *c = b[idx_b];
            ++idx_b;
        }
        ++c;
    }
    
    while (idx_a < size_a) {
        *c = a[idx_a];
        ++idx_a;
        ++c;
    }
    
    while (idx_b < size_b) {
        *c = b[idx_b];
        ++idx_b;
        ++c;
    }
}

void copyArray(
    const double *a,    // Beginning of the source array
    int n,              // Size of the source array
    double *b           // Beginning of the destination array
) {
    for (int i = 0; i < n; ++i)
        b[i] = a[i];
}

void mergeSortRecursive(
    double* a,
    int n,
    double* b            // Temporary memory to use
) {
    delete[] b; b = new double[n];
    if (n < 2) return;
    int mid = n / 2;
    double *left = new double[mid];
    double *right = new double[n - mid];
    for (int i = 0; i < mid; ++i)
        left[i] = a[i];
    for (int i = mid; i < n; ++i)
        right[i - mid] = a[i];
    mergeSortRecursive(left, mid);
    mergeSortRecursive(right, n - mid);
    merge(left, mid, right, n - mid, b);
    copyArray(b, n, a);
    delete[] b;
}

void mergeSortBottomTop(
    double* a,            // Beginning of array
    int n,                // Size of array
    double* b             // Temporary memory to use
) {
    if (n <= 1) return;
    delete[] b; b = new double[n];
    double *src = a, *dst = b;
    int len = 1;
    while (len < n) {
        int i = 0;
        while (i < n - len) {
            int len2 = len;
            if (i + len + len2 > n)
                len2 = n - (i + len);
            merge(
                src + i, len,
                src + i + len, len2,
                dst + i
            );
            i += len + len2;
        }
        if (i < n)
            copyArray(src + i, n - i, dst + i);
        len *= 2;
        double *tmp = src; src = dst; dst = tmp;
    }
    if (src != a) copyArray(b, n, a);
    delete[] b;
}
