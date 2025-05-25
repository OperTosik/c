// Reading and writing a matrix of dimension m*n
// m -- number of rows
// n -- number of columns
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <Windows.h>

const int MAX_THREADS = 16;

class ThreadArgs {
public:
    double* a;          // Pointer to matrix elements
    int rows;           // Matrix dimension: rows,
    int cols;           //                   columns 
    int resolveRow;     // Indices of resolution element: row,
    int resolveCol;     //                                column
    int row0;           // Initial row to process
    int numRows;        // Number of rows to process
    HANDLE hStartEvent;  // Event to start the work 
    HANDLE hFinishEvent; // Event that signals about finish of work
    HANDLE hThread;     // Thread handle
    DWORD threadID;     // Thread ID
    bool terminate;     // Request for suicide
};

// static int numThreads = 0;
// static ThreadArgs threadArgs[MAX_THREADS];

void initializeThreadPool(
    double *a, int m, int n,
    int numThreads,
    ThreadArgs* threadArgs
);

void releaseThreadPool(
    int numThreads,
    ThreadArgs* threadArgs
);

// Thread body function
DWORD WINAPI annihilateColumn(void* arg);

bool readMatrix(FILE* f, double **a, int* m, int* n); 
bool writeMatrix(FILE* f, const double *a, int m, int n);
void swapMatrixRows(
    double *a, int m, int n,
    int i, int k
);
void addMatrixRows(         // row[k] += row[i]*coeff 
    double *a, int m, int n,
    int k, int i, double coeff
);
void multiplyMatrixRow(
    double *a, int m, int n,
    int i, double coeff
);

int parallelGaussMethod(    // Return a matrix rank
    double *a, int m, int n,
    int numThreads = 4
); 
double det(double *a, int m, int n);

bool solveLinearSystem(
    const double *a, int n, // matrix n*n
    const double* b,        // column of the system right side
    double* x               // Solution of the system a*x = b
);

bool inverseMatrix(
    const double *a, int n, // matrix n*n
    double* inverse         // out: inverse matrix
);

const double EPS = 1e-8;

int main() {
    int m, n, numThreads;
    double *a = 0;
    
    LARGE_INTEGER frequency;    // The same as long long
    QueryPerformanceFrequency(&frequency);
    printf("Timer frequency = %lld\n", frequency.QuadPart);
        
    FILE* f = fopen("input.txt", "rt");
    if (f == NULL) {
        perror("Cannot open an input file");
        return (-1);
    }
    
    if (!readMatrix(f, &a, &m, &n)) {
        printf("Incorrect format of matrix.\n");
        delete[] a;
        fclose(f);
        return (-1);
    }
    fclose(f);
    
    printf("Matrix of size %d*%d:\n", m, n);
    writeMatrix(stdout, a, m, n);
    
    printf("Enter number of threads: ");
    if (scanf("%d", &numThreads) < 1) 
        exit(-1);
    
    DWORD startTime = 
        GetTickCount();  // Time in milliseconds since the start of system

    LARGE_INTEGER start;
    QueryPerformanceCounter(&start); // Precise time measurement

    int rank = parallelGaussMethod(a, m, n, numThreads);

    LARGE_INTEGER end;
    QueryPerformanceCounter(&end);  // Precise time measurement
    double interval = 
        double(end.QuadPart - start.QuadPart) / double(frequency.QuadPart);
    
    DWORD endTime = GetTickCount();
    DWORD dt = endTime - startTime;            
    
    printf("Row echelon form of matrix:\n");
    writeMatrix(stdout, a, m, n);

    printf("Rank of matrix: %d\n", rank);
    if (m == n) {
        printf("Determinant of matrix: %f\n", det(a, m, n));
    }

    printf("Computation time: %d ms\n", dt);
    printf("Computation interval: %.6f s\n", interval);
    
    // Writing the resulting matrix to the file "output.txt"
    FILE* g = fopen("output.txt", "wt");
    if (g == NULL) {
        perror("Cannot open an output file");
    } else {
        if (!writeMatrix(g, a, m, n))
            perror("Could not write a matrix to the output file");
        fclose(g);
    }

    delete[] a;
    
    return 0;
}

bool readMatrix(FILE* f, double **a, int* m, int* n) {
    // 2 3     
    // 11 12 13
    // 21 22 23
    int rows, cols;
    if (fscanf(f, "%d%d", &rows, &cols) < 2) {
        return false;
    }
    *m = rows; *n = cols;
    double *matrix = new double[rows*cols];
    *a = matrix;
    for (int i = 0; i < rows; ++i) {
        // Read i-th row of matrix
        for (int j = 0; j < cols; ++j) {
            if (fscanf(f, "%lf", matrix + i*cols + j) < 1) {
                // Read error
                return false;
            }
        }
    }
    return true;
}
    
bool writeMatrix(FILE* f, const double *a, int m, int n) {
    if (fprintf(f, "%d %d\n", m, n) <= 0) {
        return false;
    } 
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (fprintf(f, "%10.3f", a[i*n + j]) <= 0)
                return false;
        }
        fprintf(f, "\n");
    }    
    return true;
}

int parallelGaussMethod(    // Return a matrix rank
    double *a, int m, int n,
    int numThreads
) {  
    assert(numThreads > 0);
    if (numThreads > MAX_THREADS)
        numThreads = MAX_THREADS;
    
    ThreadArgs* threadArgs = new ThreadArgs[numThreads];
    HANDLE* activeEvents = new HANDLE[numThreads];

    initializeThreadPool(
        a, m, n,
        numThreads, threadArgs
    ); 

    int i = 0;
    int j = 0;
    while (i < m && j < n) {
        // 1. Find the maximal element in j-th column
        int k = i;
        double maxElem = fabs(a[k*n + j]);
        for (int l = i+1; l < m; ++l) {
            if (fabs(a[l*n + j]) > maxElem) {
                maxElem = fabs(a[l*n + j]);
                k = l;
            }
        }
        
        if (maxElem <= EPS) {
            // Zero colunm
            for (int l = i; l < m; ++l) {
                a[l*n + j] = 0.;
            }
            ++j;
            continue;
        }
        
        if (k != i) {
            // Swap rows i, k
            /*
            for (int l = j; l < n; ++l) {
                double tmp = a[i*n + l];
                a[i*n + l] = a[k*n + l];
                a[k*n + l] = (-tmp);
            }
            */
            swapMatrixRows(a, m, n, i, k);
        }            

        // Distribute tasks among threads
        int rowsToProcess = m - (i + 1);
        if (rowsToProcess > 0) {
            int numActiveThreads = numThreads;
            if (numActiveThreads > rowsToProcess) 
                numActiveThreads = rowsToProcess;
            int rowsPerThread = rowsToProcess/numActiveThreads;
            if (rowsToProcess%numActiveThreads != 0) {
                ++rowsPerThread;
                numActiveThreads = rowsToProcess/rowsPerThread;
                if (rowsToProcess%rowsPerThread > 0)
                    ++numActiveThreads;
            }
            
            /*
            printf(
                "Number of active threads=%d, rowsPerThread=%d\n",
                numActiveThreads, rowsPerThread
            );
            */
            
            int row = i + 1;
            for (int t = 0; t < numActiveThreads; ++t) {
                assert(row < m);
                ThreadArgs* args = &(threadArgs[t]);
                args->resolveRow = i;
                args->resolveCol = j;
                args->row0 = row;
                int nRows = rowsPerThread;
                if (row + nRows > m) {
                    nRows = m - row;
                }
                args->numRows = nRows;
                activeEvents[t] = args->hFinishEvent;
                row += nRows;
                SetEvent(args->hStartEvent);
            }
            assert(row == m);

            WaitForMultipleObjects(
                numActiveThreads,
                activeEvents,
                TRUE,
                INFINITE
            );
        }
        ++i; ++j;
    }
    
    releaseThreadPool(
        numThreads,
        threadArgs
    );
    
    delete[] activeEvents;
    delete[] threadArgs;

    return i;
}
            
double det(double *a, int m, int n) {
    double d = 1.;
    int k = n;
    if (m < n)
        k = m;
    for (int i = 0; i < k; ++i) {
        d *= a[i*n + i];
    }
    return d;
}

/*
class ThreadArgs {
public:
    double* a;
    int rows;
    int cols;
    int resolveRow;
    int resolveCol;
    int row0;           // Initial row to process
    int numRows;        // Number of rows to process
    HANDLE hThread;     // Thread handle
    HANDLE hStartEvent;  // Event to start the work 
    HANDLE hFinishEvent; // Event that signals about finish of work
    bool terminate;     // Request for suicide
};
*/

void initializeThreadPool(
    double *a, int m, int n,
    int numThreads,
    ThreadArgs* threadArgs
) {
    for (int i = 0; i < numThreads; ++i) {
        ThreadArgs* arg = &(threadArgs[i]);
        arg->a = a;
        arg->rows = m;
        arg->cols = n;
        arg->resolveRow = 0;
        arg->resolveCol = 0;
        arg->row0 = 0;
        arg->numRows = 0;
        arg->terminate = false;
        arg->hStartEvent = CreateEvent(
            NULL,   // LPSECURITY_ATTRIBUTES - default                                
            FALSE,  // bManulReset is false => auto-reset
            FALSE,  // bInitialState - nonsignaled
            NULL    // pName is NULL => not named                           
        );
        arg->hFinishEvent = CreateEvent(
            NULL,   // LPSECURITY_ATTRIBUTES - default                                
            FALSE,  // bManulReset is false => auto-reset
            FALSE,  // bInitialState - nonsignaled
            NULL    // pName is NULL => not named                           
        );
        arg->hThread = CreateThread(
            NULL,           // lpThreadAttributes
            0,              // dwStackSize - default
            &annihilateColumn,  // thread starting function
            (void *) arg,   // parameter of thread starting function
            0,              // dwCreationFlags
            &(arg->threadID)
        );
    }
}

void releaseThreadPool(
    int numThreads,
    ThreadArgs* threadArgs
) {
    HANDLE* activeThreads = new HANDLE[numThreads];
    for (int i = 0; i < numThreads; ++i) {
        threadArgs[i].terminate = true;
        SetEvent(threadArgs[i].hStartEvent);
        activeThreads[i] = threadArgs[i].hThread;
    }
    
    WaitForMultipleObjects(
        numThreads,
        activeThreads,
        TRUE,
        INFINITE
    );
    
    delete[] activeThreads;
    
    for (int i = 0; i < numThreads; ++i) {
        CloseHandle(threadArgs[i].hStartEvent);
        CloseHandle(threadArgs[i].hFinishEvent);
        CloseHandle(threadArgs[i].hThread);
    }
}


/*
class ThreadArgs {
public:
    double* a;
    int rows;
    int cols;
    int resolveRow;
    int resolveCol;
    int row0;           // Initial row to process
    int numRows;        // Number of rows to process
    HANDLE hThread;     // Thread handle
    HANDLE hStartEvent;  // Event to start the work 
    HANDLE hFinishEvent; // Event that signals about finish of work
    bool terminate;     // Request for suicide
};
*/
DWORD WINAPI annihilateColumn(void* arg) {
    ThreadArgs* threadArg = (ThreadArgs *) arg;
    double* a = threadArg->a;
    int m = threadArg->rows;
    int n = threadArg->cols;

    // printf("Thread started, ID=%d\n", threadArg->threadID); 

    while (true) {
        WaitForSingleObject(
            threadArg->hStartEvent,
            INFINITE
        );
        
        if (threadArg->terminate) {
            break;
        }
        
        assert(threadArg->numRows > 0);
        
        int i = threadArg->resolveRow;
        int j = threadArg->resolveCol;
        double r = a[i*n + j];
        int row0 = threadArg->row0;
        int row1 = row0 + threadArg->numRows;
        
        /*
        printf(
            "Thread ID=%d: process row0=%d, numRows=%d, i=%d, j=%d\n",
            threadArg->threadID, row0, threadArg->numRows, i, j
        );
        */
        
        for (int k = row0; k < row1; ++k) {
            /*...
            double coeff = a[k*n + j]/r;
            // Subtract i-th row multiplied by coeff from k-th row
            a[k*n + j] = 0.;
            for (int l = j+1; l < n; ++l) {
                a[k*n + l] -= a[i*n + l]*coeff;
            }
            ...*/
            double coeff = (-a[k*n + j]/r);
            addMatrixRows(
                a, m, n,
                k, i, coeff
            );
            a[k*n + j] = 0.;
        }
        
        SetEvent(threadArg->hFinishEvent);
    }

    // printf("Thread terminated, ID=%d\n", threadArg->threadID); 

    return 0;
}

void swapMatrixRows(
    double *a, int m, int n,
    int i, int k
) {
    for (int j = 0; j < n; ++j) {
        double tmp = a[i*n + j];
        a[i*n + j] = a[k*n + j];
        a[k*n + j] = (-tmp);
    }
}

void addMatrixRows(         // row[k] += row[i]*coeff 
    double *a, int m, int n,
    int k, int i, double coeff
) {
    for (int j = 0; j < n; ++j) {
        a[k*n + j] += a[i*n + j]*coeff;
    }
}

void multiplyMatrixRow(
    double *a, int m, int n,
    int i, double coeff
) {
    for (int j = 0; j < n; ++j) {
        a[i*n + j] *= coeff;
    }
}