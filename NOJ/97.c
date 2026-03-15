#include<stdio.h>

int main()
{
    char s1[7]={0}, s2[7]={0};
    scanf("%s",s1);
    scanf("%s",s2);

    int sum = 0;

    for (int i = 0; i < 2; i++)
    {
        if (s1[i] < s2[i]) 
            sum += s1[i]-s2[i];
        else if (s1[i] > s2[i])
            sum += 26 - (s1[i]-s2[i]);
    }

    for (int i = 2; i < 6; i++)
    {
        if (s1[i] < s2[i]) 
            sum += s2[i]-s1[i];
        else if (s1[i] > s2[i])
            sum += 10 - (s2[i]-s1[i]);
    }
    
    printf("%d",sum);
}
