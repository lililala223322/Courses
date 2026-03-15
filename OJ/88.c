#include <stdio.h>

#define MAX 100
#define IDX(i, j) ((i)*(m)+(j))  

int n, m;
char grid[MAX][MAX + 1];       
char vis[MAX * MAX];            

static const int dx[4] = {-1, 1, 0, 0};
static const int dy[4] = {0, 0, -1, 1};

int stackX[MAX * MAX];
int stackY[MAX * MAX];

void dfs(int sx, int sy) {
    int top = 0;
    stackX[top] = sx;
    stackY[top] = sy;
    vis[IDX(sx, sy)] = 1;

    while (top >= 0) {
        int x = stackX[top];
        int y = stackY[top];
        --top;

        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (grid[nx][ny] == '0' || vis[IDX(nx, ny)]) continue;

            vis[IDX(nx, ny)] = 1;
            ++top;
            stackX[top] = nx;
            stackY[top] = ny;
        }
    }
}

int main(void) {
    if (scanf("%d %d", &n, &m) != 2) return 0;
    for (int i = 0; i < n; ++i) scanf("%s", grid[i]);

    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] != '0' && !vis[IDX(i, j)]) {
                dfs(i, j);
                ++cnt;
            }
        }
    }
    printf("%d\n", cnt);
    return 0;
}