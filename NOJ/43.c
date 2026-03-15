#include<stdio.h>
#include<math.h>

int judge(int *s,int n,int N,int M)
{
    //边框为1
    int sum=0;
    for (int i = 0; i < n; i++)
    {
        sum+=*(s+M*i)+*(s+M*i+n-1);
        sum+=*(s+i)+*(s+M*(n-1)+i);
    }
    if (sum!=4*n) return 0;

    /*
    A=2*(n+m)-4是边1数
    所以n*m-A是内核数,sum-A是内1数;
    (n*m-A)-(sum-A)是内0数;
    内0-内1=(n*m-A)-2*(sum-A)=n*m-2*sum+2*(n+m)-4 
    */
    if (n>3) {
        sum=0;
        for (int  i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                sum+=*(s+n*i+j);
            }
        }
        if (fabs(n*n-2*sum+4*n-4)>1) return 0;
    }    
    return 1;

}

int main()
{
    int n , m , sum=0;
    scanf("%d %d",&n,&m);
    int s[n][m];
    for(int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            scanf("%d",&s[i][j]);
        }   
    }

    /*
    int n=4, m=4, sum=0, s[4][4]={1,1,1,1,
                                  1,0,1,1,
                                  1,1,0,1,
                                  1,1,1,1,};
    */

    for (int i = 2; i<=n&&i<=m; i++){
         for (int N = 0; N <= n-i; N++){
            for (int M = 0; M <= m-i; M++){
                if (judge(&s[N][M],i,n,m)) sum++;
            }
        }
    }
    printf("%d",sum);  
}