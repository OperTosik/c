#include <stdio.h>
#include <math.h>
#include <assert.h>

double power(double x, double a, double eps = 1e-15);
double fastPower(double x, int n);
double exponent(double x, double eps = 1e-15);

constexpr double E = 2.7182818284590452354;

int main(void) {
    while (true) {
        double a, x;
        printf("Enter x >= 0, a != 1:\n");
        if (scanf("%lf%lf", &x, &a) < 2) break;
        if (x < 0.){
            printf("Incorrect data.\n");
            continue;
        }
        double y;
        if (fabs(x) <= 0.) {
            y = 0.;
        }
        else {
            y = power(x, a);
        }
        printf("power(x, a) = %.12g\n", y);
        printf("Standart power(x, a) = %.12g\n", pow(x, a));
    }
    return 0;

}

double power(double x, double a, double eps/* = 1e-15*/) {
    return exponent(a*log(x), eps);
}

double exponent(double x, double eps/* = 1e-15*/) {
    int k = int(x);
    x -= double(k);
    assert(fabs(x) < 1.);
    // exp(x) = 1 + x + x^2/2! + x^3/3! + ...
    double s = 1.;
    double a = x;
    double n = 1.;
    while(fabs(a) > eps) {
        s += a;
        n += 1.;
        a *= x/n;
    }
    return s * fastPower(M_E, k); //Или просто Е
}

double fastPower(double x, int n) {
    if (n < 0) {
        n = (-n);
        x = 1./x;
    }
    assert(n >= 0);
    //Инвариант b^k * p = x^n
    double b = x;
    int k = n;
    double p = 1.;
    while (k > 0) {
        if ((k&1) == 0) { //эквивал k%2 == 0 
            k /= 2;
            b *= b;
        }
        else {
            k -= 1;
            p *= b;
        }
    }
    return p;
}