#include <stdio.h>
#include <stdlib.h>

double f(FILE*fin);

int main(void) {
    FILE*fin;
    fin = fopen("input.txt","r");
    if (!fin){
        return -1;
    }
    printf("%lf", f(fin));
    fclose(fin);
    return 0;
}

double f(FILE*fin) {
    double sum = 0;
    int len = 0;
    double x;
    while (fscanf(fin,"%lf\n", &x) == 1) {
        ++len;
        sum += 1/x;
    }
    if (len == 0) exit(-1);
    return len / sum;
}