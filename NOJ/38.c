#include<stdio.h>

int digit(int N)
{
    int i=0;
    while(N){
        N/=10;
        i++;
    }
    return i;
}

int keith(int N)
{
    int d=digit(N) , n[d] , sum=0;
    for(int i=d-1,m=N ; m ; i--){
        n[i]=m%10;
        sum += n[i];
        m/=10;
    }
    
    int i=0;
    while(sum<N){
        int t=sum;
        sum+=sum-n[i];
        n[i]=t;
        if (++i==d) i=0;
    }

    if (sum==N) return 1;
    else return 0;
}


int main()
{
    int N;
    scanf("%d",&N);
    if (keith(N)) printf("Yes");
    else printf("No");
}