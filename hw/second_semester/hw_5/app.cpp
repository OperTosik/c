#include <iostream>
#include <math.h>
#include <string.h>
#include "R2Graph.h"

using namespace std;

void inscribedCircle (
    const R2Point& a,
    const R2Point& b,
    const R2Point& c,
    R2Point& center,
    double& radius
);

int main(void) {
    while (true) {
        R2Point a, b, c;
        cout << "Enter vertices of triangle:" << endl;
        if (!(cin >> a >> b >> c)) break;
        R2Point center;
        double radius;
        inscribedCircle(a, b, c, center, radius);
        cout << "Circle center: " << center
            << ". radius = " << radius << endl;
    }
    return 0;
}

void inscribedCircle (
    const R2Point& a,
    const R2Point& b,
    const R2Point& c,
    R2Point& center,
    double& radius
) {
    R2Vector ab = b - a;
    ab.normalize();
    R2Vector ac = c - a;
    ac.normalize();
    R2Vector bisA = ab + ac;

    R2Vector ba = b - a;
    ba.normalize();
    R2Vector bc = b - c;
    bc.normalize();
    R2Vector bisB = ba + bc;

    //Пересечение прямых линий.
    intersectStraightLines (
        a, bisA,
        b, bisB,
        center
    );

    radius = center.distanceToLine(a, ab);
}

//Скачать qt6