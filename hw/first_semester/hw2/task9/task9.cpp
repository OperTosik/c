#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void f(int *array, int len, int *p, int *q, int *flag);

int main(void) {
    FILE*fin = fopen("input.txt", "r");
    FILE*fout = fopen("output.txt", "w");
    int len = 1;
    int x;
    int *array;
    int p, q, flag;
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
    f(array, len, &p, &q, &flag);
    if (flag == 0) fprintf(fout, "%d", -1);
    else fprintf(fout, "%d %d", p, q);
    fclose(fout);
    free(array);
    return 0;
}

void f(int *array, int len, int *p, int *q, int *flag) {
    int temp;
    *flag = 1;
    for (int i = 1; i < len; ++i) {
        for (int j = i; j > 0 && array[j - 1] > array[j]; --j) {
            temp = array[j];
            array[j] =  array[j - 1];
            array[j - 1] = temp;
        }
    }
    for (int i = 0; i < len - 1; ++i) {
        if (array[i] + 1 != array[i + 1]) *flag = 0;
    }
    if (*flag == 1) {
        *p = array[0];
        *q = array[len - 1];
    }
}