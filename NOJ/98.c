#include<stdio.h>
#include<math.h>

int main()
{
    double v , t ;
    scanf("%lf %lf",&v,&t);
    double c = 331.3 * sqrt(1 + t/273.15);
    double M = v/c/3.6;
    if (M < 0.8)
        printf("%.3lf subsonic",M);
    else if (M < 1.2)
        printf("%.3lf transonic",M);
    else if (M < 5.0)
        printf("%.3lf supersonic",M);
    else 
        printf("%.3lf hypersonic",M);
}