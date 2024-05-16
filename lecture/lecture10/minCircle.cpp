#include <cmath>
#include <cassert>
#include "minCircle.h"

using namespace std; //Ни в коем случае не писать в h файле

void computeMinCircle( //Вычислить мин окр. для заданных точек
    const vector<R2Point>& points, //Входные
    R2Point& center, //выходные
    double& radius
) {
    if (points.size() == 0) {
        return;
    } else if (points.size() == 1) {
        center = points[0];
        radius = 0.;
    } else if (points.size() == 2) {
        center = (points[0] + points[1]) * 0.5;
        radius = points[0].distance(points[1]) / 2.;
        return;
    }
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            for (size_t k = j + 1; k < points.size(); ++k) {
                computeMinCircleForTriangle(
                    points[i],
                    points[j],
                    points[k],
                    center,
                    radius
                );
                bool allPointsInside = true;
                for (size_t l = 0; l < points.size(); ++l) {
                    if (l == i || l == j || l == k)
                        continue;
                    double r = center.distance(points[l]);
                    if (r > radius) {
                        allPointsInside = false;
                        break;
                    }
                }
                if (allPointsInside)
                    return;
            }
        }
    }
}

void computeMinCircleForTriangle(
    const R2Point& a, //Входные
    const R2Point& b,
    const R2Point& c,
    R2Point& center, //Выходные
    double& radius
) {
    //Угол вектора (b-a) и (c-a)
    if (fabs((b - a).angle(c - a)) > M_PI/2.) {
        //Obtuse angle a
        center = (b + c) * 0.5;
        radius = b.distance(c) / 2.;
    } else if (fabs((a - b).angle(c - b)) > M_PI/2.) {
        //Obtuse angle b
        center = (a + c) * 0.5;
        radius = a.distance(c) / 2.;
    } else if (fabs((a - c).angle(b - c)) > M_PI/2.) {
        //Obtuse angle c
        center = (a + b) * 0.5;
        radius = a.distance(b) / 2.;
    } else {
        //all angles are acute
        computeCircumcircle(a, b, c, center, radius);
    }
}

void computeCircumcircle(
    const R2Point& a, //Входные
    const R2Point& b,
    const R2Point& c,
    R2Point& center, //Выходные
    double& radius
) {
    R2Point middle_ab = (a + b) * 0.5;
    R2Vector normal_ab = (b - a).normal();

    R2Point middle_bc = (b + c) * 0.5;
    R2Vector normal_bc = (c - b).normal();

    intersectStraightLines(
        middle_ab, normal_ab, //first point
        middle_bc, normal_bc, //second point
        center
    );

    radius = center.distance(a);
}