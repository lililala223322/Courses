#include <stdio.h>

int main(void) {
    long long n;

    if (scanf("%lld", &n) != 1) return 0;

    long long speed = 1;   // 当前速度
    long long left  = n;   // 剩余需要下载的量
    int       ans   = 0;   // 已用分钟数

    while (left > 0) {
        if (left > speed) {
            // 加倍速度
            speed *= 2;
            ans++;
        } else {
            // 直接下载完
            ans++;
            break;
        }
    }
    printf("%d\n", ans);
    return 0;
}