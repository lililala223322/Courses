//汤包

#include <stdio.h>

int main()
{
    int n;
    scanf("%d",&n);

    //N[i]={编号，时长}
    int N[n][2];
    for (int i = 0; i < n; i++){
        int a , b;
        scanf("%d %d",&a,&b);
        N[i][1] = a+b;
        N[i][0] = i+1;
    }

    //排序
    for (int i=0;i<n;i++) {
        for (int j=0;j<n-i-1;j++) { 
            if ( N[j][1] > N[j+1][1] ) {
                int a=N[j][1];
                N[j][1] = N[j+1][1];
                N[j+1][1] = a;

                int b=N[j][0];
                N[j][0] = N[j+1][0];
                N[j+1][0] = b;
            }
        }
        
    }

    for (int i = 0; i < n; i++)
        printf("%d ",N[i][0]);
    
}