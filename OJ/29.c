#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 200010
#define INF 1e100

typedef struct {
    double x, y;
} Point;

Point P[MAXN], tmp[MAXN];  

int cmpX(const void *a, const void *b) {
    double dx = ((Point*)a)->x - ((Point*)b)->x;
    if (dx < 0) return -1;
    if (dx > 0) return 1;
    return 0;
}

/* 计算两点距离平方，避免开方 */
inline double dist2(Point a, Point b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return dx*dx + dy*dy;
}

/* 分治主体，[l, r] 区间已按 x 排好序，返回区间最小距离平方 */
double closestRec(int l, int r) {
    if (r - l <= 3) {
        double best = INF;
        for (int i = l; i <= r; i++)
            for (int j = i + 1; j <= r; j++) {
                double d2 = dist2(P[i], P[j]);
                if (d2 < best) best = d2;
            }
        for (int i = l; i <= r; i++)
            for (int j = i + 1; j <= r; j++)
                if (P[i].y > P[j].y) {
                    Point t = P[i]; P[i] = P[j]; P[j] = t;
                }
        return best;
    }

    int m = (l + r) >> 1;
    double midx = P[m].x;

    double dl = closestRec(l, m);
    double dr = closestRec(m + 1, r);
    double dmin = (dl < dr ? dl : dr);

    int i = l, j = m + 1, k = 0;
    while (i <= m && j <= r)
        tmp[k++] = (P[i].y < P[j].y ? P[i++] : P[j++]);
    while (i <= m) tmp[k++] = P[i++];
    while (j <= r)  tmp[k++] = P[j++];
    for (i = 0; i < k; i++) P[l + i] = tmp[i];

    k = 0;
    for (i = l; i <= r; i++)
        if (fabs(P[i].x - midx) * fabs(P[i].x - midx) < dmin)
            tmp[k++] = P[i];

    for (i = 0; i < k; i++)
        for (j = i + 1; j < k && j < i + 7; j++) {
            double d2 = dist2(tmp[i], tmp[j]);
            if (d2 < dmin) dmin = d2;
        }
    return dmin;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++)
        scanf("%lf%lf", &P[i].x, &P[i].y);

    qsort(P, n, sizeof(Point), cmpX);
    double ans2 = closestRec(0, n - 1);
    printf("%.4f\n", sqrt(ans2));
    return 0;
}