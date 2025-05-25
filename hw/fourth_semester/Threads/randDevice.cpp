#include <iostream>
#include <random>

int main() {
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<int> intRange(1, 500);
    std::uniform_real_distribution<double> realRange(0., 10.);

    std::cout << "Random integer numbers in range (1, 500):" << std::endl;
    for (int i = 0; i < 20; ++i) {
        if (i > 0) {
            // Delimiter
            if (i%5 != 0)
                std::cout << ' ';   
            else
                std::cout << std::endl;
        }
        std::cout << intRange(gen);
    }
    std::cout << std::endl;

    std::cout << "Random real numbers in range (0., 10.):" << std::endl;
    for (int i = 0; i < 20; ++i) {
        if (i > 0) {
            // Delimiter
            if (i%5 != 0)
                std::cout << ' ';   
            else
                std::cout << std::endl;
        }
        std::cout << realRange(gen);
    }
    std::cout << std::endl;

    return 0;
}
