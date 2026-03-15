#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int n;
char s[10000];

// 计算使得最长连续段 <= max_len 所需的最小翻转次数
int min_flips(int max_len) {
    int flips = 0;
    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n && s[j] == s[i]) j++;
        int len = j - i;
        if (len > max_len) {
            int seg = len / (max_len + 1);
            flips += seg;
        }
        i = j;
    }
    return flips;
}

int main() {
    scanf("%s", s);
    n = strlen(s);
    int numOps;
    scanf("%d", &numOps);

    int left = 1, right = n;
    int ans = n;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (min_flips(mid) <= numOps) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}