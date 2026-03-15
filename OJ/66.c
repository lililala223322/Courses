#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char buf[1024];
    if (!fgets(buf, sizeof(buf), stdin)) return 0;

    int cnt[2] = {0};          // cnt[0] 偶数，cnt[1] 奇数
    char *p = buf;
    while (*p) {
        if (*p == ',' || *p == '\n') { ++p; continue; }
        int x = strtol(p, &p, 10);
        ++cnt[x & 1];
    }

    printf("%d\n", cnt[0] < cnt[1] ? cnt[0] : cnt[1]);
    return 0;
}