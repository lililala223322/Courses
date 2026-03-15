#include <stdio.h>

#define MAXSIZE 10

// 核心思路：用pos标定当前最小值的下标，遍历数组，如果遇到更小或相等的数则换位，即可保证pos指向最后一个最小值。
int lastMinfigure(int a[], int n)
{
    int pos = 0;
    for (int i = 1; i < n; i++)
    {
        if (a[i] <= a[pos])
        {
            // 找到更小或相等的数，换位
            pos = i;
        }
    }

    return pos;
}

int main()
{
    int a[MAXSIZE] = {0} , n = 0;
    
    // 输入数据，包括数组大小、数组元素
    printf("输入数组长度： ");
    scanf("%d", &n);
    printf("输入数组元素： ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }     
    
    printf("数组中最小元素的下标：%d\n", lastMinfigure(a, n));

    return 0;

}