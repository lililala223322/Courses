#include <stdio.h>

/*
折半查找算法的核心思路是：在有序数组中，通过初始化查找范围的下界和上界，
在每次迭代中计算中间位置并增加比较计数，将中间元素与目标值比较，若相等则返回位置和比较次数，
若目标值小于中间元素则缩小查找范围到左半部分，否则缩小到右半部分，如此循环直至找到目标或确定目标不存在，
*/

int binarySearchWithCount(int R[], int n, int k, int *compareCount) {
    int low = 0, high = n - 1;
    *compareCount = 0;
    
    while (low <= high) {
        int mid = (low + high) / 2;
        (*compareCount)++; // 每次比较前计数
        
        if (R[mid] == k) {
            return mid; // 找到元素，返回位置
        } else if (k < R[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    return -1; // 未找到
}

int main() {
    int R[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int n = sizeof(R) / sizeof(R[0]);
    int k, compareCount;
    
    printf("请输入要查找的关键字k: ");
    scanf("%d", &k);
    
    int index = binarySearchWithCount(R, n, k, &compareCount);
    
    if (index != -1) {
        printf("成功找到关键字 %d，位于数组位置 %d\n", k, index);
        printf("查找过程中共进行了 %d 次关键字比较\n", compareCount);
    } else {
        printf("未找到关键字 %d\n", k);
    }
    
    return 0;
}