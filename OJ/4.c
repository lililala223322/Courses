#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m, t;
    scanf("%d %d %d",&n,&m,&t);

    int count = 0;
    if (m > t)
    {
        for (int i = 0; i*m <= n; i++)
        {
            count += (n - i*m)/t + 1; 
        }
    }
    else 
    {
        for (int i = 0; i*t <= n; i++)
        {
            count += (n - i*t)/m + 1; 
        }
    }

    printf("%d",count);
    
}