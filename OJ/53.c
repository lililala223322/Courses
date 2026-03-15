#include <stdio.h>
#include <stdint.h>

typedef unsigned long long u64;

static u64  M;     
static int  topbit;   
static int  g_x;    

void build_mask(int x)
{
    g_x = x;
    M = 0;
    for (int p = x; p <= 63; p += x) M |= 1ULL << (p - 1);
    topbit = 63 - __builtin_clzll(M) + 1;
}

inline int special_value(u64 num)
{
    return __builtin_popcountll(num & M);
}

u64 cumulative_value(u64 num)
{
    u64 T = 1ULL << topbit;
    u64 full = num / T;
    u64 rem  = num % T;

    u64 ones_per_cycle = (u64)__builtin_popcountll(M) * (T >> 1);
    u64 ans = full * ones_per_cycle;

    if (rem)
    {
        for (int p = g_x; p <= topbit; p += g_x)
        {
            u64 bit = 1ULL << (p - 1);
            ans += (rem + 1) / (bit << 1) * bit;
            u64 r = (rem + 1) % (bit << 1);
            if (r > bit) ans += r - bit;
        }
    }
    return ans;
}

u64 max_economic(u64 k, int x)
{
    build_mask(x);
    u64 lo = 1, hi = 1;
    while (cumulative_value(hi) <= k) hi <<= 1;

    u64 best = 0;
    while (lo <= hi)
    {
        u64 mid = (lo + hi) >> 1;
        if (cumulative_value(mid) <= k) { best = mid; lo = mid + 1; }
        else                            { hi = mid - 1; }
    }
    return best;
}

int main(void)
{
    u64 k;
    int x;
    if (scanf("%llu %d", &k, &x) != 2) return 0;
    printf("%llu\n", max_economic(k, x));
    return 0;
}