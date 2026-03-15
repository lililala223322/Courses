#include <stdio.h>
#define MOD 1000000007

int main(void){
    static const int dx[8] = {-2,-2,-1,-1,1,1,2,2};
    static const int dy[8] = {-1,1,-2,2,-2,2,-1,1};
    /* 数字 0~9 的坐标 */
    static const int cx[10] = {3,0,0,0,1,1,1,2,2,2};
    static const int cy[10] = {1,0,1,2,0,1,2,0,1,2};

    /* 邻接表：head[u] 初值必须为 -1 */
    static int head[10], to[80], nxt[80], tot;
    for(int u = 0; u < 10; ++u) head[u] = -1;
    #define addedge(u,v) (to[tot]=v, nxt[tot]=head[u], head[u]=tot++)

    /* 建单向马步边 */
    for(int u = 0; u < 10; ++u){
        for(int d = 0; d < 8; ++d){
            int nx = cx[u] + dx[d];
            int ny = cy[u] + dy[d];
            int v = -1;
            if(nx==0&&ny==0) v=1;
            else if(nx==0&&ny==1) v=2;
            else if(nx==0&&ny==2) v=3;
            else if(nx==1&&ny==0) v=4;
            else if(nx==1&&ny==1) v=5;
            else if(nx==1&&ny==2) v=6;
            else if(nx==2&&ny==0) v=7;
            else if(nx==2&&ny==1) v=8;
            else if(nx==2&&ny==2) v=9;
            else if(nx==3&&ny==1) v=0;
            if(v != -1) addedge(u,v);
        }
    }

    int n;
    if(scanf("%d",&n)!=1) return 0;

    /* f[u][k] 滚动数组，k 最多到 n-1，n<=1000 足够 */
    static long long f[10][1001];
    for(int u = 0; u < 10; ++u) f[u][0] = 1;

    for(int k = 1; k < n; ++k){
        for(int u = 0; u < 10; ++u){
            f[u][k] = 0;
            for(int e = head[u]; e != -1; e = nxt[e]){
                int v = to[e];
                f[u][k] = (f[u][k] + f[v][k-1]) % MOD;
            }
        }
    }

    long long ans = 0;
    for(int u = 0; u < 10; ++u) ans = (ans + f[u][n-1]) % MOD;
    printf("%lld\n", ans);
    return 0;
}