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
    int flag = 0;
    if (fscanf(fin, "%d", &x) != 1) exit(-1);
    while (fscanf(fin, "%d", &y) == 1) {
        ++len;
        for (int i = 1; i < x + 1; ++i) {
            for (int j = 1; j < y + 1; ++j) {
                if (x * i == y * j) {
                    flag = 1;
                    x = x * i;
                    break;
                }
            }
            if (flag == 1) break;
        }
        flag = 0;
    }
    if (len == 0) exit(-1);
    return x;
}