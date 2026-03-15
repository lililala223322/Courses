#include <stdio.h>
#include <string.h>

int main()
{
    char s[100];
    long long int n;
    scanf("%s %lld",s,&n);

    int len = strlen(s);
    long long int half = len; // Fs的调用次数
    while (half < n)
    {
        half *= 2;
    }
    half /= 2;

    while (n > len)
    {
        n -= half;
        n--;
        if (n==0)
            n = half;
        half /= 2;
    }

    printf("%c",s[n-1]);

}