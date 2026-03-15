#include<stdio.h>

void recode(char s[],int x)
{
    int n[26]={0};
    for (int i = 0; s[i] ; i++) n[ s[i]-97 ]++;

    for (int i = 0; s[i] ; i++)
    {
        s[i] += n[ s[i]-97 ]%2? -x:x ;

        while ( s[i]<97||s[i]>122 )
        {
            if ( s[i]<97 ) s[i]+=26;
            else s[i]-=26;
        }
    }
    
    return;
}

int main()
{
    char s[1000]={0};
    for (int i = 0; 1 ; i++)
    {
        s[i]=getchar();
        if (s[i]==13 || s[i]==10) {
            s[i]=0;
            break;
        }    
    }

    int x;
    scanf("%d",&x);

    recode(s,x);

    for (int i = 0; s[i] ; i++) printf("%c",s[i]);
}