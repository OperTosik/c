#include "head.h"
#include <cstdlib>
#include <ctime>

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

    // Тестирование операций
    CVect v;
    CAngl a;

    //Операция сложения векторов
    std::cout << "Операция сложения векторов:" << std::endl;
    v = v1 + v2;
    std::cout << v << std::endl;

    //Операция сложения вектора с углом
    std::cout << "Операция сложения вектора с углом:" << std::endl;
    v = angle + v1;
    std::cout << v << std::endl;
    
    
    //Операция вычитания векторов
    std::cout << "Операция вычитания векторов:" << std::endl;
    a = v1 - v2;
    std::cout << a << std::endl;

    // std::cout << "\t" << "v_" << (i + 1) << " = (" << arrVect[i].getX() << ", " << arrVect[i].getY() << ") + ";
    // std::cout << "(" << arrVect2[i].getX() << ", " << arrVect2[i].getY() << ") = ";
    // std::cout << "(" << a.getAngle() << ")" << std::endl;
    // std::cout << std::endl;
}