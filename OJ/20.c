#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define lc (o<<1)
#define rc (o<<1|1)

int N, M;
int ans[MAXN];          // 存每天答案

typedef struct {
    long long y, x;
} Frac;

Frac maxv[MAXN << 2];

Frac maxFrac(Frac a, Frac b) {
    if (a.y * b.x >= b.y * a.x) return a;
    return b;
}

int cmpFrac(Frac a, Frac b) {
    return a.y * b.x > b.y * a.x;
}

void build(int o, int l, int r) {
    maxv[o].y = 0; maxv[o].x = 1;
    if (l == r) return;
    int m = (l + r) >> 1;
    build(lc, l, m);
    build(rc, m + 1, r);
}

void update(int o, int l, int r, int pos, Frac v) {
    if (l == r) {
        maxv[o] = v;
        return;
    }
    int m = (l + r) >> 1;
    if (pos <= m) update(lc, l, m, pos, v);
    else          update(rc, m + 1, r, pos, v);
    maxv[o] = maxFrac(maxv[lc], maxv[rc]);
}

int query(int o, int l, int r, Frac lim) {
    if (!cmpFrac(maxv[o], lim)) return 0;
    if (l == r) return 1;
    int m = (l + r) >> 1;
    int left = query(lc, l, m, lim);
    Frac newlim = maxFrac(lim, maxv[lc]);
    int right = query(rc, m + 1, r, newlim);
    return left + right;
}

int main() {
    scanf("%d %d", &N, &M);
    build(1, 1, N);
    for (int i = 1; i <= M; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        Frac v = {y, x};
        update(1, 1, N, x, v);
        Frac zero = {0, 1};
        ans[i] = query(1, 1, N, zero);
    }
    // 统一输出
    for (int i = 1; i <= M; ++i)
        printf("%d\n", ans[i]);
    return 0;
}