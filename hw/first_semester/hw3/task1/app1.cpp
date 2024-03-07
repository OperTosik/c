#include <stdio.h>

const char *DIGITS = "0123456789ABCDEF";

void int2txt(int n, char *txt, int base = 10);

int main(void) {
    char txt[128];
    int base, n;
    while (true) {
        printf("base:\n");
        if (scanf("%d", &base) < 1) break;
        printf("n: ");
        scanf("%d", &n);
        int2txt(n, txt, base);
        printf("Text representation: %s\n", txt);
    }
    return 0;
}

void int2txt(int n, char *txt, int base /*= 10*/) {
    if (n == 0) {
        txt[0] = '0';
        txt[1] = 0;
    }
    int beg = 0;
    if (n < 0) {
        n = (-n);
        txt[beg] = '-';
        ++beg;
    }
    int pos = 0;
    while(n > 0) {
        int d = n % base;
        txt[pos] = DIGITS[d];
        ++pos;
        n = (n - d) / base;
    }
    txt[pos] = 0;
    //Invert the text
    int i = beg;
    int j = pos - 1;
    while(i < j) {
        char tmp = txt[i];
        txt[i] = txt[j];
        txt[j] = tmp;
        ++i; --j;
    }
}