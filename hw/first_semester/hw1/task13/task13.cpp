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
    int x;
    int len = 0;
    int min, index = 0;
    fscanf(fin,"%d", &x);
    min = x;
    for(int i = 1; fscanf(fin,"%d", &x) == 1; ++i) {
        ++len;
	    if (x <= min) {  
            min = x;
            index = i;
        }
    }
    if (len == 0) exit(-1);
    return index;
}
