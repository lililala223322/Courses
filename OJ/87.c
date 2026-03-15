#include <stdio.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    static int row[100] = {0}, col[100] = {0};   /* 最多 100 行/列 */
    char s[101];                                   /* 读入一行 */

    for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        for (int j = 0; j < n; ++j)
            if (s[j] == 'S') {
                ++row[i];
                ++col[j];
            }
    }

    long long happy = 0;
    for (int i = 0; i < n; ++i) happy += row[i] * (row[i] - 1LL) / 2;
    for (int j = 0; j < n; ++j) happy += col[j] * (col[j] - 1LL) / 2;

    printf("%lld\n", happy);
    return 0;
}