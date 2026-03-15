#include <stdio.h>
#include <string.h>

void computeNext(const char *t, int *next, int m) {
    int i = 0, j = -1;
    next[0] = -1;
    while (i < m - 1) {
        if (j == -1 || t[i] == t[j]) {
            i++;
            j++;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}

int KMP(const char *s, const char *t) {
    int n = strlen(s);
    int m = strlen(t);
    int next[m];
    computeNext(t, next, m);

    int i = 0, j = 0;
    int count = 0; 
    while (i < n) {
        count++; 
        if (j == -1 || s[i] == t[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
        if (j == m) {
            printf("模式串位置： %d\n", i - j);
            j = next[j - 1] + 1; 
        }
    }
    printf("比较次数: %d\n", count);
    return -1; 
}

int main() {
    const char *s = "abcaabbabcabaacbacba";
    const char *t = "abcabaa";
    KMP(s, t);
    return 0;
}