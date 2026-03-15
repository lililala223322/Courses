#include<stdio.h>

int str_endswith(char str[],char suffix[],int n1,int n2)
{
    if (n1<n2) return 0;
    
    for (int i = 0; i <= n2 ; i++)
    {
        if ( str[n1-i] != suffix[n2-i] ) return 0;
    }
    
    return 1;
}

int main()
{
    char str[100]={0} , suffix[100]={0} ;
    int n1 , n2 ;

    for (int i = 0; 1 ; i++)
    {
        str[i] = getchar();
        if (str[i]==10) {str[i]=0 ; n1 = i-1 ; break;}
    }

    for (int i = 0; 1 ; i++)
    {
        suffix[i] = getchar();
        if (suffix[i]==10) {suffix[i]=0 ; n2 = i-1 ; break;}
    }

    if ( str_endswith(str,suffix,n1,n2) ) printf("Yes");
    else printf("No");

    return 0;
    
}