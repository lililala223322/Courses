#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *largestNumber(int *cost, int costSize, int target)
{
    char **dp = malloc((target + 1) * sizeof(char *));
    for (int i = 0; i <= target; ++i) {
        dp[i] = malloc(100);
        strcpy(dp[i], "0");
    }
    dp[0][0] = '\0';          /* 空串 */

    for (int i = 1; i <= target; ++i) {
        for (int j = 8; j >= 0; --j) {
            int c = cost[j];
            if (i >= c && strcmp(dp[i - c], "0") != 0) {
                char temp[100];
                sprintf(temp, "%d%s", j + 1, dp[i - c]);

                /* 先缓存长度，避免 strlen 宏冲突 */
                size_t lent = strlen(temp), lend = strlen(dp[i]);
                if (strcmp(dp[i], "0") == 0 ||
                    lent > lend ||
                    (lent == lend && strcmp(temp, dp[i]) > 0))
                    strcpy(dp[i], temp);
            }
        }
    }

    char *res = malloc(100);
    strcpy(res, strcmp(dp[target], "0") == 0 ? "0" : dp[target]);

    for (int i = 0; i <= target; ++i) free(dp[i]);
    free(dp);
    return res;
}

int main(void)
{
    int cost[9], target;
    for (int i = 0; i < 9; ++i) scanf("%d", &cost[i]);
    scanf("%d", &target);
    char *ans = largestNumber(cost, 9, target);
    printf("%s", ans);
    free(ans);
    return 0;
}