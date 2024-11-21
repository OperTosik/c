#include "head.h"
#include "test1.cpp"
#include "test2.cpp"

int main() {
    std::cout << "First test" << std::endl;
    test1();
    std::cout << "\n\n" << std::endl;

    std::cout << "Second test" << std::endl;
    test2();
    return 0;
}