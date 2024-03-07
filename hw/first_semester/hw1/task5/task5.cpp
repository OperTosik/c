#include <stdio.h>
#include <stdlib.h>

int f(FILE*fin);

int main(void) {
    FILE*fin;
    fin = fopen("input.txt","r");
    if (!fin){
        return -1;
    }
    if (f(fin) == 1) printf("yes\n");
    else printf("no\n");
    fclose(fin);
    return 0;
}

int f(FILE*fin) {
    int x, y;
    int len = 0;
    int flag = 0;
    fscanf(fin,"%d\n", &x);
    while (fscanf(fin,"%d\n", &y) == 1) {
        ++len;
        if (x == y) {
            flag = 1;
            break;
        }
    }
    if (len == 0) exit(-1);
    return flag;
}