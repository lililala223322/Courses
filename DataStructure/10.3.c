#include <stdio.h>

/*
    核心思路：
    本算法仅对R[low..high]的子数组进行排序，通过调整外层循环的起始和结束条件，
    限制排序范围，减少不必要的比较和交换操作。
*/

// 冒泡排序（对R[low..high]部分排序）
void bubbleSortPartial(int R[], int low, int high) {
    for (int i = low; i <= high; i++) {         // 外层循环控制轮次
        for (int j = low; j < high - (i - low); j++) { // 内层循环比较相邻元素
            if (R[j] > R[j + 1]) {              // 如果前一个元素大于后一个元素
                // 交换两个元素
                int temp = R[j];
                R[j] = R[j + 1];
                R[j + 1] = temp;
            }
        }
    }
}

// 打印数组
void printArray(int R[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", R[i]);
    }
    printf("\n");
}

int main() {
    int R[] = {9, 3, 7, 1, 5, 2, 8, 4, 6};
    int n = sizeof(R) / sizeof(R[0]);
    int low = 2, high = 6; // 对R[2..6]部分排序
    
    printf("排序前: ");
    printArray(R, n);
    
    bubbleSortPartial(R, low, high);
    
    printf("排序后: ");
    printArray(R, n);
    
    return 0;
}