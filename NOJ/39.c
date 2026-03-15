#include<stdio.h>
#include<stdarg.h>

int sum(int a,...)
{
    int count=0;
    va_list p;
    va_start(p , a);
    int i=a;
    while(i){
        count+=i;
        i=va_arg(p,int);
    }
    return count;
}

int main()
{
    int a,b,c,d,e,f;
    scanf("%d %d %d %d %d %d",&a,&b,&c,&d,&e,&f);
    printf("%d",sum(a,b,0)-sum(c,d,e,f,0));
}