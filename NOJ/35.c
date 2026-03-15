#include<stdio.h>
#include<stdarg.h>

double avg(int a,...)
{
    double count=0;
    va_list p;
    va_start(p , a);
    int j=0;
    double i=va_arg(p,double);
    while(a-j){
        count+=i;
        i=va_arg(p,double);
        j++;
    }
    return count/a;
}

int main()
{
    double a,b,c,d,e;
    scanf("%lf %lf %lf %lf %lf",&a,&b,&c,&d,&e);
    printf("%.4lf",avg(2,a,b)-avg(3,c,d,e));
}