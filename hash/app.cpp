#include <iostream>

int main() {
    const int n = 5, m = 4;
    int elem = 0, perenos = 0;
    int max = (n > m) ? n : m;
    char arr[n + 1] = {'+', '1', '2', '3', '4', '5'};
    char a[m + 1] = {'+', '2', '3', '4', '5'};
	char* array;
	array = new char[max+2];
    array[1] = 0;
    array[0] = '+';
    for(int i = n, k = m, j = max; i >= 0 && k >= 0; i--, k--, j--) { //quantity of iterations = max(n, m)
        if (i <= 0) {
            i = 0;
            elem = a[k] - 48  + perenos;
            perenos = 0;
            array[j] = elem + 48;
            continue;
        } 
        if (k <= 0) {
            k = 0;
            elem = arr[i] - 48 + perenos;
            perenos = 0;
            array[j] = elem + 48;
            continue;
        }
        elem = arr[i] - 48 + a[k] - 48  + perenos;
        perenos = elem / 10;
        elem = elem % 10;
        array[j] = elem+48;
    }

    std::cout << "Answer must be +14690" << std::endl;

    for (int i = 0; i < max + 2; ++i) {
        std::cout << array[i];
    }
    std::cout << std::endl;
    return 0;
}


