#include <stdio.h>
#include <math.h>
#include <assert.h> //Асерт не должен срабатывать при верном вводе

double log_a(double x, double a, double eps = 1e-12);


int main(void) {
    while (true) {
        double a, x;
        printf("Enter x > 0, a != 1:\n");
        if (scanf("%lf%lf", &x, &a) < 2) break;
        if (a <= 0. || fabs(a - 1.) <= 1e-15 || x <= 0.){
            printf("Incorrect data.\n");
            continue;
        }
        double y = log_a(x, a);
        printf("log_a(x) = %.12f\n", y);
        printf("Standart log_a(x) = %.12f\n", log(x)/log(a));
    }
    return 0;
}

double log_a(double x, double a, double eps/*= 1e-12*/) {
    double s = 1.;
    if (a < 1.) {
        a = 1./a;
        s = (-1.);
    }
    assert(a > 1. && x > 0.);
    double y = 0.;
    double z = x;
    double t = 1.;
    //assert: a^y * z*t == x инвариант цикла
    while(z < 1./a || z > a || fabs(t) > eps) {
        if (z < 1./a) {
            z *= a;
            y -= t;
        }
        else if (z > a) {
            z /= a;
            y += t;
        }
        else {
            z *= z;
            t /= 2.;
        }
    }
    return y*s;
}
