//points.push_back() //Добавить точку в конец массива 
//points.back() //последний элемент массива
// points.front //первый элемент массива
//points.pop_back() //удалить последний эелемент
//points.size() //размер массива (целое число size_t)

//Алгоритмы, например, алгоритмы сортировки
//#include <algorithm>
//std::sort(points.begin(), points.end())

//Алгоритм вычисления выпуклой оболочки
//1. Находим точку с минимальной координатой х (можно сорт)
//2. Формируем массив векторов: 
//radiusVector[i] = points[i] - points[0]
//3. Сортируем массив векторов radiusVector по углу с осью Х
//4. Обходим векторы по порядку, получаем концы векторов --
//это точки строящейся выпуклой оболочки. Если при добавлении
//новой точки мы получаем отрицательный угол между 
//предыдущим ребром и добавленным ребром, то предыдущая
//вершина многоугольника удаляется, потом проверяется 
//предыдущая вершина
// #include <iostream>
#include <vector>
#include <algorithm>
#include "convexHull.h"
#include "R2Graph.cpp"

using namespace std;

bool compareAngles( //Сравнение углов
    const R2Vector& v1, //возвращает true, когда угол от v1
    const R2Vector& v2 //строго меньше угла от v2
);

void computeConvexHull (
    const vector<R2Point>& points,
    vector<R2Point>& convexHull
) {
    if (points.size() <= 2)
        convexHull = points;

    vector<R2Point> nodes = points;
    sort(nodes.begin(), nodes.end());

    vector<R2Vector> radiusVectors(nodes.size() - 1);
    for (int i = 0; i < int(nodes.size()); ++i) {
        radiusVectors[i - 1] = nodes[i] - nodes[0];
    }
    sort(
        radiusVectors.begin(),
        radiusVectors.end(), compareAngles
    );

    convexHull.clear();
    convexHull.push_back(nodes[0]);
    convexHull.push_back(nodes[0] + radiusVectors[0]);
    for (int i = 1; i < int(radiusVectors.size()); ++i) {
        R2Point newPoint = nodes[0] + radiusVectors[i];
        R2Vector newEdge = 
            newPoint - convexHull[convexHull.size() - 1];
        R2Vector prevEdge =
            convexHull[convexHull.size() - 1] -
            convexHull[convexHull.size() - 2];
        double alpha = prevEdge.angle(newEdge);
        if (alpha <= 0.) {
            // remove last points from convex hull
            while (alpha <= 0 && convexHull.size() > 2) {
                convexHull.pop_back();
                newEdge = newPoint - convexHull[convexHull.size() - 1];
                R2Vector prevEdge =
                    convexHull[convexHull.size() - 1] -
                    convexHull[convexHull.size() - 2];
                alpha = prevEdge.angle(newEdge);
            }
        }
        convexHull.push_back(newPoint);
    }
}

bool compareAngles( //Сравнение углов
    const R2Vector& v1, //возвращает true, когда угол от v1
    const R2Vector& v2 //строго меньше угла от v2
) {
    R2Vector ex(1., 0.);
    double alpha1 = ex.angle(v1);
    double alpha2 = ex.angle(v2);
    return (
        alpha1 < alpha2 ||
        (
            alpha1 <= alpha2 &&
            v1.length() < v2.length()
        )
    );
}