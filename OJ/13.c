#include <stdio.h>

int main(void)
{
    long long K;
    if (scanf("%lld", &K) != 1) return 0;

    long long a = 1, b = 1;          // F(2)=1, F(1)=1
    for (int i = 2; i <= K ; ++i) {
        long long c = a + b;         // 下一个斐波那契数
        b = a;
        a = c;
    }
    printf("%lld %lld\n", b, a);
    return 0;
}