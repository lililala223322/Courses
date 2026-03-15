#include<stdio.h>

/*
int Prime_number(int n)
{
    int i=2;
    for (; n%i; i++) ;
    return i==n? 1:0;
}
*/

//照抄题意
void Sum_Prime_number(int n)
{
   char vis[n];
   int sum=0;

   for (int i = 0; i < n; i++){
    vis[i]=0;
   }
   
   for (int i = 2; i < n; i++){

        if (vis[i]) {sum++;continue;}
        for (int j = i*2 ; j < n; j+=i){
            vis[j]=1;
        }

   }

    for (int i = 1; i < n; i++)
        if ( !vis[i] ) printf("%d ",i);
    

   return;
   
}

int main()
{
 int n;
 scanf("%d",&n);
 Sum_Prime_number(n);
}