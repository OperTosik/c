#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>

const double EXP = 2.71828182845904;
const double PI = 3.14159265358979;
const double EPSILON = 1.0e-14;

namespace ComplexNumber{
    
    class Complex;
    class ComplexExp;

    class Complex{
    public:
        double re;
        double im;

        Complex():
            re(0.),
            im(0.)
        {}

        Complex(const Complex& z):
            re(z.re),
            im(z.im)
        {}
        Complex(double real, double image):
            re(real),
            im(image)
        {}

        Complex& operator=(const Complex& z) {
            re = z.re;
            im = z.im;
            return *this;
        }

        Complex operator+(const Complex& z) const {
            return Complex(re + z.re, im + z.im);
        }

        Complex& operator+=(const Complex& z) {
            re += z.re;
            im += z.im;
            return *this;
        }

        Complex operator-(const Complex& z) const {
            return Complex(re - z.re, im - z.im);
        }

        Complex operator-() const {
            return Complex(-re, -im);
        }

        Complex& operator-=(const Complex& z) {
            re = z.re;
            im = z.im;
            return *this;
        }

        Complex operator*(const Complex& z) const {
            return Complex(re * z.re - im * z.im, re * z.im + im * z.re);
        }

        Complex operator*(double c) const {
            return Complex(c * re, c * im);
        }

        Complex& operator*=(const Complex& z) {
            re = re * z.re - im * z.im;
            im = re * z.im + im * z.re;
            return *this;
        }

        Complex inverse() const {
            double mod2 = module2();
            double real = re/mod2;
            double image = (-im)/mod2;
            return Complex(real, image);
        }

        Complex& operator/=(const Complex& z) {
            *this *= z.inverse();
            return *this;
        }

        double module2() const {
            return (re * re + im * im);
        }

        double module() const {
            return sqrt(re * re + im * im);
        }

        Complex& normalize() {
            double mod = module();
            if (fabs(mod) > EPSILON) {
                re /= mod;
                im /= mod;
            }
            return *this;
        }

        Complex expToAlg(ComplexExp& z) {
            return Complex(z.len*sin(z.theta), z.len*cos(z.theta));
        }

        bool operator==(const Complex& z) const {
            return (
                fabs(re - z.re) <= EPSILON &&
                fabs(im - z.im) <= EPSILON
            );
        }

        bool operator!=(const Complex& z) const {
            return !(*this == z);
        }

        Complex conjugate() const {
            return Complex(re, -im);
        }

        void print() {
            std::cout << "Algebraic form: " << re << " + i"  << im << std::endl;
            ComplexExp z;
            z.algToExp(Complex(re, im));
            std::cout << "Exponent form: " << z.len << "e^i(" << z.theta << ")"  << im << std::endl;
        }
    };

    inline Complex operator/(
        const Complex& u, const Complex& v
    ) {
        Complex res = u;
        res /= v;
        return res;
    }

    class ComplexExp{
    public:
        double len;
        double theta;
        
        ComplexExp():
            len(0.),
            theta(0.)
        {}

        ComplexExp(const ComplexExp& z):
            len(z.len),
            theta(z.theta)
        {}

        ComplexExp(double llen, double ttheta):
            len(llen),
            theta(ttheta)
        {}

        ComplexExp& operator=(const ComplexExp& z) {
            len = z.len;
            theta = z.theta;
            return *this;
        }

        // ComplexExp operator+(const ComplexExp& z) const {
        //     return ComplexExp(re + z.re, im + z.im);
        // }

        // ComplexExp& operator+=(const ComplexExp& z) {
        //     re += z.re;
        //     im += z.im;
        //     return *this;
        // }

        // ComplexExp operator-(const ComplexExp& z) const {
        //     return ComplexExp(re - z.re, im - z.im);
        // }

        // ComplexExp operator-() const {
        //     return ComplexExp(-re, -im);
        // }

        // ComplexExp& operator-=(const ComplexExp& z) {
        //     re = z.re;
        //     im = z.im;
        //     return *this;
        // }

        ComplexExp operator*(const ComplexExp& z) const {
            return ComplexExp(len * z.len, theta + z.theta);
        }

        ComplexExp operator*(double c) const {
            return ComplexExp(c * len, theta);
        }

        ComplexExp& operator*=(const ComplexExp& z) {
            len = len * z.len;
            theta = theta * z.theta;
            return *this;
        }

        ComplexExp& normalize() {
            len = 1.;
            return *this;
        }

        bool operator==(const ComplexExp& z) const {
            return (
                fabs(len - z.len) <= EPSILON &&
                fabs(theta - z.theta) <= EPSILON
            );
        }

        bool operator!=(const ComplexExp& z) const {
            return !(*this == z);
        }

        ComplexExp conjugate() const {
            return ComplexExp(len, -theta);
        }

        ComplexExp algToExp(const Complex& z) {
            return ComplexExp(z.module(), atan(z.im / z.re));
        }

        ComplexExp power(const double p) {
            return ComplexExp(pow(len, p), p*theta); 
        }

        double modPiDivide2(double theta);

        // void print(
        //     const ComplexExp& z
        // );
    };
} //end of namespace

#endif