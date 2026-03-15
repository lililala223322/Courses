#include <stdio.h>  
#include <stdlib.h>
#include <string.h>  
#include <time.h>  
#include <math.h>

int bollen(double Index[],int number,int length)
{
    for (int j = 0; j < length; j++)
            if (number == Index[j]) return 1;

    return 0;
}

int main()
{
    double Index[1000];

    for (int i = 0; i < 1000; i++)
        Index[i] = INFINITY;

    int n;
    scanf("%d",&n);

    int length = 0 , sum = 0;
    for (int i = 0; i < n; i++)
    {
        int number;
        scanf("%d",&number);

        if (bollen(Index,number,length))
            sum++;
        else
            Index[length++] = number;
    }

    printf("%d",sum);
    
    return 0;
}