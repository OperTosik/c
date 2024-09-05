//Это гаарда
#ifndef MIN_CIRCLE_H //Подключаем если переменная не определена
#define MIN_CIRCLE_H 1 //Это гаарда
//Это делается чтобы исключить повторное подключение файла
#include <vector>
#include <algorithm>
#include "R2Graph.h"

void computeMinCircle( //Вычислить мин окр. для заданных точек
    const std::vector<R2Point>& points, //Входные
    R2Point& center, //выходные
    double& radius
);

void computeMinCircleForTriangle(
    const R2Point& a, //Входные
    const R2Point& b,
    const R2Point& c,
    R2Point& center, //Выходные
    double& radius
);

void computeCircumcircle(
    const R2Point& a, //Входные
    const R2Point& b,
    const R2Point& c,
    R2Point& center, //Выходные
    double& radius
);

#endif