#include <iostream>
#include <random>

int main() {
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<int> dtRange(1, 500);

    for (int i = 0; i < 10; ++i) {
        unsigned int randNumber = gen();
        std::cout << randNumber << std::endl;
        int dt = dtRange(gen);
        std::cout << "dt = " << dt << std::endl;
    }
    return 0;
}

