#include <iostream>
#include <vector>
// #include <cmath>
// #include <cassert>
#include "minCircle.h"

using namespace std;

int main(void) {
    int n;
    cout << "Enter a number of  points: ";
    if (!(cin >> n) || n <= 0)
        return (-1);
    
    vector<R2Point> points(n);

    cout << "Enter: " << n << " points: " << endl;
    for (int i = 0; i < n; ++i) {
        if (!(cin >> points[i]))
            return (-1);
    }

    R2Point center;
    double radius;
    computeMinCircle(points, center, radius);
    cout << "Minimal circle: center = " << center
         << ", radius = " << radius << endl;

    return 0;
}