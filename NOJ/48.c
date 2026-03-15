#include<stdio.h>

//根据进制计算位数
int digit(int n,int k)
{
    int i=0;
    while( n ){
        n/=k;
        i++;
    }
    return i;
}

//根据传来的数组判断是否回文
int judge(int N1[],int N2[],int n1,int n2)
{
    for (int i = 0; i < (n1/2); i++)
    {
        if (N1[i]!=N1[n1-i-1]) return 0;
    }

    for (int i = 0; i < (n2/2); i++)
    {
        if (N2[i]!=N2[n2-i-1]) return 0;
    }

    return 1;
}

//按位生成数组
int palindrome(int n,int k)
{
    int n1=digit(n,10) ,
        n2=digit(n,k)  ,
        N1[digit(n,10)],
        N2[digit(n,k)] ;

    for (int i = 0 , m=n ; i < n1 ; i++)
    {
        N1[i]=m%10;
        m/=10;
    }

    for (int i = 0 , m=n ; i < n2 ; i++)
    {
        N2[i]=m%k;
        m/=k;
    }

    if (judge(N1,N2,n1,n2)) return n;
    else return 0;
}

int main()
{
    int n , k , sum=0;
    scanf("%d %d",&n,&k);

    if (k<2||k>8) return -1;

    for (int i = 1; i <= n; i++){
        sum += palindrome( i, k);
    }
    printf("%d",sum);
}