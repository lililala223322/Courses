#include<stdio.h>

void reflect(int p[3],int B[3],int *s)
{
    int N=B[0];
    if (p[0]==0||(p[1]+B[1]==N&&B[1]!=N)) {
        B[2]=p[1];
        p[0]=p[1]>B[2]? B[2]:p[1];
        p[1]=0;
        *s+=p[0];
    }

    else if (p[1]==0||(p[2]+B[2]==N&&B[2]!=N)){
        B[0]=p[2];
        p[1]=p[2]>B[0]? B[0]:p[2];
        p[2]=0;
        *s+=p[1];
    }

    else if (p[2]==0||(p[0]+B[0]==N&&B[0]!=N)){
        B[1]=p[0];
        p[2]=p[0]>B[1]? B[1]:p[0];
        p[0]=0;
        *s+=p[2];
    }
}

int Ray_Trace(int N,int X)
{
    int p[3]={0,X,N-X} , B[3]={N,N,N} ,s=0;
    //p(0,x,N-x)
    while(1){
    reflect( p , B , &s );
    }
}

int main()
{
    int N,X;
    //scanf("%d %d",&N,&X);
    Ray_Trace(5,2);

}