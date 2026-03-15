#include <stdio.h>

#define MAXSIZE 10

// 核心思路：单次右移，记录最后一个元素，将其余元素右移一位，再将j位置的元素置为第一个元素。右移m次即调用m次该函数。
void rightMove(int a[], int n)
{
    int tail = a[n - 1];
    for (int i = n - 1; i > 0; i--)
    {
        a[i] = a[i - 1];
    }
    a[0] = tail;
}

int main()
{
    int a[MAXSIZE] = {0} , n = 0, m = 0;
    
    // 输入数据，包括数组大小、数组元素和右移长度
    printf("输入数组长度： ");
    scanf("%d", &n);
    printf("输入数组元素： ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }     
    printf("输入右移长度： ");
    scanf("%d", &m);

    // 右移m次
    for (int i = 0; i < m; i++)
    {
        rightMove(a, n);
    }
    
    // 输出结果
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

}