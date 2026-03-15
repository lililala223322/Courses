#include <stdio.h>
void main()
{
    int i,m;
    scanf("%d",&m);
    for ( i = 2 ; i <= m-1 ; i++)
        if (m%i==0)
            break;
    if (i>=m)
        printf("%d is prime number",m);
    else
        printf("%d isn't prime number",m);
    
    
   
    
}