#include<stdio.h>

//直线回归方程
void linear_regression_equation(int *p,int n)
{
    double XiYi=0 , Xi_2=0 , Ave_X=0 ,Ave_Y;

    for ( int i = 0; i < n; i++)
    {
        XiYi += (*(p+2*i)) * (*(p+2*i+1));
        Xi_2 += (*(p+2*i)) * (*(p+2*i));
        Ave_X += *(p+2*i);
        Ave_Y += *(p+2*i+1);
    }
    Ave_X/=n;
    Ave_Y/=n;

    double b = (XiYi-n*Ave_X*Ave_Y) / (Xi_2-n*Ave_X*Ave_X),
           a = Ave_Y-b*Ave_X;
    printf("Y=%.4lf+%.4lf*X",a,b);
}

int main()
{
    int n;
    scanf("%d",&n);
    int Statistics[n][2];

    for (int i = 0; i < n; i++){
        scanf("%d %d",&Statistics[i][0],&Statistics[i][1]);
        if (Statistics[i][0]<=0 || Statistics[i][1]<=0) return -1;
    }

    linear_regression_equation(&Statistics[0][0],n);

    return 0;
}