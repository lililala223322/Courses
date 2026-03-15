#include <stdio.h>
#include <stdbool.h>

typedef unsigned long long u64;

bool is_pal_u64(u64 x)
{
    if (x == 0) return true;
    u64 rev = 0, orig = x;
    while (x) { rev = rev * 10 + x % 10; x /= 10; }
    return rev == orig;
}

u64 pow10[20];
int    cnt;
u64    pal[200000];

void make_pal(u64 half, int len)
{
    u64 t = half, rev = 0;
    int tmp = len; while (tmp--) { rev = rev * 10 + t % 10; t /= 10; }
    pal[cnt++] = half * pow10[len] + rev;          
    if (len) {
        rev = 0;
        t = half / 10;
        tmp = len - 1; while (tmp--) { rev = rev * 10 + t % 10; t /= 10; }
        pal[cnt++] = half * pow10[len - 1] + rev;  
    }
}

void build_pal_root(void)
{
    pow10[0] = 1;
    for (int i = 1; i <= 18; ++i) pow10[i] = pow10[i - 1] * 10;
    for (int len = 0; len <= 9; ++len) {
        u64 from = (len == 0) ? 0 : pow10[len - 1];
        u64 to   = pow10[len] - 1;
        for (u64 h = from; h <= to; ++h) make_pal(h, len);
    }
}

int main(void)
{
    build_pal_root();

    u64 L, R;
    if (scanf("%llu %llu", &L, &R) != 2) return 0;

    int ans = 0;
    for (int i = 0; i < cnt; ++i) {
        u64 r   = pal[i];
        u64 sq  = r * r;
        if (sq >= L && sq <= R && is_pal_u64(sq)) ++ans;
    }
    printf("%d\n", ans);
    return 0;
}