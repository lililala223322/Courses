#include<stdio.h>

void Cycle_sort(int N[],int n)
{
    for (int j = 0 , item , pos ; j < n; j++){
    
        item = N[j];
        pos = j;

        //步骤3
        for (int i = j+1 ; i < n; i++)
        {
            if ( N[i]<item ) pos++;
        }

        //对于重复数据的处理
        for ( ;item == N[pos] && pos!=j; pos++) ;

        //步骤4
        if ( pos!=j ) 
        {
            int t = N[j];
            N[j--] = N[pos];
            N[pos] = t;
        }

    }
}

int main()
{
    int n;
    scanf("%d",&n);
    int N[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&N[i]);
    }
    
    Cycle_sort(N,n);

    for (int i = 0; i < n; i++)
    { 
        printf("%d",N[i]);
        if ( i+1 < n ) printf(" "); 
    }
    
}