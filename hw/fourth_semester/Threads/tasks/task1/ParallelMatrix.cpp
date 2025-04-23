#include "ParallelMatrix.h"

bool readMatrix(FILE* f, double **a, int* m, int* n, int action) {
    // 2 3     
    // 11 12 13
    // 21 22 23
    int rows, cols;
    if (fscanf(f, "%d%d", &rows, &cols) < 2) {
        return false;
    }
    if (action == 2 && rows != cols) {
        scanf("Matrix is not square");
        return false;
    }
    *m = rows; *n = cols;
    double *matrix = new double[rows*action*cols];
    *a = matrix;
    for (int i = 0; i < rows; ++i) {
        // Read i-th row of matrix
        for (int j = 0; j < cols; ++j) {
            if (fscanf(f, "%lf", matrix + i*action*cols + j) < 1) {
                // Read error
                return false;
            }
        }
        for (int j = cols; j < action*cols && action == 2; ++j) {
            if (i == j - cols) {
                matrix[i*action*cols + j] = 1;
            }
            else {
                matrix[i*action*cols + j] = 0;
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
    int numThreads,
    int action
) {  
    assert(numThreads > 0);
    if (numThreads > MAX_THREADS)
        numThreads = MAX_THREADS;
    
    threadArgs.resize(numThreads);

    initializeThreadPool(
        a, m, action*n,
        numThreads
    ); 

    int i = 0;
    int j = 0;
    while (i < m && j < n) {
        // 1. Find the maximal element in j-th column
        int k = i;
        double maxElem = fabs(a[k*action*n + j]);
        for (int l = i+1; l < m; ++l) {
            if (fabs(a[l*action*n + j]) > maxElem) {
                maxElem = fabs(a[l*action*n + j]);
                k = l;
            }
        }
        
        if (maxElem <= EPS) {
            // Zero colunm
            for (int l = i; l < m; ++l) {
                a[l*action*n + j] = 0.;
            }
            ++j;
            continue;
        }
        
        if (k != i) {
            swapMatrixRows(a, m, action*n, i, k, action);
        }            

        // Distribute tasks among threads
        int rowsToProcess = m - (i + 1);
        if (rowsToProcess > 0) {
            {
                std::lock_guard<std::mutex> lock(finishMutex);
                numFinishedThreads = 0;
            }

            {
                std::lock_guard<std::mutex> lock(startMutex);

                numActiveThreads = numThreads;
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
                    args->start = true;
                    row += nRows;
                }
                assert(row == m);
            }

            // printf("notify_all to start\n");

            startCondition.notify_all();

            waitForAllThreads();

        } // end if (rowsToProcess > 0)

        ++i; ++j;
    } // end while
    
    releaseThreadPool();
    
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

void initializeThreadPool(
    double *a, int m, int n,
    int numThreads
) {
    {
        std::lock_guard<std::mutex> lock(finishMutex);
        numWorkingThreads = 0;
    }

    for (int threadIdx = 0; threadIdx < numThreads; ++threadIdx) {
        ThreadArgs* arg = &(threadArgs[threadIdx]);
        arg->a = a;
        arg->rows = m;
        arg->cols = n;
        arg->resolveRow = 0;
        arg->resolveCol = 0;
        arg->row0 = 0;
        arg->numRows = 0;
        arg->start = false;
        arg->terminate = false;
        arg->working = false;
        threads.push_back(
            std::thread(annihilateColumn, threadIdx)
        );
    }

    {
        std::unique_lock<std::mutex> lock(finishMutex);
        while (numWorkingThreads < numThreads) {
            // printf("numWorkingThreads=%d, waiting...\n", numWorkingThreads);
            finishCondition.wait(lock);
        }
        /*
        printf(
            "numWorkingThreads=%d, all threads started\n", 
            numWorkingThreads
        );
        */
    }
}

void releaseThreadPool() {
    {
        std::lock_guard<std::mutex> lock(startMutex);
        for (int i = 0; i < numThreads; ++i) {
            threadArgs[i].terminate = true;
        }
    }

    // printf("notify_all to terminate.\n");

    startCondition.notify_all();

    for (int i = 0; i < numThreads; ++i) {
        // printf("joining thread %d.\n", i);
        threads[i].join();
    }
}

void annihilateColumn(int threadIdx, int action) {
    ThreadArgs& threadArg = threadArgs[threadIdx];
    double* a = threadArg.a;
    int m = threadArg.rows;
    int n = threadArg.cols;

    // printf("Thread is created, idx=%d\n", threadIdx);
    {
        std::lock_guard<std::mutex> lock(finishMutex);
        ++numWorkingThreads;
    }
    finishCondition.notify_one();

    while (true)
    {
        bool endWork = false;
        {
            std::unique_lock<std::mutex> lock(startMutex);
            while (true) {
                if (threadArg.terminate) {
                    endWork = true;
                    break;
                } else if (threadIdx < numActiveThreads && threadArg.start) {
                    break;
                }

                // printf("Thread %d, waiting for start...\n", threadIdx);
                startCondition.wait(lock);
            }
        }

        if (endWork) {
            // printf("Thread %d, terminating\n", threadIdx);
            break;
        }
        
        // printf("Thread is started, idx=%d\n", threadIdx);

        assert(threadArg.start);
        threadArg.start = false;
        assert(threadArg.numRows > 0);
        
        int i = threadArg.resolveRow;
        int j = threadArg.resolveCol;
        double r = a[i*action*n + j];
        int row0 = threadArg.row0;
        int row1 = row0 + threadArg.numRows;
        
        /*
        printf(
            "ThreadIdx=%d: process row0=%d, numRows=%d, i=%d, j=%d\n",
            threadIdx, row0, threadArg.numRows, i, j
        );
        */
        
        for (int k = row0; k < row1; ++k) {
            // Subtract i-th row multiplied by coeff from k-th row
            //     so that the element a_kj becomes zero
            double coeff = (-a[k*action*n + j]/r);
            addMatrixRows(
                a, m, action*n,
                k, i, coeff,
                action
            );
            a[k*action*n + j] = 0.;
        }
        
        {
            std::lock_guard<std::mutex> lock(finishMutex);
            ++numFinishedThreads;
        }

        finishCondition.notify_one(); // Signal the end of work

    } // end while

    // printf("Thread terminated, ID=%d\n", threadArg.threadIdx);
}

void waitForAllThreads() {
    std::unique_lock<std::mutex> lock(finishMutex);
    while (numFinishedThreads < numActiveThreads) {
        /*
        printf(
            "numFinishedThreads = %d, waiting for %d\n",
            numFinishedThreads, numActiveThreads
        );
        */
        finishCondition.wait(lock);
    }
    // printf("waitForAllThreads finished.\n");
}

void swapMatrixRows(
    double *a, int m, int n,
    int i, int k, int action
) {
    assert(0 <= i && i < m);
    assert(0 <= k && k < m);
    for (int j = 0; j < action*n; ++j) {
        double tmp = a[i*action*n + j];
        a[i*action*n + j] = a[k*action*n + j];
        a[k*action*n + j] = (-tmp);
    }
}

void addMatrixRows(         // row[k] += row[i]*coeff 
    double *a, int m, int n,
    int k, int i, double coeff,
    int action
) {
    assert(0 <= i && i < m);
    assert(0 <= k && k < m);
    for (int j = 0; j < action*n; ++j) {
        a[k*action*n + j] += a[i*action*n + j]*coeff;
    }
}

void multiplyMatrixRow(
    double *a, int m, int n,
    int i, double coeff
) {
    assert(0 <= i && i < m);
    for (int j = 0; j < n; ++j) {
        a[i*n + j] *= coeff;
    }
}

bool inverseMatrix(
    double *a, int n, // matrix n*n
    double* inverse,         // out: inverse matrix
    int threadIdx,
    int action
) {
    annihilateColumn(threadIdx, action);
    
    inverse = new double[n*n];
    for (int i = 0; i < n; ++i) {
        // Read i-th row of matrix
        for (int j = n; j < 2*n; ++j) {
            inverse[i*n + j] = a[i*2*n + j];
        }
    }
    
    return true;
}

bool solveLinearSystem(
    const double *a, int n, // matrix n*n
    const double* b,        // column of the system right side
    double* x               // Solution of the system a*x = b
) {

}

