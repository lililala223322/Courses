#include <math.h>
#include <stdio.h>

int Day_Count(int year,int month,int day)
{
    int count = 0;
    switch ( month )
    {
        case 12:count+=30;
        case 11:count+=31;
        case 10:count+=30;
        case 9:count+=31;
        case 8:count+=31;
        case 7:count+=30;
        case 6:count+=31;
        case 5:count+=30;
        case 4:count+=31;
        case 3:count+=28;
        case 2:count+=31;
        case 1:break;
    }

    count += day;

    if ( (month > 2) && ( (year % 400 == 0) || (year % 4 == 0 && year % 100 !=0) ) )
        count++;

    return count;
}

int main()
{
    int year , month , day ;
    double lon , lat , t;
    scanf("%d %d %d",&year,&month,&day);
    scanf("%lf %lf",&lon,&lat);
    scanf("%lf",t);

    


}