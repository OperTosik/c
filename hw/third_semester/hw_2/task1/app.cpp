#include "complex.h"

bool interface(
    ComplexNumber::Complex& a,
    ComplexNumber::Complex& b,
    ComplexNumber::Complex& c,
    ComplexNumber::Complex& d
);
void cardanoMethod(double a, double b, double c, double d);
void moveCoeff(double& a, double& b, double& c, double& d);
void xNotEqualNull(double& a, double& b);

int main() {
    while (true) {
        double real, image;
        ComplexNumber::Complex a, b, c, d;
        
        
        if (!std::cin) break;
        cardanoMethod(a, b, c, d);
        
    }
}

bool interface(
    ComplexNumber::Complex& a,
    ComplexNumber::Complex& b,
    ComplexNumber::Complex& c,
    ComplexNumber::Complex& d
) {
    int active;
    double x, y;
    std::cout << "Choose form for complex number:" << std::endl;
    std::cout << "1 - algebraic form\t 2 - exponencial form" << std::endl;
    std::cin >> active;
    if (active == 1) {
        std::cout << "Enter complex coefficients of cubic equation: " << std::endl;
        std::cout << "a: "; 
        std::cin >> x >> y;
        a = ComplexNumber::Complex(x, y);
        std::cout << "b: "; 
        std::cin >> x >> y;
        b = ComplexNumber::Complex(x, y);
        std::cout << "c: "; 
        std::cin >> x >> y;
        c = ComplexNumber::Complex(x, y);
        std::cout << "d: "; 
        std::cin >> x >> y;
        d = ComplexNumber::Complex(x, y);
    }
    else if (active == 2) {
        std::cout << "Enter complex coefficients of cubic equation: " << std::endl;
        std::cout << "a: "; 
        std::cin >> x >> y;
        a = ComplexNumber::ComplexExp(x, y);
        std::cout << "b: "; 
        std::cin >> x >> y;
        b = ComplexNumber::Complex(x, y);
        std::cout << "c: "; 
        std::cin >> x >> y;
        c = ComplexNumber::Complex(x, y);
        std::cout << "d: "; 
        std::cin >> x >> y;
        d = ComplexNumber::Complex(x, y);
    }
    else {
        std::cout << "Exit" << std::endl;
        return false;
    }
}

void cardanoMethod(double a, double b, double c, double d){}

void moveCoeff(double& a, double& b, double& c, double& d){
    double s = -b / (3.*a);
    d = (a*s*s*s + b*s*s + c*s + d) / a;
    c = (3.*a*s*s + 2.*b*s + c) / a;
    b = d;
    a = c;
    
}

void xNotEqualNull(double& a, double& b) {
    bool sign = true;
    double discriminant = 81.*b*b + 12.*a*a*a; // discr^2

    if (discriminant - EPSILON < 0) {
        sign = false;
    }

    discriminant = sqrt(fabs(discriminant)); // possitive number under root (unsigned)

    if (discriminant < EPSILON) {
        discriminant = 0.;
    }

    ComplexNumber::ComplexExp uExp;
    
    if (sign) {
        uExp.algToExp(ComplexNumber::Complex((-9.*b + discriminant) / 18., 0.));
    }
    else {
        uExp.algToExp(ComplexNumber::Complex((-9.*b) / 18., discriminant / 18.));
    }

    uExp.power(1/3);
    ComplexNumber::Complex uAlg;
    uAlg.expToAlg(uExp);
    ComplexNumber::Complex v = ComplexNumber::Complex(-a, 0.) / (uAlg*3.); // mb error
    v += uAlg; // first value x
    
    
}