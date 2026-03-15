#include <stdio.h>

#define MAXT 1000
#define MAXN 100

int max(int a, int b) { return a > b ? a : b; }

int main(void) {
    int T, N;
    int t[MAXN + 1], v[MAXN + 1];
    int dp[MAXT + 1] = {0};          // 初始全 0

    scanf("%d %d", &T, &N);
    for (int i = 1; i <= N; ++i)
        scanf("%d %d", &t[i], &v[i]);

    // 0/1 背包一维倒序
    for (int i = 1; i <= N; ++i)
        for (int j = T; j >= t[i]; --j)
            dp[j] = max(dp[j], dp[j - t[i]] + v[i]);

    printf("%d\n", dp[T]);
    return 0;
}