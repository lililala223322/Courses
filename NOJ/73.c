#include<stdio.h>

int main()
{
    double Ti,Tf,m1,c1,m2,c2;
    scanf("%lf %lf",&Ti,&Tf);
    scanf("%lf %lf",&m1,&c1);
    scanf("%lf %lf",&m2,&c2);

    double heat = ( (Tf-Ti) * (m1*c1 + m2*c2) )/1000,
            p1 = m1*c1 / (m1*c1 + m2*c2),
            p2 = m2*c2 / (m1*c1 + m2*c2);
            
    printf("%.2lfkJ,%.2lf%%,%.2lf%%",heat,p2,p1);
}