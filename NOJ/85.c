/*
一维数组
N[0] = 1
N[1] = 1
N[2] = N[0] + N[1] = 2;
N[3] = N[1] + N[2] = 3;
......
每次计算，插入坏阶
一个被抠掉了部分区域的斐波那契数列
*/

#include <stdio.h>

int Compare(int M[],int m,int N)
{
    for (int i = 0; i < m; i++)
        if ( M[i] == N ) return 0;
    return 1;
}

int main()
{
    int n , m ;
    scanf("%d %d",&n,&m);
    int M[m];
    for (int i = 0; i < m; i++)
        scanf("%d",&M[i]);

    //初始化
    int N[n];
    if ( Compare(M,m,1) ) N[0] = 1;
    else N[0] = 0;
    if ( Compare(M,m,2) ) N[1] = N[0] + 1;
    else N[1] = 0;

    for (int i = 2; i < n; i++){
        if ( Compare(M,m,i+1) )
            N[i] = ( N[i-1] + N[i-2] ) % 1000000007;
        else N[i] = 0;
    }
    
    printf("%d",N[n-1]);
    return 0;
    
}
