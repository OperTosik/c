#include "test.h"

void getArray(CVect &arr) {
	double x;
    double y;
    CVectElem tmp[N];

	for (int i = 0; i < N; ++i) {
		x = ((double)rand()/RAND_MAX) * 20 - 10;
        y = ((double)rand()/RAND_MAX) * 20 - 10;
		tmp[i] = CVectElem(x, y);
	}

    arr = CVect(tmp);
    // std::cout << "v1 = " << arr << "\n" << std::endl;

}

void getArray(CAngl &arr) {
	double x[N];

	for (int i = 0; i < N; ++i) {
		x[i] = ((double)rand()/RAND_MAX) * 200 - 100;
	}

    arr = CAngl(x);
}

//Ввиду запрета перегрузки оператора, унарный минус предствим в виде функции
//Чтобы не усложнять класс не будем писать функцию setAngle для объекта класса
void unaryOperatorMinus(CAngl& arr) {
    double tmp[N];
    for (int i = 0; i < N; ++i) {
        tmp[i] = -arr.getAngle(i);
    }
    arr = CAngl(tmp);
}

void test1() {
    srand(time(NULL));

    CVect v1;
    getArray(v1);
    std::cout << "v1 = " << v1 << "\n" << std::endl;
    
    CVect v2;
    getArray(v2);
    std::cout << "v2 = " << v2 << "\n" << std::endl;

    CAngl angle;
    getArray(angle);
    std::cout << "angle = " << angle << "\n" << std::endl;

    CAngl minusAngle{angle};
    unaryOperatorMinus(minusAngle);
    std::cout << "-angle = " << minusAngle << "\n" << std::endl;

    // Тестирование операций
    CVect v;
    CAngl a;

    //Операция сложения векторов
    std::cout << "Операция сложения векторов:" << std::endl;
    v = v1 + v2;
    std::cout << v << "\n" << std::endl;

    //Операции сложения вектора с углом
    std::cout << "Операция сложения вектора с углом (поворот на angle):" << std::endl;
    v = angle + v1;
    std::cout << v << "\n" << std::endl;

    std::cout << "Операция сложения вектора с углом (поворот на -angle):" << std::endl;
    v = minusAngle + v1;
    std::cout << v << "\n" << std::endl;
    
    //Операция вычитания векторов
    std::cout << "Операция вычитания векторов:" << std::endl;
    a = v1 - v2;
    std::cout << a << "\n" << std::endl;



    std::cout << "Операция вычитания векторов:" << std::endl;
    a = v2 - v1;
    std::cout << a << "\n" << std::endl;

    std::cout << "My test" << std::endl;
    v = v1 + (v2 - v1) + (v1 - v2);
    std::cout << v << "\n" << std::endl;

}