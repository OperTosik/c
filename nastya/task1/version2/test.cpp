#include "head.h"
#include <cstdlib>
#include <ctime>

void getArray(CVect* arr) {
	double x;
    double y;

	for (int i = 0; i < N; ++i) {
		x = ((double)rand()/RAND_MAX) * 200 - 100;
        y = ((double)rand()/RAND_MAX) * 200 - 100;
		arr[i] = CVect(x, y);
		std::cout << "Vector_" << (i + 1) << " = (" << x << ", " << y << ")" << std::endl;
	}

	std::cout << std::endl;
}

void getArray(CAngl* arr) {
	double x;

	for (int i = 0; i < N; ++i) {
		x = ((double)rand()/RAND_MAX) * 200 - 100;
		arr[i] = CAngl(x);
		std::cout << "Angle_" << (i + 1) << " = " << x << std::endl;
	}
    
	std::cout << std::endl;
}

void test() {
    srand(time(NULL));

    CVect arrVect[10];
    getArray(arrVect);
    
    CVect arrVect2[10];
    getArray(arrVect2);

    CAngl arrAngle[10];
    getArray(arrAngle);

    // Тестирование операций
    CVect v;
    CAngl a;

    //Операция сложения векторов
    std::cout << "Операция сложения векторов:" << std::endl;
    for (int i = 0; i < N; ++i) {
        v = arrVect[i] + arrVect2[i];

        std::cout << "\t" << "v_" << (i + 1) << " = (" << arrVect[i].x << ", " << arrVect[i].y << ") + ";
        std::cout << "(" << arrVect2[i].x << ", " << arrVect2[i].y << ") = ";
        std::cout << "(" << v.x << ", " << v.y << ")" << std::endl;
    }
    std::cout << std::endl;

    //Операция сложения вектора с углом
    std::cout << "Операция сложения вектора с углом:" << std::endl;
    for (int i = 0; i < N; ++i) {
        v = arrAngle[i] + arrVect[i];

        std::cout << "\t" << "v_" << (i + 1) << " = (" << arrAngle[i].angle << ") + (";
        std::cout << arrVect[i].x << ", " << arrVect[i].y << ") = ";
        std::cout << "(" << v.x << ", " << v.y << ")" << std::endl;
    }
    std::cout << std::endl;
    
    //Операция вычитания векторов
    std::cout << "Операция вычитания векторов:" << std::endl;
    for (int i = 0; i < N; ++i) {
        a = arrVect[i] - arrVect2[i];

        std::cout << "\t" << "v_" << (i + 1) << " = (" << arrVect[i].x << ", " << arrVect[i].y << ") + ";
        std::cout << "(" << arrVect2[i].x << ", " << arrVect2[i].y << ") = ";
        std::cout << "(" << a.angle << ")" << std::endl;
    }
    std::cout << std::endl;
}