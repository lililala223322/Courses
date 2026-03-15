#include<stdio.h>

void str_split(char str[],char sep[],int n1,int n2)
{
    int judge=0 , point=0;

    for (int i = 0; i < n1; i++)
    {
        //judge=n2即找到了对应数列
        if (str[i]==sep[judge]) judge++;
        else judge = 0;

        if ( judge == n2 || i == n1-1 )
        {
            //输出
            if (i==n1-1) i++;
            for(int j = point; j<i-n2+1 ; j++) printf("%c",str[j]);
            printf("\n");

            //重置
            point = i+1;
            judge = 0;
        }
    }    
}

int main()
{
    char str[100]={0} , sep[100]={0} ;
    int n1 , n2 ;

    for (int i = 0; 1 ; i++)
    {
        str[i] = getchar();
        if (str[i]==13 || str[i]==10) {str[i]=0 ; n1 = i ; break;}
    }

    for (int i = 0; 1 ; i++)
    {
        sep[i] = getchar();
        if (sep[i]==13 || sep[i]==10) {sep[i]=0 ; n2 = i ; break;}
    }

    str_split(str,sep,n1,n2);

    return 0;
    
}