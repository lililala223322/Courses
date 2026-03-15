//子数组最大和

#include <stdio.h>

int Max(int a,int b)
{
    return a>b? a:b;
}

int main()
{
    //输入数据
    int n;
    scanf("%d",&n);
    int N[n];
    for (int i = 0; i < n; i++)
        scanf("%d",&N[i]);

    //两层for循环，第一层for循环用于推进个数，第二层用于推进序列
    int m = N[0];
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; i+j <= n; j++)
        {
            if (i==1) m = Max(m,N[j]);

            else{
                int sum=0;
                for (int p = 0; p < i; p++)
                    sum += N[j+p];
                m = Max(m,sum);
            }
        }
    }
    
    printf("%d",m);
}