#include <stdio.h>
#include <stdlib.h>

int f(FILE*fin);

int main(void) {
    FILE*fin = fopen("input.txt", "r");
    if (fin == NULL) return -1;
    printf("%d\n", f(fin));
    fclose(fin);
    return 0;
}

int f(FILE*fin) {
    int len = 0;
    int x, y;
    int sum = 0;
    int flag = 0;
    int subflag = 0;
    fscanf(fin, "%d", &x);
    while (fscanf(fin, "%d", &y) == 1) {
        ++len;
        if (x >= y) {
            if (flag == 1) subflag = 1;
            flag = 0;
        }
        else flag = 1;
        if (subflag == 1) ++sum;
        subflag = 0;
        x = y;
    }
    if (len == 0) exit(-1);
    return sum;
}