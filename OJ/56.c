#include <stdio.h>
#include <string.h>

int n;
long long ans;
unsigned char wall[2][20];   /* 0=空 1=占 */

/* 检查在 (r,c) 放形号 t 是否合法 */
static int canput(int r,int c,int t){
    static const int dr[7][3] = {     /* 每种砖相对坐标 */
        {0,1,0},   /* 0 : 2x1 竖 */
        {0,0,1},   /* 1 : 2x1 横上 */
        {1,1,1},   /* 2 : 2x1 横下 */
        {0,1,1},   /* 3 : L 旋转1 */
        {0,0,1},   /* 4 : L 旋转2 */
        {0,1,0},   /* 5 : L 旋转3 */
        {0,0,0}    /* 6 : L 旋转4 */
    };
    static const int dc[7][3] = {
        {0,0,1},   /* 竖 */
        {0,1,1},   /* 横上 */
        {0,1,1},   /* 横下 */
        {0,0,1},
        {0,1,0},
        {0,0,-1},
        {0,1,0}
    };
    for(int i=0;i<3;i++){
        int rr = r + dr[t][i];
        int cc = c + dc[t][i];
        if(cc<0||cc>=n||rr<0||rr>=2) return 0;
        if(wall[rr][cc]) return 0;
    }
    return 1;
}

/* 放置/撤销 操作 */
static void apply(int r,int c,int t,int v){
    static const int dr[7][3] = {{0,1,0},{0,0,1},{1,1,1},{0,1,1},{0,0,1},{0,1,0},{0,0,0}};
    static const int dc[7][3] = {{0,0,1},{0,1,1},{0,1,1},{0,0,1},{0,1,0},{0,0,-1},{0,1,0}};
    for(int i=0;i<3;i++){
        int rr = r + dr[t][i];
        int cc = c + dc[t][i];
        wall[rr][cc] = v;
    }
}

/* 回溯主过程 */
static void dfs(int r,int c){
    if(c==n){ dfs(0,c-1); return; }   /* 换列 */
    if(r==2){ dfs(0,c+1); return; }   /* 下一列 */
    if(wall[r][c]){ dfs(r+1,c); return; } /* 已占 */

    /* 6 种砖依次试 */
    for(int t=0;t<6;t++){
        if(!canput(r,c,t)) continue;
        apply(r,c,t,1);
        dfs(r+1,c);
        apply(r,c,t,0);
    }
    /* 如果啥也放不下，就自然退回去 */
}

int main(){
    if(scanf("%d",&n)!=1) return 0;
    memset(wall,0,sizeof(wall));
    ans = 0;
    dfs(0,0);
    printf("%lld\n", ans);
    return 0;
}