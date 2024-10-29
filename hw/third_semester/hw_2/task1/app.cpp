#include "complex.h"

bool interface(
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&
);
void cardanoMethod(
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&
);
void moveCoeff(
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&
);
void bNotEqualNull(
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&
);

void hornerMethod(
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&
);

void equation2(
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&,
    ComplexNumber::ComplexExp&
);

bool test(
    const ComplexNumber::ComplexExp&,
    const ComplexNumber::ComplexExp&,
    const ComplexNumber::ComplexExp&,
    const ComplexNumber::ComplexExp&,
    const ComplexNumber::ComplexExp&
);

int main() {
    while (true) {
        ComplexNumber::ComplexExp a, b, c, d;
        ComplexNumber::ComplexExp x1, x2, x3;

        if (interface(a, b, c, d)) {
            std::cout << "exit" << std::endl;
            return 0;
        }

        //test
            ComplexNumber::ComplexExp k = a;
            ComplexNumber::ComplexExp l = b;
            ComplexNumber::ComplexExp m = c;
            ComplexNumber::ComplexExp n = d;
        //
        
        cardanoMethod(a, b, c, d, x1, x2, x3);
        
        std::cout << "Solution: " << std::endl;
        std::cout << "x1 = " << x1 << std::endl;
        std::cout << "x2 = " << x2 << std::endl;
        std::cout << "x3 = " << x3 << std::endl;
        
        //test
            std::cout << std::endl;
            std::cout << "Check answer of correction" << std::endl;
            if (test(k, l, m, n, x1)) {
                std::cout << "x1 is TRUE root of equation" << std::endl;
            }
            else {
                std::cout << "x1 is FALSE root of equation" << std::endl;
            }
            if (test(k, l, m, n, x2)) {
                std::cout << "x2 is TRUE root of equation" << std::endl;
            }
            else {
                std::cout << "x1 is FALSE root of equation" << std::endl;
            }
            if (test(k, l, m, n, x3)) {
                std::cout << "x3 is TRUE root of equation" << std::endl;
            }
            else {
                std::cout << "x1 is FALSE root of equation" << std::endl;
            }
        //
        std::cout << std::endl;
    }
}

bool interface(
    ComplexNumber::ComplexExp& a,
    ComplexNumber::ComplexExp& b,
    ComplexNumber::ComplexExp& c,
    ComplexNumber::ComplexExp& d
) {    
    std::cout << "Enter complex coefficients of cubic equation in format: len angle" << std::endl;
    std::cout << "a: ";
    std::cin >> a;
    std::cout << "b: "; 
    std::cin >> b;
    std::cout << "c: "; 
    std::cin >> c;
    std::cout << "d: "; 
    std::cin >> d;
    std::cout << std::endl;
    if (!std::cin) return true;
    return false;
}

void cardanoMethod(
    ComplexNumber::ComplexExp& a,
    ComplexNumber::ComplexExp& b,
    ComplexNumber::ComplexExp& c,
    ComplexNumber::ComplexExp& d,
    ComplexNumber::ComplexExp& x1,
    ComplexNumber::ComplexExp& x2,
    ComplexNumber::ComplexExp& x3
) {
    ComplexNumber::ComplexExp s = (-b) / (3.*a);
    moveCoeff(a, b, c, d); // x^3 + ax + b = 0
    
    if (fabs(b.real()) < EPSILON && fabs(b.image()) < EPSILON) {
        x1 = ComplexNumber::ComplexExp();
        x2 = (-a).power(0.5);
        x3 = -x2;

        x1 += s;
        x2 += s;
        x3 += s;

        return;
    } 

    bNotEqualNull(a, b, x1);
    
    c = ComplexNumber::ComplexExp(1., 0.);
    d = ComplexNumber::ComplexExp();
    hornerMethod(c, d, a, b, x1); //x^3 + ax + b = 0

    equation2(c, d, a, x2, x3);
    x1 += s;
    x2 += s;
    x3 += s;

}

void moveCoeff(
    ComplexNumber::ComplexExp& a,
    ComplexNumber::ComplexExp& b,
    ComplexNumber::ComplexExp& c,
    ComplexNumber::ComplexExp& d
) {
    // ComplexNumber::ComplexExp s = (-1.*b) / (3.*a);
    d = (d/a) - ((b*b*b) / (27.*a*a*a)) + ((b*b*b) / (9.*a*a*a)) - ((b*c) / (3.*a));
    c = (c/a) + ((b*b) / (3.*a*a)) - ((2.*b*b) / (3.*a*a));
    b = d;
    a = c;
    
}

void bNotEqualNull(
    ComplexNumber::ComplexExp& a,
    ComplexNumber::ComplexExp& b,
    ComplexNumber::ComplexExp& x
) {
    ComplexNumber::ComplexExp discriminant = (81.*b*b) + (12.*a*a*a); // discr^2
    discriminant.power(0.5);

    if (fabs(discriminant.real()) < EPSILON && fabs(discriminant.image()) < EPSILON) {
        discriminant = ComplexNumber::ComplexExp();
    }

    ComplexNumber::ComplexExp u = ((-9.*b + discriminant) / 18.).power(1/3);
    ComplexNumber::ComplexExp v = (-a) / (3*u);
    x = u + v;
}

void hornerMethod(
    ComplexNumber::ComplexExp& a,
    ComplexNumber::ComplexExp& b,
    ComplexNumber::ComplexExp& c,
    ComplexNumber::ComplexExp& d,
    ComplexNumber::ComplexExp& x
) {
    b += x * a;
    c += x * b;
    d += x * c;

    // if (fabs(d.real()) >= EPSILON || fabs(d.image()) >= EPSILON) {
    //     std::cout << x << " is not solution" << std::endl;
    // }
}

void equation2(
    ComplexNumber::ComplexExp& a,
    ComplexNumber::ComplexExp& b,
    ComplexNumber::ComplexExp& c,
    ComplexNumber::ComplexExp& x,
    ComplexNumber::ComplexExp& y
) {
    ComplexNumber::ComplexExp discriminant = (b*b - 4.*a*c).power(1/2);
    x = (-b + discriminant) / (2.*a);
    y = (-b - discriminant) / (2.*a);
}

bool test(
    const ComplexNumber::ComplexExp& a,
    const ComplexNumber::ComplexExp& b,
    const ComplexNumber::ComplexExp& c,
    const ComplexNumber::ComplexExp& d,
    const ComplexNumber::ComplexExp& x
) {
    ComplexNumber::ComplexExp res = a*x*x*x + b*x*x + c*x + d;
    if (fabs(res.real()) < EPSILON && fabs(res.image()) < EPSILON) {
        return true;
    }
    return false;
}