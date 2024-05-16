#include <iostream>
#include <vector>
#include "convexHull.cpp"

using namespace std;

int main() {
    vector<R2Point> points;
    int n = 0;
    cout << "Enter the number of points: ";
    if (!(cin >> n) || n <= 0) {
        return -1;
    }
    points.resize(n);
    vector<R2Point> convexHull;
    for (int i = 0; i < n; ++i) {
        if (!(cin >> points[i]))
            return -1;
    }
    computeConvexHull(points, convexHull);
    cout << "Convex Hull: " << endl;
    for (size_t i = 0; i < convexHull.size(); ++i) {
        cout << " " << convexHull[i];
    }
    cout << endl;
    return 0;
}