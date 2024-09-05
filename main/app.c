#include <stdio.h>
#include <stdlib.h>

void f(double *array_a, double *array_b, int len_a, int len_b, double*d, int *main_flag);

int main(void) {
    FILE*fin_a = fopen("a.txt", "r");
    FILE*fin_b = fopen("b.txt", "r");
    FILE*fout = fopen("o.txt", "w");
    int main_flag;
    double *array_a;
    double *array_b;
    double x;
    double d;
    int len_a = 1;
    int len_b = 1;
    if (fin_a == NULL) {
		fclose(fin_a);
        fclose(fin_b);
        fclose(fout);
		return -1;
	}
    if (fin_b == NULL) {
		fclose(fin_a);
        fclose(fin_b);
        fclose(fout);
		return -1;
	}
    if (fscanf(fin_a, "%lf", &x) != 1) exit(-1);
    if (fscanf(fin_b, "%lf", &x) != 1) exit(-1);
    while (fscanf(fin_a, "%lf", &x) == 1) ++len_a;
    while (fscanf(fin_b, "%lf", &x) == 1) ++len_b;
    rewind(fin_a);
    rewind(fin_b);
    array_a = (double*)malloc(len_a * sizeof(double));
    array_b = (double*)malloc(len_b * sizeof(double));
    for (int i = 0; fscanf(fin_a, "%lf", &x) == 1; ++i) {
        array_a[i] = x;
    }
    for (int i = 0; fscanf(fin_b, "%lf", &x) == 1; ++i) {
        array_b[i] = x;
    }
    fclose(fin_a);
    fclose(fin_b);
    // for (int i = 0; i < len_a; ++i) fprintf(fout, "%lf ", array_a[i]);
    // for (int i = 0; i < len_a; ++i) fprintf(fout, "%lf ", array_b[i]);

    f(array_a, array_b, len_a, len_b, &d, &main_flag);
    // for (int i = 0; i < len_a; ++i) fprincattf(fout, "%lf ", array_a[i]);
    // for (int i = 0; i < len_a; ++i) fprintf(fout, "%lf ", array_b[i]);
    // printf("%lf", d);
    if (main_flag == 0) fprintf(fout, "NO\n");
    else {
        fprintf(fout, "%lf\n%d\n", d, len_a);
        for (int i = 0; i < len_a; ++i) {
            fprintf(fout, "%lf ", array_a[i]);
        }
    }
    fclose(fout);
    return 0;
}

void f(double *array_a, double *array_b, int len_a, int len_b, double*d, int *main_flag) {
    double temp;
    double df;
    int flag = 1;
    double eps = 1e-10;
    // for (int i = 0; i < len_b; ++i) printf("%lf ", array_b[i]);
    for (int i = 0; i < len_a - 1; i++) {
        for (int j = 0; j < len_a - i - 1; j++) {
            if (array_a[j + 1] + eps < array_a[j]) {
                temp = array_a[j];
                array_a[j] = array_a[j + 1];
                array_a[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < len_b - 1; i++) {
        for (int j = 0; j < len_b - i - 1; j++) {
            if (array_b[j + 1] + eps < array_b[j]) {
                temp = array_b[j];
                array_b[j] = array_b[j + 1];
                array_b[j + 1] = temp;
            }
        }
    }
    // for (int i = 0; i < len_a; ++i) printf("%lf ", array_a[i]);
    df = array_a[1] - array_a[0];
    // printf("%lf", df);
    for (int i = 0; i < len_a - 1; ++i) {
        if (array_a[i + 1] - array_a[i] != df) flag = 0;
        // printf("%lf ", array_a[i + 1] - array_a[i]);
        printf("%d", flag);
    }
    if (flag = 0) *main_flag = 0;
    else {
        flag = 1;
        for (int i = 0; i < len_b - 1; ++i) {
            if ((array_b[i + 1] - array_b[i]) != df) flag = 0;
        }
        if (flag == 1)  {
            *main_flag = 1;
            *d = df;
        }
        else *main_flag = 0;
    }
}
