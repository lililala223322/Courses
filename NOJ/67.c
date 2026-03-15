/* Arduino
A[0] 0 1 2 3 4 5 6 7 8 9   + =
A[1] 6 2 5 5 4 5 6 3 7 6   2 2
数字组成 = n-4

思路：
用数字凑功耗
i j直接表示数字: j>=i 且 i+j <=9

双重循环，先涨j再涨i

最内层循环:
    
*/

#include<stdio.h>

int main(){
    int A[] = {6,2,5,5,4,5,6,3,7,6} , n , num = 0 ;
    scanf("%d",&n);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; i+j < 10; i++)
        {
            if ( A[i] + A[j] + A[i+j] == n-4 )
                if ( i!=j ) num+=2;
                else num++;
        }
    }
    
    printf("%d",num);
}