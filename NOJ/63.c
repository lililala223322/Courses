#include<stdio.h>
#include<time.h>

int main()
{
    int A[3] , B[3] ;

    for (int i = 0; i < 3; i++)
    {
        scanf("%d",&A[i]);
    }

    for (int i = 0; i < 3; i++)
    {
        scanf("%d",&B[i]);
    }

    struct tm Date1 = {0,0,0,A[2],A[1]-1,A[0]-1900,}, 
              Date2 = {0,0,0,B[2],B[1]-1,B[0]-1900,};

    double diff_t = mktime(&Date1) - mktime(&Date2);
    
    printf("%lf",diff_t);
}