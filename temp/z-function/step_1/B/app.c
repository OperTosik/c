#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *preffix();
char *suffix();
int string();
char *substr();

int main(void) {
    int t, sum = 0;
    char s[500];
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        scanf("%s", s);
        sum += string(s);
    }
    printf("%d\n", sum);
    return 0;
}

int string(const char *s) {
    char *sub_str;
    int sum = 0;
    for (long unsigned int i = 0; i < strlen(s); i++) {
        for (long unsigned int j = 0; j < strlen(s); j++) {
            int flag = 0;
            sub_str = substr(s, j, j + (i + 1));
            if (strcmp(sub_str, preffix(s, i + 1)) == 0) {flag++;}
            if (strcmp(sub_str, suffix(s, i + 1)) == 0) {flag++;}
            if (flag == 1) {sum++;}
        }
    }
    return sum;
}

char *preffix(const char *s, int len) {
    return substr(s, 0, len);
}

char *suffix(const char *s, int len) {
    return substr(s, strlen(s) - len, strlen(s));
}

char *substr(const char *src, int m, int n) {
    int len = n - m;
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
    for (int i = m; i < n && (*(src + i) != '\0'); i++) {
        *dest = *(src + i);
        dest++;
    }
    *dest = '\0';
    return dest - len;
}