#include <iostream>

int add(int x, int y) {
    return x + y;
}

int operation(int(*op)(int, int), int a, int b)
{
    return op(a, b);
}

int main()
{
    int a = 10;
    int b = 6;
    int result = operation(add, a, b);
    std::cout << "result: " << result << std::endl;

    return 0;
}