#include "test.h"

void test2() {
    CVectElem vectElems1[10] = {
        CVectElem(1., 10.), CVectElem(2., 9.), CVectElem(3., 8.), CVectElem(4., 7.), CVectElem(5., 6.),
        CVectElem(6., 5.), CVectElem(7., 4.), CVectElem(8., 3.), CVectElem(9., 2.), CVectElem(10., 1.),
    };
    CVect v1 = CVect(vectElems1);

    CVectElem vectElems2[10] = {
        CVectElem(10., 1.), CVectElem(9., 2.), CVectElem(8., 3.), CVectElem(7., 4.), CVectElem(6., 5.),
        CVectElem(5., 6.), CVectElem(4., 7.), CVectElem(3., 8.), CVectElem(2., 9.), CVectElem(1., 10.),
    };
    CVect v2 = CVect(vectElems2);

    double arrAngle[10] = {
        (M_PI/4), (M_PI/3), (M_PI/2), (2*M_PI/3), (3*M_PI/4),
        (5*M_PI/6), (7*M_PI/6), (4*M_PI/3), (5*M_PI/3), (11*M_PI/6)
    };
    CAngl angle = CAngl(arrAngle);

    double minusArrAngle[10] = {
        -(M_PI/4), -(M_PI/3), -(M_PI/2), -(2*M_PI/3), -(3*M_PI/4),
        -(5*M_PI/6), -(7*M_PI/6), -(4*M_PI/3), -(5*M_PI/3), -(11*M_PI/6)
    };
    CAngl minusAngle = CAngl(minusArrAngle);

    std::cout << "v1 = " << v1 << "\n" << std::endl;
    std::cout << "v2 = " << v2 << "\n" << std::endl;
    std::cout << "angle = " << angle << "\n" << std::endl;
    std::cout << "-angle = " << minusAngle << "\n" << std::endl;

    // Тестирование операций
    CVect v;
    CAngl a;

    //Операция сложения векторов
    std::cout << "Операция сложения векторов:" << std::endl;
    v = v1 + v2;
    std::cout << v << "\n" << std::endl;

    //Операция сложения векторов
    std::cout << "Операция сложения векторов:" << std::endl;
    v = v1 + v2;
    std::cout << v << "\n" << std::endl;

    //Операции сложения вектора с углом
    std::cout << "Операция сложения вектора с углом (поворот на angle):" << std::endl;
    v = angle + v1;
    std::cout << v << "\n" << std::endl;

    std::cout << "Операция сложения вектора с углом (поворот на angle):" << std::endl;
    v = v1 + (v2 - v1) + (v1 - v2);
    std::cout << v << "\n" << std::endl;

    std::cout << "Операция сложения вектора с углом (поворот на -angle):" << std::endl;
    v = minusAngle + v1;
    std::cout << v << "\n" << std::endl;
    
    
    //Операция вычитания векторов
    std::cout << "Операция вычитания векторов:" << std::endl;
    a = v1 - v2;
    std::cout << a << "\n" << std::endl;

}