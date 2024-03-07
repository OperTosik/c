#include <stdio.h>
#include <stdlib.h>

int f(FILE*fin);

int main(void) {
    FILE*fin;
    fin = fopen("input.txt","r");
    if (!fin){
        return -1;
    }
    if (f(fin) == 0) printf("yes\n");
    else printf("no\n");
    fclose(fin);
    return 0;
}

int f(FILE*fin) {
    int x, y, z;
    int a, b, c, d;
    int flag = 0;
    fscanf(fin,"%d\n", &a);
    fscanf(fin,"%d\n", &b);
    fscanf(fin,"%d\n", &c);
    fscanf(fin,"%d\n", &d);
    fscanf(fin,"%d\n", &x);
    fscanf(fin,"%d\n", &y);
    while (fscanf(fin,"%d\n", &z) == 1) {
        if ((a * x) + (b * y) + (c * z) != d) {
            flag = 1;
            break;
        }
        x = y;
        y = z;
    }
    return flag;
}