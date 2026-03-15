#include <stdio.h>
#define MAXN 40000 + 10
 
int phi[MAXN],ans[MAXN];
 
void euler()
{
    ans[1] = 1;
    for (int i = 1; i <= MAXN; i++)
    {
        int res = i, n = i;
        for (int j = 2; j * j <= n; j++)
        {
            if (!(n % j))
                res = res * (j - 1) / j;
            while (!(n % j))
                n /= j;
        }
        if (n > 1)
            res = res * (n - 1) / n;
        phi[i] = res;
    }
    for (int i = 2; i <= MAXN; i++)
        for (int j = 1; j < i; j++)
            ans[i] += phi[j];
}
 
int main(int argc, char const *argv[])
{
    euler();
    int n;
    while (~scanf("%d", &n))
    {
        if (n == 1) //方阵大小为1*1时特判，此时队列中只有自己，输出0
        {
            puts("0");
            continue;
        }
        printf("%d\n", 2 * ans[n] + 1);
    }
    return 0;
}