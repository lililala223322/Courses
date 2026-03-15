#include <stdio.h>

/*
    核心思路：
    在已排序部分中快速定位新元素的插入位置，减少比较次数；
    仅当插入位置与当前位置不同时，才移动后续元素；
    若初始数据已为正序，则每次插入位置即为当前位置，移动次数为零。
*/

void binaryInsertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int low = 0, high = i - 1;

        // 折半查找插入位置
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] < key) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        // 移动元素（仅当需要时）
        for (int j = i - 1; j >= low; j--) {
            arr[j + 1] = arr[j];
        }

        // 插入元素
        if (low != i) { // 仅当位置变化时才移动
            arr[low] = key;
        }
    }
}

// 打印数组
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {5, 3, 8, 1, 2}; // 初始数据（正序时移动次数为0）
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    binaryInsertionSort(arr, n);

    printf("Sorted array (descending): ");
    printArray(arr, n);

    return 0;
}