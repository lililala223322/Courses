#include <stdio.h>

/*
    核心思路：
    该算法通过不断缩小有序表的搜索范围来高效定位目标关键字。每次迭代时：
    计算中间位置mid，并比较arr[mid]与目标值k；
    若相等则直接返回；
    若arr[mid] < k，说明目标在右半部分，调整low=mid+1；
    若arr[mid] > k，说明目标在左半部分，调整high=mid-1。
*/
void binarySearchWithTrace(int arr[], int n, int k) {
    int low = 0, high = n - 1;
    printf("查找序列: ");
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        // 输出当前比较的关键字
        printf("%d ", arr[mid]);
        
        if (arr[mid] == k) {
            printf("\n成功找到关键字 %d\n", k);
            return;
        } else if (arr[mid] < k) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    printf("\n未找到关键字 %d\n", k);
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 7; // 示例查找关键字
    
    binarySearchWithTrace(arr, n, k);
    
    return 0;
}