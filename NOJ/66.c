#include <stdio.h>
#define N 100

//长安

/*
    先算所有可能，除去含P的坐标。
*/                                                                                                                                                                             

//ps：题目有问题，原点坐标是（1,1）不是(0,0)

//阶乘
int Factorial(int A)
{   
    int m = 1;                                      

    for (int i = 1 ; i <= A; i++) m*=i;

    return m;
    
}

int Path(int A[4])
{
    //A[0,1,2,3] = Xb,Yb,Xp,Yp
    if ( (A[0]==A[2]) && (A[1]==A[3]) ) return 0;

    else if ( (A[0]<A[2]) || (A[1]<A[3]) ) 
        return ( Factorial(A[0]+A[1]-2) / ( Factorial(A[0]-1) * Factorial(A[1]-1) ) );

    else {
        int Total = Factorial(A[0]+A[1]-2) / ( Factorial(A[0]-1) * Factorial(A[1]-1) );
        int Repeat1 =  Factorial(A[2]+A[3]-2) / ( Factorial(A[2]-1) * Factorial(A[3]-1) );
        int Repeat2 =  Factorial(A[0]+A[1]-A[2]-A[3]) / ( Factorial(A[0]-A[2]) * Factorial(A[1]-A[3]) );
        return Total-Repeat1*Repeat2;
    } 
}

int main()
{
    int Pos[N][4] = {0} , n ;

    for ( int i = 0 ; 1 ; i++){
        scanf("%d %d %d %d",&Pos[i][0],&Pos[i][1],&Pos[i][2],&Pos[i][3]);

        //全是0就退出
        if (!Pos[i][0] || !Pos[i][1] || !Pos[i][2] || !Pos[i][3]) {
            n=i;
            break;
        }
    }

    for (int i = 0; i < n; i++)
        printf("%d\n",Path(Pos[i]));
    
}