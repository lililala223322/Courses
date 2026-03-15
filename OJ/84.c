#include <stdio.h>
#include <stdbool.h>

#define MAXM 15
#define MAXN 15

int m, n;
int maze[MAXM][MAXN];
bool vis[MAXM][MAXN];

int sx, sy, ex, ey;

int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};

int pathX[MAXM * MAXN], pathY[MAXM * MAXN];
int pathLen = 0;

bool found; 

void printPath(void) {
    for (int i = 0; i < pathLen; ++i) {
        printf("(%d,%d)", pathX[i], pathY[i]);
        if (i + 1 < pathLen) printf("->");
    }
    putchar('\n');
}

/* DFS */
void dfs(int x, int y) {
    if (x == ex && y == ey) {   
        printPath();
        found = true;
        return;
    }
    for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (nx < 1 || nx > m || ny < 1 || ny > n) continue;
        if (!maze[nx][ny] || vis[nx][ny]) continue;
        vis[nx][ny] = true;
        pathX[pathLen] = nx;
        pathY[pathLen] = ny;
        ++pathLen;
        dfs(nx, ny);
        /* 回溯 */
        --pathLen;
        vis[nx][ny] = false;
    }
}

int main(void) {
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            scanf("%d", &maze[i][j]);

    scanf("%d %d", &sx, &sy);
    scanf("%d %d", &ex, &ey);

    found = false;
    /* 起点先入路径 */
    pathX[0] = sx;
    pathY[0] = sy;
    pathLen = 1;
    vis[sx][sy] = true;

    dfs(sx, sy);

    if (!found) puts("-1");
    return 0;
}