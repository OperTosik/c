#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* substr();
char* revstr();
char* cycle();

int main(void) {
    int t;
    scanf("%d", &t);
    for(int i = 0; i < t; i++){
        char str[2000];
        scanf("%s", str);
        cycle(str);
    }
    return 0;
}

char *cycle(const char *src) {
    for(long unsigned int i = 0; i < strlen(src); i++) {
        char *temp = substr(src, 0, strlen(src) - i);
        char dest[2000];
        strcpy(dest, temp);
        if (strcmp(temp, revstr(dest)) == 0) {
            printf("%s \n", temp);
            break;
        }
    }
    return 0;
}

char* substr(const char *src, int m, int n) {
    int len = n - m;
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
    for (int i = m; i < n && (*(src + i) != '\0'); i++) {
        *dest = *(src + i);
        dest++;
    }
    *dest = '\0';
    return dest - len;
}

char* revstr(char* str) {
    int i, len;
    len = strlen(str);
    for (i = 0; i < len/2; i++) {
        str[i] = str[i] ^ str[len - i - 1];
        str[len - i - 1] = str[i] ^ str[len - i - 1];
        str[i] = str[i] ^ str[len - i - 1];
    }  
    return str;
}