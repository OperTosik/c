#include <stdio.h>
#include <stdlib.h>

int f(FILE*fin);

int main(void) {
    FILE*fin = fopen("input.txt", "r");
    FILE*fout = fopen("output.txt", "w");
    if (fin == NULL) return -1;
    fprintf(fout, "%d\n", f(fin));
    fclose(fin);
    fclose(fout);
    return 0;
}

int f(FILE*fin) {
    int len = 0;
    int x, y;
    int sum = 0;
    int flag = 0;
    fscanf(fin, "%d", &x);
    while (fscanf(fin, "%d", &y) == 1) {
        ++len;
        if (x < y) {
            if (flag == 0) ++sum;
            flag = 1;
        }
        else {
            flag = 0;
        }
        x = y;
    }
    if (len == 0) exit(-1);
    return sum;
}