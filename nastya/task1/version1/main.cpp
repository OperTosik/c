#include "head.h"
#include "interface.h"

int main() {
    interface();

    // // Создание векторов
    // double x[N] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    // double y[N] = {10.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    // CVect v1(x, y);

    // double x2[N] = {10.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    // double y2[N] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    // CVect v2(x2, y2);

    // double angle[N] = {M_PI/4, M_PI/3, M_PI/2, 2*M_PI/3, 3*M_PI/4, 5*M_PI/6, 7*M_PI/6, 4*M_PI/3, 5*M_PI/3, 11*M_PI/6};
    // CAngl a1(angle);

    // // Тестирование операций
    // CVect v3 = v1 + v2;
    // CVect v4 = v1 + a1;
    // CAngl a2 = v1 - v2;

    // std::cout << "v1 + v2 = ";
    // for (int i = 0; i < N; i++) {
    //     std::cout << "(" << v3.x[i] << ", " << v3.y[i] << ") ";
    // }
    // std::cout << std::endl;

    // std::cout << "v1 + a1 = ";
    // for (int i = 0; i < N; i++) {
    //     std::cout << "(" << v4.x[i] << ", " << v4.y[i] << ") ";
    // }
    // std::cout << std::endl;

    // std::cout << "v1 - v2 = ";
    // for (int i = 0; i < N; i++) {
    //     std::cout << a2.angle[i] << " ";
    // }
    // std::cout << std::endl;

    return 0;
}