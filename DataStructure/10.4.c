#include <stdio.h>

/*
    核心思路：
    交替改变扫描方向，先从左到右，再从右到左，
    在每一轮中同时将最大元素移到右侧、最小元素移到左侧，
    减少了传统冒泡排序在接近有序时的无效遍历。
*/

void Sort(int arr[], int n) {
    int left = 0, right = n - 1;
    int swapped;
    
    while (left < right) {
        // 从左到右扫描，将最大元素移到右侧
        swapped = 0;
        for (int i = left; i < right; i++) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
        }
        right--; // 右边界左移
        
        // 从右到左扫描，将最小元素移到左侧
        swapped = 0;
        for (int i = right; i > left; i--) {
            if (arr[i] < arr[i - 1]) {
                int temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                swapped = 1;
            }
        }
        left++; // 左边界右移
        
        // 若未发生交换，提前终止
        if (!swapped) break;
    }
}

int main() {
    int arr[] = {5, 1, 4, 2, 8, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    Sort(arr, n);
    
    printf("排序后数组: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n"); // 输出：0 1 2 4 5 8
    return 0;
}