#include <stdio.h>

void mergeArrays(int arr1[], int n, int arr2[], int m, int mergedArr[]) {
    int i = 0, j = 0, k = 0;

    // 有序合并两个数组的共有长度部分
    while (i < n && j < m) {
        if (arr1[i] < arr2[j]) {
            mergedArr[k++] = arr1[i++];
        } else {
            mergedArr[k++] = arr2[j++];
        }
    }

    // 将剩余的元素复制到合并数组中
    while (i < n) {
        mergedArr[k++] = arr1[i++];
    }
    while (j < m) {
        mergedArr[k++] = arr2[j++];
    }
}

int main() {
    int n, m;

    // 读取第一个数组的长度和元素
    scanf("%d", &n);
    int arr1[20] = {0};
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr1[i]);
    }

    // 读取第二个数组的长度和元素
    scanf("%d", &m);
    int arr2[20] = {0};
    for (int i = 0; i < m; i++) {
        scanf("%d", &arr2[i]);
    }

    // 创建一个合并后的数组
    int mergedArr[40];

    // 合并两个有序数组
    mergeArrays(arr1, n, arr2, m, mergedArr);

    // 输出合并后的数组
    for (int i = 0; i < n + m - 1; i++) {
        printf("%d\n", mergedArr[i]);
    }
    printf("%d", mergedArr[n+m-1]);

    return 0;
}