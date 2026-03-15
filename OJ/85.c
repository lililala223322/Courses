#include <stdio.h>

#define MAXN 205
#define INF 0x3f3f3f3f

int N, S, T;
int E[MAXN];
int dist[MAXN];      
int q[MAXN], head, tail;

int main(void) {
    scanf("%d %d %d", &N, &S, &T);
    for (int i = 1; i <= N; ++i) scanf("%d", &E[i]);

    if (S == T) {
        puts("0");
        return 0;
    }

    for (int i = 1; i <= N; ++i) dist[i] = -1;
    head = 0;
    tail = 1;
    q[0] = S;
    dist[S] = 0;

    while (head < tail) {
        int u = q[head++];
        int step = dist[u];
        int jump = E[u];

        // 向上跳
        int v = u + jump;
        if (v <= N && dist[v] == -1) {
            dist[v] = step + 1;
            if (v == T) {
                printf("%d\n", dist[v]);
                return 0;
            }
            q[tail++] = v;
        }

        // 向下跳
        v = u - jump;
        if (v >= 1 && dist[v] == -1) {
            dist[v] = step + 1;
            if (v == T) {
                printf("%d\n", dist[v]);
                return 0;
            }
            q[tail++] = v;
        }
    }

    puts("-1");
    return 0;
}