#include "head.h"

// Конструктор по умолчанию
CVect::CVect(): x(0.), y(0.) {}

// Конструктор с параметрами
CVect::CVect(double _x, double _y): x(_x), y(_y) {}

// Оператор сложения для CVect
CVect CVect::operator+(const CVect& other) {
    double _x, _y;
    _x = x + other.x;
    _y = y + other.y;
    return CVect(_x, _y);
}

// Оператор сложения для CAngl и CVect (поворот вектора)
CVect CVect::operator+(const CAngl& other) {
    x = x * cos(other.angle) - y * sin(other.angle);
    y = x * sin(other.angle) + y * cos(other.angle);
    return CVect(x, y);
}

// Оператор вычитания для CVect
CAngl CVect::operator-(const CVect& other) {
    double angle = atan2(y - other.y, x - other.x);
    return CAngl(angle);
}







// Конструктор по умолчанию
CAngl::CAngl(): angle(0.) {}

// Конструктор с параметрами
CAngl::CAngl(double _angle): angle(_angle) {}

// Оператор сложения для CVect и CAngl
CVect CAngl::operator+(const CVect& other) {
    double x, y;
    x = other.x * cos(angle) - other.y * sin(angle);
    y = other.x * sin(angle) + other.y * cos(angle);
    return CVect(x, y);
}

