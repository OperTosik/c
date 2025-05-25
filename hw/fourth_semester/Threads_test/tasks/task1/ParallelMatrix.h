#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

const double EPS = 1e-8;
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
    bool start;         // Request for start
    bool terminate;     // Request for suicide
    bool working;       // Thread is working

    ThreadArgs():
        a(nullptr),
        rows(0),
        cols(0),
        resolveRow(0),
        resolveCol(0),
        row0(0),
        numRows(0),
        start(false),
        terminate(false),
        working(false)
    {}
};

static std::mutex startMutex;
static std::condition_variable startCondition;

static std::mutex finishMutex;
static std::condition_variable finishCondition;

static int numThreads = 0;
static int numActiveThreads = 0;
static int numFinishedThreads = 0;
static int numWorkingThreads = 0;

static std::vector<ThreadArgs> threadArgs;
static std::vector<std::thread> threads;


void releaseThreadPool();

void initializeThreadPool(
    double *a, int m, int n,
    int numThreads
);

// Wait until all working threads finish their part of work
void waitForAllThreads();

// Thread body function
void annihilateColumn(int threadsIdx, int action);

bool readMatrix(FILE* f, double **a, int* m, int* n, int action); 

bool writeMatrix(FILE* f, const double *a, int m, int n);

void swapMatrixRows(
    double *a, int m, int n,
    int i, int k, int action
);
void addMatrixRows(         // row[k] += row[i]*coeff 
    double *a, int m, int n,
    int k, int i, double coeff,
    int action
);
void multiplyMatrixRow(
    double *a, int m, int n,
    int i, double coeff
);

int parallelGaussMethod(    // Return a matrix rank
    double *a, int m, int n,
    int numThreads = 4,
    int action
); 
double det(double *a, int m, int n);

bool solveLinearSystem(
    double *a, int n, // matrix n*n
    const double* b,        // column of the system right side
    double* x               // Solution of the system a*x = b
);

bool inverseMatrix(
    const double *a, int n, // matrix n*n
    double* inverse,         // out: inverse matrix
    int threadsIdx,
    int action
);