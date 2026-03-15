#include<stdio.h>

int judge(int A,int B,int C,int D,int E)
{
    if (C<=E && A+B<=D) return 1;
    if (B<=E && C+A<=D) return 1;
    if (A<=E && B+C<=D) return 1;
    return 0;
}

int main()
{
    int T;
    scanf("%d",&T);
    int N[T][5];

    for (int i = 0; i < T; i++){
        scanf("%d %d %d %d %d",&N[i][0],&N[i][1],&N[i][2],&N[i][3],&N[i][4]);
    }
    
    for (int i = 0; i < T ; i++){
        if (judge(N[i][0],N[i][1],N[i][2],N[i][3],N[i][4]))
            printf("YES\n");
        else
            printf("NO\n");
    }
}