#include <stdio.h>  
#include <stdlib.h>
#include <string.h>  
#include <time.h>  
#include <math.h>  

typedef struct
{
    char s[10];
    int X;
    int Y;
}plane;

double distance(int X,int Y)
{
    return sqrt(X*X+Y*Y);
}

int main()
{
    int n;
    scanf("%d",&n);

    plane p[n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 10; j++)
            p[i].s[j] = 0;
        
        scanf("%s %d %d",p[i].s,&p[i].X,&p[i].Y);
    }

    int p1 = 0 , p2 = 0 ;
    double min_distance = INFINITY;
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            int dx = abs(p[i].X - p[j].X);
            int dy = abs(p[i].Y - p[j].Y);
            double dis = distance(dx,dy);
            if ( dis < min_distance )
            {
                p1 = i;
                p2 = j;
                min_distance = dis;
            }
        }
        
    }
    
    printf("%s-%s %.4lf",p[p1].s,p[p2].s,min_distance);

}