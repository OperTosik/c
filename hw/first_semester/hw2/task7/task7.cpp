#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void f(int *array, int len);

int main(void) {
    FILE*fin = fopen("input.txt", "r");
    FILE*fout = fopen("output.txt", "w");
    int len = 1;
    int x;
    int *array;
    if (fin == NULL) {
        perror("Cannot open an input file");
        fclose(fin);
        return -1;
    }
    if (fscanf(fin, "%d", &x) != 1) {
        fprintf(stderr, "Incorrect file format\n");
        fclose(fin);
        return -1;
    }
    while (fscanf(fin, "%d", &x) == 1) ++len;
    rewind(fin);
    array = (int*)malloc(len * sizeof(int));
    for (int i = 0; i < len; ++i) 
        fscanf(fin, "%d", array + i);
    fclose(fin);
    if (fout == NULL) {
        perror("Cannot open an input file");
        free(array);
        return -1;
    }
    f(array, len);
    for (int i = 0; i < len; ++i) {
        fprintf(fout, "%d ", array[i]);
    }
    fclose(fout);
    free(array);
    return 0;
}

void f(int *array, int len) {
    int possitive_iterator = 0;
    for (int i = 0; i < len; ++i) {
        if (array[i] >= 0) {
            array[possitive_iterator] = array[i];
            if (i != possitive_iterator) array[i] = -1;
            ++possitive_iterator;
        }
    }
    for (int i = 0; i < len; ++i) {
        if (array[i] < 0) array[i] = 0;
    }
}