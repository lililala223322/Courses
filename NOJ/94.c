#include <stdio.h>

int main()
{
    int n;
    scanf("%d",&n);

    double pi = 3;

    for (int i = 1; i < n; i++)
    {
        double a = 1.0/(2*i),
        b = 1.0/(2*i+1),
        c = 1.0/(2*i+2),
        dpi = 4.0*a*b*c;

        if (i%2)
            pi += dpi;
        else
            pi -= dpi;
    }
    
    printf("%.7lf",pi);
}