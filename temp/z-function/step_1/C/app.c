#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *substr();
void entry();
int cmp();
int get_size();

int main(void) {
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        char t[50000];
        char p[100];
        scanf("%s", t);
        scanf("%s", p);
        int size_mas = get_size(t, p);
        printf("%d\n", size_mas);
        if (size_mas == 0) {
            printf(" ");
        }
        else {
            entry(t, p);
            }
        printf("\n");
        }
        return 0;
}

void entry(const char *t, const char *p) {
    int len = strlen(p);
    for (long unsigned int i = 0; i < strlen(p) - len; i++) {
        if (cmp(substr(t, i, i + len), p) == 1) {
            printf("%ld", i);
        }
    }
}

int get_size(const char *t, const char *p) {
    int len = strlen(p);
    int sum = 0;
    for (long unsigned int i = 0; i < strlen(p) - len; i++) {
        if (cmp(substr(t, i, i + len), p) == 1) {
           sum++;
        }
    }
    return sum;
}

int cmp(const char *str1, const char *str2) {
    for (long unsigned int i = 0; i < strlen(str1); i++) {
        if (strcmp(substr(str2, i, i + 1), "?") == 0) {
            continue;
        }
        else {
            if (strcmp(substr(str1, i, i + 1), substr(str2, i, i + 1)) == 1) {
                return 0;
            }
        }
    }
    return 1;
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