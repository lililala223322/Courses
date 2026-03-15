#include <stdio.h>

void insert(int L[], int *n, int x) {
    int i;
    
    // 找到插入位置
    for (i = *n - 1; (i >= 0 && L[i] > x); i--) {
        L[i + 1] = L[i]; // 元素后移
    }
    
    // 插入元素x
    L[i + 1] = x;
    
    // 增加数组长度
    (*n)++;
}

int main()
{
    int L[100] = {1,3,5,7};
    int n = 4; // 当前数组长度
    int x = 6; // 要插入的元素

    insert(L, &n, x);

    // 输出插入后的数组
    for (int i = 0; i < n; i++) {
        printf("%d ", L[i]);
    }
    
    return 0;
}