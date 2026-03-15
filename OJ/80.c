#include <stdio.h>

#define MAXD 10000
#define MAXN 100000

int cntD[MAXD+1];          /* damage==d 的敌人个数 */
int bufH[MAXD+1];          /* 循环缓冲：同档 health 暂存 */
int head[MAXD+1];          /* 缓冲队头指针 */

int main(void)
{
    int power, x;
    /* 1. 读 power */
    if (scanf("%d", &power)!=1) return 0;

    /* 2. 读 damage 行 */
    while (scanf("%d", &x)==1){
        cntD[x]++;
        int c=getchar();
        if (c=='\n'||c==EOF) break;
        ungetc(c,stdin);
    }

    /* 3. 读 health 行，按 damage 从大到小依次把 health 压入对应缓冲 */
    for (int dv=MAXD; dv>0; --dv){
        for (int i=0; i<cntD[dv]; ++i){
            if (scanf("%d", &x)!=1) return 0;
            /* 用 head[dv] 当栈顶，倒序存放，后面弹出时就是原顺序 */
            bufH[dv - head[dv]++] = x;
        }
        int c=getchar();
        if (c=='\n'||c==EOF) break;
        ungetc(c,stdin);
    }

    /* 4. 按 damage 降序，逐个敌人算贡献 */
    long long prefixRounds = 0, ans = 0;
    for (int dv=MAXD; dv>0; --dv){
        while (head[dv]){
            int h = bufH[dv - (--head[dv])];
            long long rounds = (h + power - 1) / power;
            ans += dv * (prefixRounds + rounds);
            prefixRounds += rounds;
        }
    }

    printf("%lld\n", ans);
    return 0;
}