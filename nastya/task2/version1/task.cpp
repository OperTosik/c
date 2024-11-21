#include "head.h"

// class CVectElem
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

// Функция получения x текущего объект класса
double CVectElem::getX() const {
    return this->x;
}

// Функция получения y текущего объект класса
double CVectElem::getY() const {
    return this->y;
}





//class CVect
// Конструктор по умолчанию
CVect::CVect(): lenght(0), arr(nullptr) {}    //Пустой вектор

// Конструктор с параметрами
CVect::CVect(const CVectElem* other, size_t otherLenght) {
    arr = new CVectElem[otherLenght];
    lenght = otherLenght;
    for (size_t i = 0; i < lenght; ++i) {
        arr[i] = other[i];
    }
}

//Конструктор копирования
CVect::CVect(const CVect& other) {
    lenght = other.getLenght();
    arr = new CVectElem[lenght];
    for (size_t i = 0; i < lenght; ++i) {
        arr[i] = other.arr[i];
    }
}

//Конструктор перемещения
CVect::CVect(CVect&& other) {
    lenght = other.getLenght();
    arr = other.arr;
    other.arr = nullptr;
}

//Деструктор
CVect::~CVect() {
    delete[] arr;
}

//Оператор присваивания
CVect CVect::operator=(const CVect& other) {
    delete[] arr;
    lenght = other.getLenght();
    arr = new CVectElem[lenght];
    for (size_t i = 0; i < lenght; ++i) {
        arr[i] = other.arr[i];
    }
    return *this;
}

//Оператор перемещения
CVect& CVect::operator=(CVect&& other) {
    delete[] arr;
    lenght = other.getLenght();
    arr = other.arr;
    other.arr = nullptr;
    return *this;
}

//Префиксныый инкремент
CVect& CVect::operator++() {
    CVect tmp = *this;
    delete[] arr;
    ++lenght;
    arr = new CVectElem[lenght];
    for (size_t i = 0; i < lenght - 1; ++i) {
        arr[i] = tmp.arr[i];
    }
    arr[lenght - 1] = arr[lenght - 2];
    return *this;
}

//Постфиксный инкремент
CVect CVect::operator++(int) {
    ++(*this);
    return *this;
}

//Префиксный декремент
CVect& CVect::operator--() {
    CVect tmp = *this;
    delete[] arr;
    --lenght;
    arr = new CVectElem[lenght];
    for (size_t i = 0; i < lenght; ++i) {
        arr[i] = tmp.arr[i];
    }
    return *this;
}

//Постфиксный декремент
CVect CVect::operator--(int) {
    --(*this);
    return *this;
}

//Оператор сложения массива вектора с массивом углов
CVect CVect::operator+(const CAngl& other) {
    double x, y;
    CVect tmp = *this;
    delete[] arr;
    lenght = (lenght < other.getLenght()) ? lenght : other.getLenght();
    arr = new CVectElem[lenght];

    for (int i = 0; i < lenght; ++i) {
        x = tmp.arr[i].getX() * cos(other.getAngle(i)) - tmp.arr[i].getY() * sin(other.getAngle(i));
        y = tmp.arr[i].getX() * sin(other.getAngle(i)) + tmp.arr[i].getY() * cos(other.getAngle(i));
        arr[i] = CVectElem(x, y);
    }
    return *this;
}

//Оператор вычитания векторов
CAngl CVect::operator-(const CVect& other) const {
    int angLenght = (lenght < other.getLenght()) ? lenght : other.getLenght();
    double angle[angLenght];
    for (int i = 0; i < angLenght; ++i) {
        angle[i] = acos((arr[i].getX()*other.arr[i].getX() + arr[i].getY()*other.arr[i].getY()) / 
                    (sqrt(arr[i].getX()*arr[i].getX() + arr[i].getY()*arr[i].getY()) *
                    (sqrt(other.arr[i].getX()*other.arr[i].getX() + other.arr[i].getY()*other.arr[i].getY()))));
        // angle[i] = (arr[i].getX()*other.arr[i].getY() - arr[i].getY()*other.arr[i].getX()) / 
        //             (2 * (sqrt(arr[i].getX()*arr[i].getX() + arr[i].getY()*arr[i].getY()) *
        //             (sqrt(other.arr[i].getX()*other.arr[i].getX() + other.arr[i].getY()*other.arr[i].getY()))));
    }

    return CAngl(angle, angLenght);
}

//Функция возвращающая длину
size_t CVect::getLenght() const {
    return lenght;
}

//Функция обращения к элементу массива векторов
CVectElem CVect::getVect(int k) const {
    return arr[k];
}

//Оператор вставки для массива векторов
std::ostream& operator<<(std::ostream& os, const CVect& v) {
    os << "{\n";
    for (int i = 0; i < v.getLenght(); ++i) {
        os << "\t(" << v.arr[i].getX() << ", " << v.arr[i].getY() << ")\n";
    }
    os << "}";
	return os;
}





//class CAngl
//Конструктор по умолчанию
CAngl::CAngl(): lenght(0), angle(nullptr) {}

//Конструтор с параметрами
CAngl::CAngl(double* _angle, size_t _lenght) {
    angle = new double[_lenght];
    lenght = _lenght;
    for (size_t i = 0; i < lenght; ++i) {
        angle[i] = _angle[i];
    }
}

//Конструктор копирования
CAngl::CAngl(const CAngl& other) {
    lenght = other.getLenght();
    angle = new double[lenght];
    for (size_t i = 0; i < lenght; ++i) {
        angle[i] = other.angle[i];
    }
}

//Конструктор перемещения
CAngl::CAngl(CAngl&& other) {
    lenght = other.getLenght();
    angle = other.angle;
    other.angle = nullptr;
}

//Деструктор
CAngl::~CAngl() {
    delete[] angle;
}

//Оператор присваивания
CAngl CAngl::operator=(const CAngl& other) {
    delete[] angle;
    lenght = other.getLenght();
    angle = new double[lenght];
    for (size_t i = 0; i < lenght; ++i) {
        angle[i] = other.angle[i];
    }
    return *this;
}

//Оператор перемещения
CAngl& CAngl::operator=(CAngl&& other) {
    delete[] angle;
    lenght = other.getLenght();
    angle = other.angle;
    other.angle = nullptr;
    return *this;
}

//Префиксный инкремент
CAngl& CAngl::operator++() {
    CAngl tmp = *this;
    delete[] angle;
    ++lenght;
    angle = new double[lenght];
    for (size_t i = 0; i < lenght - 1; ++i) {
        angle[i] = tmp.angle[i];
    }
    angle[lenght - 1] = angle[lenght - 2];
    return *this;
}

//Постфиксынй инкремент
CAngl CAngl::operator++(int) {
    ++(*this);
    return *this;
}

//Префиксный декремент
CAngl& CAngl::operator--() {
    CAngl tmp = *this;
    delete[] angle;
    --lenght;
    angle = new double[lenght];
    for (size_t i = 0; i < lenght; ++i) {
        angle[i] = tmp.angle[i];
    }
    return *this;
}

//Постфиксный декремент
CAngl CAngl::operator--(int) {
    --(*this);
    return *this;
}

//Оператор сложения массива углов  массивом векторов
CVect CAngl::operator+(CVect& other) {
    other = std::move(other + (*this));
    return other;
}

//Функция возвращающая длину массива углов
size_t CAngl::getLenght() const {
    return lenght;
}

//Функция обращения к элементу массива углов
double CAngl::getAngle(int k) const {
    return angle[k];
}

//Оператор вставки для массива углов
std::ostream& operator<<(std::ostream& os, const CAngl& a) {
    os << "{\n";
    for (int i = 0; i < a.getLenght(); ++i) {
        os << "\t" << a.angle[i] << ",\n";
    }
    os << "}";
	return os;
}