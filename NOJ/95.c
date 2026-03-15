#include <stdio.h>

int main()
{
    int n;
    scanf("%d",&n);

    int ten = 0 , five = 0 , two = 0 , one = 0;

    while (n >= 10)
    {
        n -= 10;
        ten++;
    }

    while (n >= 5)
    {
        n -= 5;
        five++;
    }

    while (n >= 2)
    {
        n -= 2;
        two++;
    }

    while (n >= 1)
    {
        n -= 1;
        one++;
    }

    if (one)
        printf("1=%d\n",one);
    if (two)
        printf("2=%d\n",two);
    if (five)
        printf("5=%d\n",five);
    if (ten)
        printf("10=%d\n",ten);
    
    

}