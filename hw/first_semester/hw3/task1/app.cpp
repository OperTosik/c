#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char *DIGITS = "0123456789ABCDEF";

int txt2int(const char *txt, int base = 10);
int find(char c, const char* line);

int main(void) {
    while (true) {
        char txt[128];
        printf("Enter the base:\n");
        fgets(txt, 126, stdin);
        int b = txt2int(txt, 10);
        if (b == 0) break;
        printf("Enter the text of the number:\n");
        fgets(txt, 126, stdin);
        int n = txt2int(txt, b);
        printf("n = %d\n", n);
    }
    return 0;
}

int txt2int(const char *txt, int base /*= 10*/) {
    int l = (int)strlen(txt);
    if (l == 0) return 0;
    int s = 1;
    const char *beg = txt;
    if (txt[0] == '-') {
        s = (-1);
        ++beg;
    }
    else if (txt[0] == '+') {
        ++beg;
        --l;
    }
    int n = 0;
    for (int i = 0; i < l; ++i) {
        char c = beg[i];
        if (isalpha(c)) {
            c = char(toupper(c));
        }
        int d = find(c, DIGITS);
        if (d < 0) break;
        n = n * base + d;
    }
    return n * s;
}

int find(char c, const char* line) {
    int i = 0;
    while(line[i] != 0) {
        if (line[i] == c) return i;
        ++i;
    }
    return -1;
}