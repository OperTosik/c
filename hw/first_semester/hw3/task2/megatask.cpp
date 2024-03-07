#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

const char *DIGITS = "01T";

void int2txt(int n, char *txt, int base = 3);

int main(void) {
    char txt[128];
    int base = 3, n;
    while (true) {
        printf("n: ");
        if (scanf("%d", &n) <= 0)
            break;
        int2txt(n, txt, base);
        printf("Text representation: %s\n", txt);
    }
    return 0;
}

void int2txt(int n, char *txt, int base /*= 3*/) {
    if (n == 0) {
        txt[0] = '0';
        txt[1] = 0;
        return;
    }
    int beg = 0;
    /*
    if (n < 0) {
        n = (-n);
        txt[beg] = '-';
        ++beg;
    }
    */
    int pos = 0;
    while (n != 0) {
        int d = n % base;
        int k = n / base;
        assert(n == k*base + d);
        assert(0 <= abs(d) && abs(d) < base);
        if (d > base/2) {
            d -= base;
            k += 1;
        } else if (d < -base/2) {
            d += base;
            k -= 1;
        }
        assert(n == k*base + d);
        assert(-base/2 <= d && d <= base/2);
        int idx = d;
        if (d < 0)
            idx += base;
        assert(0 <= idx && idx < (int) strlen(DIGITS));
        txt[pos] = DIGITS[idx];
        ++pos;
        // n = (n - d) / base;
        n = k;
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
