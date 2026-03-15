#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define FAC9 362880

char goal[] = "123804765";

/* 9 个位置各自的邻居个数 + 邻居下标 */
int neighbor[9][5] = {
    {2, 1, 3},      // 0
    {3, 0, 2, 4},   // 1
    {2, 1, 5},      // 2
    {3, 0, 4, 6},   // 3
    {4, 1, 3, 5, 7},// 4
    {3, 2, 4, 8},   // 5
    {2, 3, 7},      // 6
    {3, 4, 6, 8},   // 7
    {2, 5, 7}       // 8
};

int cantor(const char *s) {
    int code = 0;
    for (int i = 0; i < 9; ++i) {
        int cnt = 0;
        for (int j = i + 1; j < 9; ++j)
            if (s[j] < s[i]) ++cnt;
        static const int fact[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
        code += cnt * fact[8 - i];
    }
    return code;
}

char q[FAC9][10]; 
int dist[FAC9];
int head, tail;

bool vis[FAC9];

int main(void) {
    char start[10];
    scanf("%9s", start);

    if (strcmp(start, goal) == 0) {
        puts("0");
        return 0;
    }

    head = 0;
    tail = 1;
    strcpy(q[0], start);
    int startCode = cantor(start);
    dist[startCode] = 0;
    vis[startCode] = true;

    int targetCode = cantor(goal);
    int ans = -1;

    while (head < tail) {
        char *cur = q[head];
        int  d    = dist[cantor(cur)];
        int  z    = strchr(cur, '0') - cur;  

        for (int i = 1; i <= neighbor[z][0]; ++i) {
            int nz = neighbor[z][i];
            char nxt[10];
            strcpy(nxt, cur);
            nxt[z] = nxt[nz];
            nxt[nz] = '0';

            int code = cantor(nxt);
            if (vis[code]) continue;
            vis[code] = true;
            dist[code] = d + 1;
            strcpy(q[tail], nxt);
            ++tail;

            if (code == targetCode) {
                ans = d + 1;
                break;
            }
        }
        ++head;
    }

    printf("%d\n", ans);
    return 0;
}