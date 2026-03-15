#include <stdio.h>
#include <stdbool.h>

// 核心思路：非方阵false，方阵则就地转置，将每个元素与其对称元素对换位置
bool transposeInPlace(int m, int n, int a[m][n]) {
    // 如果不是方阵，返回 false
    if (m != n) {
        return false;
    }

    //就地转置
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < n; j++) {
            int temp = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = temp;
        }
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

    bool result = transposeInPlace(m, n, a);

    if (result) {
        printf("转置后的数组:\n");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("数组不是方阵，无法就地转置。\n");
    }

    return 0;
}