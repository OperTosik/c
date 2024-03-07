#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int f(const int *array, int len);

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
    fprintf(fout, "%d\n", f(array, len));
    fclose(fout);
    free(array);
    return 0;
}

int f(const int *array, int len) {
    int max_1 = 0, max_2 = 0;
    int value;
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            if (array[i] == array[j]) ++max_2;
        }
        if (max_2 > max_1) value = array[i];
        max_1 = max_2;
    }
    return value;
}