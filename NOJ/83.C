//三角形
/*
    排序
    judge当前三角形
    正确，比对并保存，右侧推进
    错误，若左侧未紧贴右侧，左侧推进，反之整体推进
    左侧与右侧有标志变量i，j，中边长为右-1
*/

#include <stdio.h>

void Select_sort(int N[],int n)
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

int judge(int a,int b,int c)
{
    if (a+b>c) return 1;
    else return 0;
}

//1为之前的三角形，2为现在的三角形
//选前一个返回1，选后一个返回0，无法选择返
int compare(int a1,int b1,int c1,int a2,int b2,int c2)
{
    if (a1+b1+c1 > a2+b2+c2) return 0;
    else if (a1+b1+c1 < a2+b2+c2) return 1;
    else if (c1 > c2) return 0;
    else if (c1 < c2) return 1;
    else if (a1 > a2) return 0;
    else if (a1 < a2) return 1;
    else return 0;
}

int main()
{
    int n;
    scanf("%d",&n);
    int N[n];
    for (int i = 0; i < n; i++)
        scanf("%d",&N[i]);

    Select_sort(N,n);

    int min = 0 , mid = 0 , max = 0 ;
    for (int i = 0 , j = 2 ; i < n-2; ){

        if ( judge(N[i],N[j-1],N[j]) ){

            //该三角形合理
            if ( compare(min,mid,max,N[i],N[j-1],N[j]) ) { 
                //返回为1，改
                min = N[i];
                mid = N[j-1];
                max = N[j];
            }

            //推进，并进入下一次循环
            j++;
            continue;
        }

        else{
            
            //该三角形不合理，i必须++，j不一定
            if (j-i==2) j++;
            i++;
            continue;
        } 
    }
    if ( min && mid && max)
        printf("%d %d %d",min,mid,max);
    else
        printf("-1");
    return 0;
}