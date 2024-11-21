#include "head.h"
#include "test1.cpp"
#include "test2.cpp"

int main() {
    std::cout << "Первый тест" << std::endl;
    test1();
    std::cout << "\n\n" << std::endl;

    std::cout << "Второй тест" << std::endl;
    test2();
    return 0;
}