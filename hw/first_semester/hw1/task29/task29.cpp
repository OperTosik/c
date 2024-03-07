#include <stdio.h>
#include <stdlib.h>

double f(FILE*fin);

int main(void) {
    FILE*fin = fopen("input.txt", "r");
    if (fin == NULL) return -1;
    printf("%lf\n", f(fin));
    fclose(fin);
    return 0;
}

double f(FILE*fin) {
    int len;
    double c, t, pow_t = 1;
    double res;
    if (fscanf(fin, "%lf", &t) != 1) exit(-1);
    for (int i = 0; fscanf(fin, "%lf", &c) == 1; ++i) {
        len = i;
        res += c * pow_t;
        pow_t *= t;
    }
    if (len == 0) exit(-1);
    return res;
}