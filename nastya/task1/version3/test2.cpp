#include "head.h"
// #include <cstdlib>


void test2() {
    CVect arrVect[10] = {
        CVect(1., 10.), CVect(2., 9.), CVect(3., 8.), CVect(4., 7.), CVect(5., 6.),
        CVect(6., 5.), CVect(7., 4.), CVect(8., 3.), CVect(9., 2.), CVect(10., 1.),
    };

    CVect arrVect2[10] = {
        CVect(10., 1.), CVect(9., 2.), CVect(8., 3.), CVect(7., 4.), CVect(6., 5.),
        CVect(5., 6.), CVect(4., 7.), CVect(3., 8.), CVect(2., 9.), CVect(1., 10.),
    };

    CAngl arrAngle[10] = {
        CAngl(M_PI/4), CAngl(M_PI/3), CAngl(M_PI/2), CAngl(2*M_PI/3), CAngl(3*M_PI/4),
        CAngl(5*M_PI/6), CAngl(7*M_PI/6), CAngl(4*M_PI/3), CAngl(5*M_PI/3), CAngl(11*M_PI/6)
    };

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