#include <stdio.h>
#include <string.h>

int func(int num, int n)
{
    while (num > 0) {
        if (--n == 0)
            return num%10;
        num /= 10;
    }
    return -1;
}

int main() {
    int n, num;
    scanf("%d %d", &num, &n);
    printf("%d",func(num,n));

    return 0;
}