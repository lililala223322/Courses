#include<stdio.h>
#include<math.h>

int gcd(int n)
{
    int j=sqrt(n);
    for(int i=2;i<=j;i++){
        if (!(n%i)) return 0;
    }
    return 1;
}

int main()
{
    int a,b,n=0;
    scanf("%d %d",&a,&b);

    for(int i=a;i<=b;i++){
        if (gcd(i)) n++;
    }
    printf("%d",n);
}