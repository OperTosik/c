#include <stdio.h>
#include <stdlib.h>
#include <cmath>

double f(FILE*fin);

int main(void) {
    FILE*fin = fopen("input.txt", "r");
    FILE*fout = fopen("output.txt", "w");
    if (fin == NULL) {
        perror("Cannot open an input file");
        fclose(fin);
        return -1;
    }
    
    if (fout == NULL) {
        perror("Cannot open an input file");
        return -1;
    }
    fprintf(fout, "%lf", f(fin));
    fclose(fin);
    fclose(fout);
    return 0;
}

double f(FILE*fin) {
    double product = 1;
    double len = 0;
    double x;
    while (fscanf(fin, "%lf", &x) == 1) {
        ++len;
        product *= x;
    }
    return pow(product, 1/len);
}