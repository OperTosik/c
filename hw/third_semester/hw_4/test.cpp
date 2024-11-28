#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "utf8.h"

typedef int unicodeChar;
// typedef std::basic_string<unicodeChar> unicodeString;

int main() {
    char c = ' ';
    std::cout << int(c) << std::endl;
    std::cout << std::hex << int(c) << std::endl;

   return 0;
}