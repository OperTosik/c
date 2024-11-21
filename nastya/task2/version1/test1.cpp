#include "test.h"

void getArray(CVect &arr) {
	double x;
    double y;
    size_t lenght = rand() % 20;
    while (lenght == 0) lenght = rand() % 20;
    // CVectElem tmp[lenght];
    CVectElem* tmp = new CVectElem[lenght];

	for (int i = 0; i < lenght; ++i) {
		x = ((double)rand()/RAND_MAX) * 20 - 10;
        y = ((double)rand()/RAND_MAX) * 20 - 10;
		tmp[i] = CVectElem(x, y);
	}

    arr = CVect(tmp, lenght);
    // std::cout << "v1 = " << arr << "\n" << std::endl;
    // delete[] tmp;

}

void getArray(CAngl &arr) {
    size_t lenght = rand() % 20;
    while (lenght == 0) lenght = rand() % 20;
	double* x = new double[lenght];

	for (int i = 0; i < lenght; ++i) {
		x[i] = ((double)rand()/RAND_MAX) * 200 - 100;
	}

    arr = CAngl(x, lenght);
}

void unaryOperatorMinus(CAngl& arr) {
    size_t lenght = arr.getLenght();
    double tmp[lenght];
    for (int i = 0; i < lenght; ++i) {
        tmp[i] = -arr.getAngle(i);
    }
    arr = CAngl(tmp, lenght);
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
    // std::cout << "Операция сложения векторов:" << std::endl;
    // v = v1 + v2;
    // std::cout << v << "\n" << std::endl;

    //Операции сложения вектора с углом
    std::cout << "Операция сложения вектора с углом (поворот на angle):" << std::endl;
    v = v1 + angle;
    std::cout << v << "\n" << std::endl;

    std::cout << "Операция сложения вектора с углом (поворот на -angle):" << std::endl;
    v = minusAngle + v1;
    std::cout << v << "\n" << std::endl;
    
    //Операция вычитания векторов
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