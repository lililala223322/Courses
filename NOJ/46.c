#include<stdio.h>

//照抄题意
int main()
{
    int num , n , m;
    scanf("%d %d",&n,&m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0 , k ; j < m; j++)
        {
            scanf("%d",&k);
            if (!k) num++;
        }
        
    }

    double ratio = num/n/m;

    if(ratio<=0.05 && (n*m-num==n || n*m-num==m))
         printf("Yes");

    else printf("No");
    
}