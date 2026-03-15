#include <stdio.h>
#include <string.h>

int N;
unsigned char vis[500]; 
int result;

// 深度优先枚举整数划分
void dfs(int remain, int maxp, int sumsq)
{
    if (remain == 0) {
        int i = (N*N - sumsq) >> 1;
        if (!vis[i]) {
            vis[i] = 1;
            ++result;
        }
        return;
    }
    for (int p = 1; p <= maxp && p <= remain; ++p)
        dfs(remain - p, p, sumsq + p*p);
}

int main(void)
{
    scanf("%d", &N);
    dfs(N, N, 0);
    printf("%d\n", result);
    return 0;
}