#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char *substr();
char *grey();

int main(void) {
    int t;
    scanf("%d", &t);

    printf("%d", t);

    printf("%s", grey(2));
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

char *grey(int k) {
    char *abc = "abcdifghijklmnopqrstuvwxyz";
    char *g = "a";
    for (int i = 1; i < k; i++) {
        char *temp = substr(abc, i, i + 1);
        char dest[strlen(g)];
        strcpy(dest, g);
        strcat(g, temp);
        strcat(g, dest);
    }
    return g;
}
