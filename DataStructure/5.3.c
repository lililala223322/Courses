#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SizeOfArray 5

// 顺序填充数组b
void fillArray(int b[]) {
    for (int i = 0; i < SizeOfArray; i++) {
        b[i] = i;
    }
}

// 数组b乱序
void shuffleArray(int b[]) {
    srand(time(NULL)); // 初始化随机数种子
    for (int i = SizeOfArray - 1; i > 0; i--) {
        int j = rand() % (i + 1); // 生成0到i之间的随机数
        int temp = b[i];
        b[i] = b[j];
        b[j] = temp;
    }
}

// 核心算法：用数组c记录原数组a，数组a根据数组b的元素从数组c取数换位。
void transposeArray(double a[], int b[]) {
    double c[SizeOfArray];
    for (int i = 0; i < SizeOfArray; i++) {
        c[i] = a[i];
    }
    
    for (int i = 0; i < SizeOfArray; i++) {
        a[i] = c[b[i]];
    }
}

int main() {
    double a[SizeOfArray] = {1,2,3,4,5};
    int b[SizeOfArray] = {2,3,4,1,0};

    fillArray(b);
    shuffleArray(b);

    printf("数组a: ");
    for (int i = 0; i < SizeOfArray; i++) {
        printf("%.0lf ", a[i]);
    }
    printf("\n");
    printf("数组b: ");
    for (int i = 0; i < SizeOfArray; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");

    transposeArray(a, b);

    printf("执行后的数组a: ");
    for (int i = 0; i < SizeOfArray; i++) {
        printf("%.0lf ", a[i]);
    }

    return 0;
}