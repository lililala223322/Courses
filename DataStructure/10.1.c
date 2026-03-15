#include <stdio.h>

/*
    核心思路：
    将无序区的尾元素与有序区的元素逐个比较，找到合适的插入位置：
    从数组的倒数第二个元素开始，将其作为无序区的尾元素，与有序区从头开始的元素进行比较，
    若有序区的元素小于当前无序区尾元素，则将该元素前移，
    直到找到第一个大于或等于当前无序区尾元素的位置，将原无序区尾元素插入到该位置的前一个位置。
*/

void insertionSort(int R[], int n) {
    int i, j, temp;
    
    for (i = n - 2; i >= 0; i--) { // 从倒数第二个元素开始，向前遍历无序区
        temp = R[i]; // 保存当前无序区的尾元素
        
        // 在有序区中查找插入位置
        for (j = i + 1; j < n && R[j] < temp; j++) {
            R[j - 1] = R[j]; // 元素前移
        }
        
        R[j - 1] = temp; // 插入到正确位置
    }
}

int main() {
    int R[] = {5, 3, 8, 6, 2, 7, 1, 4};
    int n = sizeof(R) / sizeof(R[0]);
    
    printf("排序前数组: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", R[i]);
    }
    printf("\n");
    
    insertionSort(R, n);
    
    printf("排序后数组: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", R[i]);
    }
    printf("\n");
    
    return 0;
}