#include <stdio.h>
#include <string.h>

#define MAXLEN 1000  // 最多 1000 位十进制

int result[MAXLEN], len;

void mul2_add2() {
    int carry = 0;
    for (int i = 0; i < len; i++) {
        int t = result[i] * 2 + carry;
        result[i] = t % 10;
        carry = t / 10;
    }
    while (carry) {
        result[len++] = carry % 10;
        carry /= 10;
    }
    result[0] += 2;
    int i = 0;
    while (result[i] >= 10) {
        result[i] -= 10;
        result[++i] += 1;
        if (i == len) len++;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    // 初始值 2
    memset(result, 0, sizeof(result));
    result[0] = 2;
    len = 1;

    for (int i = 0; i < n; i++) {
        mul2_add2();
    }

    for (int i = len - 1; i >= 0; i--) {
        putchar('0' + result[i]);
    }
    putchar('\n');

    return 0;
}