//Интегралы
#include <stdio.h>
//#include <iostream>
#include <math.h>
#include <assert.h>
//#include <cassert>

// double integral(
//     //double *f(double) //ф-я, возвр. значение типа double
//     double (*f)(double), //Указатель на ф-ю, возвр. значение типа double
//     double a, double b,
//     int n = 100
// );

/**double *(*a[10])(double x, int j);
 *  6)    5)3)1)2)  4)
 * 1) a - это 
 * 2) массив из 10 элементов типа
 * 3) указатель на ф-я аргументрами типа double, int.
*/

typedef double(*func_ptr)(double);

double integral_trapezium(
    func_ptr f,
    double a, double b, //пределы интегрирования
    int n //= 100 //Кол-во точек
);

double integral_simpson(
    func_ptr f,
    double a, double b, //пределы интегрирования
    int n //= 100 //Кол-во точек
);

double f(double);
double antider_f(double);

int main(void) {
    //\int_a^b f(x)dx = (f(a) + 4f((a+b)/2) + f(b))(b - a)
    //Формула Симпсона
    while (true) {
        double a, b;
        int n;
        printf("a, b: ");
        //cout << "a, b: ";
        scanf("%lf%lf", &a, &b);
        //if (!cin >> a >> b) break;
        printf("n: ");
        scanf("%d", &n);
        double y = integral_trapezium(f, a, b, n);
        printf("Integral_trapezium = %lf\n", y);
        //cout << "Integral_trapezium = " << y << endl;
        y = integral_simpson(f, a, b, n);
        printf("Integral_simpson = %lf\n", y);
        //cout << "Integral_simpson = " << y << endl;
        double y_precize = antider_f(b) - antider_f(a);
        printf("Integral_trapezium = %lf\n", y_precize);
        //cout << "Must_be = " << y << endl;
        
    }
    return 0;
}

double f(double x) {
    return x*x*x - x - 1.;
}

double antider_f(double x) {
    double xx = x*x;
    return xx * xx / 4. - xx/2. - x;
}

double integral_trapezium(
    func_ptr f,
    double a, double b, //пределы интегрирования
    int n //= 100 //Кол-во точек
) {
    assert(n > 0);
    double dx = (b - a) / n;
    double s = (f(a) + f(b)) / 2.;
    double x = a + dx;
    for (int i = 1; i < n; ++i) {
        s += f(x);
        x += dx;
    }
    return s* dx;
}

double integral_simpson(
    func_ptr f,
    double a, double b, //пределы интегрирования
    int n //= 100 //Кол-во точек
) {
    assert(n > 0);
    if (n % 2 != 0) ++n;
    double dx = (b - a)/n;
    double s0 = f(a) + f(b);
    
    double s1 = 0.; //Нечетные точки
    double x = a + dx;
    for (int i = 1; i < n; i += 2) {
        s1 += f(x);
        x += 2. * dx;
    }

    double s2 = 0.; //Четные точки
    x = a + dx;
    for (int i = 2; i < n; i += 2) {
        s2 += f(x);
        x += 2. * dx;
    }
    return (s0 + 4. * s1 + 2*s2)/3. * dx;
}