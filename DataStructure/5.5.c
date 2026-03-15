#include <stdio.h>
#include <stdbool.h>

bool diagonalSums(int m, int n, int a[m][n], int *sum1, int *sum2) {
    // 如果不是方阵，返回 false
    if (m != n) {
        return false;
    }

    *sum1 = 0; // 左上角到右下角对角线的和
    *sum2 = 0; // 右上角到左下角对角线的和

    for (int i = 0; i < n; i++) {
        *sum1 += a[i][i];            // 主对角线
        *sum2 += a[i][n - 1 - i];    // 次对角线，从第一排的右侧开始往左下走
    }

    return true;
}

int main() {
    int m = 3, n = 3;
    int a[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int sum1, sum2;
    bool result = diagonalSums(m, n, a, &sum1, &sum2);

    if (result) {
        printf("主对角线和: %d\n", sum1);
        printf("次对角线和: %d\n", sum2);
    } else {
        printf("数组不是方阵，无法计算对角线之和。\n");
    }

    return 0;
}