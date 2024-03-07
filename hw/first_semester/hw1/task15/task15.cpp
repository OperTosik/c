#include <stdio.h>
#include <stdlib.h>

double f(FILE*fin);

int main(void) {
    FILE*fin;
    fin = fopen("input.txt","r");
    printf("%lf\n", f(fin));
    return 0;
}

double f(FILE*fin) {
    double x;
    double sum_1 = 0, sum_2 = 0;
    int len = 0;
    while (fscanf(fin,"%lf\n", &x) == 1) {
        ++len;
        sum_1 += (x * x);
        sum_2 += x;
    }
    sum_2 = (sum_2 * sum_2) / len;
    if (len == 0) exit(-1);
    return (sum_1 - sum_2) / (len - 1);
}
