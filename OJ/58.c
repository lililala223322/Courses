#include <stdio.h>
#define MOD 1000000007
#define MAXN 1005
#define MAXK 1005

int dp[MAXN][MAXK];
int S[MAXN][MAXK];   /* 前缀和数组 */

int main(void){
    int n, k;
    if(scanf("%d %d", &n, &k) != 2) return 0;

    /* 初始化边界：0 个数字只有 0 个逆序对 */
    dp[0][0] = 1;
    for(int j = 0; j <= k; ++j) S[0][j] = 1;

    for(int i = 1; i <= n; ++i){
        for(int j = 0; j <= k; ++j){
            /* dp[i][j] = S[i-1][j] - S[i-1][j-i]  (j>=i) */
            int tmp = S[i-1][j];
            if(j >= i) tmp = (tmp - S[i-1][j - i] + MOD) % MOD;
            dp[i][j] = tmp;

            /* 更新前缀和 S[i][j] */
            S[i][j] = tmp;
            if(j > 0) S[i][j] = (S[i][j] + S[i][j - 1]) % MOD;
        }
    }

    printf("%d\n", dp[n][k]);
    return 0;
}