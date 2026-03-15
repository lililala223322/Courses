#include <stdio.h>
#include <stdlib.h>

// 定义栈结构
typedef struct {
    int low;
    int high;
} Stack;

// 初始化栈
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(capacity * sizeof(Stack));
    return stack;
}

// 检查栈是否为空
int isEmpty(Stack* stack, int top) {
    return top == -1;
}

// 交换两个整数的值
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
    核心思路：
    通过显式栈模拟递归调用的过程，具体步骤如下：
    初始化栈：将初始的数组范围（low和high）压入栈。
    循环处理栈：只要栈不为空，弹出栈顶的low和high，对当前范围进行分区操作。
    分区操作：选择一个枢轴元素，将数组分为小于枢轴和大于枢轴的两部分，返回枢轴的最终位置。
    压栈子范围：如果左子数组或右子数组有多个元素，将其范围压入栈中以便后续处理。
    终止条件：当栈为空时，排序完成。
*/

// 分区函数
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // 选择最后一个元素作为枢轴
    int i = low - 1;      // i是小于枢轴的区域的边界

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// 非递归快速排序
void quickSortIterative(int arr[], int low, int high) {
    int capacity = high - low + 1;
    Stack* stack = createStack(capacity);
    int top = -1;

    // 初始压栈
    stack[++top].low = low;
    stack[top].high = high;

    while (!isEmpty(stack, top)) {
        // 弹出栈顶元素
        int current_low = stack[top].low;
        int current_high = stack[top--].high;

        // 分区
        int pi = partition(arr, current_low, current_high);

        // 如果左子数组有多个元素，压栈
        if (pi - 1 > current_low) {
            stack[++top].low = current_low;
            stack[top].high = pi - 1;
        }

        // 如果右子数组有多个元素，压栈
        if (pi + 1 < current_high) {
            stack[++top].low = pi + 1;
            stack[top].high = current_high;
        }
    }

    free(stack);
}

// 打印数组
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 测试代码
int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("原始数组: ");
    printArray(arr, n);

    quickSortIterative(arr, 0, n - 1);

    printf("排序后数组: ");
    printArray(arr, n);

    return 0;
}