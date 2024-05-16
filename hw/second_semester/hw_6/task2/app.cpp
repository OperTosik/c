#include <iostream>
#include <math.h>
#include <string.h>
#include "R2Graph.h"

using namespace std;

R2Point nagelPoint (
    const R2Point& a,
    const R2Point& b,
    const R2Point& c
);

int main(void) {
    while (true) {
        R2Point a, b, c;
        cout << "Enter vertices of triangle:" << endl;
        if (!(cin >> a >> b >> c)) break;
        R2Point nPoint = nagelPoint(a,b,c);
        cout << "Nagel point: " << nPoint << endl;
    }
    return 0;
}

R2Point nagelPoint (
    const R2Point& a,
    const R2Point& b,
    const R2Point& c
) {
    R2Vector ba = a - b;
    ba.normalize();
    R2Vector ac = c - a;
    ac.normalize();
    R2Vector outBisectA = ba + ac;

    R2Vector ab = b - a;
    ab.normalize();
    R2Vector bc = c - b;
    bc.normalize();
    R2Vector outBisectB = ab + bc;

    R2Vector ca = a - c;
    ca.normalize();
    R2Vector outBisectC = ca + bc;

    R2Point CenterA;
    intersectStraightLines(
        b, outBisectB,
        c, outBisectC,
        CenterA
    );

    R2Point CenterB;
    intersectStraightLines(
        a, outBisectA,
        c, outBisectC,
        CenterB
    );

    // R2Point CenterC;
    // intersectStraightLines(
    //     a, outBisectA,
    //     b, outBisectB,
    //     CenterC
    // );

    R2Point cevA;
    intersectStraightLines(
        CenterA, bc.normal(),
        b, c - b,
        cevA
    );

    R2Point cevB;
    intersectStraightLines(
        CenterB, ac.normal(),
        a, c - a,
        cevB
    );

    R2Point nPoint;
    intersectStraightLines(
        a, cevA,
        b, cevB,
        nPoint
    );
    return nPoint;
}