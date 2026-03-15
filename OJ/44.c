#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

const char *s;
int  n, K;

int ok(int lim)
{
    int cnt = 1;         
    long long cur = 0;    
    for (int i = 0; i < n; ++i) {
        int d = s[i] - '0';
        if (d > K) return 0;         
        cur = cur * 10 + d;
        if (cur > K) {                 
            ++cnt;
            cur = d;               
            if (cnt > lim) return 0;   
        }
    }
    return 1;
}

int main(void)
{
    static char buf[200010];
    if (!fgets(buf, sizeof(buf), stdin)) return 0;

    char *p = strtok(buf, " \r\n");
    s = p;
    n = strlen(s);
    p = strtok(NULL, " \r\n");
    K = atoi(p);

    if (K < 10) {
        for (int i = 0; i < n; ++i)
            if (s[i] - '0' > K) { puts("-1"); return 0; }
    }

    int lo = (n - 1) / (K < 10 ? 1 : 9) + 1; 
    int hi = n;                               
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (ok(mid)) hi = mid;
        else         lo = mid + 1;
    }
    printf("%d\n", ok(lo) ? lo : -1);
    return 0;
}