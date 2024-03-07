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
    int max_dist_1, max_dist_2 = 0;
    int min = -1;
    int x, y, z;
    if (fscanf(fin, "%d", &x) != 1) exit(-1);
    y = x;
    for (int i = 1; fscanf(fin, "%d", &z) == 1; ++i) {
        len = i;
        if (x >= y && y <= z) {
            if (min == -1) min = i - 1;
            else {
                max_dist_1 = (i - 1) - min;
                min = i - 1;
            }
        }
        else {
            if (max_dist_1 > max_dist_2) max_dist_2 = max_dist_1;
            max_dist_1 = 0;
        }
        if (y >= z) max_dist_1 = len - min;
        if (max_dist_1 > max_dist_2) max_dist_2 = max_dist_1;

        x = y;
        y = z;
    }

    return max_dist_2;
}