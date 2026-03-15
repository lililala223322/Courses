#include <stdio.h>
#include <string.h>

int main() {
    char s[100001];
    scanf("%s", s);
    int n = strlen(s);
    int len = n;
    while (len % 2 == 0) {
        int is_pal = 1;
        for (int i = 0; i < len / 2; i++) {
            if (s[i] != s[len - 1 - i]) {
                is_pal = 0;
                break;
            }
        }
        if (is_pal) {
            len /= 2;
        } else {
            break;
        }
    }
    printf("%d\n", len);
    return 0;
}