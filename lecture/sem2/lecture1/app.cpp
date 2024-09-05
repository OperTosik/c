// 1. Вычисление стандартных функций рядами
// 2. Алгоритм работы с матрицами (Гаусс)
//    Нормально писать представление матрицы
//    Не двумерным, а одномерным массивом

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double my_sqrt(double a, double eps = 1e-12);
double my_atan(double x, double eps = 1e-12);
double my_atan0(double x, double eps = 1e-12); //Для суммы ряда

int main(void) {
    while (true) {
        double x;
        printf("x: ");
        if (scanf("%lg", &x) < 1) break;
        double y = my_atan(x);
        printf("My atan(x) = %.12f\n", y);
        printf("%lf\n", atan(x));
    }
    return 0;
}

double my_sqrt(double a, double eps/*= 1e-8*/) {
    double x = 1. + a/2.;
    double x_previos = 1e+30;
    while (fabs(x_previos - x) > eps) {
        x_previos = x;
        x = (x + a/x) / 2.;
    }
    return x;
}

double my_atan(double x, double eps/* = 1e-8*/) {
    if (fabs(x) <= eps) return x;
    double y = (my_sqrt(1 + x * x) - 1.) / x;
    return 2. * my_atan0(y, eps);
}

double my_atan0(double x, double eps/* = 1e-8*/) {
    // y = x - x^3/3 + x^5/5 - x^7/7 +...
    double sgn = 1.;
    if (x < 0.) {
        x = (-x);
        sgn = (-1.);
    }
    if (1 - x <= 1e-8) return sgn * M_PI / 4.;
    double xxx = x; //Степень x
    double n = 1.;
    double a = xxx;
    double s = a;
    while (fabs(a) > eps) {
        xxx *= (-x * x);
        n += 2;
        a = xxx / n;
        s += a;
    }
    return sgn * s;
}