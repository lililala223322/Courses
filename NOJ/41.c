#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

double Int_1(double a,double b,int N)
{
    double y=0;
    for (int i=1;i<=N;i++){
        double x=a+(rand()/(double)RAND_MAX*(b-a));
        y+=pow(x,4)/exp(x)/N;
    }
    return y*(b-a);
}

double Int_2(double a,double b,int N)
{
    double y=0;
    for (int i=1;i<=N;i++){
        double x=a+(rand()/(double)RAND_MAX*(b-a));
        y+=(pow(x,2)+1)/N;
    }
    return y*(b-a);
}

double Int_3(double a,double b,int N)
{
    double y=0;
    for (int i=1;i<=N;i++){
        double x=a+(rand()/(double)RAND_MAX*(b-a));
        y+=cos(x)/N;
    }
    return y*(b-a);
}

double Int_4(double a,double b,int N)
{
    double y=0;
    for (int i=1;i<=N;i++){
        double x=a+(rand()/(double)RAND_MAX*(b-a));
        y+=(x-2)*sqrt(x)/N;
    }
    return y*(b-a);
}

double Int_5(double a,double b,int N)
{
    double y=0;
    for (int i=1;i<=N;i++){
        double x=a+(rand()/(double)RAND_MAX*(b-a));
        y+=(2*sin(x)-5*cos(x))/N;
    }
    return y*(b-a);
}

int main()
{
    int m,N;
    double a,b;
    scanf("%d %lf %lf %d",&m,&a,&b,&N);
    srand(RAND_MAX);
    
    double out;
    switch (m){
        case 1:out=Int_1(a,b,N);break;
        case 2:out=Int_2(a,b,N);break;
        case 3:out=Int_3(a,b,N);break;
        case 4:out=Int_4(a,b,N);break;
        case 5:out=Int_5(a,b,N);break;
    }
    printf("%lf",out);

    /*
    13.317870 1224822
    13.317870 1628500
    13.317870 1711649
    */
}