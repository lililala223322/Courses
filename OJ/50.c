#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500
#define max(a, b) ((a) > (b) ? (a) : (b))

int gemValues[MAXN];
int prefix[MAXN + 1];
int memo[MAXN][MAXN];
int n;

int sum(int l, int r) {
    return prefix[r + 1] - prefix[l];
}

int dfs(int l, int r) {
    if (l == r) return 0;
    if (memo[l][r] != -1) return memo[l][r];
    int res = 0;
    for (int k = l; k < r; k++) {
        int left_sum = sum(l, k);
        int right_sum = sum(k + 1, r);
        if (left_sum < right_sum) {
            res = max(res, left_sum + dfs(l, k));
        } else if (left_sum > right_sum) {
            res = max(res, right_sum + dfs(k + 1, r));
        } else {
            res = max(res, left_sum + max(dfs(l, k), dfs(k + 1, r)));
        }
    }
    return memo[l][r] = res;
}

int main() {
    char line[1 << 20];
    if (!fgets(line, sizeof(line), stdin)) return 0;
    n = 0;
    for (char *tok = strtok(line, " \t\r\n"); tok; tok = strtok(NULL, " \t\r\n")) {
        gemValues[n++] = atoi(tok);
    }
    prefix[0] = 0;
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + gemValues[i];
    }
    memset(memo, -1, sizeof(memo));
    printf("%d\n", dfs(0, n - 1));
    return 0;
}