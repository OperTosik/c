#include "test.h"

void test2() {
    CVectElem vectElems1[10] = {
        CVectElem(1., 10.), CVectElem(2., 9.), CVectElem(3., 8.), CVectElem(4., 7.), CVectElem(5., 6.),
        CVectElem(6., 5.), CVectElem(7., 4.), CVectElem(8., 3.), CVectElem(9., 2.), CVectElem(10., 1.),
    };
    CVect v1 = CVect(vectElems1, 10);

    CVectElem vectElems2[10] = {
        CVectElem(10., 1.), CVectElem(9., 2.), CVectElem(8., 3.), CVectElem(7., 4.), CVectElem(6., 5.),
        CVectElem(5., 6.), CVectElem(4., 7.), CVectElem(3., 8.), CVectElem(2., 9.), CVectElem(1., 10.),
    };
    CVect v2 = CVect(vectElems2, 10);

    double arrAngle[10] = {
        (M_PI/4), (M_PI/3), (M_PI/2), (2*M_PI/3), (3*M_PI/4),
        (5*M_PI/6), (7*M_PI/6), (4*M_PI/3), (5*M_PI/3), (11*M_PI/6)
    };
    CAngl angle = CAngl(arrAngle, 10);

    double minusArrAngle[10] = {
        -(M_PI/4), -(M_PI/3), -(M_PI/2), -(2*M_PI/3), -(3*M_PI/4),
        -(5*M_PI/6), -(7*M_PI/6), -(4*M_PI/3), -(5*M_PI/3), -(11*M_PI/6)
    };
    CAngl minusAngle = CAngl(minusArrAngle, 10);

    std::cout << "v1 = " << v1 << "\n" << std::endl;
    std::cout << "v2 = " << v2 << "\n" << std::endl;
    std::cout << "angle = " << angle << "\n" << std::endl;
    std::cout << "-angle = " << minusAngle << "\n" << std::endl;

   
    CVect v;
    CAngl a;

    // std::cout << "Операция сложения векторов:" << std::endl;
    // v = v1 + v2;
    // std::cout << v << "\n" << std::endl;


    // std::cout << "Операция сложения векторов:" << std::endl;
    // v = v1 + v2;
    // std::cout << v << "\n" << std::endl;


    std::cout << "Операция сложения вектора с углом (поворот на angle):" << std::endl;
    v = v1 + angle;
    std::cout << v << "\n" << std::endl;

    v = v1 + (v1-v2) + (v2-v1);
    std::cout << "Поворот вектора на угол и обратно" << std::endl;
    std::cout << v << "\n" << std::endl;
    
    std::cout << "Операция вычитания векторов:" << std::endl;
    a = v1 - v2;
    std::cout << a << "\n" << std::endl;

    //Преинкремент
    std::cout << "Оператор преинкремента: " << std::endl;
    ++v1;
    std::cout << v1 << "\n" << std::endl;

    --v1;
    //Постинкремент
    std::cout << "Оператор постинкремента: " << std::endl;
    v1++;
    std::cout << v1 << "\n" << std::endl;

    --v1;
    //Предекремент
    std::cout << "Оператор предекремента: " << std::endl;
    --v1;
    std::cout << v1 << "\n" << std::endl;

    ++v1;
    //Постдекремент
    std::cout << "Оператор постдекремента: " << std::endl;
    v1--;
    std::cout << v1 << "\n" << std::endl;

}