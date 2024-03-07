#include <stdio.h>
#include <stdlib.h>

int f(FILE*fin);

int main(void) {
    FILE*fin;
    fin = fopen("input.txt","r");
    printf("%d\n", f(fin));
    fclose(fin);
    return 0;
}

int f(FILE*fin) {
    int x, y, c, t;
    int len = 0;
    int sum = 0;
    fscanf(fin,"%d\n", &x);
    c = x;
    while (fscanf(fin,"%d\n", &y) == 1) {
        ++len;
        if (x == y) {
            ++sum;
            t = x;
        }
        if (c != t) {
            c = t;
            ++sum;
        }
        x = y;
    }
    if (len == 0) exit(-1);
    return sum;
}