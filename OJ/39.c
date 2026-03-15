#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXR 10000
#define INF  0x3f3f3f3f

int trans[MAXR][3];
int transCnt = 0;
long long net[MAXR];
int ans;

/* ---------- 1. 读入 & 解析 ---------- */
void readTransactions(void) {
    char *line = NULL;
    size_t len = 0, cap = 0;
    int c;
    while ((c = getchar()) != EOF && c != '\n' && c != 0) {
        if (len + 1 >= cap) {
            cap = cap ? cap * 2 : 1024;
            line = realloc(line, cap);
        }
        line[len++] = (char)c;
    }
    if (line == NULL) return;
    line[len] = '\0';

    char *s = line;
    if (*s == '{') s++;
    char *t = line + len - 1;
    while (t > s && *t != '}') t--;
    *t = '\0';

    char *row = strtok(s, "},{");
    while (row) {
        while (*row == '{') row++;
        char *e = row + strlen(row) - 1;
        while (e > row && *e == '}') *e-- = '\0';
        int x, y, v;
        if (sscanf(row, "%d,%d,%d", &x, &y, &v) == 3) {
            trans[transCnt][0] = x;
            trans[transCnt][1] = y;
            trans[transCnt][2] = v;
            transCnt++;
        }
        row = strtok(NULL, "},{");
    }
    free(line);
}

/* ---------- 2. DFS 求最少次数 ---------- */
struct Node { long long v; } a[MAXR];
int m;

void dfs(int pos, int cnt) {
    if (cnt >= ans) return;
    while (pos < m && a[pos].v == 0) pos++;
    if (pos == m) { ans = cnt; return; }
    if (a[pos].v < 0) {                      // 负债人
        for (int i = pos + 1; i < m; ++i) {
            if (a[i].v > 0) {
                long long g = -a[pos].v < a[i].v ? -a[pos].v : a[i].v;
                a[pos].v += g;  a[i].v -= g;
                dfs(pos, cnt + 1);
                a[pos].v -= g;  a[i].v += g;
                if (a[pos].v == 0) break;
            }
        }
    } else {                                 // 债权人
        for (int i = pos + 1; i < m; ++i) {
            if (a[i].v < 0) {
                long long g = a[pos].v < -a[i].v ? a[pos].v : -a[i].v;
                a[pos].v -= g;  a[i].v += g;
                dfs(pos, cnt + 1);
                a[pos].v += g;  a[i].v -= g;
                if (a[pos].v == 0) break;
            }
        }
    }
}

/* ---------- 3. main ---------- */
int main(void) {
    readTransactions();

    /* 计算净额 */
    int maxId = -1;
    for (int i = 0; i < transCnt; ++i) {
        int x = trans[i][0], y = trans[i][1], v = trans[i][2];
        net[x] += v;
        net[y] -= v;
        if (x > maxId) maxId = x;
        if (y > maxId) maxId = y;
    }

    /* 抽出非零净额 */
    m = 0;
    for (int i = 0; i <= maxId; ++i)
        if (net[i] != 0) { a[m].v = net[i]; m++; }

    if (m == 0) { puts("0"); return 0; }

    ans = m - 1;
    dfs(0, 0);
    printf("%d\n", ans);
    return 0;
}