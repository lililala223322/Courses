#include <stdio.h>

// 核心思路：实现题目给的说法
int Max(int a[], int start, int end) {
    // 只有一个元素
    if (start == end) {
        return a[start];
    }

    // 计算中间位置
    int mid = (start + end) / 2;

    // 递归求前半部分和后半部分的最大值
    int max1 = Max(a, start, mid);
    int max2 = Max(a, mid + 1, end);

    // 返回两个最大值中的较大者
    return (max1 > max2)? max1 : max2;
}


int main() {
    int a[] = {2, 5, 1, 8, 3, 7, 4, 2 , 10 , 5 , 61 , 2 , 3, };
    int n = sizeof(a) / sizeof(a[0]);

    int maxElement = Max(a, 0, n - 1);
    printf("最大值为 %d\n", maxElement);
    return 0;
}

