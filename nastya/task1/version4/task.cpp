#include "head.h"

// Конструктор по умолчанию
CVect::CVect() {
    for (int i = 0; i < N; ++i) {
        arr[i] = CVectElem(0., 0.);
    }
}

// Конструктор с параметрами
CVect::CVect(const CVectElem other[N]) {
    for (int i = 0; i < N; ++i) {
        arr[i] = other[i];
    }
}

// Конструктор копирования
CVect::CVect(const CVect& other) {
    for (int i = 0; i < N; ++i) {
        arr[i] = other.arr[i];
    }
}

CVect CVect::operator+(const CVect& other) const {
    CVectElem res[10];

    for (int i = 0; i < N; ++i) {
        res[i] = arr[i] + other[i];
    }
    return CVect(res);
}

CVect CVect::operator+(const CAngl& other) const {
    double x, y;
    CVectElem res[10];

    for (int i = 0; i < N; ++i) {
        x = arr[i].getX() * cos(other[i]) - arr[i].getY() * sin(other[i]);
        y = arr[i].getX() * sin(other[i]) + arr[i].getY() * cos(other[i]);
        res[i] = CVectElem(x, y);
    }
    return CVect(res);
}

CAngl CVect::operator-(const CVect& other) const {
    double angle[N];
    for (int i = 0; i < N; ++i) {
        angle[i] = atan2(arr[i].getY() - other[i].getY(), arr[i].getX()- other[i].getX());
    }

    return CAngl(angle);
}

// CVect CVect::operator=(const CVect& other) const {
//     for (int i = 0; i < N; ++i) {
//         arr[i] = other[i];
//     }
//     return *this;
// }

CVectElem CVect::operator[](int k) const {
    return arr[k];
}

//Оператор вставки для CVect
std::ostream& operator<<(std::ostream& os, const CVect& v) {
    os << "{\n";
    for (int i = 0; i < N; ++i) {
        os << "\t(" << v[i].getX() << ", " << v[i].getY() << ")\n";
    }
    os << "}";
	return os;
}

//Оператор вставки для CAngle
std::ostream& operator<<(std::ostream& os, const CAngl& a) {
	os << "{\n";
    for (int i = 0; i < N; ++i) {
        os << "\t" << a[i] << ",\n";
    }
    os << "}";
	return os;
}





// Конструктор по умолчанию
CVectElem::CVectElem(): x(0.), y(0.) {}

// Конструктор с параметрами
CVectElem::CVectElem(double _x, double _y): x(_x), y(_y) {}

// Оператор сложения для CVectElem
CVectElem CVectElem::operator+(const CVectElem& other) const {
    double _x, _y;
    _x = x + other.x;
    _y = y + other.y;
    return CVectElem(_x, _y);
}

// CVectElem CVectElem::operator=(const CVectElem& other) const {
//     double x = other.x;
//     double y = other.y;
//     return CVectElem(x, y);
// }

// Функция получения x текущего объект класса
double CVectElem::getX() const {
    return this->x;
}

// Функция получения y текущего объект класса
double CVectElem::getY() const {
    return this->y;
}








// Конструктор по умолчанию
CAngl::CAngl() {
    for (int i = 0; i < N; ++i) {
        angle[i] = 0.;
    }
}

// Конструктор с параметрами
CAngl::CAngl(double _angle[N]) {
    for (int i = 0; i < N; ++i) {
        angle[i] = _angle[i];
    }
}

// Оператор сложения для CVect и CAngl
CVect CAngl::operator+(const CVect& other) const {
    double x, y;
    CVectElem res[10];

    for (int i = 0; i < N; ++i) {
        x = other[i].getX() * cos(angle[i]) - other[i].getY() * sin(angle[i]);
        y = other[i].getX() * sin(angle[i]) + other[i].getY() * cos(angle[i]);
        res[i] = CVectElem(x, y);
    }

    return CVect(res);
}

// Функция получения angle текущего объект класса
double CAngl::operator[](int k) const {
    return angle[k];
}