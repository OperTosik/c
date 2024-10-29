#include <stdio.h>
#include <stdlib.h>
// #include <malloc.h>

void f(const int *array, int len, int *k, int*s);

int main(void) {
    FILE*fin = fopen("input.txt", "r");
    FILE*fout = fopen("output.txt", "w");
    int len = 1;
    int x;
    int *array;
    int k = -1;
    int s;
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
    f(array, len, &k, &s);
    if (k != -1) fprintf(fout, "%d %d\n", k, s);
    else fprintf(fout, "-1\n");
    fclose(fout);
    //free(array);
    return 0;
}

void f(const int *array, int len, int *k, int *s) {
    int sum_prefix = 0;
    int sum_suffix = 0;
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            if (j < i) sum_prefix += array[j];
            else sum_suffix += array[j];
        }
        if (sum_prefix == sum_suffix) {
            *k = i;
            *s = sum_prefix;
            break;
        }
        else {
            sum_prefix = 0;
            sum_suffix = 0;
        }
    }
}
