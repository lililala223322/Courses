#include <stdio.h>

int rotateDigit(int d) {
    switch (d) {
        case 0: case 1: case 8: return d;
        case 2: return 5;
        case 5: return 2;
        case 6: return 9;
        case 9: return 6;
        default: return -1;   // 不可旋转
    }
}

int isGood(int n) {
    int orig = n;
    int rev  = 0;   // 旋转后的真正数值
    int tmp  = n;
    int diff = 0;

    while (tmp) {
        int d = tmp % 10;
        int rd = rotateDigit(d);
        if (rd == -1) return 0;      // 含 3/4/7
        if (rd != d) diff = 1;    // 至少有一位会变
        rev = rev * 10 + rd;
        tmp /= 10;
    }
    /* 此时 rev 是“倒序旋转”结果，必须再倒回来 */
    int realRev = 0, t = rev;
    while (t) {
        realRev = realRev * 10 + t % 10;
        t /= 10;
    }
    return diff && realRev != orig;
}

int main(void) {
    int n, cnt = 0;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 1; i <= n; ++i)
        if (isGood(i)) ++cnt;
    printf("%d\n", cnt);
    return 0;
}