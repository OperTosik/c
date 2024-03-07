#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void f(int *array, int n);

int main(void) {
    FILE*fin = fopen("input.txt", "r");
    FILE*fout = fopen("output.txt", "w");
    int n;
    int *array;
    if (fin == NULL) {
        perror("Cannot open an input file");
        fclose(fin);
        return -1;
    }
    if (fscanf(fin, "%d", &n) != 1) {
        fprintf(stderr, "Incorrect file format\n");
        fclose(fin);
        return -1;
    }
    fclose(fin);
    array = (int*)malloc((n + 1) * sizeof(int));
    f(array, n);
    for (int i = 0; i < n + 1; i++) {
        fprintf(fout, "%d ", array[i]);
    }
    fclose(fout);
    free(array);
    return 0;
}

void f(int *array, int n) {
    for (int i = 0; i < n + 1; ++i) array[i] = 0;
    array[0] = 1;
    for (int i = 1; i < n + 1; ++i) {
        for (int j = i; j > 0; --j) {
            array[j] += array[j - 1];
        }
    }
}