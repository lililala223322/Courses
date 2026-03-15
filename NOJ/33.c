#include<stdio.h>

int gcd(int i,int j)
{
    int k=i%j;
    while (k) {
        i=j;
        j=k;
        k=i%j;
    } 
    if (!(j-1)) return 1;
    return 0;
}

int main()
{
    int N, n=0 ;
    scanf("%d",&N);

    for (int i=1; i<N; i++) {

        for (int j=1; j<N; j++) {

            if ( gcd(i,j) ) n++;
        }
        //if (i%1000==0) printf("%d processing\n",i);
    }
    n += N-1? 2:0;
    printf("%d",n);
}