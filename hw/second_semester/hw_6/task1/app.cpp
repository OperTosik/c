#include <iostream>
#include <math.h>
#include <string.h>
#include "R2Graph.h"

using namespace std;

R2Point gergonePoint (
    const R2Point& a,
    const R2Point& b,
    const R2Point& c
);

int main(void) {
    while (true) {
        R2Point a, b, c;
        cout << "Enter vertices of triangle:" << endl;
        if (!(cin >> a >> b >> c)) break;
        R2Point gPoint = gergonePoint(a,b,c);
        cout << "Circle center: " << gPoint << endl;
    }
    return 0;
}

R2Point gergonePoint (
    const R2Point& a,
    const R2Point& b,
    const R2Point& c
) {
    R2Vector ab = b - a;
    ab.normalize();
    R2Vector ac = c - a;
    ac.normalize();
    R2Vector bisectA = ab + ac;

    R2Vector ba = a - b;
    ba.normalize();
    R2Vector bc = c - b;
    bc.normalize();
    R2Vector bisectB = ba + bc;

    R2Point inCenter;
    intersectStraightLines(
        a, bisectA,
        b, bisectB,
        inCenter
    );

    R2Point cevA, cevB;
    intersectStraightLines(
        inCenter, (b - c).normal(),
        b, c - b,
        cevA
    );
    intersectStraightLines(
        inCenter, (a-c).normal(),
        a, c - a,
        cevB
    );

    R2Point gPoint;
    intersectStraightLines(
        a, cevA - a,
        b, cevB - b,
        gPoint
    );
    return gPoint;
}