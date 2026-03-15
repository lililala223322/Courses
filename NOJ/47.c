#include<stdio.h>
#include<stdlib.h>

void devide(int i,int n,int *p,int *P)
{
    for(int j = 0 ; j<n ; j++){
        for(int K = 0 , k=0 ; K<n+1 ; K++){

            /*
               if内表达式：左侧为子数组元素，右侧为对应的原数组元素。
               越过屏蔽列后kk=1以跳过屏蔽列。
            */

            if (K-i) *(p + n*j + k++) = *(P + (n+1)*(j+1) + K );
                                      
        }           
    }
}

int det(int *p,int n)
{
    int sum=0;

    if (n>2){

        //按列分解
        for(int i = 0; i<n ; i++){

            //创建并生成子行列式
            int N[n-1][n-1];
            devide(i,n-1,&N[0][0],p); 

            if (i%2){
                sum -= (*(p+i)) * det(&N[0][0],n-1);
            }

            else{
                sum += (*(p+i)) * det(&N[0][0],n-1);
            }  
            
            //子列所用数列在当前det结束后自动收回
        }
    }
    
    else sum += (*p) * *(p+3) - *(p+1) * *(p+2);
    
    return sum;  
}

int main()
{
    int n;
    scanf("%d",&n);
    int A[n][n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d",&A[i][j]);
        }
        
    }

    printf("%d",det(&A[0][0],n));

    return 0;
}
