#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>
// #include <cassert>

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
            double mod2 = abs2();
            double real = re/mod2;
            double image = (-im)/mod2;
            return Complex(real, image);
        }

        Complex& operator/=(const Complex& z) {
            *this *= z.inverse();
            return *this;
        }

        double abs2() const {
            return (re * re + im * im);
        }

        double abs() const {
            return sqrt(re * re + im * im);
        }

        Complex& normalize() {
            double mod = abs();
            if (fabs(mod) > EPSILON) {
                re /= mod;
                im /= mod;
            }
            return *this;
        }

        // ComplexExp algToExp() {
        //     return ComplexExp(this->abs(), atan(this->im / this->re));
        // }

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

        
    };

    inline std::ostream& operator<<(std::ostream& s, const Complex& z) {
        s << "(" <<  z.re << ")" << " + " << "i*" << "(" <<  z.im << ")";
        return s;
    }

    inline std::istream& operator>>(std::istream& s, Complex& z) {
        double r, i;
        if (s >> r >> i) {
            z = Complex(r, i);
        }
        return s;
    }

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
        {
            while (fabs(theta) >= 2.*PI + EPSILON) {
                theta = theta > 2.*PI ? theta - 2.*PI : theta + 2.*PI;
            }
            if (fabs(theta) < EPSILON) {
                theta = 0.;
            }
            if (fabs(len) < EPSILON) {
                len = 0.;
                theta = 0.;
            }
            if (len < -EPSILON) {
                len = fabs(len);
                theta += PI;
            }
        }

        double real() const {
            return len*cos(theta);
        }

        double image() const {
            return len*sin(theta);
        }

        ComplexExp& operator=(const ComplexExp& z) {
            len = z.len;
            theta = z.theta;
            return *this;
        }

        ComplexExp operator+(const ComplexExp& z) const {
            double re = this->real() + z.real();
            double im = this->image() + z.image();
            double lenght = sqrt(re*re + im*im);
            double angle = atan2(im, re);
            if (fabs(lenght) < EPSILON) {
                return ComplexExp();
            }
            if (fabs(theta) < EPSILON) {
                angle = 0.;
            }
            return ComplexExp(lenght, angle);
        }

        ComplexExp& operator+=(const ComplexExp& z) {
            double re = this->real() + z.real();
            double im = this->image() + z.image();
            len = sqrt(re*re + im*im);
            theta = atan2(im, re);
            if (fabs(len) < EPSILON) {
                len = 0.;
                theta = 0.;
            }
            if (fabs(theta) < EPSILON) {
                theta = 0.;
            }
            return *this;
        }

        ComplexExp operator-(const ComplexExp& z) const {
            double re = this->real() - z.real();
            double im = this->image() - z.image();
            double lenght = sqrt(re*re + im*im);
            double angle = atan2(im, re);
            if (fabs(lenght) < EPSILON) {
                return ComplexExp();
            }
            if (fabs(theta) < EPSILON) {
                angle = 0.;
            }
            return ComplexExp(lenght, angle);
        }

        ComplexExp operator-() const{
            double ttheta = theta + PI;
            while (fabs(ttheta) >= 2*PI + EPSILON) {
                ttheta = ttheta > 2*PI ? ttheta - 2*PI : ttheta + 2*PI;
            }
            if (fabs(ttheta) < EPSILON) {
                ttheta = 0.;
            }
            return ComplexExp(len, ttheta);
        }

        ComplexExp& operator-=(const ComplexExp& z) {
            double re = this->real() - z.real();
            double im = this->image() - z.image();
            len = sqrt(re*re + im*im);
            theta = atan2(im, re);
            if (fabs(len) < EPSILON) {
                len = 0.;
                theta = 0.;
            }
            if (fabs(theta) < EPSILON) {
                theta = 0.;
            }
            return *this;
        }

        ComplexExp operator*(const ComplexExp& z) const {
            double llen = len * z.len;
            double ttheta = theta + z.theta;
            if (fabs(llen) < EPSILON) {
                return ComplexExp();
            }
            while (fabs(ttheta) >= 2*PI + EPSILON) {
                ttheta = ttheta > 2*PI ? ttheta - 2*PI : ttheta + 2*PI;
            }
            if (fabs(ttheta) < EPSILON) {
                ttheta = 0.;
            }
            return ComplexExp(llen, ttheta);
        }

        ComplexExp operator*(const double c) const {
            if (fabs(c) < EPSILON) {
                return ComplexExp();
            }
            if (c <= -EPSILON) {
                double ttheta = theta +  PI;
                if (fabs(ttheta) < EPSILON) {
                    ttheta = 0.;
                }
                return ComplexExp((-c) * len, ttheta);
            }
            return ComplexExp(c * len, theta);
        }

        ComplexExp operator/(const ComplexExp& z) const {
            double llen = len / z.len;
            double ttheta = theta - z.theta;
            if (fabs(llen) < EPSILON) {
                return ComplexExp();
            }
            if (llen < -EPSILON) {
                llen = -llen;
                ttheta += PI;
            }
            while (fabs(ttheta) >= 2*PI + EPSILON) {
                ttheta = ttheta > 2*PI ? ttheta - 2*PI : ttheta + 2*PI;
            }
            if (fabs(ttheta) < EPSILON) {
                ttheta = 0.;
            }
            return ComplexExp(llen, ttheta);
        }

        ComplexExp operator/(const double c) const {
            if (fabs(c) < EPSILON) {
                return ComplexExp();
            }
            if (c < -EPSILON) {
                double ttheta = theta + PI;
                if (fabs(ttheta) < EPSILON) {
                    ttheta = 0.;
                }
                return ComplexExp(len / (-c), ttheta);
            }
            return ComplexExp(len / c, theta);
        }

        ComplexExp& operator*=(const ComplexExp& z) {
            len = len * z.len;
            theta = theta * z.theta;
            if (fabs(len) < EPSILON) {
                len = 0.;
                theta = 0.;
            }
            while (fabs(theta) >= 2*PI + EPSILON) {
                theta = theta > 2*PI ? theta - 2*PI : theta + 2*PI;
            }
            if (fabs(theta) < EPSILON) {
                theta = 0.;
            }
            return *this;
        }

        ComplexExp& normalize() {
            if (fabs(len) < EPSILON) {
                len = 0.;
                theta = 0.;
            }
            else {
                len = 1.;
            }
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

        // Complex expToAlg() {
        //     return Complex(this->len * cos(this->theta), this->len * sin(this->theta));
        // }

        ComplexExp conjugate() const {
            return ComplexExp(len, -theta);
        }

        ComplexExp power(const double p) {
            return ComplexExp(pow(len, p), p*theta); 
        }

        // double modPiDivide2(double theta);

        
    };

    const ComplexExp operator*(const double c, ComplexExp& z) {
        if (fabs(c) < EPSILON) {
            return ComplexExp();
        }

        if (c < -EPSILON) {
            double ttheta = z.theta + PI;
            if (fabs(ttheta) < EPSILON) {
                ttheta = 0.;
            }
            return ComplexExp((-c) * z.len, ttheta);
        }

        return ComplexExp(c * z.len, z.theta);
    }

    inline std::ostream& operator<<(std::ostream& s, const ComplexExp& z) {
        s << "(" << z.len << ")" << "e^i*" << "(" <<  z.theta << ")";
        return s;
    }

    inline std::istream& operator>>(std::istream& s, ComplexExp& z) {
        double llen, ttheta;
        if (s >> llen >> ttheta) {
            z = ComplexExp(llen, ttheta);
        }
        return s;
    }

    void algToExp(Complex& a, ComplexExp& b) {
        b.len = a.abs();
        b.theta = atan2(a.im, a.re);
    }

    // Complex expToAlg() {
    //     return Complex(this->len * cos(this->theta), this->len * sin(this->theta));
    // }

    void expToAlg(ComplexExp& a, Complex& b) {
        b.im = a.len * sin(a.theta);
        b.re = a.len * cos(a.theta);
    }

} //end of namespace

#endif