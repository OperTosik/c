#include "head.h"

// Конструктор по умолчанию
CVect::CVect() {
    for (int i = 0; i < N; i++) {
        x[i] = 0.0;
        y[i] = 0.0;
    }
}

// Конструктор с параметрами
CVect::CVect(double* _x, double* _y) {
    for (int i = 0; i < N; i++) {
        x[i] = _x[i];
        y[i] = _y[i];
    }
}

// Оператор сложения для CVect
CVect CVect::operator+(const CVect& other) {
    double newX[N], newY[N];
    for (int i = 0; i < N; i++) {
        newX[i] = x[i] + other.x[i];
        newY[i] = y[i] + other.y[i];
    }
    return CVect(newX, newY);
}

// Оператор сложения для CAngl и CVect (поворот вектора)
CVect CVect::operator+(const CAngl& other) {
    double newX[N], newY[N];
    for (int i = 0; i < N; i++) {
        newX[i] = x[i] * cos(other.angle[i]) - y[i] * sin(other.angle[i]);
        newY[i] = x[i] * sin(other.angle[i]) + y[i] * cos(other.angle[i]);
    }
    return CVect(newX, newY);
}

// Оператор вычитания для CVect
CAngl CVect::operator-(const CVect& other) {
    double angle[N];
    for (int i = 0; i < N; i++) {
        angle[i] = atan2(y[i] - other.y[i], x[i] - other.x[i]);
    }
    return CAngl(angle);
}







// Конструктор по умолчанию
CAngl::CAngl() {
    for (int i = 0; i < N; i++) {
        angle[i] = 0.0;
    }
}

// Конструктор с параметрами
CAngl::CAngl(double* _angle) {
    for (int i = 0; i < N; i++) {
        angle[i] = _angle[i];
    }
}

// Оператор сложения для CVect и CAngl
CVect CAngl::operator+(const CVect& other) {
    double newX[N], newY[N];
    for (int i = 0; i < N; i++) {
        newX[i] = other.x[i] * cos(angle[i]) - other.y[i] * sin(angle[i]);
        newY[i] = other.x[i] * sin(angle[i]) + other.y[i] * cos(angle[i]);
    }
    return CVect(newX, newY);
}

