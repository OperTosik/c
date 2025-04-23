#include "ParallelMatrix.h"

int main() {
    int m, n;
    double *a = 0;
    
    int action;
    printf("Choose action:\n1. Solve lianear system\t2. Calculate inverse matrix");
    scanf("$d", &action);
    if (action != 1 || action != 2) {
        printf("%d is incorrect number of action", action);
        return 1;
    }

    FILE* f = fopen("input.txt", "rt");
    if (f == NULL) {
        perror("Cannot open an input file");
        return (-1);
    }
    
    if (!readMatrix(f, &a, &m, &n, action)) {
        printf("Incorrect format of matrix.\n");
        delete[] a;
        fclose(f);
        return (-1);
    }
    fclose(f);

    if (action == 1) {
        printf("Matrix of size %d*%d:\n", m, n);
        writeMatrix(stdout, a, m, n);
    }

    if (action == 2) {
        printf("Matrix of size (%d+1)*%d:\n", m-1, n);
        writeMatrix(stdout, a, m, n);
    }
    
    printf("Enter number of threads: ");
    if (scanf("%d", &numThreads) < 1) 
        exit(-1);
    
    /*
    struct timeval timeOfDay;
    gettimeofday(&timeOfDay, NULL);
    double startTimeInSeconds =
        double(timeOfDay.tv_sec) + double(timeOfDay.tv_usec)/1000000.;
    */
    auto begin = std::chrono::high_resolution_clock::now();

    int rank = parallelGaussMethod(a, m, n, numThreads, action);
    if (action == 2) {
        double* inverse;
        inverseMatrix(a, n, inverse, threadIdx, action);
    }
    /*
    gettimeofday(&timeOfDay, NULL);
    double finishTimeInSeconds =
        double(timeOfDay.tv_sec) + double(timeOfDay.tv_usec)/1000000.;
    double timeIntervalInSeconds = 
        finishTimeInSeconds - startTimeInSeconds;
    */
    auto end = std::chrono::high_resolution_clock::now();
    // auto elapsed = 
    //     std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    // double timeIntervalInSeconds = double(elapsed.count())/1e9;
    auto elapsed =
        std::chrono::duration<double, std::milli>(end - begin);
    
    printf("Row echelon form of matrix:\n");
    writeMatrix(stdout, a, m, n);

    printf("Rank of matrix: %d\n", rank);
    if (m == n) {
        printf("Determinant of matrix: %f\n", det(a, m, n));
    }

    // printf("Computation time: %.3lf ms\n", timeIntervalInSeconds*1000.);
    printf(
        "Computation time: %.3lf ms\n", 
        elapsed.count()
    );

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

 
