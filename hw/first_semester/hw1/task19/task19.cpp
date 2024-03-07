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
    int sum_in = 0, sum_de = 0;
    int flag = 0, subflag = 0;
    int flag_de = 0, subflag_de = 0;
    fscanf(fin, "%d", &x);
    while (fscanf(fin, "%d", &y) == 1) {
        ++len;
        if (x >= y) {
            if (flag == 1) subflag = 1;
            flag = 0;
        }
        else flag = 1;
        if (subflag == 1) ++sum_in;
        subflag = 0;

        if (x <= y) {
            if (flag_de == 1) subflag_de = 1;
            flag_de = 0;
        }
        else flag_de = 1;
        if (subflag_de == 1) ++sum_de;
        subflag_de = 0;

        x = y;
    }
    if (len == 0) exit(-1);
    if (sum_in >= sum_de) return sum_in - sum_de + 1;
    else return sum_de - sum_in + 1;
    
}