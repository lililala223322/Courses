#include <stdio.h>

int dp[11][11];

void init(void) {
    for (int j = 0; j <= 10; ++j) dp[0][j] = 1;
    for (int i = 1; i <= 10; ++i) dp[i][1] = 1;

    for (int i = 1; i <= 10; ++i)
        for (int j = 2; j <= 10; ++j)
            dp[i][j] = (i >= j) ? dp[i][j - 1] + dp[i - j][j]
                                : dp[i][j - 1];
}

int main(void) {
    init();

    int t;
    if (scanf("%d", &t) != 1) return 0;

    int m[20], n[20], ans[20];
    for (int i = 0; i < t; ++i) {
        scanf("%d %d", &m[i], &n[i]);
        ans[i] = dp[m[i]][n[i]];
    }
    for (int i = 0; i < t; ++i)
        printf("%d\n", ans[i]);

    return 0;
}