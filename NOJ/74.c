#include<stdio.h>

/*
    读取和计算都在while内进行，读一次算一次
    取一个中间变量c，先看c是否为0/-1，-1则退，双非则存入number并进入下一次while
    c=0：计算中位数，插入number，再将number插入result，
    number和result各自需要一个标志变量
    
*/

//从隔壁抠下来的排序
void Select_sort(double N[],int n)
{
    for (int i = 0 , number = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (N[j]<N[number]) number=j;
        }
         
        if (i - number) 
        {
            int t = N[number];
            N[number] = N[i];
            N[i] = t; 
        }

        number = i+1;
    }
    
}

int main()
{
    double number[1000]={0} , result[200][1000]={0};
    int c , i = 0 , j = 0 ;
    
    while (1)
    {
        scanf("%d",&c);

        if ( c==-1 ){
            for(int p=0 ; p<=j ; p++)
            {
                for(int q=1 ; q <= result[p][0] ; q++)
                {
                    if ( q != result[p][0] ) printf("%.0lf ",result[p][q]);
                    else printf("%lf\n",result[p][q]);
                }
            }
            return 0;
        }
        
        if ( c!=0 ) 
        {
            number[i++] = c;
            continue;
        }
        
        else 
        {
            double N[1000] , middle;
            result[j][0] = i+1; //result的第j行有i+1个数（含middle）
            
            for (int n=0 ; n <= i ; n++) 
            {
                N[n] = number[n];
                result[j][n+1] = number[n];
            }    

            //给N[100]排序,计算中位数middle赋给result[j][i+2]
            Select_sort(N,i);
            if ( i%2 ) 
                middle = N[i/2];
            else 
                middle = ( N[(i-1)/2] + N[(i+1)/2] ) / 2;

            result[j][i+1] = middle;
            
            j++;
        }
    }
}