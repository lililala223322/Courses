#include<stdio.h>

int main()
{
    char c[1000] ={0};
    int n;

    for (int i = 0; 1 ; i++)
    {
        c[i]=getchar();
        if (c[i]==13 || c[i]==10) break;
        n=i;
    }
    
    for (int i = 0; i <= n; i++)
    {
        if (c[i]>64 && c[i]<91) c[i]+=32;
        else if (c[i]>96 && c[i]<123) c[i]-=32;
        printf("%c",c[i]);
    }

    return 0;

}