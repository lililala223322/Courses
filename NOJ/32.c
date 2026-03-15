#include<stdio.h>

int digit(int n)
{
 int i=0;
 for ( ; n ; i++ ) {n/=10;}
 return i;
}

int sum(int n)
{
 int N=digit(n) , sum=0;
 for ( ; N ; N-- )
 {
  sum += n % 10;
  n/=10;
 }
 return sum;
}

int main()
{
 int n , N=0;
 scanf("%d",&n);
 
 if (!(n-1)) N=1;
 while (n%sum(n)==0 && n!=1)
 {
  N++;
  n/=sum(n);
 }
 
 printf("%d",N);
}