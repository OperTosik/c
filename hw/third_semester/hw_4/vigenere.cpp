#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cassert>
#include "utf8/utf8.h"

typedef int unicodeChar;
typedef std::basic_string<unicodeChar> unicodeString;

int readInputData(unicodeString&);
void encode(
    int,
    int,
    unicodeString&,
    unicodeString&
);

void decode(
    unicodeString&,
    unicodeString&
);

int main() {
    unicodeString key;
    unicodeString content;

    //readingInputDatas
    std::cout << "Enter the key for Vigenere's cipher: " << std::endl;
    int lenKey = readInputData(key);
    std::cout << "Enter the text: " << std::endl;
    int lenContent = readInputData(content);

    //encoding
    std::cout << "Encoding text: " << std::endl;
    encode(lenKey, lenContent, key, content);
    for (auto i: content) {
        output_utf8(std::cout, i);
    }
    std::cout << std::endl;

    //decoding
    std::cout << "Decoding text: " << std::endl;
    decode(key, content);
    for (auto i: content) {
        output_utf8(std::cout, i);
    }
    std::cout << std::endl;
    
    return 0;
}

int readInputData(unicodeString& s) {
    int state = 0;
    int len = 0;
    while (true) {
        bool readFails = false;
        unicodeChar c;
        c = unicodeChar(get_utf8_code_point(std::cin, readFails));
        if (readFails || c == 10) {
            break;
        }
        bool letter = isRussianLetter(c);
        if (letter) {
            s += unicodeChar(toLowerLetter(c));
        }
        
        ++len;
    }
    return len;
}

void encode(
    int lenKey,
    int lenContent,
    unicodeString& key,
    unicodeString& content
) {
    for (int i = 0; i < lenContent; ++i) {
        int m = i % (lenKey - 1);
        int shift = key[m] - 0x430;
        if (content[i] + shift > 0x44F) {
            shift -= 33;
        }
        content[i] += shift;
    }
}

void decode(
    unicodeString& key,
    unicodeString& content
) {
    int lenKey = key.size();
    int lenContent = content.size();
    for (int i = 0; i < lenContent; ++i) {
        int m = i % (lenKey - 1);
        int shift = key[m] - 0x430;
        if (content[i] - shift < 0x430) {
                shift -= 33;
        }
        content[i] -= shift;
    }
}