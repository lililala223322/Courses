//排序，从小到大，然后算相邻量

#include <stdio.h>

void Select_sort(int N[],int n)
{
    for (int i = 0 , number = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (N[j]<N[number]) number=j;
        }
         
        if (i - number) 
        {
            int t = N[number];
            N[number] = N[i];
            N[i] = t; 
        }

        number = i+1;
    }
}

int Min (int a,int b)
{
    return a>b? b:a;
}

int main() 
{
    int n;
    scanf("%d",&n);
    int N[n];
    for (int i = 0; i < n; i++)
        scanf("%d",&N[i]);

    Select_sort(N,n);
    
    int min = N[1] - N[0];
    for (int i = 1; i < n-1 ; i++) {

        min = Min( min , N[i+1] - N[i] );

        if ( !min ) {
            printf("0");
            return 0;
        }
    }
    
    printf("%d",min);
    return 0;
}