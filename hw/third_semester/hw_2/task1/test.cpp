#include "complex.h"
#include <cstdlib>

using namespace std;
using namespace ComplexNumber;

int main() {
    ComplexExp a(1, 0);
    ComplexExp b(0, 0);
    ComplexExp c(-1, 0);
    ComplexExp d(-1, 0);

    cout << "d/a: " << d/a << endl;
    cout << "void: " << - ((b*b*b) / (27.*a*a*a)) + ((b*b*b) / (9.*a*a*a)) - ((b*c) / (3.*a)) << endl;

    d = (d/a) - ((b*b*b) / (27.*a*a*a)) + ((b*b*b) / (9.*a*a*a)) - ((b*c) / (3.*a));

    c = (c/a) + ((b*b) / (3.*a*a)) - ((2.*b*b) / (3.*a*a));

    cout << "c: " << c << endl;
    cout << "d: " << d << endl;
    
    return 0;
}