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
    int sum_1 = 0, sum_2 = 0;
    fscanf(fin, "%d", &x);
    sum_1 += x;
    while (fscanf(fin, "%d", &y) == 1) {
        ++len;
        if (x != y) {
            if (sum_1 > sum_2) sum_2 = sum_1;
            sum_1 = 0;
        }
        sum_1 += y;
        x = y;
    }
    if (sum_1 > sum_2) sum_2 = sum_1;
    
    if (len == 0) exit(-1);
    return sum_2;

}